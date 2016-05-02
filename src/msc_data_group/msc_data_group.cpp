
#include <bitset>

#include "msc_data_group/msc_data_group.h"
#include "util/crc16.h"
#include "util/vector_helpers.h"
#include "common/common_types.h"
#include "common/common_literals.h"
#include "constants/msc_data_group_constants.h"


namespace dabip {

  using namespace binary;

  byte_vector_t build_header()
    {
    auto header = byte_vector_t(2);
    header[0]  = 0 << 7;  //Extension flag
    header[0] |= 1 << 6;  //CRC flag
    header[0] |= 0 << 5;  //Segmentation flag
    header[0] |= 0 << 4;  //User access flag
    header[1]  = constants::kDataGroupTypes[0];    //Data group type
    header[1] |= m_continuity_index << 4; //Continuity index
    header[1] |= m_repetition_index;      //Repetition index
    return header;
    }

  byte_vector_t msc_data_group_generator::build(byte_vector_t & ip_datagram)
    {
    if(ip_datagram != m_last_ip_datagram)
      {
      m_continuity_index = (m_continuity_index + 1) % 16;
      m_repetition_index = 0;
      }
    else
      {
      m_repetition_index > 0 ? m_repetition_index-- : m_repetition_index = 0;
      }
    m_last_ip_datagram = ip_datagram;
    auto header = build_header();
    concat_vectors_inplace(header, ip_datagram);
    auto crc = genCRC16(header);
    concat_vectors_inplace(header, crc);
    return header;
    }

// TODO handle failed CRC ignore group??
  pair_complete_vector_t parse(byte_vector_t & msc_data_group)
    {
    byte_vector_t msc_dg_without_crc {msc_data_group};
    std::uint8_t header_size {2};
    auto first_header = std::bitset<8>{msc_data_group[0]};
    std::bitset<16> segment_field;
    if(first_header[6]) //CRC flag
      {
      auto parts = split_vector(msc_data_group, msc_data_group.size()-2);
      if(genCRC16(parts.first)!=parts.second)
        {
        m_valid = false;
        m_ip_datagram.clear();
        //TODO set segmentation false
        return pair_complete_vector_t{true, byte_vector_t{}};
        }
      else
        {
        m_valid = true;
        msc_dg_without_crc = parts.first;
        }
      }
    else
      {
      m_valid = true;
      msc_dg_without_crc = msc_data_group;
      }
    if(first_header[7]) //Extension flag
      {
      header_size = 4;
      }
    if(first_header[5]) //Segment flag
      {
      std::uint16_t segment_field_int = msc_dg_without_crc[header_size] << 8 | msc_dg_without_crc[header_size+1];
      segment_field = std::bitset<16>{segment_field_int};
      if(segment_field[15]) //Last segment flag
        {
        m_segmented = false;
        }
      //TODO track segment number
      header_size += 2;
      }
    if(first_header[4]) //User access flag
      {
      header_size += msc_dg_without_crc[header_size] & 1111_b;
      }
    auto data_field = split_vector(msc_dg_without_crc, header_size).second;
    auto ip_datagram = concat_vectors(m_ip_datagram, data_field);
    //Data group type ignored
    std::int8_t continuity_index = msc_data_group[1] << 4;
    m_continuity_index_difference = (continuity_index - (m_last_continuity_index + 1))%16;
    m_last_continuity_index = continuity_index;
    //Repetition index ignored
    //Extension field ignored
    if(m_segmented)
      {
      concat_vectors_inplace(m_ip_datagram, ip_datagram);
      return pair_complete_vector_t{false, byte_vector_t{}};
      }
    else
      {
      m_ip_datagram.clear();
      return pair_complete_vector_t{true, ip_datagram};
      }
    }

  std::uint8_t msc_data_group_parser::no_of_missing_data_groups() const
    {
    return m_continuity_index_difference;
    }

  bool msc_data_group_parser::is_valid() const
    {
    return m_valid;
    }
}
