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
#include "constellations_impl.h"

using namespace gr::ieee802_11;

constellation_bpsk::sptr
constellation_bpsk::make() {
	return constellation_bpsk::sptr(new constellation_bpsk_impl());
}

constellation_bpsk::constellation_bpsk() {}

constellation_bpsk_impl::constellation_bpsk_impl() {
	d_constellation.resize(2);
	d_constellation[0] = gr_complex(-1, 0);
	d_constellation[1] = gr_complex(1, 0);
	d_rotational_symmetry = 2;
	d_dimensionality = 1;
	calc_arity();
}

constellation_bpsk_impl::~constellation_bpsk_impl() {
}

unsigned int
constellation_bpsk_impl::decision_maker(const gr_complex *sample) {
	return (real(*sample) > 0);
}

/**********************************************************/

constellation_256qam::sptr
constellation_256qam::make() {
	return constellation_256qam::sptr(new constellation_256qam_impl());
}

constellation_256qam::constellation_256qam() {}

constellation_256qam_impl::constellation_256qam_impl() {

	const float level = sqrt(float(1/170.0));
	d_constellation.resize(256);
	//1st quadrant
	d_constellation[ 19] = gr_complex(  1*level,15*level);
	d_constellation[ 27] = gr_complex(  3*level,15*level);
	d_constellation[ 31] = gr_complex(  5*level,15*level);
	d_constellation[ 23] = gr_complex(  7*level,15*level);
	d_constellation[ 21] = gr_complex(  9*level,15*level);
	d_constellation[ 29] = gr_complex( 11*level,15*level);
	d_constellation[ 25] = gr_complex( 13*level,15*level);
	d_constellation[ 17] = gr_complex( 15*level,15*level);

	d_constellation[147] = gr_complex(  1*level,13*level);
	d_constellation[155] = gr_complex(  3*level,13*level);
	d_constellation[159] = gr_complex(  5*level,13*level);
	d_constellation[151] = gr_complex(  7*level,13*level);
	d_constellation[149] = gr_complex(  9*level,13*level);
	d_constellation[157] = gr_complex( 11*level,13*level);
	d_constellation[153] = gr_complex( 13*level,13*level);
	d_constellation[145] = gr_complex( 15*level,13*level);

	d_constellation[211] = gr_complex(  1*level,11*level);
	d_constellation[219] = gr_complex(  3*level,11*level);
	d_constellation[223] = gr_complex(  5*level,11*level);
	d_constellation[215] = gr_complex(  7*level,11*level);
	d_constellation[213] = gr_complex(  9*level,11*level);
	d_constellation[221] = gr_complex( 11*level,11*level);
	d_constellation[217] = gr_complex( 13*level,11*level);
	d_constellation[209] = gr_complex( 15*level,11*level);

	d_constellation[ 83] = gr_complex(  1*level, 9*level);
	d_constellation[ 91] = gr_complex(  3*level, 9*level);
	d_constellation[ 95] = gr_complex(  5*level, 9*level);
	d_constellation[ 87] = gr_complex(  7*level, 9*level);
	d_constellation[ 85] = gr_complex(  9*level, 9*level);
	d_constellation[ 93] = gr_complex( 11*level, 9*level);
	d_constellation[ 89] = gr_complex( 13*level, 9*level);
	d_constellation[ 81] = gr_complex( 15*level, 9*level);

	d_constellation[115] = gr_complex(  1*level, 7*level);
	d_constellation[123] = gr_complex(  3*level, 7*level);
	d_constellation[127] = gr_complex(  5*level, 7*level);
	d_constellation[119] = gr_complex(  7*level, 7*level);
	d_constellation[117] = gr_complex(  9*level, 7*level);
	d_constellation[125] = gr_complex( 11*level, 7*level);
	d_constellation[121] = gr_complex( 13*level, 7*level);
	d_constellation[113] = gr_complex( 15*level, 7*level);

	d_constellation[243] = gr_complex(  1*level, 5*level);
	d_constellation[251] = gr_complex(  3*level, 5*level);
	d_constellation[255] = gr_complex(  5*level, 5*level);
	d_constellation[247] = gr_complex(  7*level, 5*level);
	d_constellation[245] = gr_complex(  9*level, 5*level);
	d_constellation[253] = gr_complex( 11*level, 5*level);
	d_constellation[249] = gr_complex( 13*level, 5*level);
	d_constellation[241] = gr_complex( 15*level, 5*level);

	d_constellation[179] = gr_complex(  1*level, 3*level);
	d_constellation[187] = gr_complex(  3*level, 3*level);
	d_constellation[191] = gr_complex(  5*level, 3*level);
	d_constellation[183] = gr_complex(  7*level, 3*level);
	d_constellation[181] = gr_complex(  9*level, 3*level);
	d_constellation[189] = gr_complex( 11*level, 3*level);
	d_constellation[185] = gr_complex( 13*level, 3*level);
	d_constellation[177] = gr_complex( 15*level, 3*level);

	d_constellation[ 51] = gr_complex(  1*level, 1*level);
	d_constellation[ 59] = gr_complex(  3*level, 1*level);
	d_constellation[ 63] = gr_complex(  5*level, 1*level);
	d_constellation[ 55] = gr_complex(  7*level, 1*level);
	d_constellation[ 53] = gr_complex(  9*level, 1*level);
	d_constellation[ 61] = gr_complex( 11*level, 1*level);
	d_constellation[ 57] = gr_complex( 13*level, 1*level);
	d_constellation[ 49] = gr_complex( 15*level, 1*level);

	//2nd quadrant
	d_constellation[ 18] = gr_complex( -1*level,15*level);
	d_constellation[ 26] = gr_complex( -3*level,15*level);
	d_constellation[ 30] = gr_complex( -5*level,15*level);
	d_constellation[ 22] = gr_complex( -7*level,15*level);
	d_constellation[ 20] = gr_complex( -9*level,15*level);
	d_constellation[ 28] = gr_complex(-11*level,15*level);
	d_constellation[ 24] = gr_complex(-13*level,15*level);
	d_constellation[ 16] = gr_complex(-15*level,15*level);

	d_constellation[146] = gr_complex( -1*level,13*level);
	d_constellation[154] = gr_complex( -3*level,13*level);
	d_constellation[158] = gr_complex( -5*level,13*level);
	d_constellation[150] = gr_complex( -7*level,13*level);
	d_constellation[148] = gr_complex( -9*level,13*level);
	d_constellation[156] = gr_complex(-11*level,13*level);
	d_constellation[152] = gr_complex(-13*level,13*level);
	d_constellation[144] = gr_complex(-15*level,13*level);

	d_constellation[210] = gr_complex( -1*level,11*level);
	d_constellation[218] = gr_complex( -3*level,11*level);
	d_constellation[222] = gr_complex( -5*level,11*level);
	d_constellation[214] = gr_complex( -7*level,11*level);
	d_constellation[212] = gr_complex( -9*level,11*level);
	d_constellation[220] = gr_complex(-11*level,11*level);
	d_constellation[216] = gr_complex(-13*level,11*level);
	d_constellation[208] = gr_complex(-15*level,11*level);

	d_constellation[ 82] = gr_complex( -1*level, 9*level);
	d_constellation[ 90] = gr_complex( -3*level, 9*level);
	d_constellation[ 94] = gr_complex( -5*level, 9*level);
	d_constellation[ 86] = gr_complex( -7*level, 9*level);
	d_constellation[ 84] = gr_complex( -9*level, 9*level);
	d_constellation[ 92] = gr_complex(-11*level, 9*level);
	d_constellation[ 88] = gr_complex(-13*level, 9*level);
	d_constellation[ 80] = gr_complex(-15*level, 9*level);

	d_constellation[114] = gr_complex( -1*level, 7*level);
	d_constellation[122] = gr_complex( -3*level, 7*level);
	d_constellation[126] = gr_complex( -5*level, 7*level);
	d_constellation[118] = gr_complex( -7*level, 7*level);
	d_constellation[116] = gr_complex( -9*level, 7*level);
	d_constellation[124] = gr_complex(-11*level, 7*level);
	d_constellation[120] = gr_complex(-13*level, 7*level);
	d_constellation[112] = gr_complex(-15*level, 7*level);

	d_constellation[242] = gr_complex( -1*level, 5*level);
	d_constellation[250] = gr_complex( -3*level, 5*level);
	d_constellation[254] = gr_complex( -5*level, 5*level);
	d_constellation[246] = gr_complex( -7*level, 5*level);
	d_constellation[244] = gr_complex( -9*level, 5*level);
	d_constellation[252] = gr_complex(-11*level, 5*level);
	d_constellation[248] = gr_complex(-13*level, 5*level);
	d_constellation[240] = gr_complex(-15*level, 5*level);

	d_constellation[178] = gr_complex( -1*level, 3*level);
	d_constellation[186] = gr_complex( -3*level, 3*level);
	d_constellation[190] = gr_complex( -5*level, 3*level);
	d_constellation[182] = gr_complex( -7*level, 3*level);
	d_constellation[180] = gr_complex( -9*level, 3*level);
	d_constellation[188] = gr_complex(-11*level, 3*level);
	d_constellation[184] = gr_complex(-13*level, 3*level);
	d_constellation[176] = gr_complex(-15*level, 3*level);

	d_constellation[ 50] = gr_complex( -1*level, 1*level);
	d_constellation[ 58] = gr_complex( -3*level, 1*level);
	d_constellation[ 62] = gr_complex( -5*level, 1*level);
	d_constellation[ 54] = gr_complex( -7*level, 1*level);
	d_constellation[ 52] = gr_complex( -9*level, 1*level);
	d_constellation[ 60] = gr_complex(-11*level, 1*level);
	d_constellation[ 56] = gr_complex(-13*level, 1*level);
	d_constellation[ 48] = gr_complex(-15*level, 1*level);

	//3rd quadrant
	d_constellation[  2] = gr_complex( -1*level,-15*level);
	d_constellation[ 10] = gr_complex( -3*level,-15*level);
	d_constellation[ 14] = gr_complex( -5*level,-15*level);
	d_constellation[  6] = gr_complex( -7*level,-15*level);
	d_constellation[  4] = gr_complex( -9*level,-15*level);
	d_constellation[ 12] = gr_complex(-11*level,-15*level);
	d_constellation[  8] = gr_complex(-13*level,-15*level);
	d_constellation[  0] = gr_complex(-15*level,-15*level);

	d_constellation[130] = gr_complex( -1*level,-13*level);
	d_constellation[138] = gr_complex( -3*level,-13*level);
	d_constellation[142] = gr_complex( -5*level,-13*level);
	d_constellation[134] = gr_complex( -7*level,-13*level);
	d_constellation[132] = gr_complex( -9*level,-13*level);
	d_constellation[140] = gr_complex(-11*level,-13*level);
	d_constellation[136] = gr_complex(-13*level,-13*level);
	d_constellation[128] = gr_complex(-15*level,-13*level);

	d_constellation[194] = gr_complex( -1*level,-11*level);
	d_constellation[202] = gr_complex( -3*level,-11*level);
	d_constellation[206] = gr_complex( -5*level,-11*level);
	d_constellation[198] = gr_complex( -7*level,-11*level);
	d_constellation[196] = gr_complex( -9*level,-11*level);
	d_constellation[204] = gr_complex(-11*level,-11*level);
	d_constellation[200] = gr_complex(-13*level,-11*level);
	d_constellation[192] = gr_complex(-15*level,-11*level);

	d_constellation[ 66] = gr_complex( -1*level, -9*level);
	d_constellation[ 74] = gr_complex( -3*level, -9*level);
	d_constellation[ 78] = gr_complex( -5*level, -9*level);
	d_constellation[ 70] = gr_complex( -7*level, -9*level);
	d_constellation[ 68] = gr_complex( -9*level, -9*level);
	d_constellation[ 76] = gr_complex(-11*level, -9*level);
	d_constellation[ 72] = gr_complex(-13*level, -9*level);
	d_constellation[ 64] = gr_complex(-15*level, -9*level);

	d_constellation[ 98] = gr_complex( -1*level, -7*level);
	d_constellation[106] = gr_complex( -3*level, -7*level);
	d_constellation[110] = gr_complex( -5*level, -7*level);
	d_constellation[102] = gr_complex( -7*level, -7*level);
	d_constellation[100] = gr_complex( -9*level, -7*level);
	d_constellation[108] = gr_complex(-11*level, -7*level);
	d_constellation[104] = gr_complex(-13*level, -7*level);
	d_constellation[ 96] = gr_complex(-15*level, -7*level);

	d_constellation[226] = gr_complex( -1*level, -5*level);
	d_constellation[234] = gr_complex( -3*level, -5*level);
	d_constellation[238] = gr_complex( -5*level, -5*level);
	d_constellation[230] = gr_complex( -7*level, -5*level);
	d_constellation[228] = gr_complex( -9*level, -5*level);
	d_constellation[236] = gr_complex(-11*level, -5*level);
	d_constellation[232] = gr_complex(-13*level, -5*level);
	d_constellation[224] = gr_complex(-15*level, -5*level);

	d_constellation[162] = gr_complex( -1*level, -3*level);
	d_constellation[170] = gr_complex( -3*level, -3*level);
	d_constellation[174] = gr_complex( -5*level, -3*level);
	d_constellation[166] = gr_complex( -7*level, -3*level);
	d_constellation[164] = gr_complex( -9*level, -3*level);
	d_constellation[172] = gr_complex(-11*level, -3*level);
	d_constellation[168] = gr_complex(-13*level, -3*level);
	d_constellation[160] = gr_complex(-15*level, -3*level);

	d_constellation[ 34] = gr_complex( -1*level, -1*level);
	d_constellation[ 42] = gr_complex( -3*level, -1*level);
	d_constellation[ 46] = gr_complex( -5*level, -1*level);
	d_constellation[ 38] = gr_complex( -7*level, -1*level);
	d_constellation[ 36] = gr_complex( -9*level, -1*level);
	d_constellation[ 44] = gr_complex(-11*level, -1*level);
	d_constellation[ 40] = gr_complex(-13*level, -1*level);
	d_constellation[ 32] = gr_complex(-15*level, -1*level);

	//4th quadrant
	d_constellation[  3] = gr_complex(  1*level,-15*level);
	d_constellation[ 11] = gr_complex(  3*level,-15*level);
	d_constellation[ 15] = gr_complex(  5*level,-15*level);
	d_constellation[  7] = gr_complex(  7*level,-15*level);
	d_constellation[  5] = gr_complex(  9*level,-15*level);
	d_constellation[ 13] = gr_complex( 11*level,-15*level);
	d_constellation[  9] = gr_complex( 13*level,-15*level);
	d_constellation[  1] = gr_complex( 15*level,-15*level);

	d_constellation[131] = gr_complex(  1*level,-13*level);
	d_constellation[139] = gr_complex(  3*level,-13*level);
	d_constellation[143] = gr_complex(  5*level,-13*level);
	d_constellation[135] = gr_complex(  7*level,-13*level);
	d_constellation[133] = gr_complex(  9*level,-13*level);
	d_constellation[141] = gr_complex( 11*level,-13*level);
	d_constellation[137] = gr_complex( 13*level,-13*level);
	d_constellation[129] = gr_complex( 15*level,-13*level);

	d_constellation[195] = gr_complex(  1*level,-11*level);
	d_constellation[203] = gr_complex(  3*level,-11*level);
	d_constellation[207] = gr_complex(  5*level,-11*level);
	d_constellation[199] = gr_complex(  7*level,-11*level);
	d_constellation[197] = gr_complex(  9*level,-11*level);
	d_constellation[205] = gr_complex( 11*level,-11*level);
	d_constellation[201] = gr_complex( 13*level,-11*level);
	d_constellation[193] = gr_complex( 15*level,-11*level);

	d_constellation[ 67] = gr_complex(  1*level, -9*level);
	d_constellation[ 75] = gr_complex(  3*level, -9*level);
	d_constellation[ 79] = gr_complex(  5*level, -9*level);
	d_constellation[ 71] = gr_complex(  7*level, -9*level);
	d_constellation[ 69] = gr_complex(  9*level, -9*level);
	d_constellation[ 77] = gr_complex( 11*level, -9*level);
	d_constellation[ 73] = gr_complex( 13*level, -9*level);
	d_constellation[ 65] = gr_complex( 15*level, -9*level);

	d_constellation[ 99] = gr_complex(  1*level, -7*level);
	d_constellation[107] = gr_complex(  3*level, -7*level);
	d_constellation[111] = gr_complex(  5*level, -7*level);
	d_constellation[103] = gr_complex(  7*level, -7*level);
	d_constellation[101] = gr_complex(  9*level, -7*level);
	d_constellation[109] = gr_complex( 11*level, -7*level);
	d_constellation[105] = gr_complex( 13*level, -7*level);
	d_constellation[ 97] = gr_complex( 15*level, -7*level);

	d_constellation[227] = gr_complex(  1*level, -5*level);
	d_constellation[235] = gr_complex(  3*level, -5*level);
	d_constellation[239] = gr_complex(  5*level, -5*level);
	d_constellation[231] = gr_complex(  7*level, -5*level);
	d_constellation[229] = gr_complex(  9*level, -5*level);
	d_constellation[237] = gr_complex( 11*level, -5*level);
	d_constellation[233] = gr_complex( 13*level, -5*level);
	d_constellation[225] = gr_complex( 15*level, -5*level);

	d_constellation[163] = gr_complex(  1*level, -3*level);
	d_constellation[171] = gr_complex(  3*level, -3*level);
	d_constellation[175] = gr_complex(  5*level, -3*level);
	d_constellation[167] = gr_complex(  7*level, -3*level);
	d_constellation[165] = gr_complex(  9*level, -3*level);
	d_constellation[173] = gr_complex( 11*level, -3*level);
	d_constellation[169] = gr_complex( 13*level, -3*level);
	d_constellation[161] = gr_complex( 15*level, -3*level);

	d_constellation[ 35] = gr_complex(  1*level, -1*level);
	d_constellation[ 43] = gr_complex(  3*level, -1*level);
	d_constellation[ 47] = gr_complex(  5*level, -1*level);
	d_constellation[ 39] = gr_complex(  7*level, -1*level);
	d_constellation[ 37] = gr_complex(  9*level, -1*level);
	d_constellation[ 45] = gr_complex( 11*level, -1*level);
	d_constellation[ 41] = gr_complex( 13*level, -1*level);
	d_constellation[ 33] = gr_complex( 15*level, -1*level);

	d_rotational_symmetry = 4;
	d_dimensionality = 1;
	calc_arity();
}

