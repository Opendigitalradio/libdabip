

#include "msc_data_group/msc_data_group.h"
#include "util/crc16.h"
#include "util/vector_helpers.h"
#include "common/common_types.h"



namespace dabip {

  byte_vector_t msc_data_group_generator::build_msc_data_group_header()
    {
    auto header = byte_vector_t(2);
    header[0]  = 1 << 7;  //Extension flag
    header[0] |= 1 << 6;  //CRC flag
    header[0] |= 0 << 5;  //Segmentation flag
    header[0] |= 0 << 4;  //User access flag
    header[1]  = msc_data_group_generator::kdata_group_types[0];    //Data group type
    header[1] |= msc_data_group_generator::m_continuity_index << 4; //Continuity index
    header[1] |= msc_data_group_generator::m_repetition_index;      //Repetition index
    return header;
    }

  byte_vector_t msc_data_group_generator::build_msc_data_group(byte_vector_t & ip_datagram)
    {
    if(ip_datagram != msc_data_group_generator::m_last_ip_datagram)
      {
      msc_data_group_generator::m_continuity_index = (msc_data_group_generator::m_continuity_index + 1) % 16;
      msc_data_group_generator::m_repetition_index = 0;
      }
    else
      {
      msc_data_group_generator::m_repetition_index > 0 ? msc_data_group_generator::m_repetition_index-- : m_repetition_index = 0;
      }
    msc_data_group_generator::m_last_ip_datagram = ip_datagram;
    auto header = msc_data_group_generator::build_msc_data_group_header();
    auto msc_dg = concat_vectors(header, ip_datagram);
    auto crc = genCRC16(msc_dg);
    return concat_vectors(msc_dg, crc);
    }
}
