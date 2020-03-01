/*
 * Copyright (C) 2013 Bastian Bloessl <bloessl@ccs-labs.org>
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
#include "utils.h"

#include <cassert>
#include <cstring>
#include <math.h>
/*	Modulation Coding Schemes (MCS)
		IEEE 802.11 (2007): See Page 597
		n_bpsc: bits per subcarrier
		n_cbps: coded bits per OFDM symbol
		n_dbps: data bits per symbol
		rate_field: data rate Mbit/s (rate bits)
*/
ofdm_param::ofdm_param(Encoding e) {
	encoding = e;

	switch(e) {
		case BPSK_1_2:
			n_bpsc = 1;
			n_cbps = 48;
			n_dbps = 24;
			rate_field = 0x0D; // 0b00001101
			break;

		case BPSK_3_4:
			n_bpsc = 1;
			n_cbps = 48;
			n_dbps = 36;
			rate_field = 0x0F; // 0b00001111
			break;

		case QPSK_1_2:
			n_bpsc = 2;
			n_cbps = 96;
			n_dbps = 48;
			rate_field = 0x05; // 0b00000101
			break;

		case QPSK_3_4:
			n_bpsc = 2;
			n_cbps = 96;
			n_dbps = 72;
			rate_field = 0x07; // 0b00000111
			break;

		case QAM16_1_2:
			n_bpsc = 4;
			n_cbps = 192;
			n_dbps = 96;
			rate_field = 0x09; // 0b00001001
			break;

		case QAM16_3_4:
			n_bpsc = 4;
			n_cbps = 192;
			n_dbps = 144;
			rate_field = 0x0B; // 0b00001011
			break;

		case QAM64_2_3:
			n_bpsc = 6;
			n_cbps = 288;
			n_dbps = 192;
			rate_field = 0x01; // 0b00000001
			break;

		case QAM64_3_4:
			n_bpsc = 6;
			n_cbps = 288;
			n_dbps = 216;
			rate_field = 0x03; // 0b00000011
			break;

		defaut:
			assert(false);
			break;
	}
}

// S1G OFDM constructor
ofdm_param::ofdm_param(S1g_encoding s1g_enc, S1g_cw cw){
	s1g_encoding = s1g_enc;
	s1g_cw = cw;

	switch (s1g_enc) {
		case S1G_BPSK_1_2: // MCS 0
			if(S1G_CW_1M == cw){ // 1MHz
				std::cout << "BPSK 1/2 1MHZ" << std::endl;
				n_bpsc = 1;
				n_cbps = 24;
				n_dbps = 12;
			}else if(S1G_CW_2M == cw){ // 2MHz
				std::cout << "BPSK 1/2 2MHZ" << std::endl;
				n_bpsc = 1;
		    n_cbps = 52;
		    n_dbps = 26;
			}
			break;

		case S1G_QPSK_1_2: // MCS 1
			if(S1G_CW_1M == cw){ // 1MHz
				std::cout << "QPSK 1/2 1MHZ" << std::endl;
				n_bpsc = 2;
				n_cbps = 48;
				n_dbps = 24;
			}else if(S1G_CW_2M == cw){ // 2MHz
				std::cout << "QPSK 1/2 2MHZ" << std::endl;
				n_bpsc = 2;
		    n_cbps = 104;
		    n_dbps = 52;
			}
			break;

		case S1G_QPSK_3_4: // MCS 2
			if(S1G_CW_1M == cw){ // 1MHz
				std::cout << "QPSK 3/4 1MHZ" << std::endl;
				n_bpsc = 2;
				n_cbps = 48;
				n_dbps = 36;
			}else if(S1G_CW_2M == cw){ // 2MHz
				std::cout << "QPSK 3/4 2MHZ" << std::endl;
				n_bpsc = 2;
		    n_cbps = 104;
		    n_dbps = 78;
			}
			break;

		case S1G_16QAM_1_2: // MCS 3
			if(S1G_CW_1M == cw){ // 1MHz
				std::cout << "16-QAM 3/4 1MHZ" << std::endl;
				n_bpsc = 4;
				n_cbps = 96;
				n_dbps = 48;
			}else if(S1G_CW_2M == cw){ // 2MHz
				std::cout << "16-QAM 3/4 2MHZ" << std::endl;
				n_bpsc = 4;
		    n_cbps = 208;
		    n_dbps = 104;
			}
			break;

		case S1G_16QAM_3_4: // MCS 4
			if(S1G_CW_1M == cw){ // 1MHz
				std::cout << "16-QAM 3/4 1MHZ" << std::endl;
				n_bpsc = 4;
				n_cbps = 96;
				n_dbps = 72;
			}else if(S1G_CW_2M == cw){ // 2MHz
				std::cout << "16-QAM 3/4 2MHZ" << std::endl;
				n_bpsc = 4;
		    n_cbps = 208;
		    n_dbps = 156;
			}
			break;

		case S1G_64QAM_2_3: // MCS 5
			if(S1G_CW_1M == cw){ // 1MHz
				std::cout << "64-QAM 2/3 1MHZ" << std::endl;
				n_bpsc = 6;
				n_cbps = 144;
				n_dbps = 96;
			}else if(S1G_CW_2M == cw){ // 2MHz
				std::cout << "64-QAM 2/3 2MHZ" << std::endl;
				n_bpsc = 6;
		    n_cbps = 312;
		    n_dbps = 208;
			}
			break;

		case S1G_64QAM_3_4: // MCS 6
			if(S1G_CW_1M == cw){ // 1MHz
				std::cout << "64-QAM 3/4 1MHZ" << std::endl;
				n_bpsc = 6;
				n_cbps = 144;
				n_dbps = 108;
			}else if(S1G_CW_2M == cw){ // 2MHz
				std::cout << "64-QAM 3/4 2MHZ" << std::endl;
				n_bpsc = 6;
		    n_cbps = 312;
		    n_dbps = 234;
			}
			break;

		case S1G_64QAM_5_6: // MCS 7
			if(S1G_CW_1M == cw){ // 1MHz
				std::cout << "64-QAM 5/6 1MHZ" << std::endl;
				n_bpsc = 6;
				n_cbps = 144;
				n_dbps = 120;
			}else if(S1G_CW_2M == cw){ // 2MHz
				std::cout << "64-QAM 5/6 2MHZ" << std::endl;
				n_bpsc = 6;
		    n_cbps = 312;
		    n_dbps = 260;
			}
			break;

		case S1G_256QAM_3_4: // MCS 8
			if(S1G_CW_1M == cw){ // 1MHz
				std::cout << "256-QAM 3/4 1MHZ" << std::endl;
				n_bpsc = 8;
				n_cbps = 192;
				n_dbps = 144;
			}else if(S1G_CW_2M == cw){ // 2MHz
				std::cout << "256-QAM 3/4 2MHZ" << std::endl;
				n_bpsc = 8;
		    n_cbps = 416;
		    n_dbps = 312;
			}
			break;


		case S1G_256QAM_5_6: // MCS 9
			if(S1G_CW_1M == cw){ // 1MHz
				std::cout << "256-QAM 5/6 1MHZ" << std::endl;
				n_bpsc = 8;
				n_cbps = 192;
				n_dbps = 160;
			}else if(S1G_CW_2M == cw){ // 2MHz
				std::cout << "256-QAM 5/6 2MHZ : not valid!" << std::endl;
			}
			break;

		case S1G_BPSK_REP_1_2: // MCS 10
			if(S1G_CW_1M){
				std::cout << "REP BPSK 1/2 1MHZ" << std::endl;
				n_bpsc = 1;
				n_cbps = 24;
				n_dbps = 6;
			}else if(S1G_CW_2M == cw){ // 2MHz
				std::cout << "REP BPSK 1/2 2MHZ : not valid!" << std::endl;
			}
			break;
		defaut:
			assert(false);
			break;
	}
}

