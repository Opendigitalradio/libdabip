#ifndef __DABIP_PACKET__PACKET_GENERATOR
#define __DABIP_PACKET__PACKET_GENERATOR

#include <cstdint>

#include "common/common_literals.h"
#include "common/common_types.h"

namespace dabip
  {
  using namespace binary;
  struct packet_generator
    {

    packet_generator(uint16_t address);

    /**
     * @author Tobias Stauber
     *
     * @brief Builds dab packets from msc data group.
     *
     *
     */
    byte_vector_t build(byte_vector_t & msc_data_group);

    private:

    /**
     * @author Tobias Stauber
     *
     * @brief Builds dab packet header
     *
     *
     */
    byte_vector_t build_header(std::uint8_t const packet_length, std::uint8_t const useful_data_length);

    /**
     * @author Tobias Stauber
     *
     * @brief Assembles packets
     *
     *
     */
    byte_vector_t assemble(byte_vector_t & msc_data_group, std::uint8_t packet_length);

    void set_first_last();

    std::uint8_t m_first_last = 11_b;
    std::uint16_t const kAddress;
    std::uint8_t m_continuity_index {};
    };
}

#endif //__DABIP_PACKET__PACKET_GENERATOR
