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

#include "signal_field_impl.h"
#include "utils.h"
#include <boost/crc.hpp>
#include <gnuradio/digital/lfsr.h>

using namespace gr::ieee802_11;

signal_field::sptr
signal_field::make() {
	return signal_field::sptr(new signal_field_impl());
}

signal_field::signal_field() : packet_header_default(48, "packet_len") {};


signal_field_impl::signal_field_impl() : packet_header_default(48, "packet_len") {}


signal_field_impl::~signal_field_impl() {}


int signal_field_impl::get_bit(int b, int i) {
	return (b & (1 << i) ? 1 : 0);
}


void signal_field_impl::generate_signal_field(char *out, frame_param &frame,
																						  ofdm_param &ofdm, S1g_ppdu_format s1g_format,
																							bool s1g_enabled) {

	if(s1g_enabled){ // S1G Format
		switch (s1g_format) {
			case S1G_SHORT:
			{
				//data bits of the signal header
				char *signal_header = (char *) malloc(sizeof(char) * 2 * 24);
				//signal header after...
				//convolutional encoding
				char *encoded_signal_header = (char *) malloc(sizeof(char) * 2 * 48);
				//interleaving
				char *interleaved_signal_header = (char *) malloc(sizeof(char) * 2 * 48);

				int length = frame.psdu_size;
				int partial_aid = 0;
				int color = 0;

				/* SIG1 Field (24 bits) */
				// Reserved
				signal_header[ 0] = 1;
				// No STBC
				signal_header[ 1] = 0;
				// Uplink Indication
				signal_header[ 2] = 0;
				// Bandwidth CBW2 (=2MHz)
				signal_header[ 3] = 0;
				signal_header[ 4] = 0;
				// Nsts = 1
				signal_header[ 5] = 0;
				signal_header[ 6] = 0;
				// ID
				signal_header[ 7] = get_bit(color,  0);
				signal_header[ 8] = get_bit(color,  1);
				signal_header[ 9] = get_bit(color,  2);
				signal_header[10] = get_bit(partial_aid, 0);
				signal_header[11] = get_bit(partial_aid, 1);
				signal_header[12] = get_bit(partial_aid, 2);
				signal_header[13] = get_bit(partial_aid, 3);
				signal_header[14] = get_bit(partial_aid, 4);
				signal_header[15] = get_bit(partial_aid, 5);
				// No Short GI
				signal_header[16] = 0;
				// Coding (Only BCC)
				signal_header[17] = 0;
				// LDCP Extra
				signal_header[18] = 0;
				// MCS Index
				signal_header[19] = get_bit(ofdm.s1g_encoding, 0);
				signal_header[20] = get_bit(ofdm.s1g_encoding, 1);
				signal_header[21] = get_bit(ofdm.s1g_encoding, 2);
				signal_header[22] = get_bit(ofdm.s1g_encoding, 3);
				// Smoothing
				signal_header[23] = 0;
				/* SIG2 Field (24 bits) */
				// Aggregation
				signal_header[24] = 0;
				// Length
				signal_header[25] = get_bit(length, 0);
				signal_header[26] = get_bit(length, 1);
				signal_header[27] = get_bit(length, 2);
				signal_header[28] = get_bit(length, 3);
				signal_header[29] = get_bit(length, 4);
				signal_header[30] = get_bit(length, 5);
				signal_header[31] = get_bit(length, 6);
				signal_header[32] = get_bit(length, 7);
				signal_header[33] = get_bit(length, 8);
				// Response Indication
				signal_header[34] = 0;
				signal_header[35] = 0;
				// Traveling Pilots
				signal_header[36] = 0;
				// NDP Indication
				signal_header[37] = 0;
				// CRC (4 Bits)
				boost::crc_32_type result;
				result.process_bytes(signal_header, 38);
				uint32_t crc_sum = result.checksum();
				signal_header[38] = get_bit(crc_sum, 3);
				signal_header[39] = get_bit(crc_sum, 2);
				signal_header[40] = get_bit(crc_sum, 1);
				signal_header[41] = get_bit(crc_sum, 0);
				// Tail (6 Bits = 0)
				for (int i = 0; i < 6; i++) {
					signal_header[42 + i] = 0;
				}

				ofdm_param signal_ofdm(BPSK_1_2);
				frame_param signal_param;
				signal_param.set_service_field_length(s1g_enabled);
				signal_param.set_frame_params(signal_ofdm, 0);

				// convolutional encoding (scrambling is not needed)
				convolutional_encoding(signal_header, encoded_signal_header, signal_param);
				// interleaving
				interleave(encoded_signal_header, out, signal_param, signal_ofdm);

				free(signal_header);
				free(encoded_signal_header);
				free(interleaved_signal_header);
				break;
			}
			case S1G_1M:
			{

				break;
			}
			defaut:
				break;
		}
	}else{ // No S1G Format
		//data bits of the signal header
		char *signal_header = (char *) malloc(sizeof(char) * 24);
		//signal header after...
		//convolutional encoding
		char *encoded_signal_header = (char *) malloc(sizeof(char) * 48);
		//interleaving
		char *interleaved_signal_header = (char *) malloc(sizeof(char) * 48);

		int length = frame.psdu_size;

		// first 4 bits represent the modulation and coding scheme
		signal_header[ 0] = get_bit(ofdm.rate_field, 3);
		signal_header[ 1] = get_bit(ofdm.rate_field, 2);
		signal_header[ 2] = get_bit(ofdm.rate_field, 1);
		signal_header[ 3] = get_bit(ofdm.rate_field, 0);
		// 5th bit is reserved and must be set to 0
		signal_header[ 4] = 0;
		// then 12 bits represent the length
		signal_header[ 5] = get_bit(length,  0);
		signal_header[ 6] = get_bit(length,  1);
		signal_header[ 7] = get_bit(length,  2);
		signal_header[ 8] = get_bit(length,  3);
		signal_header[ 9] = get_bit(length,  4);
		signal_header[10] = get_bit(length,  5);
		signal_header[11] = get_bit(length,  6);
		signal_header[12] = get_bit(length,  7);
		signal_header[13] = get_bit(length,  8);
		signal_header[14] = get_bit(length,  9);
		signal_header[15] = get_bit(length, 10);
		signal_header[16] = get_bit(length, 11);
		//18-th bit is the parity bit for the first 17 bits
		int sum = 0;
		for(int i = 0; i < 17; i++) {
			if(signal_header[i]) {
				sum++;
			}
		}
		signal_header[17] = sum % 2;

		// last 6 bits must be set to 0
		for (int i = 0; i < 6; i++) {
			signal_header[18 + i] = 0;
		}

		ofdm_param signal_ofdm(BPSK_1_2);
		frame_param signal_param;
		signal_param.set_service_field_length(s1g_enabled);
		signal_param.set_frame_params(signal_ofdm, 0);

		// convolutional encoding (scrambling is not needed)
		convolutional_encoding(signal_header, encoded_signal_header, signal_param);
		// interleaving
		interleave(encoded_signal_header, out, signal_param, signal_ofdm);

		free(signal_header);
		free(encoded_signal_header);
		free(interleaved_signal_header);
	}

}

