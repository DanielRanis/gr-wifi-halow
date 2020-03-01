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
#ifndef INCLUDED_IEEE802_11_MAPPER_H
#define INCLUDED_IEEE802_11_MAPPER_H

#include <ieee802-11/api.h>
#include <gnuradio/block.h>

enum Encoding {
	BPSK_1_2  = 0,
	BPSK_3_4  = 1,
	QPSK_1_2  = 2,
	QPSK_3_4  = 3,
	QAM16_1_2 = 4,
	QAM16_3_4 = 5,
	QAM64_2_3 = 6,
	QAM64_3_4 = 7,
};

enum S1g_encoding {
	S1G_BPSK_1_2 = 0,
	S1G_QPSK_1_2 = 1,
	S1G_QPSK_3_4 = 2,
	S1G_16QAM_1_2 = 3,
	S1G_16QAM_3_4 = 4,
	S1G_64QAM_2_3 = 5,
	S1G_64QAM_3_4 = 6,
	S1G_64QAM_5_6 = 7,
	S1G_256QAM_3_4 = 8,
	S1G_256QAM_5_6 = 9,
	S1G_BPSK_REP_1_2 = 10,
};

enum S1g_ppdu_format {
	S1G_SHORT = 0,
	S1G_1M = 1,
};

enum S1g_cw {
	S1G_CW_1M = 1,
	S1G_CW_2M = 2,
};

namespace gr {
namespace ieee802_11 {

class IEEE802_11_API mapper : virtual public block
{
public:

	typedef boost::shared_ptr<mapper> sptr;
	static sptr make(Encoding e, bool debug = false, S1g_ppdu_format s1g_format = S1G_SHORT,
		               S1g_encoding s1g_enc = S1G_BPSK_1_2, S1g_cw s1g_cw = S1G_CW_1M, bool s1g_cap = false);
	virtual void set_encoding(Encoding mcs) = 0;
	virtual void enable_s1g(bool s1g_cap) = 0;
	virtual void set_s1g_encoding(S1g_encoding mcs) = 0;
	virtual void set_frame_format(S1g_ppdu_format s1g_format) = 0;
	virtual void set_s1g_cw(S1g_cw cw) = 0;
};

}  // namespace ieee802_11
}  // namespace gr

#endif /* INCLUDED_IEEE802_11_MAPPER_H */
