#ifndef __DABIP_PACKET__PACKET
#define __DABIP_PACKET__PACKET

#include <cstdint>

#include "common/common_literals.h"
#include "common/common_types.h"

namespace dabip {

  using namespace binary;
  struct packet_generator {

    packet_generator(uint16_t address):kaddress{address}
      {
      }

    /**
     * @author Tobias Stauber
     *
     * @brief Builds dab packets from msc data group.
     *
     *
     */
    byte_vector_t build_packets(byte_vector_t & msc_data_group);

    private:

    /**
     * @author Tobias Stauber
     *
     * @brief Builds dab packet header
     *
     *
     */
    byte_vector_t build_packet_header(std::uint8_t const packet_length, std::uint8_t const useful_data_length);

    /**
     * @author Tobias Stauber
     *
     * @brief Assembles packets
     *
     *
     */
    byte_vector_t assemble_packets(byte_vector_t & msc_data_group, std::uint8_t packet_length);

    void set_first_last();

    std::uint8_t m_first_last = 11_b;
    std::uint16_t const kaddress;
    std::uint8_t m_continuity_index {};
    std::uint8_t static constexpr kpacket_lengths[] {24, 48, 72, 96};
    std::uint8_t static constexpr kpacket_data_lengths[] {kpacket_lengths[0]-5, kpacket_lengths[1]-5, kpacket_lengths[2]-5, kpacket_lengths[3]-5};
  };

}

#endif //__DABIP_PACKET__PACKET
