#include <bitset>

#include <types/common_types.h>
#include <literals/binary_literal.h>

#include "msc_data_group/msc_data_group_generator.h"
#include "util/crc16.h"
#include "util/vector_helpers.h"
#include "constants/msc_data_group_constants.h"


namespace dab
  {

  using namespace __internal_dabip;

  byte_vector_t msc_data_group_generator::build_header()
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
  }
