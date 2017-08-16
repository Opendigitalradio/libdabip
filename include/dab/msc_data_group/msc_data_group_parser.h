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

#ifndef DABIP_MSC_DATA_GROUP_MSC_DATA_GROUP_PARSER
#define DABIP_MSC_DATA_GROUP_MSC_DATA_GROUP_PARSER

#include <cstdint>

#include <dab/types/common_types.h>

namespace dab
  {
  /**
   * @author Tobias Stauber
   *
   * @brief A parser for MSC data groups.
   *
   **/
  struct msc_data_group_parser
    {

    /**
     * @author Tobias Stauber
     *
     * @brief Parses msc_data_groups.
     * @param msc_data_group A MSC data group.
     * @return[first] A flag indicating the status of the parser.
     * @return[second] If first==parse_status::ok the ip_datagram else an empty byte_vector_t.
     */
    pair_status_vector_t parse(byte_vector_t & msc_data_group);

    /**
     * @author Tobias Stauber
     *
     * @return Validity of the last parsed MSC_data_group.
     *
     */
    bool is_valid() const;

    /**
     * @author Tobias Stauber
     *
     * @return Number of missing msc_data_groups since previous fed.
     *
     */
    std::uint8_t no_of_missing_data_groups() const;

    private:

    bool m_segmented {false};
    bool m_start_new {true};
    bool m_group_valid {false};
    std::int8_t m_last_continuity_index {-1};
    std::uint16_t m_last_segment_number {};
    std::uint8_t m_continuity_index_difference {};
    byte_vector_t m_ip_datagram {};
  };

}

#endif
