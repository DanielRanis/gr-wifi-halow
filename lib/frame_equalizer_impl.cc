/*
 * Copyright (C) 2016 Bastian Bloessl <bloessl@ccs-labs.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "frame_equalizer_impl.h"
#include "equalizer/base.h"
#include "equalizer/comb.h"
#include "equalizer/lms.h"
#include "equalizer/ls.h"
#include "equalizer/sta.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace ieee802_11 {

frame_equalizer::sptr
frame_equalizer::make(Equalizer algo, double freq, double bw, bool log, bool debug,
											S1g_ppdu_format s1g_format, S1g_encoding s1g_encoding,
											S1g_cw s1g_cw, bool s1g_cap) {
	return gnuradio::get_initial_sptr
		(new frame_equalizer_impl(algo, freq, bw, log, debug, s1g_format,
															s1g_encoding, s1g_cw, s1g_cap));
}


frame_equalizer_impl::frame_equalizer_impl(Equalizer algo, double freq, double bw, bool log, bool debug,
																				S1g_ppdu_format s1g_format, S1g_encoding s1g_encoding,
																				S1g_cw s1g_cw, bool s1g_cap) :
	gr::block("frame_equalizer",
			gr::io_signature::make(1, 1, 64 * sizeof(gr_complex)),
			gr::io_signature::make(1, 1, 48)),
	d_current_symbol(0), d_log(log), d_debug(debug), d_equalizer(NULL),
	d_freq(freq), d_bw(bw), d_frame_bytes(0), d_frame_symbols(0),
	d_freq_offset_from_synclong(0.0), d_s1g_format(s1g_format),
	d_s1g_encoding(s1g_encoding), d_s1g_cw(s1g_cw), d_s1g_cap(s1g_cap) {

	message_port_register_out(pmt::mp("symbols"));

	d_bpsk = constellation_bpsk::make();
	d_qbpsk = constellation_qbpsk::make();
	d_qpsk = constellation_qpsk::make();
	d_16qam = constellation_16qam::make();
	d_64qam = constellation_64qam::make();

	d_frame_mod = d_bpsk;

	set_tag_propagation_policy(block::TPP_DONT);
	set_algorithm(algo);
}

frame_equalizer_impl::~frame_equalizer_impl() {
}


void
frame_equalizer_impl::set_algorithm(Equalizer algo) {
	gr::thread::scoped_lock lock(d_mutex);
	delete d_equalizer;

	switch(algo) {

	case COMB:
		dout << "Comb" << std::endl;
		d_equalizer = new equalizer::comb();
		break;
	case LS:
		dout << "LS" << std::endl;
		d_equalizer = new equalizer::ls();
		break;
	case LMS:
		dout << "LMS" << std::endl;
		d_equalizer = new equalizer::lms();
		break;
	case STA:
		dout << "STA" << std::endl;
		d_equalizer = new equalizer::sta();
		break;
	default:
		throw std::runtime_error("Algorithm not implemented");
	}
}

void
frame_equalizer_impl::set_bandwidth(double bw) {
	gr::thread::scoped_lock lock(d_mutex);
	d_bw = bw;
}

void
frame_equalizer_impl::set_frequency(double freq) {
	gr::thread::scoped_lock lock(d_mutex);
	d_freq = freq;
}

void
frame_equalizer_impl::enable_s1g(bool s1g_cap){
	gr::thread::scoped_lock lock(d_mutex);
	std::cout << "frame_equalizer: enable_s1g: " << s1g_cap << std::endl;
	d_s1g_cap = s1g_cap;

}

void
frame_equalizer_impl::set_s1g_encoding(S1g_encoding mcs){
	gr::thread::scoped_lock lock(d_mutex);
	std::cout << "frame_equalizer: set_s1g_encoding: " << mcs << std::endl;
	d_s1g_encoding = mcs;
}

void
frame_equalizer_impl::set_frame_format(S1g_ppdu_format s1g_format){
	gr::thread::scoped_lock lock(d_mutex);
	std::cout << "frame_equalizer: set_frame_format: " << s1g_format << std::endl;
	d_s1g_format = s1g_format;
}

void
frame_equalizer_impl::set_s1g_cw(S1g_cw cw){
	gr::thread::scoped_lock lock(d_mutex);
	std::cout << "frame_equalizer: set_s1g_cw: " << cw << std::endl;
	d_s1g_cw = cw;
}

void
frame_equalizer_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required) {
	ninput_items_required[0] = noutput_items;
}

int
frame_equalizer_impl::general_work (int noutput_items,
		gr_vector_int &ninput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items) {

	gr::thread::scoped_lock lock(d_mutex);

	const gr_complex *in = (const gr_complex *) input_items[0];
	uint8_t *out = (uint8_t *) output_items[0];

	int i = 0;
	int o = 0;
	int offs = 0;
	gr_complex symbols[48];
	gr_complex current_symbol[64];

	dout << "FRAME EQUALIZER: input " << ninput_items[0] << "  output " << noutput_items << std::endl;

	while((i < ninput_items[0]) && (o < noutput_items)) {

		get_tags_in_window(tags, 0, i, i + 1, pmt::string_to_symbol("wifi_start"));

		// new frame
		if(tags.size()) {
			std::cout << "frame_equalizer_impl: new frame" << std::endl;
			d_current_symbol = 0;
			d_frame_symbols = 0;
			d_frame_mod = d_bpsk;

			d_freq_offset_from_synclong = pmt::to_double(tags.front().value) * d_bw / (2 * M_PI);
			d_epsilon0 = pmt::to_double(tags.front().value) * d_bw / (2 * M_PI * d_freq);
			d_er = 0;

			dout << "epsilon: " << d_epsilon0 << std::endl;
		}

		if(d_s1g_cap){
			offs = 3;
		}else{
			offs = 2;
		}
		//not interesting -> skip
		if(d_current_symbol > (d_frame_symbols + offs)) {
			i++;
			continue;
		}


		std::memcpy(current_symbol, in + i*64, 64*sizeof(gr_complex));

		// compensate sampling offset
		for(int i = 0; i < 64; i++) {
			current_symbol[i] *= exp(gr_complex(0, 2*M_PI*d_current_symbol*80*(d_epsilon0 + d_er)*(i-32)/64));
		}

		gr_complex p = equalizer::base::POLARITY[(d_current_symbol - 2) % 127];
		gr_complex sum =
			(current_symbol[11] *  p) +
			(current_symbol[25] *  p) +
			(current_symbol[39] *  p) +
			(current_symbol[53] * -p);

		double beta;
		if(d_current_symbol < 2) {
			beta = arg(
					current_symbol[11] -
					current_symbol[25] +
					current_symbol[39] +
					current_symbol[53]);

		} else {
			beta = arg(
					(current_symbol[11] *  p) +
					(current_symbol[39] *  p) +
					(current_symbol[25] *  p) +
					(current_symbol[53] * -p));
		}

		double er = arg(
				(conj(d_prev_pilots[0]) * current_symbol[11] *  p) +
				(conj(d_prev_pilots[1]) * current_symbol[25] *  p) +
				(conj(d_prev_pilots[2]) * current_symbol[39] *  p) +
				(conj(d_prev_pilots[3]) * current_symbol[53] * -p));

		er *= d_bw / (2 * M_PI * d_freq * 80);

		d_prev_pilots[0] = current_symbol[11] *  p;
		d_prev_pilots[1] = current_symbol[25] *  p;
		d_prev_pilots[2] = current_symbol[39] *  p;
		d_prev_pilots[3] = current_symbol[53] * -p;

		// compensate residual frequency offset
		for(int i = 0; i < 64; i++) {
			current_symbol[i] *= exp(gr_complex(0, -beta));
		}

		// update estimate of residual frequency offset
		if(d_current_symbol >= 2) {

			double alpha = 0.1;
			d_er = (1-alpha) * d_er + alpha * er;
		}

		// do equalization
		d_equalizer->equalize(current_symbol, d_current_symbol,
				symbols, out + o * 48, d_frame_mod);

		// signal field
		if(d_current_symbol == 2) {
			if(decode_signal_field(out + o * 48)) {

				if(!d_s1g_cap){
					pmt::pmt_t dict = pmt::make_dict();
					dict = pmt::dict_add(dict, pmt::mp("frame_bytes"), pmt::from_uint64(d_frame_bytes));
					dict = pmt::dict_add(dict, pmt::mp("encoding"), pmt::from_uint64(d_frame_encoding));
					dict = pmt::dict_add(dict, pmt::mp("snr"), pmt::from_double(d_equalizer->get_snr()));
					dict = pmt::dict_add(dict, pmt::mp("freq"), pmt::from_double(d_freq));
					dict = pmt::dict_add(dict, pmt::mp("freq_offset"), pmt::from_double(d_freq_offset_from_synclong));
					add_item_tag(0, nitems_written(0) + o,
							pmt::string_to_symbol("wifi_start"),
							dict,
							pmt::string_to_symbol(alias()));
				}
			}
		}

		// S1G enabled; second symbol of signal field
		if (d_s1g_cap){
			if(d_current_symbol == 3){
				if(decode_signal_field(out + o * 48)){

					pmt::pmt_t dict = pmt::make_dict();
					dict = pmt::dict_add(dict, pmt::mp("frame_bytes"), pmt::from_uint64(d_frame_bytes));
					dict = pmt::dict_add(dict, pmt::mp("encoding"), pmt::from_uint64(d_frame_encoding));
					dict = pmt::dict_add(dict, pmt::mp("snr"), pmt::from_double(d_equalizer->get_snr()));
					dict = pmt::dict_add(dict, pmt::mp("freq"), pmt::from_double(d_freq));
					dict = pmt::dict_add(dict, pmt::mp("freq_offset"), pmt::from_double(d_freq_offset_from_synclong));
					add_item_tag(0, nitems_written(0) + o,
							pmt::string_to_symbol("wifi_start"),
							dict,
							pmt::string_to_symbol(alias()));
				}
			}
		}

		if(d_current_symbol > offs) {
			o++;
			pmt::pmt_t pdu = pmt::make_dict();
			message_port_pub(pmt::mp("symbols"), pmt::cons(pmt::make_dict(), pmt::init_c32vector(48, symbols)));
		}

		i++;
		d_current_symbol++;
	}

	consume(0, i);
	return o;
}

bool
frame_equalizer_impl::decode_signal_field(uint8_t *rx_bits) {

	static ofdm_param ofdm = ofdm_param(BPSK_1_2);

	static frame_param frame;
  frame.set_service_field_length(d_s1g_cap);
	frame.set_frame_params(ofdm, 0);

	deinterleave(rx_bits);
	uint8_t *decoded_bits = d_decoder.decode(&ofdm, &frame, d_deinterleaved, d_s1g_cap);

	return parse_signal(decoded_bits);
}

void
frame_equalizer_impl::deinterleave(uint8_t *rx_bits) {
	for(int i = 0; i < 48; i++) {
		d_deinterleaved[i] = rx_bits[interleaver_pattern[i]];
	}
}

bool
frame_equalizer_impl::parse_signal(uint8_t *decoded_bits) {

	int r,mcs,len;
	d_frame_bytes = 0;
	bool parity = false;

	r = mcs = len = 0;

	if(d_s1g_cap && (d_current_symbol == 2)){ // decoding first sig symbol
		for (int i = 0; i < 24; i++) {
			// decoding mcs
			if((i > 18) && (i < 23) && decoded_bits[i]) {
				mcs = mcs | (1 << (i - 19));
			}

		}
	}else if(d_s1g_cap && (d_current_symbol == 3)){ // decoding second sig symbol
		for (int i = 0; i < 24; i++) {
			// decoding length
			if((i > 0) && (i < 10) && decoded_bits[i]) {
				len = len | (1 << (i - 1));
			}

		}
	  // set parameters
	  d_frame_bytes = len;
	  switch(mcs) {
		  case 0:
			 d_frame_encoding = 0;
			 d_frame_symbols = (int) ceil((8 + 8 * d_frame_bytes + 6) / (double) 26);
			 d_frame_mod = d_bpsk;
			 dout << "S1G BPSK 1/2 Encoding   ";
			 break;
		  case 1:
			 d_frame_encoding = 2;
			 d_frame_symbols = (int) ceil((8 + 8 * d_frame_bytes + 6) / (double) 52);
			 d_frame_mod = d_qpsk;
			 dout << "S1G QPSK 1/2 Encoding   ";
			 break;
		  case 2:
			 d_frame_encoding = 3;
			 d_frame_symbols = (int) ceil((8 + 8 * d_frame_bytes + 6) / (double) 78);
			 d_frame_mod = d_qpsk;
			 dout << "S1G QPSK 3/4 Encoding   ";
			 break;
		  default:
			 dout << "unknown encoding" << std::endl;
			 return false;
	  }
	}else{
		for(int i = 0; i < 17; i++) {
			parity ^= decoded_bits[i];

			if((i < 4) && decoded_bits[i]) {
				r = r | (1 << i);
			}

			if(decoded_bits[i] && (i > 4) && (i < 17)) {
				d_frame_bytes = d_frame_bytes | (1 << (i-5));
			}
		}

		if(parity != decoded_bits[17]) {
			dout << "SIGNAL: wrong parity" << std::endl;
			return false;
		}
		switch(r) {
		case 11:
			d_frame_encoding = 0;
			d_frame_symbols = (int) ceil((16 + 8 * d_frame_bytes + 6) / (double) 24);
			d_frame_mod = d_bpsk;
			dout << "Encoding: 3 Mbit/s   ";
			break;
		case 15:
			d_frame_encoding = 1;
			d_frame_symbols = (int) ceil((16 + 8 * d_frame_bytes + 6) / (double) 36);
			d_frame_mod = d_bpsk;
			dout << "Encoding: 4.5 Mbit/s   ";
			break;
		case 10:
			d_frame_encoding = 2;
			d_frame_symbols = (int) ceil((16 + 8 * d_frame_bytes + 6) / (double) 48);
			d_frame_mod = d_qpsk;
			dout << "Encoding: 6 Mbit/s   ";
			break;
		case 14:
			d_frame_encoding = 3;
			d_frame_symbols = (int) ceil((16 + 8 * d_frame_bytes + 6) / (double) 72);
			d_frame_mod = d_qpsk;
			dout << "Encoding: 9 Mbit/s   ";
			break;
		case 9:
			d_frame_encoding = 4;
			d_frame_symbols = (int) ceil((16 + 8 * d_frame_bytes + 6) / (double) 96);
			d_frame_mod = d_16qam;
			dout << "Encoding: 12 Mbit/s   ";
			break;
		case 13:
			d_frame_encoding = 5;
			d_frame_symbols = (int) ceil((16 + 8 * d_frame_bytes + 6) / (double) 144);
			d_frame_mod = d_16qam;
			dout << "Encoding: 18 Mbit/s   ";
			break;
		case 8:
			d_frame_encoding = 6;
			d_frame_symbols = (int) ceil((16 + 8 * d_frame_bytes + 6) / (double) 192);
			d_frame_mod = d_64qam;
			dout << "Encoding: 24 Mbit/s   ";
			break;
		case 12:
			d_frame_encoding = 7;
			d_frame_symbols = (int) ceil((16 + 8 * d_frame_bytes + 6) / (double) 216);
			d_frame_mod = d_64qam;
			dout << "Encoding: 27 Mbit/s   ";
			break;
		default:
			dout << "unknown encoding" << std::endl;
			return false;
		}
		mylog(boost::format("encoding: %1% - length: %2% - symbols: %3%")
				% d_frame_encoding % d_frame_bytes % d_frame_symbols);
	}


	return true;
}

const int
frame_equalizer_impl::interleaver_pattern[48] = {
	 0, 3, 6, 9,12,15,18,21,
	24,27,30,33,36,39,42,45,
	 1, 4, 7,10,13,16,19,22,
	25,28,31,34,37,40,43,46,
	 2, 5, 8,11,14,17,20,23,
	26,29,32,35,38,41,44,47};

} /* namespace ieee802_11 */
} /* namespace gr */
