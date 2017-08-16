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
#include "dab/packet/packet_generator.h"
#include "dab/constants/packet_constants.h"

#include <dab/types/common_types.h>
#include <dab/literals/binary_literal.h>

#include <cstdint>

namespace dab
  {

  using namespace internal;
  using namespace literals;

  packet_generator::packet_generator(std::uint16_t address) : kAddress{address}
    {
    }

  byte_vector_t packet_generator::build(byte_vector_t & msc_data_group)
    {
    auto len = msc_data_group.size();

    if(len > constants::kPacketDataLengths[3])
      {
      auto packet_length = constants::kPacketDataLengths[3];
      if(m_first_last == 01_b || m_first_last == 11_b)
        {
        m_first_last = 10_b;
        }
      else if(m_first_last == 10_b)
        {
        m_first_last = 00_b;
        }
      auto parts = split_vector(msc_data_group, packet_length);
      auto hd_packets = assemble(parts.first, packet_length+5);
      auto tl_packets = build(parts.second);

      concat_vectors_inplace(hd_packets, tl_packets);
      return hd_packets;
      }
    else if (len > constants::kPacketDataLengths[2])
      {
      set_first_last();
      return assemble(msc_data_group, constants::kPacketLengths[3]);
      }
    else if (len > constants::kPacketDataLengths[1])
      {
      set_first_last();
      return assemble(msc_data_group, constants::kPacketLengths[2]);
      }
    else if (len > constants::kPacketDataLengths[0])
      {
      set_first_last();
      return assemble(msc_data_group, constants::kPacketLengths[1]);
      }
    else
      {
      set_first_last();
      return assemble(msc_data_group, constants::kPacketLengths[0]);

      }

    }

  byte_vector_t packet_generator::build_header(std::uint8_t const packet_length, std::uint8_t const useful_data_lenght)
    {
    auto header = byte_vector_t{0, 0, 0};
    // Packet length:
    switch(packet_length)
      {
      case constants::kPacketLengths[3]:
        header[0] = 11000000_b;
        break;
      case constants::kPacketLengths[2]:
        header[0] = 10000000_b;
        break;
      case constants::kPacketLengths[1]:
        header[0] = 01000000_b;
        break;
      case constants::kPacketLengths[0]:
        header[0] = 00000000_b;
        break;
      }
    // Continuity index:
    header[0] |= m_continuity_index << 4;
    m_continuity_index = (m_continuity_index + 1)%4;
    // First/Last:
    header[0] |= m_first_last << 2;
    // Address:
    header[0] |= 00000011_b & (kAddress >> 8);
    header[1] = kAddress;
    // Command:
    header[2] = 0_b << 7;
    // Useful data length:
    header[2] |= useful_data_lenght;
    return header;
    }

  void packet_generator::set_first_last()
    {
    if(m_first_last == 00_b || m_first_last == 10_b)
      {
      m_first_last = 01_b;
      }
    else
      {
      m_first_last = 11_b;
      }
    }

  byte_vector_t packet_generator::assemble(byte_vector_t & msc_data_group, std::uint8_t packet_length)
    {
    auto packets = byte_vector_t(0);
    auto header = build_header(packet_length, msc_data_group.size());
    concat_vectors_inplace(packets, header, msc_data_group);
    concat_vectors_inplace(packets, byte_vector_t(packet_length - 5 - msc_data_group.size(), 0x00)); //Padding
    auto crc = genCRC16(packets);
    concat_vectors_inplace(packets, crc);
    return packets;
    }
}
