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
#include <ieee802-11/mapper.h>
#include "utils.h"
#include <gnuradio/io_signature.h>

using namespace gr::ieee802_11;


class mapper_impl : public mapper {
public:

static const int S1G_CW_2M_DATA_CARRIERS = 52;
static const int S1G_CW_4M_DATA_CARRIERS = 108;
static const int S1G_CW_8M_DATA_CARRIERS = 234;
static const int S1G_CW_16M_DATA_CARRIERS = 468;
static const int DATA_CARRIERS = 48;

mapper_impl(Encoding e, bool debug, S1g_encoding s1g_enc, S1g_cw s1g_cw, bool s1g_cap) :
	block ("mapper",
			gr::io_signature::make(0, 0, 0),
			gr::io_signature::make(1, 1, sizeof(char))),
			d_symbols_offset(0),
			d_symbols(NULL),
			d_debug(debug),
			d_scrambler(1),
			d_ofdm(e),
			d_s1g_cap(s1g_cap),
			d_s1g_encoding(s1g_enc),
			d_s1g_cw(s1g_cw) {

	message_port_register_in(pmt::mp("in"));
	set_encoding(e);
}

~mapper_impl() {
	free(d_symbols);
}

void print_message(const char *msg, size_t len) {

	dout << std::hex << "MAPPER input symbols" << std::endl
		<< "===========================" << std::endl;

	for(int i = 0; i < len; i++) {
		dout << std::hex << (int)msg[i] << " ";
	}
	dout << std::dec << std::endl;
}


int general_work(int noutput, gr_vector_int& ninput_items,
			gr_vector_const_void_star& input_items,
			gr_vector_void_star& output_items ) {

	unsigned char *out = (unsigned char*)output_items[0];

	dout << "MAPPER called offset: " << d_symbols_offset <<
		"   length: " << d_symbols_len << std::endl;

	while(!d_symbols_offset) {
		pmt::pmt_t msg(delete_head_nowait(pmt::intern("in")));

		if(!msg.get()) {
			return 0;
		}

		if(pmt::is_pair(msg)) {
			dout << "MAPPER: received new message" << std::endl;
			gr::thread::scoped_lock lock(d_mutex);

			int	psdu_length = pmt::blob_length(pmt::cdr(msg));
			const char *psdu = static_cast<const char*>(pmt::blob_data(pmt::cdr(msg)));

			// ############ INSERT MAC STUFF
			frame_param 			frame;

			if(d_s1g_cap){ // S1G enabled
				d_ofdm = ofdm_param(d_s1g_encoding, d_s1g_cw);
				// set amount of service bits
				frame.set_service_field_length(d_s1g_cap);
				frame.set_frame_params(d_ofdm, psdu_length);
				// set amount of symbols
				switch (d_s1g_cw) {
					case S1G_CW_2M:
						d_symbols_len = frame.n_sym * S1G_CW_2M_DATA_CARRIERS;
						break;
					case S1G_CW_4M:
						d_symbols_len = frame.n_sym * S1G_CW_4M_DATA_CARRIERS;
						break;
					case S1G_CW_8M:
						d_symbols_len = frame.n_sym * S1G_CW_8M_DATA_CARRIERS;
						break;
					case S1G_CW_16M:
						d_symbols_len = frame.n_sym * S1G_CW_16M_DATA_CARRIERS;
						break;
					default:
						assert(false);
						break;
				}

			}else{ // S1G disabled
				d_ofdm = ofdm_param(d_encoding);
				// set amount of service bits
				frame.set_service_field_length(d_s1g_cap);
				frame.set_frame_params(d_ofdm, psdu_length);
				// set amount of symbols
				d_symbols_len = frame.n_sym * DATA_CARRIERS;

			}
			if(frame.n_sym > MAX_SYM) {
				std::cout << "packet too large, maximum number of symbols is " << MAX_SYM << std::endl;
				return 0;
			}

			d_ofdm.print();
			frame.print();
			std::cout << "d_s1g_encoding: " << d_s1g_encoding << std::endl;
			std::cout << "d_s1g_cap: " << d_s1g_cap << std::endl;
			std::cout << "d_s1g_cw: " << d_s1g_cw << std::endl;

			//alloc memory for modulation steps
			char *data_bits        = (char*)calloc(frame.n_data_bits, sizeof(char));
			char *scrambled_data   = (char*)calloc(frame.n_data_bits, sizeof(char));
			char *encoded_data     = (char*)calloc(frame.n_data_bits * 2, sizeof(char));
			char *punctured_data   = (char*)calloc(frame.n_encoded_bits, sizeof(char));
			char *interleaved_data = (char*)calloc(frame.n_encoded_bits, sizeof(char));
			char *symbols          = (char*)calloc((frame.n_encoded_bits / d_ofdm.n_bpsc), sizeof(char));
			std::cout << "symbols: " << frame.n_encoded_bits / d_ofdm.n_bpsc << std::endl;

			//generate the WIFI data field, adding service field and pad bits
			generate_bits(psdu, data_bits, frame);

			// scrambling
			scramble(data_bits, scrambled_data, frame, d_scrambler++);

			if(d_scrambler > 127) {
				d_scrambler = 1;
			}

			// reset tail bits
			reset_tail_bits(scrambled_data, frame);
			// encoding
			convolutional_encoding(scrambled_data, encoded_data, frame);
			// puncturing
			puncturing(encoded_data, punctured_data, frame, d_ofdm, d_s1g_cap);
			//std::cout << "punctured" << std::endl;
			// interleaving
			if(d_s1g_cap){
				interleave(punctured_data, interleaved_data, frame, d_ofdm, false, true);
			}else{
				interleave(punctured_data, interleaved_data, frame, d_ofdm);
			}
			//std::cout << "interleaved" << std::endl;

			// one byte per symbol
			split_symbols(interleaved_data, symbols, frame, d_ofdm, d_symbols_len);

			std::cout << "d_symbols_len: " << d_symbols_len << std::endl;
			d_symbols = (char*)calloc(d_symbols_len, 1);
			std::memcpy(d_symbols, symbols, d_symbols_len);


			// add tags
			pmt::pmt_t key = pmt::string_to_symbol("packet_len");
			pmt::pmt_t value = pmt::from_long(d_symbols_len);
			pmt::pmt_t srcid = pmt::string_to_symbol(alias());
			add_item_tag(0, nitems_written(0), key, value, srcid);

			pmt::pmt_t psdu_bytes = pmt::from_long(psdu_length);
			add_item_tag(0, nitems_written(0), pmt::mp("psdu_len"),
					psdu_bytes, srcid);

			if(!d_s1g_cap){ // S1G disabled
				std::cout << "mapper: general_work: add_item_tag: set encoding" << std::endl;
				pmt::pmt_t encoding = pmt::from_long(d_encoding);
				add_item_tag(0, nitems_written(0), pmt::mp("encoding"),
					encoding, srcid);
			}else{ // S1G enabled
				// Add S1G Encoding tag
				pmt::pmt_t s1g_encoding = pmt::from_long(d_s1g_encoding);
				add_item_tag(0, nitems_written(0), pmt::mp("s1g_encoding"),
					s1g_encoding, srcid);
				// add S1G CW tag
				pmt::pmt_t s1g_cw = pmt::from_long(d_s1g_cw);
				add_item_tag(0, nitems_written(0), pmt::mp("s1g_cw"),
						s1g_cw, srcid);
				// // add S1G format tag
				// pmt::pmt_t s1g_format = pmt::from_long(d_s1g_format);
				// add_item_tag(0, nitems_written(0), pmt::mp("s1g_format"),
				// 		s1g_format, srcid);
			}

			free(data_bits);
			free(scrambled_data);
			free(encoded_data);
			free(punctured_data);
			free(interleaved_data);
			free(symbols);

			break;
		}
	}

	int i = std::min(noutput, d_symbols_len - d_symbols_offset);
	std::memcpy(out, d_symbols + d_symbols_offset, i);
	d_symbols_offset += i;

	if(d_symbols_offset == d_symbols_len) {
		d_symbols_offset = 0;
		free(d_symbols);
		d_symbols = 0;
	}

	return i;
}

/* GRC Callbacks */
void set_encoding(Encoding mcs){
	gr::thread::scoped_lock lock(d_mutex);
	d_encoding = mcs;
	std::cout << "MAPPER: encoding: " << mcs << std::endl;
	// if(!d_s1g_cap){ // S1G disabled
	// 	d_ofdm = ofdm_param(mcs);
	// 	d_frame.set_service_field_length(d_s1g_cap);
	// 	d_frame.set_frame_params(d_ofdm, psdu_length);
	// 	frame = d_frame;
	// }
}

void set_s1g_encoding(S1g_encoding mcs){
	gr::thread::scoped_lock lock(d_mutex);
	std::cout << "MAPPER: s1g_encoding: " << mcs << std::endl;
	d_s1g_encoding = mcs;
	// if(d_s1g_cap){ // S1G enabled
	// 	d_ofdm = ofdm_param(d_s1g_encoding,d_s1g_cw);
	// 	s1g_frame.set_service_field_length(d_s1g_cap);
	// 	s1g_frame.set_frame_params(d_ofdm, psdu_length);
	// 	frame = s1g_frame;
	// }
}

// void set_frame_format(S1g_ppdu_format s1g_format) {
// 	gr::thread::scoped_lock lock(d_mutex);
// 	std::cout << "MAPPER: frame_format: " << s1g_format << std::endl;
// 	d_s1g_format = s1g_format;
// }

void set_s1g_cw(S1g_cw cw){
	gr::thread::scoped_lock lock(d_mutex);
	std::cout << "MAPPER: s1g_cw: " << cw << std::endl;
	d_s1g_cw = cw;
	// if(d_s1g_cap){ // S1G enabled
	// 	d_ofdm = ofdm_param(d_s1g_encoding,d_s1g_cw);
	// 	s1g_frame.set_service_field_length(d_s1g_cap);
	// 	s1g_frame.set_frame_params(d_ofdm, psdu_length);
	// 	frame = s1g_frame;
	// }
}

void enable_s1g(bool s1g_cap){
	gr::thread::scoped_lock lock(d_mutex);
	std::cout << "MAPPER: enable_s1g: " << s1g_cap << std::endl;
	d_s1g_cap = s1g_cap;
	// if(!s1g_cap){ // S1G disabled: update values
	// 	d_ofdm = ofdm_param(d_encoding);
	// 	d_frame.set_service_field_length(d_s1g_cap);
	// 	d_frame.set_frame_params(d_ofdm, psdu_length);
	// 	frame = d_frame;
	// }else{
	// 	d_ofdm = ofdm_param(d_s1g_encoding, d_s1g_cw);
	// 	s1g_frame.set_service_field_length(d_s1g_cap);
	// 	s1g_frame.set_frame_params(d_ofdm, psdu_length);
	// 	frame = s1g_frame;
	// }
}

private:
	uint8_t      			d_scrambler;
	bool         			d_debug;
	char*        			d_symbols;
	int          			d_symbols_offset;
	int          			d_symbols_len;
	ofdm_param   			d_ofdm;
	Encoding     			d_encoding;
	S1g_encoding 			d_s1g_encoding;
	//S1g_ppdu_format 	d_s1g_format;
	S1g_cw 			 			d_s1g_cw;
	bool 				 			d_s1g_cap;
	//frame_param 			frame;
	gr::thread::mutex d_mutex;
};

mapper::sptr
mapper::make(Encoding e, bool debug, S1g_encoding s1g_enc, S1g_cw s1g_cw, bool s1g_cap) {
	return gnuradio::get_initial_sptr(new mapper_impl(e, debug, s1g_enc, s1g_cw, s1g_cap));
}
