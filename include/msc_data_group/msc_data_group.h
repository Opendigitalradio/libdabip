#ifndef __DABIP_MSC_DATA_GROUP__MSC_DATA_GROUP
#define __DABIP_MSC_DATA_GROUP__MSC_DATA_GROUP

#include <cstdint>

#include "common/common_types.h"

namespace dabip
  {

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
    byte_vector_t build_header();

    byte_vector_t m_last_ip_datagram {};
    std::uint8_t m_continuity_index {15};
    std::uint8_t m_repetition_index {};
  };


  struct msc_data_group_parser
    {

    /**
     * @author Tobias Stauber
     *
     * @brief Parses msc_data_groups.
     * @param msc_data_group A MSC data group.
     * @return A flag, if the set of segments is complete as first and if successful, the ip_datagram else an empty byte_vector_t as second.
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
     * @return Missed msc_data_group since last fed.
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
#endif //__DABIP_MSC_DATA_GROUP__MSC_DATA_GROUP
