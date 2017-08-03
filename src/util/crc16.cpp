#include "dab/util/crc16.h"

#include <algorithm>

namespace dab
  {

  namespace internal
    {

    byte_vector_t genCRC16(byte_vector_t const & input)
      {

      auto crc = byte_vector_t(2);
      std::uint8_t x {};
      std::uint16_t init {0xFFFF};

      std::for_each(input.begin(), input.end(), [&] (std::uint8_t element) {
        x = init >> 8 ^ element;
        x ^= x >> 4;
        init = (init << 8) ^ ((std::uint16_t)(x << 12)) ^ ((std::uint16_t)(x << 5)) ^ ((std::uint16_t)x);
        });

      init = ~init;
      crc[0] = (std::uint8_t)(init >> 8);
      crc[1] = (std::uint8_t)(init);
      return crc;
      }
    }
  }