void
ofdm_param::print() {
	std::cout << "OFDM Parameters:" << std::endl;
	std::cout << "endcoding :" << encoding << std::endl;
	std::cout << "rate_field :" << (int)rate_field << std::endl;
	std::cout << "n_bpsc :" << n_bpsc << std::endl;
	std::cout << "n_cbps :" << n_cbps << std::endl;
	std::cout << "n_dbps :" << n_dbps << std::endl;
}


void frame_param::set_frame_params(ofdm_param &ofdm, int psdu_length) {

	psdu_size = psdu_length;

	// number of symbols (17-11)
	n_sym = (int) ceil((n_service_bits + 8 * psdu_size + 6) / (double) ofdm.n_dbps);

	n_data_bits = n_sym * ofdm.n_dbps;

	// number of padding bits (17-13)
	n_pad = n_data_bits - (n_service_bits + 8 * psdu_size + 6);

	n_encoded_bits = n_sym * ofdm.n_cbps;
}

void frame_param::set_service_field_length(bool s1g_cap) {
	if(s1g_cap){ // S1G enabled
		n_service_bits = 8;
	}else{
		n_service_bits = 16;
	}
}

void
frame_param::print() {
	std::cout << "FRAME Parameters:" << std::endl;
	std::cout << "psdu_size: " << psdu_size << std::endl;
	std::cout << "n_sym: " << n_sym << std::endl;
	std::cout << "n_pad: " << n_pad << std::endl;
	std::cout << "n_encoded_bits: " << n_encoded_bits << std::endl;
	std::cout << "n_data_bits: " << n_data_bits << std::endl;
	std::cout << "n_service_bits: " << n_service_bits << std::endl;
}


void scramble(const char *in, char *out, frame_param &frame, char initial_state) {

    int state = initial_state;
    int feedback;
    for (int i = 0; i < frame.n_data_bits; i++) {
			feedback = (!!(state & 64)) ^ (!!(state & 8));
			out[i] = feedback ^ in[i];
			state = ((state << 1) & 0x7e) | feedback;
    }
}


void reset_tail_bits(char *scrambled_data, frame_param &frame) {
	memset(scrambled_data + frame.n_data_bits - frame.n_pad - 6, 0, 6 * sizeof(char));
}


