#ifndef __DABIP_MSC_DATA_GROUP__MSC_DATA_GROUP_PARSER
#define __DABIP_MSC_DATA_GROUP__MSC_DATA_GROUP_PARSER

#include <cstdint>

#include "common/common_types.h"

namespace dab
  {
  using namespace types;
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
#endif //__DABIP_MSC_DATA_GROUP__MSC_DATA_GROUP_PARSER
