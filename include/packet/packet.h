#ifndef __DABIP_PACKET__PACKET
#define __DABIP_PACKET__PACKET

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

  struct packet_parser
    {
    packet_parser(uint16_t address);

    /**
     * @author Tobias Stauber
     *
     * @brief parses dab packets
     * @return A flag, if the set of segments is complete as first and if successful && address==kAddress the msc_data_group else an empty byte_vector_t as second.
     */
    pair_status_vector_t parse(byte_vector_t & packet);

    bool is_valid() const;

    /**
     * @author Tobias Stauber
     *
     * @return Number of missed packets since last fed.
     */
    std::uint8_t no_of_missing_packets() const;

    private:
    std::uint16_t const kAddress;
    bool m_group_valid {true};
    byte_vector_t m_msc_data_group {};
    };

}

#endif //__DABIP_PACKET__PACKET
