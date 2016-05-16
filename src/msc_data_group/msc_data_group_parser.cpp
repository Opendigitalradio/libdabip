#include <bitset>

#include <types/common_types.h>
#include <literals/binary_literal.h>

#include "msc_data_group/msc_data_group_parser.h"
#include "util/crc16.h"
#include "util/vector_helpers.h"
#include "constants/msc_data_group_constants.h"


namespace dab {

  using namespace types;
  using namespace __internal_dabip;
  using namespace __internal_common::literals;

  pair_status_vector_t msc_data_group_parser::parse(byte_vector_t & msc_data_group)
    {
    byte_vector_t msc_dg_without_crc {msc_data_group};
    std::uint8_t header_size {2};
    auto header_flags = std::bitset<8>{msc_data_group[0]};

    if(m_start_new)
      {
      m_group_valid = true;
      m_ip_datagram.clear();
      }

    if(header_flags[7]) //Extension flag set
      {
      header_size +=2;
      //Extension field handling not jet implemented
      }

    if(header_flags[6]) //CRC flag set
      {
      auto parts = split_vector(msc_data_group, msc_data_group.size()-2);
      if(genCRC16(parts.first)==parts.second)
        {
        if(!m_segmented)
          {
          m_start_new = true;
          }
        msc_dg_without_crc = parts.first;
        }
      else
        {
        m_group_valid = false;
        m_ip_datagram.clear();
        return pair_status_vector_t{parse_status::invalid_crc, byte_vector_t{}};
        }
      }

    if(header_flags[5]) //Segment flag set
      {
      std::uint16_t segment_number = (msc_dg_without_crc[header_size] & 01111111_b) << 8 | msc_dg_without_crc[header_size+1];
      if(!m_start_new && segment_number <= m_last_segment_number)
        {
        //Somehow unpredicted a new session started, maybe last segment got lost...
        m_ip_datagram.clear();
        m_group_valid = true;
        //Maybe unusable in the end
        }
      if((msc_dg_without_crc[header_size] & 10000000_b) >> 7) //Last flag set
        {
        m_segmented = false;
        m_last_segment_number = 0;
        }
      else //Last flag not set
        {
        m_segmented = true;
        if(segment_number != m_last_segment_number + 1)
          {
          m_group_valid = false;
          return pair_status_vector_t{parse_status::segment_lost, byte_vector_t{}};
          }
        m_last_segment_number = segment_number;
        }
      header_size += 2;
      }
    else //Segment flag not set
      {
      m_start_new = true;
      m_segmented = false;
      m_group_valid = true;
      m_ip_datagram.clear();
      }

    if(header_flags[4]) //User access flag
      {
      header_size += (msc_dg_without_crc[header_size] & 1111_b) + 1;
      //Ignored apart of header size
      }

    //Data group type ignored

    std::int8_t continuity_index = msc_data_group[1] >> 4;
    if(m_last_continuity_index == -1)
      {
      m_continuity_index_difference = 1;
      }
    else
      {
      m_continuity_index_difference = (continuity_index - m_last_continuity_index)%16;
      }
    m_last_continuity_index = continuity_index;
    if(m_continuity_index_difference != 1)
      {
      m_group_valid = false;
      return pair_status_vector_t{parse_status::segment_lost, byte_vector_t{}};
      }

    //Repetition index ignored

    auto data_field = split_vector(msc_dg_without_crc, header_size).second;
    concat_vectors_inplace(m_ip_datagram, data_field);

    if(m_segmented)
      {
      if(m_group_valid)
        {
        return pair_status_vector_t{parse_status::segment_lost, byte_vector_t{}};
        }
      return pair_status_vector_t{parse_status::incomplete, byte_vector_t{}};
      }
    else
      {
      return pair_status_vector_t{parse_status::ok, m_ip_datagram};
      }
    }

  std::uint8_t msc_data_group_parser::no_of_missing_data_groups() const
    {
    return m_continuity_index_difference;
    }

  bool msc_data_group_parser::is_valid() const
    {
    return m_group_valid;
    }
}