constellation_256qam_impl::~constellation_256qam_impl() {
}

unsigned int
constellation_256qam_impl::decision_maker(const gr_complex *sample) {
	unsigned int ret = 0;
	const float level = sqrt(float(1/170.0));
	float re = sample->real();
	float im = sample->imag();

	ret |= re > 0; //b0
	ret |= (std::abs(re) < (8*level)) << 1; //b1
	ret |= (std::abs(re) < (12*level) && std::abs(re) > (4*level)) << 2; //b2
	ret |= ((std::abs(re) < (6*level) && std::abs(re) > (2*level)) ||
	        (std::abs(re) < (14*level) && std::abs(re) > (10*level)))  << 3; //b3
	ret |= (im > 0 ) << 4; //b4
	ret |= (std::abs(im) < (8*level)) << 5; //b5
	ret |= (std::abs(im) < (12*level) && std::abs(im) > (4*level)) << 6; //b6
	ret |= (std::abs(im) < (6*level) && std::abs(im) > (2*level) ||
         (std::abs(im) < (14*level) && std::abs(im) > (10*level))) << 7; //b7

	return ret;
}
/**********************************************************/

constellation_qpsk::sptr
constellation_qpsk::make() {
	return constellation_qpsk::sptr(new constellation_qpsk_impl());
}

