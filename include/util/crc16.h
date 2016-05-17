#ifndef __DABIP_UTIL__CRC_16
#define __DABIP_UTIL__CRC_16

#include <cstdint>
#include <vector>

#include <types/common_types.h>

namespace dab
  {
  namespace __internal_dabip
    {
    /**
     * @author Tobias Stauber
     * @brief Calculates CRC16 of input with initial value 0xFFFF by the polynomial x^16 + x^12 + x^5 + 1.
     *
     * @returns CRC16 CCITT of input.
     **/
    byte_vector_t genCRC16(byte_vector_t const & input);
    }
  }

#endif
