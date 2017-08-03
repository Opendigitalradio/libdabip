#ifndef DABIP_UTIL_CRC_16
#define DABIP_UTIL_CRC_16

#include <dab/types/common_types.h>

#include <cstdint>
#include <vector>

namespace dab
  {
  namespace internal
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
