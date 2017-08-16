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

#ifndef DABIP_MSC_DATA_GROUP_MSC_DATA_GROUP_GENERATOR
#define DABIP_MSC_DATA_GROUP_MSC_DATA_GROUP_GENERATOR

#include <cstdint>

#include <dab/types/common_types.h>

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

#endif
