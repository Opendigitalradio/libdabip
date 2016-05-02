#include <bitset>
#include <cstdint>

#include "util/crc16.h"
#include "util/vector_helpers.h"
#include "packet/packet.h"
#include "common/common_types.h"
#include "constants/packet_constants.h"

namespace dabip {

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
      auto hd_packets = assemble(parts.first, packet_length);
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
    concat_vectors_inplace(packets, byte_vector_t(packet_length - 5 -msc_data_group.size(), 0x00)); //Padding
    auto crc = genCRC16(packets);
    concat_vectors_inplace(packets, crc);
    return packets;
    }


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
    auto parts = split_vector(packet, packet.size()-2);
    std::uint8_t useful_data_lenght = packet[2] & 1111111_b;
    auto data_field = split_vector(parts.first, 3).second;
    auto useful_data_field = split_vector(data_field, useful_data_lenght).first;
    if(genCRC16(parts.first) != parts.second)
      {
      m_group_valid = false;
      return pair_status_vector_t{parse_status::invalid_crc, byte_vector_t{}};
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
        if(!m_group_valid)
          {
          return pair_status_vector_t{parse_status::segment_lost, byte_vector_t{}};
          }
        else
          {
          concat_vectors_inplace(m_msc_data_group, useful_data_field);
          return pair_status_vector_t{parse_status::ok, m_msc_data_group};
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
        concat_vectors_inplace(m_msc_data_group, useful_data_field);
        return pair_status_vector_t{parse_status::incomplete, byte_vector_t{}};
        }
      }

    }

  bool packet_parser::is_valid() const
    {
    return m_group_valid;
    }

}
