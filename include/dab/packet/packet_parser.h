/*
 * Copyright (C) 2017 Opendigitalradio (http://www.opendigitalradio.org/)
 * Copyright (C) 2017 Felix Morgner <felix.morgner@hsr.ch>
 * Copyright (C) 2017 Tobias Stauber <tobias.stauber@hsr.ch>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DABIP_PACKET_PACKET_PARSER
#define DABIP_PACKET_PACKET_PARSER

#include <dab/types/common_types.h>

#include <cstdint>

namespace dab
  {

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

#endif
