#ifndef __DABIP_PACKET__PACKET_PARSER
#define __DABIP_PACKET__PACKET_PARSER

#include <cstdint>

#include "common/common_types.h"

namespace dabip
  {
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
    std::int8_t m_last_continuity_index {-1};
    std::uint8_t m_continuity_index_difference {};
    bool m_group_valid {true};
    byte_vector_t m_msc_data_group {};
    };
}

#endif //__DABIP_PACKET__PACKET_PARSER