constellation_qpsk::constellation_qpsk() {}

constellation_qpsk_impl::constellation_qpsk_impl() {
	const float level = sqrt(float(0.5));
	d_constellation.resize(4);
	// Gray-coded
	d_constellation[0] = gr_complex(-level, -level);
	d_constellation[1] = gr_complex( level, -level);
	d_constellation[2] = gr_complex(-level,  level);
	d_constellation[3] = gr_complex( level,  level);

	d_rotational_symmetry = 4;
	d_dimensionality = 1;
	calc_arity();
}

constellation_qpsk_impl::~constellation_qpsk_impl() {
}

unsigned int
constellation_qpsk_impl::decision_maker(const gr_complex *sample) {
	return 2*(imag(*sample)>0) + (real(*sample)>0);
}


/**********************************************************/

constellation_16qam::sptr
constellation_16qam::make() {
	return constellation_16qam::sptr(new constellation_16qam_impl());
}

constellation_16qam::constellation_16qam() {}

constellation_16qam_impl::constellation_16qam_impl()
{
	const float level = sqrt(float(0.1));
	d_constellation.resize(16);

	d_constellation[ 0] = gr_complex(-3*level,-3*level);
	d_constellation[ 1] = gr_complex( 3*level,-3*level);
	d_constellation[ 2] = gr_complex(-1*level,-3*level);
	d_constellation[ 3] = gr_complex( 1*level,-3*level);
	d_constellation[ 4] = gr_complex(-3*level, 3*level);
	d_constellation[ 5] = gr_complex( 3*level, 3*level);
	d_constellation[ 6] = gr_complex(-1*level, 3*level);
	d_constellation[ 7] = gr_complex( 1*level, 3*level);
	d_constellation[ 8] = gr_complex(-3*level,-1*level);
	d_constellation[ 9] = gr_complex( 3*level,-1*level);
	d_constellation[10] = gr_complex(-1*level,-1*level);
	d_constellation[11] = gr_complex( 1*level,-1*level);
	d_constellation[12] = gr_complex(-3*level, 1*level);
	d_constellation[13] = gr_complex( 3*level, 1*level);
	d_constellation[14] = gr_complex(-1*level, 1*level);
	d_constellation[15] = gr_complex( 1*level, 1*level);

	d_rotational_symmetry = 4;
	d_dimensionality = 1;
	calc_arity();
}