int ones(int n) {
	int sum = 0;
	for(int i = 0; i < 8; i++) {
		if(n & (1 << i)) {
			sum++;
		}
	}
	return sum;
}


void convolutional_encoding(const char *in, char *out, frame_param &frame) {

	int state = 0;
	for(int i = 0; i < frame.n_data_bits; i++) {
		assert(in[i] == 0 || in[i] == 1);
		state = ((state << 1) & 0x7e) | in[i];
		out[i * 2]     = ones(state & 0155) % 2;
		out[i * 2 + 1] = ones(state & 0117) % 2;
	}
}


void puncturing(const char *in, char *out, frame_param &frame,
	              ofdm_param &ofdm, bool s1g_cap) {
	int mod;
	if(!s1g_cap){ // S1G disabled
		for (int i = 0; i < frame.n_data_bits * 2 ; i++) {
			switch(ofdm.encoding) {
				case BPSK_1_2:
				case QPSK_1_2:
				case QAM16_1_2:
					*out = in[i];
					out++;
					break;

				case QAM64_2_3:
					if (i % 4 != 3) {
						*out = in[i];
						out++;
					}
					break;

				case BPSK_3_4:
				case QPSK_3_4:
				case QAM16_3_4:
				case QAM64_3_4:
					mod = i % 6;
					if (!(mod == 3 || mod == 4)) {
						*out = in[i];
						out++;
					}
					break;
				default:
					assert(false);
					break;
			}
		}
	}else{ // S1G enabled
		for (int j = 0; j < frame.n_data_bits * 2; j++) {
			switch(ofdm.s1g_encoding) {
					case S1G_BPSK_1_2:
					case S1G_BPSK_REP_1_2:
					case S1G_QPSK_1_2:
					case S1G_16QAM_1_2:
						*out = in[j];
						out++;
						break;

				case S1G_64QAM_2_3:
					if (j % 4 != 3) {
						*out = in[j];
						out++;
					}
					break;

					case S1G_QPSK_3_4:
					case S1G_16QAM_3_4:
					case S1G_64QAM_3_4:
					case S1G_256QAM_3_4:
						mod = j % 6;
						if (!(mod == 3 || mod == 4)) {
							*out = in[j];
							out++;
						}
						break;

					//TODO: S1G_64QAM_5_6

					default:
						assert(false);
						break;
			}
		}
	}
}


void interleave(const char *in, char *out, frame_param &frame, ofdm_param &ofdm, bool reverse, bool data_field_interleaving) {

	int n_cbps = ofdm.n_cbps;
	int first[n_cbps];
	int second[n_cbps];
	int s = std::max(ofdm.n_bpsc / 2, 1);

	if(!data_field_interleaving){ // interleaving SIG field
		for(int j = 0; j < n_cbps; j++) {
			first[j] = s * (j / s) + ((j + int(floor(16.0 * j / n_cbps))) % s);
		}

		for(int i = 0; i < n_cbps; i++) {
			second[i] = 16 * i - (n_cbps - 1) * int(floor(16.0 * i / n_cbps));
		}

		for(int i = 0; i < frame.n_sym; i++) {
			for(int k = 0; k < n_cbps; k++) {
				if(reverse) {
					out[i * n_cbps + second[first[k]]] = in[i * n_cbps + k];
				} else {
					out[i * n_cbps + k] = in[i * n_cbps + second[first[k]]];
				}
			}
		}
	}else{ // interleaving data field
		int n_col,n_row;
		int n_bpsc = ofdm.n_bpsc;

		if(S1G_CW_1M == ofdm.s1g_cw){
			n_col = 8;
			n_row = 3 * n_bpsc;
		}else if (S1G_CW_2M == ofdm.s1g_cw) {
			n_col = 13;
			n_row = 4 * n_bpsc;
		}

		for(int k = 0; k < n_cbps; k++) {
			first[k] = n_row * (k % n_col) + int(floor(k/n_col));
		}
		for(int i = 0; i < n_cbps; i++) {
			second[i] = s * int(floor(i / s)) + ((i + n_cbps - int(floor(n_col * i / n_cbps))) % s);
		}

		for(int i = 0; i < frame.n_sym; i++) {
			for(int k = 0; k < n_cbps; k++) {
				out[i * n_cbps + second[first[k]]] = in[i * n_cbps + k];
			}
		}
	}


}


void split_symbols(const char *in, char *out, frame_param &frame, ofdm_param &ofdm, int symbols) {

	//symbols = frame.n_sym * 48;

	for (int i = 0; i < symbols; i++) {
		out[i] = 0;
		for(int k = 0; k < ofdm.n_bpsc; k++) {
			assert(*in == 0 || *in == 1);
			out[i] |= (*in << k);
			in++;
		}
	}
}


void generate_bits(const char *psdu, char *data_bits, frame_param &frame) {

	// first 16/8 bits are zero (SERVICE/DATA field)
	memset(data_bits, 0, frame.n_service_bits);
	data_bits += frame.n_service_bits;

	for(int i = 0; i < frame.psdu_size; i++) {
		for(int b = 0; b < 8; b++) {
			data_bits[i * 8 + b] = !!(psdu[i] & (1 << b));
		}
	}
}
