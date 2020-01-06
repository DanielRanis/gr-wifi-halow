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

#include "s1g_signal_field_impl.h"
#include "utils.h"
#include <boost/crc.hpp>
#include <gnuradio/digital/lfsr.h>

using namespace gr::ieee802_11;

s1g_signal_field::sptr
s1g_signal_field::make() {
	return s1g_signal_field::sptr(new s1g_signal_field_impl());
}

s1g_signal_field::s1g_signal_field() : packet_header_default(2 * 48, "packet_len") {};


s1g_signal_field_impl::s1g_signal_field_impl() : packet_header_default(2 * 48, "packet_len") {}


s1g_signal_field_impl::~s1g_signal_field_impl() {}


int s1g_signal_field_impl::get_bit(int b, int i) {
	return (b & (1 << i) ? 1 : 0);
}


void s1g_signal_field_impl::generate_s1g_signal_field(char *out, frame_param &frame,
																						  ofdm_param &ofdm, S1g_ppdu_format s1g_format) {
	switch (s1g_format) {
		case S1G_SHORT:
		{
			std::cout << "generate_s1g_signal_field: S1G_SHORT " << std::endl;
			//data bits of the signal header
			char *signal_header = (char *) malloc(sizeof(char) * 24);
			//signal header after...
			//convolutional encoding
			char *encoded_signal_header = (char *) malloc(sizeof(char) * 48);
			//interleaving
			//char *interleaved_signal_header = (char *) malloc(sizeof(char) * 2 * 48);
			int length = frame.psdu_size;
			int partial_aid = 0;
			int color = 0;
			//ofdm_param signal_ofdm(S1G_BPSK_1_2,ofdm.s1g_cw);
			ofdm_param signal_ofdm(BPSK_1_2);
			frame_param signal_param;
			signal_param.set_service_field_length(true);
			signal_param.set_frame_params(signal_ofdm, 0);
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
			// convolutional encoding (scrambling is not needed)
			convolutional_encoding(signal_header, encoded_signal_header, signal_param);
			// interleaving
			interleave(encoded_signal_header, out, signal_param, signal_ofdm);
			/* SIG2 Field (24 bits) */
			// Aggregation
			signal_header[0] = 0;
			// Length
			signal_header[ 1] = get_bit(length, 0);
			signal_header[ 2] = get_bit(length, 1);
			signal_header[ 3] = get_bit(length, 2);
			signal_header[ 4] = get_bit(length, 3);
			signal_header[ 5] = get_bit(length, 4);
			signal_header[ 6] = get_bit(length, 5);
			signal_header[ 7] = get_bit(length, 6);
			signal_header[ 8] = get_bit(length, 7);
			signal_header[ 9] = get_bit(length, 8);
			// Response Indication
			signal_header[10] = 0;
			signal_header[11] = 0;
			// Traveling Pilots
			signal_header[12] = 0;
			// NDP Indication
			signal_header[13] = 0;
			// CRC (4 Bits)
			boost::crc_32_type result;
			result.process_bytes(signal_header, 14);
			uint32_t crc_sum = result.checksum();
			signal_header[14] = get_bit(crc_sum, 3);
			signal_header[15] = get_bit(crc_sum, 2);
			signal_header[16] = get_bit(crc_sum, 1);
			signal_header[17] = get_bit(crc_sum, 0);
			// Tail (6 Bits = 0)
			for (int i = 0; i < 6; i++) {
				signal_header[18 + i] = 0;
			}
			// convolutional encoding (scrambling is not needed)
			convolutional_encoding(signal_header, encoded_signal_header, signal_param);
			// interleaving
			interleave(encoded_signal_header, out + 48, signal_param, signal_ofdm);
			free(signal_header);
			free(encoded_signal_header);
			//free(interleaved_signal_header);
			break;
		}
		case S1G_1M:
		{
			// std::cout << "generate_s1g_signal_field: S1G_1M " << std::endl;
			// //data bits of the signal header
			// char *signal_header = (char *) malloc(sizeof(char) * 6 * 6);
			// //signal header after...
			// //convolutional encoding
			// char *encoded_signal_header = (char *) malloc(sizeof(char) * 2 * 36);
			// //interleaving
			// //char *interleaved_signal_header = (char *) malloc(sizeof(char) * 2 * 36);
			//
			// int length = frame.psdu_size;
			//
			// /* SIG1 Field */
			// // Nsts
			// signal_header[ 0] = 0;
			// signal_header[ 1] = 0;
			// // Short GI
			// signal_header[ 2] = 0;
			// // Coding
			// signal_header[ 3] = 0;
			// // LDPC Extra
			// signal_header[ 4] = 1;
			// // STBC
			// signal_header[ 5] = 0;
			//
			// /* SIG2 Field */
			// // Reserved
			// signal_header[ 6] = 1;
			// // MCS Index
			// signal_header[ 7] = get_bit(ofdm.s1g_encoding, 0);
			// signal_header[ 8] = get_bit(ofdm.s1g_encoding, 1);
			// signal_header[ 9] = get_bit(ofdm.s1g_encoding, 2);
			// signal_header[10] = get_bit(ofdm.s1g_encoding, 3);
			// // Aggregation
			// signal_header[11] = 0;
			//
			// /* SIG3 Field and SIG4 Field */
			// // Length
			// signal_header[12] = get_bit(length, 0);
			// signal_header[13] = get_bit(length, 1);
			// signal_header[14] = get_bit(length, 2);
			// signal_header[15] = get_bit(length, 3);
			// signal_header[16] = get_bit(length, 4);
			// signal_header[17] = get_bit(length, 5);
			// signal_header[18] = get_bit(length, 6);
			// signal_header[19] = get_bit(length, 7);
			// signal_header[20] = get_bit(length, 8);
			// // Response Indication
			// // Length
			// signal_header[21] = 0;
			// signal_header[22] = 0;
			// // Smoothing
			// signal_header[23] = 0;
			//
			// /* SIG5 Field */
			// // Traveling Pilots
			// signal_header[24] = 0;
			// // NDP Indication
			// signal_header[25] = 0;
			// // CRC (4 Bits)
			// boost::crc_32_type result;
			// result.process_bytes(signal_header, 26);
			// uint32_t crc_sum = result.checksum();
			// signal_header[26] = get_bit(crc_sum, 3);
			// signal_header[27] = get_bit(crc_sum, 2);
			// signal_header[28] = get_bit(crc_sum, 1);
			// signal_header[29] = get_bit(crc_sum, 0);
			//
			// /* SIG6 Field */
			// // Tail (6 Bits = 0)
			// for (int i = 0; i < 6; i++) {
			// 	signal_header[30 + i] = 0;
			// }
			//
			// ofdm_param signal_ofdm(S1G_BPSK_1_2,ofdm.s1g_cw);
			// frame_param signal_param;
			// signal_param.set_service_field_length(true);
			// signal_param.set_frame_params(signal_ofdm, 0);
			//
			// // convolutional encoding (scrambling is not needed)
			// convolutional_encoding(signal_header, encoded_signal_header, signal_param);
			//
			// // MCS10 Repetition: 1 BCC encoded OFDM Symbol: ([C1...C12],[C1...C12] XOR s)
			// if(S1G_BPSK_REP_1_2 == ofdm.s1g_encoding){
			//
			// 	char *temp_encoded_signal_header = (char *) malloc(sizeof(char) * 2 * 36);
			// 	char *rep_encoded_signal_header = (char *) malloc(sizeof(char) * 2 * 2 * 36);
			// 	char *interleaved_rep_signal_header = (char *) malloc(sizeof(char) * 2 * 2 * 36);
			//
			// 	// store encoded_signal_header
			// 	for(int i = 0;  i < 2 * 36; i++){
			// 			rep_encoded_signal_header[i] = encoded_signal_header[i];
			// 	}
			//
			// 	// generate repetition of encoded_signal_header
			// 	char s[12] = {1,0,0,0,0,1,0,1,0,1,1,1};
			// 	int cnt = 0;
			// 	for(int i = 0;  i < 2 * 36; i++){ // 6 OFDM (SIG) Symbols
			// 			if(12 == cnt){ cnt = 0; }
			// 			temp_encoded_signal_header[i] = encoded_signal_header[i] ^ s[cnt];
			// 			cnt++;
			// 	}
			//
			// 	// store temp_encoded_signal_header
			// 	for(int i = 0;  i < 2 * 36; i++){
			// 			rep_encoded_signal_header[i + (2 * 36)] = temp_encoded_signal_header[i];
			// 	}
			//
			// 	// std::memcpy(&rep_encoded_signal_header[sizeof(temp_encoded_signal_header)],
			// 	// 	          temp_encoded_signal_header, sizeof(temp_encoded_signal_header));
			//
			// 	// interleaving
			// 	interleave(rep_encoded_signal_header, out, signal_param, signal_ofdm);
			//
			// 	free(temp_encoded_signal_header);
			// 	free(rep_encoded_signal_header);
			// 	free(interleaved_rep_signal_header);
			// }else{
			// 	// interleaving
			// 	interleave(encoded_signal_header, out, signal_param, signal_ofdm);
			// }
			// free(signal_header);
			// free(encoded_signal_header);
			// //free(interleaved_signal_header);
			// break;
		}
		default:
			break;
	}

}

bool s1g_signal_field_impl::header_formatter(long packet_len, unsigned char *out, const std::vector<tag_t> &tags)
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

	std::cout << "header_formatter: packet_len: " << packet_len << std::endl;
	// read tags
	for(int i = 0; i < tags.size(); i++) {
		if(pmt::eq(tags[i].key, pmt::mp("encoding"))) {
			encoding_found = true;
			encoding = pmt::to_long(tags[i].value);
		}else if(pmt::eq(tags[i].key, pmt::mp("s1g_encoding"))){
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


	if(!s1g_encoding_found){ // S1G not enabled
		std::cout << "header_formatter: No S1G Encoding found!" << std::endl;
		return true;
	}

	ofdm_param ofdm((S1g_encoding)s1g_encoding, (S1g_cw) s1g_cw);

	frame_param frame;
	// set amount of service bits
	frame.set_service_field_length(s1g_encoding_found);
	frame.set_frame_params(ofdm, len);

	generate_s1g_signal_field((char*)out, frame, ofdm, (S1g_ppdu_format) s1g_format);
	return true;
}

bool s1g_signal_field_impl::header_parser(
		const unsigned char *in, std::vector<tag_t> &tags) {

	throw std::runtime_error("not implemented yet");
	return false;
}
