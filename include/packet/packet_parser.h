#ifndef __DABIP_PACKET__PACKET_PARSER
#define __DABIP_PACKET__PACKET_PARSER

#include <cstdint>

#include "common/common_types.h"

namespace dab
  {
  using namespace types;
  /**
   * @author Tobias Stauber
   *
   * @brief A parser for DAB packets.
   *
   **/
  struct packet_parser
    {
    /**
     * @author Tobias Stauber
     *
     * @param address An integer in the interval [1,1023] specifying the address of the service component.
     **/
    packet_parser(uint16_t address);

    /**
     * @author Tobias Stauber
     *
     * @brief parses dab packets
     * @param packet A DAB packet.
     * @return[first] A flag indicating the status of the parser
     * @return[second] If first==parse_status::ok the msc_data_group else an empty byte_vector_t.
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

  std::vector<byte_vector_t> split_packets(byte_vector_t & packets);
}

#endif //__DABIP_PACKET__PACKET_PARSER
