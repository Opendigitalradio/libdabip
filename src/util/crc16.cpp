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
