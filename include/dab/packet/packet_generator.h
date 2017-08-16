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
