/*
 * Copyright (C) 2013, 2016 Bastian Bloessl <bloessl@ccs-labs.org>
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
#include <ieee802-11/decode_mac.h>

#include "utils.h"
#include "viterbi_decoder.h"

#include <boost/crc.hpp>
#include <gnuradio/io_signature.h>

using namespace gr::ieee802_11;

#define LINKTYPE_IEEE802_11 105 /* http://www.tcpdump.org/linktypes.html */

class decode_mac_impl : public decode_mac {

public:

	static const int S1G_CW_2M_DATA_CARRIERS = 52;
	static const int DATA_CARRIERS = 48;

decode_mac_impl(bool log, bool debug, bool s1g_cap) :
	block("decode_mac",
			gr::io_signature::make(1, 1, (s1g_cap) ? S1G_CW_2M_DATA_CARRIERS : DATA_CARRIERS),
			gr::io_signature::make(0, 0, 0)),
	d_log(log),
	d_debug(debug),
	d_s1g_cap(s1g_cap),
	d_snr(0),
	d_nom_freq(0.0),
	d_freq_offset(0.0),
	d_ofdm(BPSK_1_2),
	d_frame_complete(true) {

	message_port_register_out(pmt::mp("out"));
	d_frame.set_frame_params(d_ofdm, 0);
}

int general_work (int noutput_items, gr_vector_int& ninput_items,
		gr_vector_const_void_star& input_items,
		gr_vector_void_star& output_items) {

	const uint8_t *in = (const uint8_t*)input_items[0];

	int i = 0;

	std::vector<gr::tag_t> tags;
	const uint64_t nread = this->nitems_read(0);

	//std::cout << "Decode MAC: input " << ninput_items[0] << std::endl;

	while(i < ninput_items[0]) {

		get_tags_in_range(tags, 0, nread + i, nread + i + 1, pmt::string_to_symbol("wifi_start"));

		if(tags.size()) {
			if (d_frame_complete == false) {
				std::cout << "Decode MAC: Warning: starting to receive new frame before old frame was complete" << std::endl;
				std::cout << "Decode MAC: Already copied " << copied << " out of " << d_frame.n_sym << " symbols of last frame" << std::endl;
			}
			d_frame_complete = false;

			pmt::pmt_t dict = tags[0].value;
			int len_data = pmt::to_uint64(pmt::dict_ref(dict, pmt::mp("frame_bytes"), pmt::from_uint64(MAX_PSDU_SIZE+1)));
			int encoding = pmt::to_uint64(pmt::dict_ref(dict, pmt::mp("encoding"), pmt::from_uint64(0)));
			d_snr = pmt::to_double(pmt::dict_ref(dict, pmt::mp("snr"), pmt::from_double(0)));
			// std::cout << "Decode MAX: d_snr: " << std::to_string(d_snr) << std::endl;
			d_nom_freq = pmt::to_double(pmt::dict_ref(dict, pmt::mp("freq"), pmt::from_double(0)));
			d_freq_offset = pmt::to_double(pmt::dict_ref(dict, pmt::mp("freq_offset"), pmt::from_double(0)));
			d_serv_bytes = 2;
			d_data_subcr = DATA_CARRIERS;

			ofdm_param ofdm	= ofdm_param((Encoding)encoding);
			frame_param frame;

			//S1g_encoding
			if(d_s1g_cap){
				ofdm = ofdm_param((S1g_encoding) encoding);
				d_serv_bytes = 1;
				d_data_subcr = S1G_CW_2M_DATA_CARRIERS;
			}

			frame.set_service_field_length(d_s1g_cap);
			frame.set_frame_params(ofdm, len_data);

			// check for maximum frame size
			if(frame.n_sym <= MAX_SYM && frame.psdu_size <= MAX_PSDU_SIZE) {
				d_ofdm = ofdm;
				d_frame = frame;
				copied = 0;
				// std::cout << "Decode MAC: frame start -- len " << len_data
				// 	<< "  symbols " << frame.n_sym << "  encoding "
				// 	<< encoding << std::endl;
			} else {
				std::cout << "Dropping frame which is too large (symbols or bits)" << std::endl;
			}
		}

		if(copied < d_frame.n_sym) {
			//std::cout << "Decode MAC: copy one symbol, copied " << copied << " out of " << d_frame.n_sym << std::endl;
			std::memcpy(d_rx_symbols + (copied * d_data_subcr), in, d_data_subcr);
			copied++;

			if(copied == d_frame.n_sym) {
				//std::cout << "Decode MAC: received complete frame - decoding" << std::endl;
				decode();
				in += d_data_subcr;
				i++;
				d_frame_complete = true;
				break;
			}
		}

		in += d_data_subcr;
		i++;
	}

	consume(0, i);

	return 0;
}

void decode() {

	//std::cout << "Decode MAC: decode()" << std::endl;

	for(int i = 0; i < d_frame.n_sym *d_data_subcr ; i++) {
		for(int k = 0; k < d_ofdm.n_bpsc; k++) {
			d_rx_bits[i*d_ofdm.n_bpsc + k] = !!(d_rx_symbols[i] & (1 << k));
		}
	}

	deinterleave();
	//std::cout << "Decode MAC: viterbi decoder start" << std::endl;
	uint8_t *decoded = d_decoder.decode(&d_ofdm, &d_frame, d_deinterleaved_bits, d_s1g_cap);
	//std::cout << "Decode MAC: viterbi decoder finished" << std::endl;
	descramble(decoded);
	//print_output();

	// skip service field
	// boost::crc_32_type result;
	// result.process_bytes(out_bytes + d_serv_bytes, d_frame.psdu_size);
	// if(result.checksum() != 558161692) {
	// 	std::cout << "checksum wrong -- dropping" << std::endl;
	// 	return;
	// }

	mylog(boost::format("encoding: %1% - length: %2% - symbols: %3%")
			% d_ofdm.encoding % d_frame.psdu_size % d_frame.n_sym);

	// create PDU
	pmt::pmt_t blob = pmt::make_blob(out_bytes + d_serv_bytes, d_frame.psdu_size - 4);
	pmt::pmt_t enc = pmt::from_uint64(d_ofdm.encoding);
	pmt::pmt_t dict = pmt::make_dict();
	dict = pmt::dict_add(dict, pmt::mp("encoding"), enc);
	dict = pmt::dict_add(dict, pmt::mp("snr"), pmt::from_double(d_snr));
	dict = pmt::dict_add(dict, pmt::mp("nomfreq"), pmt::from_double(d_nom_freq));
	dict = pmt::dict_add(dict, pmt::mp("freqofs"), pmt::from_double(d_freq_offset));
	dict = pmt::dict_add(dict, pmt::mp("dlt"), pmt::from_long(LINKTYPE_IEEE802_11));
	message_port_pub(pmt::mp("out"), pmt::cons(dict, blob));
}

void deinterleave() {

//TODO: Adopt deinterleaving of data field
	int n_col,n_row;
	int n_bpsc = d_ofdm.n_bpsc;
	int n_cbps = d_ofdm.n_cbps;
	int first[n_cbps];
	int second[n_cbps];
	int s = std::max(n_bpsc / 2, 1);

	// std::cout << "Decode MAC: deinterleave()" << std::endl;

	// For S1G_CW_2M
	n_col = 13;
	n_row = 4 * n_bpsc;

	if(d_s1g_cap){
		for(int j = 0; j < n_cbps; j++) {
			first[j] = s * int(floor(j / s)) + ((j + int(floor(n_col * j / n_cbps))) % s);
		}

		for(int i = 0; i < n_cbps; i++) {
			second[i] = n_col * i - (n_cbps - 1) * int(floor( i / n_row));
		}

		int count = 0;
		for(int i = 0; i < d_frame.n_sym; i++) {
			for(int k = 0; k < n_cbps; k++) {
				//d_deinterleaved_bits[i * n_cbps + second[first[k]]] = d_rx_bits[i * n_cbps + k];
				d_deinterleaved_bits[i * n_cbps + k] = d_rx_bits[i * n_cbps + second[first[k]]];
			}
		}

		// std::cout << "Decode MAC: deinterleave(): finished" << std::endl;
	}else{
		for(int j = 0; j < n_cbps; j++) {
			first[j] = s * (j / s) + ((j + int(floor(16.0 * j / n_cbps))) % s);
		}

		for(int i = 0; i < n_cbps; i++) {
			second[i] = 16 * i - (n_cbps - 1) * int(floor(16.0 * i / n_cbps));
		}

		int count = 0;
		for(int i = 0; i < d_frame.n_sym; i++) {
			for(int k = 0; k < n_cbps; k++) {
				d_deinterleaved_bits[i * n_cbps + second[first[k]]] = d_rx_bits[i * n_cbps + k];
			}
		}
	}
}


void descramble (uint8_t *decoded_bits) {

	int state = 0;
	int feedback;
	int bit;
	int serv_bits = d_serv_bytes * 8;
	int debug_2_bytes[64];
	int cnt=0;
	// std::cout << "Decode MAC: descramble()" << std::endl;

	std::memset(out_bytes, 0, d_frame.psdu_size + 2);

	for(int i = 0; i < 7; i++) {
		if(decoded_bits[i]) {
			state |= 1 << (6 - i);
		}
	}
	out_bytes[0] = state;

	for(int i = 7; i < d_frame.psdu_size*8+serv_bits; i++) {
		feedback = ((!!(state & 64))) ^ (!!(state & 8));
		bit = feedback ^ (decoded_bits[i] & 0x1);
		out_bytes[i/8] |= bit << (i%8);
		state = ((state << 1) & 0x7e) | feedback;
	}
	// std::cout << "Decode MAC: descramble() finished" << std::endl;

}

void print_output() {

	std::cout << std::endl;
	for(int i = d_serv_bytes; i < d_frame.psdu_size + d_serv_bytes; i++) {
		std::cout << std::setfill('0') << std::setw(2) << std::hex << ((unsigned int)out_bytes[i] & 0xFF) << std::dec << " ";
		if(i % 16 == 15) {
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
	for(int i = d_serv_bytes; i < d_frame.psdu_size + d_serv_bytes; i++) {
		if((out_bytes[i] > 31) && (out_bytes[i] < 127)) {
			std::cout << ((char) out_bytes[i]);
		} else {
			std::cout << ".";
		}
	}
	std::cout << std::endl;
}

private:
	bool d_debug;
	bool d_log;

	frame_param d_frame;
	ofdm_param d_ofdm;
	double d_snr;  // dB
	double d_nom_freq;  // nominal frequency, Hz
	double d_freq_offset;  // frequency offset, Hz
	viterbi_decoder d_decoder;
	int d_serv_bytes;
	bool d_s1g_cap;
	int d_data_subcr;

	uint8_t d_rx_symbols[S1G_CW_2M_DATA_CARRIERS * MAX_SYM];
	uint8_t d_rx_bits[MAX_ENCODED_BITS];
	uint8_t d_deinterleaved_bits[MAX_ENCODED_BITS];
	uint8_t out_bytes[MAX_PSDU_SIZE + 2]; // 2 for signal field

	int copied;
	bool d_frame_complete;
};

decode_mac::sptr
decode_mac::make(bool log, bool debug, bool s1g_cap) {
	return gnuradio::get_initial_sptr(new decode_mac_impl(log, debug, s1g_cap));
}
