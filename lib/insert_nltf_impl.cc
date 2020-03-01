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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "insert_nltf_impl.h"

namespace gr {
namespace ieee802_11 {
insert_nltf::sptr
insert_nltf::make(int fft_len,
                  bool s1g_cap,
                  const std::string& len_tag_key)
{
  return gnuradio::get_initial_sptr
    (new insert_nltf_impl(fft_len,
                          s1g_cap,
                          len_tag_key));
}
/*
 * The private constructor
 */
insert_nltf_impl::insert_nltf_impl(
                  int fft_len,
                  bool s1g_cap,
                  const std::string& len_tag_key)
  : gr::tagged_stream_block("insert_nltf",
          gr::io_signature::make(1, 1, sizeof(gr_complex)*fft_len),
          gr::io_signature::make(1, 1, sizeof(gr_complex)*fft_len),
          len_tag_key),
    d_fft_len(fft_len),
    d_s1g_cap(s1g_cap)
{
  // d_output_size = fft_len;// * d_ltf_sync_word.size();
  // set_output_multiple(d_output_size);

}
/*
 * Our virtual destructor.
 */
insert_nltf_impl::~insert_nltf_impl()
{
}
int
insert_nltf_impl::calculate_output_stream_length(const gr_vector_int &ninput_items)
{
  int noutput_items = 0;
  if(d_s1g_cap){
    noutput_items = ninput_items[0] + 2;
  } else{
    noutput_items = ninput_items[0];
    std::cout << "calculate_output_stream_length: " << ninput_items[0] << std::endl;
  }
  return noutput_items;
}


int
insert_nltf_impl::work (int noutput_items,
                   gr_vector_int &ninput_items,
                   gr_vector_const_void_star &input_items,
                   gr_vector_void_star &output_items)
{
  const gr_complex *in= (const gr_complex *) input_items[0];
  gr_complex *out = (gr_complex *) output_items[0];

  gr_complex *nltf_sync = (gr_complex *)malloc(sizeof(gr_complex) * d_fft_len * 2);

  int symbols_to_read = 0;
  symbols_to_read = ninput_items[0];

  std::cout << "ninput_items[0]: " << ninput_items[0] << std::endl;
  std::cout << "noutput_items: " << noutput_items << std::endl;

  //memset((void*)out, 0x00, sizeof(gr_complex) * d_fft_len * noutput_items);
  if(!d_s1g_cap){ // S1G disabled
    // bypass symbols
    for (int i = 0; i < symbols_to_read; i++) {
        memcpy((void*)out, (void*)in, d_fft_len * sizeof(gr_complex));
        // out[i]=in[i];
        in += d_fft_len;
        out += d_fft_len;
    }
  }else{ // S1G enabled
    // bypass sync + signal symbols (S1G_SHORT Format)
    for (int sym_idx = 0; sym_idx < 6; sym_idx++) {
        memcpy((void*)out, (void*)in, d_fft_len * sizeof(gr_complex));

        // copy ltf symbols
        if(sym_idx == 2){
            memcpy((void*)nltf_sync, (void*)in, sizeof(gr_complex) * d_fft_len * 2);
            //memset((void*)nltf_sync, 0, sizeof(gr_complex) * d_fft_len * 2);
        }

        in += d_fft_len;
        out += d_fft_len;
    }
    // copy nltf_sync word
    memcpy((void*)out, (void*)nltf_sync, sizeof(gr_complex) * d_fft_len * 2);
    out += 2 * d_fft_len;

    // bypass symbols
    for (int sym_idx = 6; sym_idx < symbols_to_read; sym_idx++) {
        memcpy((void*)(out), (void*)in, d_fft_len * sizeof(gr_complex));

        in += d_fft_len;
        out += d_fft_len;
    }


  }
  // add tags
  std::vector<tag_t> tags;
  get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + symbols_to_read);
  for (unsigned i = 0; i < tags.size(); i++) {
      tags[i].offset =
          ((tags[i].offset - nitems_read(0)) * d_output_size) + nitems_written(0);
      add_item_tag(0, tags[i].offset, tags[i].key, tags[i].value);
  }

  // Tell runtime system how many output items we produced.
  if(!d_s1g_cap){
    return symbols_to_read;
  }else{
    return symbols_to_read + 2;
  }
}

void
insert_nltf_impl::enable_s1g(bool s1g_cap){
	gr::thread::scoped_lock lock(d_mutex);
	d_s1g_cap = s1g_cap;
}

} /* namespace ieee802_11 */
} /* namespace gr */
