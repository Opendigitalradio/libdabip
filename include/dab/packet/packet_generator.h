#ifndef DABIP_PACKET_PACKET_GENERATOR
#define DABIP_PACKET_PACKET_GENERATOR

#include <dab/types/common_types.h>

#include <cstdint>

namespace dab
  {
  /**
   * @author Tobias Stauber
   *
   * @brief A generator for building DAB packets from MSC data groups.
   *
   **/
  struct packet_generator
    {
    /**
     * @author Tobias Stauber
     *
     * @param address An integer in the interval [1,1023] that specifies the address of the service component.
     **/
    packet_generator(uint16_t address);

    /**
     * @author Tobias Stauber
     *
     * @brief Builds dab packets from msc data group.
     *
     * @return A byte_vector_t containing one ore more DAB packets.
     *
     */
    byte_vector_t build(byte_vector_t & msc_data_group);

    private:

    /**
     * @internal
     *
     * @author Tobias Stauber
     *
     * @brief Builds dab packet header
     *
     * @return The header for the DAB packet.
     */
    byte_vector_t build_header(std::uint8_t const packet_length, std::uint8_t const useful_data_length);

    /**
     * @internal
     *
     * @author Tobias Stauber
     *
     * @brief Assembles packets
     *
     * @return The assembled DAB packet.
     */
    byte_vector_t assemble(byte_vector_t & msc_data_group, std::uint8_t packet_length);

    void set_first_last();

    std::uint8_t m_first_last = 3;
    std::uint16_t const kAddress;
    std::uint8_t m_continuity_index {};
    };
}

#endif
