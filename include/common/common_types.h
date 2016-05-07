#ifndef __DABIP_COMMON__COMMON_TYPES
#define __DABIP_COMMON__COMMON_TYPES

#include <vector>
#include <cstdint>

namespace dabip {

  /**
   * @author Tobias Stauber
   *
   * @brief Status values returned by parsers.
   **/
  enum parse_status
    {
    invalid_crc,
    invalid_address,
    incomplete,
    segment_lost,
    ok
    };

  using byte_vector_t = std::vector<std::uint8_t>;
  using pair_status_vector_t = std::pair<parse_status, byte_vector_t>;
}

#endif // __DABIP_COMMON__COMMON_TYPES