bool signal_field_impl::header_formatter(long packet_len, unsigned char *out, const std::vector<tag_t> &tags)
{

	bool encoding_found = 		false;
	bool s1g_encoding_found = false;
	bool s1g_format_found = 	false;
	bool s1g_cw_found = 			false;
	bool len_found = 					false;
	int encoding = 						BPSK_1_2;
	int s1g_encoding = 				S1G_BPSK_1_2;
	int s1g_format = 					S1G_SHORT;
	int s1g_cw = 							S1G_CW_1M;
	int len = 								0;

	// read tags
	for(int i = 0; i < tags.size(); i++) {
		if(pmt::eq(tags[i].key, pmt::mp("encoding"))) {
			encoding_found = true;
			encoding = pmt::to_long(tags[i].value);
		}else if(pmt::eq(tags[i].key, pmt::mp("s1g_enoding"))){
			s1g_encoding_found = true;
			s1g_encoding = pmt::to_long(tags[i].value);
		}else if(pmt::eq(tags[i].key, pmt::mp("s1g_cw"))){
			s1g_cw_found = true;
			s1g_cw = pmt::to_long(tags[i].value);
		}else if(pmt::eq(tags[i].key, pmt::mp("s1g_format"))){
			s1g_format_found = true;
			s1g_format = pmt::to_long(tags[i].value);
		}else if(pmt::eq(tags[i].key, pmt::mp("psdu_len"))) {
			len_found = true;
			len = pmt::to_long(tags[i].value);
		}
	}

	// check if all tags are present
	// if((!encoding_found) || (!len_found)) {
	// 	return false;
	// }

	ofdm_param ofdm((Encoding)encoding);
	if(s1g_encoding_found){ // S1G enabled
		ofdm = ofdm_param((S1g_encoding)s1g_encoding, (S1g_cw) s1g_cw);
	}

	frame_param frame;
	// set amount of service bits
	frame.set_service_field_length(s1g_encoding_found);
	frame.set_frame_params(ofdm, len);

	generate_signal_field((char*)out, frame,
	                      ofdm, (S1g_ppdu_format) s1g_format,
	                      (bool) s1g_encoding_found);
	return true;
}

bool signal_field_impl::header_parser(
		const unsigned char *in, std::vector<tag_t> &tags) {

	throw std::runtime_error("not implemented yet");
	return false;
}
