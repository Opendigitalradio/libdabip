#ifndef __DABIP_UTIL__CRC_16
#define __DABIP_UTIL__CRC_16

#include <cstdint>
#include <vector>

#include "common/common_types.h"

namespace dabip {

  /**
   * @author Tobias Stauber
   *
   * @brief Returns CRC16 XModem of input.
   * @details Calculates CRC16 of input with initial value 0xFFFF by the polynomial x^16 + x^12 + x^5 + 1.
   **/
  byte_vector_t genCRC16(byte_vector_t const & input);

}

#endif
