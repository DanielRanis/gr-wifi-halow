/* -*- c++ -*- */
/*
 * Copyright 2020 Daniel Ranisavljevic.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_IEEE802_11_INSERT_NLTF_IMPL_H
#define INCLUDED_IEEE802_11_INSERT_NLTF_IMPL_H

#include <ieee802-11/insert_nltf.h>

namespace gr {
namespace ieee802_11 {
class insert_nltf_impl : public insert_nltf
{
private:
  bool d_s1g_cap;
  const int d_fft_len;
  int d_output_size;
  gr::thread::mutex d_mutex;


protected:
  int calculate_output_stream_length(const gr_vector_int &ninput_items);

public:
  insert_nltf_impl(int fft_len,
                   bool s1g_cap,
                   const std::string& len_tag_key);
  ~insert_nltf_impl();
  // Where all the action really happens
  int work(int noutput_items,
      gr_vector_int &ninput_items,
      gr_vector_const_void_star &input_items,
      gr_vector_void_star &output_items);

  virtual void enable_s1g(bool s1g_cap);

};
} // namespace ieee802_11
} // namespace gr

#endif /* INCLUDED_IEEE802-11_INSERT_NLTF_IMPL_H */