constellation_16qam_impl::~constellation_16qam_impl() {
}

unsigned int
constellation_16qam_impl::decision_maker(const gr_complex *sample)
{
	unsigned int ret = 0;
	const float level = sqrt(float(0.1));
	float re = sample->real();
	float im = sample->imag();

	ret |= re > 0;
	ret |= (std::abs(re) < (2*level)) << 1;
	ret |= (im > 0) << 2;
	ret |= (std::abs(im) < (2*level)) << 3;

	return ret;
}


/**********************************************************/

constellation_64qam::sptr
constellation_64qam::make() {
	return constellation_64qam::sptr(new constellation_64qam_impl());
}

constellation_64qam::constellation_64qam() {}

constellation_64qam_impl::constellation_64qam_impl() {
	const float level = sqrt(float(1/42.0));
	d_constellation.resize(64);

	d_constellation[ 0] = gr_complex(-7*level,-7*level);
	d_constellation[ 1] = gr_complex( 7*level,-7*level);
	d_constellation[ 2] = gr_complex(-1*level,-7*level);
	d_constellation[ 3] = gr_complex( 1*level,-7*level);
	d_constellation[ 4] = gr_complex(-5*level,-7*level);
	d_constellation[ 5] = gr_complex( 5*level,-7*level);
	d_constellation[ 6] = gr_complex(-3*level,-7*level);
	d_constellation[ 7] = gr_complex( 3*level,-7*level);
	d_constellation[ 8] = gr_complex(-7*level, 7*level);
	d_constellation[ 9] = gr_complex( 7*level, 7*level);
	d_constellation[10] = gr_complex(-1*level, 7*level);
	d_constellation[11] = gr_complex( 1*level, 7*level);
	d_constellation[12] = gr_complex(-5*level, 7*level);
	d_constellation[13] = gr_complex( 5*level, 7*level);
	d_constellation[14] = gr_complex(-3*level, 7*level);
	d_constellation[15] = gr_complex( 3*level, 7*level);
	d_constellation[16] = gr_complex(-7*level,-1*level);
	d_constellation[17] = gr_complex( 7*level,-1*level);
	d_constellation[18] = gr_complex(-1*level,-1*level);
	d_constellation[19] = gr_complex( 1*level,-1*level);
	d_constellation[20] = gr_complex(-5*level,-1*level);
	d_constellation[21] = gr_complex( 5*level,-1*level);
	d_constellation[22] = gr_complex(-3*level,-1*level);
	d_constellation[23] = gr_complex( 3*level,-1*level);
	d_constellation[24] = gr_complex(-7*level, 1*level);
	d_constellation[25] = gr_complex( 7*level, 1*level);
	d_constellation[26] = gr_complex(-1*level, 1*level);
	d_constellation[27] = gr_complex( 1*level, 1*level);
	d_constellation[28] = gr_complex(-5*level, 1*level);
	d_constellation[29] = gr_complex( 5*level, 1*level);
	d_constellation[30] = gr_complex(-3*level, 1*level);
	d_constellation[31] = gr_complex( 3*level, 1*level);
	d_constellation[32] = gr_complex(-7*level,-5*level);
	d_constellation[33] = gr_complex( 7*level,-5*level);
	d_constellation[34] = gr_complex(-1*level,-5*level);
	d_constellation[35] = gr_complex( 1*level,-5*level);
	d_constellation[36] = gr_complex(-5*level,-5*level);
	d_constellation[37] = gr_complex( 5*level,-5*level);
	d_constellation[38] = gr_complex(-3*level,-5*level);
	d_constellation[39] = gr_complex( 3*level,-5*level);
	d_constellation[40] = gr_complex(-7*level, 5*level);
	d_constellation[41] = gr_complex( 7*level, 5*level);
	d_constellation[42] = gr_complex(-1*level, 5*level);
	d_constellation[43] = gr_complex( 1*level, 5*level);
	d_constellation[44] = gr_complex(-5*level, 5*level);
	d_constellation[45] = gr_complex( 5*level, 5*level);
	d_constellation[46] = gr_complex(-3*level, 5*level);
	d_constellation[47] = gr_complex( 3*level, 5*level);
	d_constellation[48] = gr_complex(-7*level,-3*level);
	d_constellation[49] = gr_complex( 7*level,-3*level);
	d_constellation[50] = gr_complex(-1*level,-3*level);
	d_constellation[51] = gr_complex( 1*level,-3*level);
	d_constellation[52] = gr_complex(-5*level,-3*level);
	d_constellation[53] = gr_complex( 5*level,-3*level);
	d_constellation[54] = gr_complex(-3*level,-3*level);
	d_constellation[55] = gr_complex( 3*level,-3*level);
	d_constellation[56] = gr_complex(-7*level, 3*level);
	d_constellation[57] = gr_complex( 7*level, 3*level);
	d_constellation[58] = gr_complex(-1*level, 3*level);
	d_constellation[59] = gr_complex( 1*level, 3*level);
	d_constellation[60] = gr_complex(-5*level, 3*level);
	d_constellation[61] = gr_complex( 5*level, 3*level);
	d_constellation[62] = gr_complex(-3*level, 3*level);
	d_constellation[63] = gr_complex( 3*level, 3*level);

	d_rotational_symmetry = 4;
	d_dimensionality = 1;
	calc_arity();
}

constellation_64qam_impl::~constellation_64qam_impl() {
}

unsigned int
constellation_64qam_impl::decision_maker(const gr_complex *sample) {
	unsigned int ret = 0;
	const float level = sqrt(float(1/42.0));
	float re = sample->real();
	float im = sample->imag();

	ret |= re > 0;
	ret |= (std::abs(re) < (4*level)) << 1;
	ret |= (std::abs(re) < (6*level) && std::abs(re) > (2*level)) << 2;
	ret |= (im > 0) << 3;
	ret |= (std::abs(im) < (4*level)) << 4;
	ret |= (std::abs(im) < (6*level) && std::abs(im) > (2*level)) << 5;

	return ret;
}
