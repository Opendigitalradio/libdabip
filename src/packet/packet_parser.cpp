/*
 * Copyright (C) 2017 Opendigitalradio (http://www.opendigitalradio.org/)
 * Copyright (C) 2017 Felix Morgner <felix.morgner@hsr.ch>
 * Copyright (C) 2017 Tobias Stauber <tobias.stauber@hsr.ch>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "dab/util/crc16.h"
#include "dab/util/vector_helpers.h"
#include "dab/packet/packet_parser.h"
#include "dab/constants/packet_constants.h"

#include <dab/types/common_types.h>
#include <dab/literals/binary_literal.h>

#include <bitset>
#include <cstdint>

namespace dab {

  using namespace internal;
  using namespace literals;

  packet_parser::packet_parser(std::uint16_t address): kAddress{address}
    {
    }

  pair_status_vector_t packet_parser::parse(byte_vector_t & packet)
    {
    std::bitset<6> header_flags(packet[0] >> 2);
    std::uint16_t address = (packet[0] & 11_b) << 8 | packet[1];
    if(address != kAddress)
      {
      return pair_status_vector_t{parse_status::invalid_address, byte_vector_t{}};
      }
    auto size_factor = (header_flags[5] << 1) + header_flags[4];

    auto plength = constants::kPacketLengths[size_factor];
    packet.resize(plength);

    auto parts = split_vector(packet, packet.size()-2);
    std::uint8_t useful_data_lenght = packet[2] & 1111111_b;

    if(useful_data_lenght > constants::kPacketDataLengths[size_factor])
      {
      return pair_status_vector_t{parse_status::invalid_crc, byte_vector_t{}};
      }

    auto data_field = split_vector(parts.first, 3).second;
    auto useful_data_field = split_vector(data_field, useful_data_lenght).first;
    if(genCRC16(parts.first) != parts.second)
      {
      m_group_valid = false;
      return pair_status_vector_t{parse_status::invalid_crc, byte_vector_t{}};
      }
    std::int8_t continuity_index = (packet[0] & 00110000_b) >> 4;
    if(m_last_continuity_index == -1) //Status before initialization
      {
      m_continuity_index_difference = 1;
      }
    else
      {
      m_continuity_index_difference = (continuity_index - m_last_continuity_index)%16;
      }
    if(m_continuity_index_difference != 1)
      {
      m_group_valid = false;
      return pair_status_vector_t{parse_status::segment_lost, byte_vector_t{}};
      }
    if(header_flags[0]) //Last flag
      {
      if(header_flags[1]) //First flag
        {
        m_group_valid = true;
        m_msc_data_group = useful_data_field;
        return pair_status_vector_t{parse_status::ok, useful_data_field};
        }
      else
        {
        if(m_group_valid)
          {
          concat_vectors_inplace(m_msc_data_group, useful_data_field);
          return pair_status_vector_t{parse_status::ok, m_msc_data_group};
          }
        else
          {
          return pair_status_vector_t{parse_status::segment_lost, byte_vector_t{}};
          }
        }
      }
    else //Last flag not set
      {
      if(header_flags[1]) //First flag
        {
        m_group_valid = true;
        m_msc_data_group = useful_data_field;
        return pair_status_vector_t{parse_status::incomplete, byte_vector_t{}};
        }
      else //Intermediate packet
        {
        if(m_group_valid)
          {
          concat_vectors_inplace(m_msc_data_group, useful_data_field);
          return pair_status_vector_t{parse_status::incomplete, byte_vector_t{}};
          }
        else
          {
          return pair_status_vector_t{parse_status::segment_lost, byte_vector_t{}};
          }
        }
      }

    }

  bool packet_parser::is_valid() const
    {
    return m_group_valid;
    }

  std::uint8_t packet_parser::no_of_missing_packets() const
    {
    return m_continuity_index_difference;
    }

  std::vector<byte_vector_t> split_packets(byte_vector_t & packets)
    {
    auto local_packets = packets;
    std::vector<byte_vector_t> splitted {};
    while( local_packets.size() > 0 )
      {
      auto packet_len = ((local_packets[0]>>6)+1)*24;
      auto parts = split_vector(local_packets, packet_len);
      local_packets = parts.second;
      splitted.push_back(parts.first);
      }
    return splitted;
    }

}
