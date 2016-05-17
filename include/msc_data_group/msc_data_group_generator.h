#ifndef __DABIP_MSC_DATA_GROUP__MSC_DATA_GROUP_GENERATOR
#define __DABIP_MSC_DATA_GROUP__MSC_DATA_GROUP_GENERATOR

#include <cstdint>

#include <types/common_types.h>

namespace dab
  {
  /**
   * @author Tobias Stauber
   *
   * @brief A generator for building MSC data groups from IP packets.
   *
   **/
  struct msc_data_group_generator
    {

    /**
     * @author Tobias Stauber
     *
     * @brief Packs ip_datagram in a msc_data_group
     * @param ip_datagram An IP datagram of max size 8191 bytes.
     * @return A MSC data group containing the ip_datagram.
     */
    byte_vector_t build(byte_vector_t & ip_datagram);

    private:

    /**
     * @internal
     *
     * @author Tobias Stauber
     *
     * @brief Generates the MSC data group header.
     *
     **/
    byte_vector_t build_header();

    byte_vector_t m_last_ip_datagram {};
    std::uint8_t m_continuity_index {15};
    std::uint8_t m_repetition_index {};
  };
}
#endif //__DABIP_MSC_DATA_GROUP__MSC_DATA_GROUP_GENERATOR
