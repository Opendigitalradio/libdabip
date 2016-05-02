
#include "util/crc16.h"
#include "util/vector_helpers.h"
#include "packet/packet.h"
#include "common/common_types.h"
#include "constants/packet_constants.h"

namespace dabip {

  byte_vector_t packet_generator::build(byte_vector_t & msc_data_group)
    {
    auto len = msc_data_group.size();

    if(len > constants::kPacketDataLengths[3])
      {
      auto packet_length = constants::kPacketDataLengths[3];
      if(packet_generator::m_first_last == 01_b || packet_generator::m_first_last == 11_b)
        {
        packet_generator::m_first_last = 10_b;
        }
      else if(packet_generator::m_first_last == 10_b)
        {
        packet_generator::m_first_last = 00_b;
        }
      auto parts = split_vector(msc_data_group, packet_length);
      auto hd_packets = packet_generator::assemble(parts.first, packet_length);
      auto tl_packets = packet_generator::build(parts.second);
      return concat_vectors(hd_packets, tl_packets);
      }
    else if (len > constants::kPacketDataLengths[2])
      {
      packet_generator::set_first_last();
      return packet_generator::assemble(msc_data_group, constants::kPacketLengths[3]);
      }
    else if (len > constants::kPacketDataLengths[1])
      {
      packet_generator::set_first_last();
      return packet_generator::assemble(msc_data_group, constants::kPacketLengths[2]);
      }
    else if (len > constants::kPacketDataLengths[0])
      {
      packet_generator::set_first_last();
      return packet_generator::assemble(msc_data_group, constants::kPacketLengths[1]);
      }
    else
      {
      packet_generator::set_first_last();
      return packet_generator::assemble(msc_data_group, constants::kPacketLengths[0]);

      }

    }

  byte_vector_t packet_generator::build_header(std::uint8_t const packet_length, std::uint8_t const useful_data_lenght)
    {
    auto header = byte_vector_t{0, 0, 0};
    // Packet length:
    switch(packet_length)
      {
      case constants::kPacketLengths[3]:
        header[0] = 11_b;
        break;
      case constants::kPacketLengths[2]:
        header[0] = 10_b;
        break;
      case constants::kPacketLengths[1]:
        header[0] = 01_b;
        break;
      case constants::kPacketLengths[0]:
        header[0] = 00_b;
        break;
      }
    // Continuity index:
    header[0] |= packet_generator::m_continuity_index << 4;
    packet_generator::m_continuity_index = (packet_generator::m_continuity_index + 1)%4;
    // First/Last:
    header[0] |= packet_generator::m_first_last << 2;
    // Address:
    header[0] |= 00000011_b & (packet_generator::kAddress >> 8);
    header[1] = packet_generator::kAddress;
    // Command:
    header[2] = 0_b << 7;
    // Useful data length:
    header[2] |= useful_data_lenght;
    return header;
    }

  void packet_generator::set_first_last()
    {
    if(packet_generator::m_first_last == 00_b || packet_generator::m_first_last == 10_b)
      {
      packet_generator::m_first_last = 01_b;
      }
    else
      {
      packet_generator::m_first_last = 11_b;
      }
    }

  byte_vector_t packet_generator::assemble(byte_vector_t & msc_data_group, std::uint8_t packet_length)
    {
    auto packets = byte_vector_t(packet_length);
    auto header = packet_generator::build_header(packet_length, msc_data_group.size());

    concat_vectors_inplace(packets, header, msc_data_group);
    auto crc = genCRC16(packets);
    packets.reserve(packets.size()+2);
    return concat_vectors(packets, crc);
    }




}
