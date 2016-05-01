#ifndef __DABIP_MSC_DATA_GROUP__MSC_DATA_GROUP
#define __DABIP_MSC_DATA_GROUP__MSC_DATA_GROUP

#include <cstdint>

#include "common/common_types.h"

namespace dabip {

  struct msc_data_group_generator {

    /**
     * @author Tobias Stauber
     *
     * @brief Packs ip_datagram in a msc_data_group
     * ipDatagram.size() must be 8191 or less
     */
    byte_vector_t build_msc_data_group(byte_vector_t & ip_datagram);

    private:
    byte_vector_t build_msc_data_group_header();

    std::uint8_t static constexpr kdata_group_types[] {0, 1, 2};
    byte_vector_t m_last_ip_datagram {};
    std::uint8_t m_continuity_index {15};
    std::uint8_t m_repetition_index {};
  };

}
#endif //__DABIP_MSC_DATA_GROUP__MSC_DATA_GROUP
