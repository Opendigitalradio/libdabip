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

#ifndef DABIP_TEST_UTIL_CRC16_TESTS
#define DABIP_TEST_UTIL_CRC16_TESTS

#include "dab/util/crc16.h"

#include <cute/cute.h>
#include <cute/cute_suite.h>
#include <cutex/descriptive_suite.h>

namespace dab
  {

  namespace test
    {

    namespace ip
      {

      namespace util
        {

        CUTE_DESCRIPTIVE_STRUCT(crc16_tests)
          {
#define LOCAL_TEST(Test) CUTE_SMEMFUN(crc16_tests, Test)
          static cute::suite suite()
            {
            return {
              LOCAL_TEST(crc),
            };
            }
#undef LOCAL_TEST

          void crc()
            {
            byte_vector_t const input {
              0x12, 0x34, 0x56, 0x78, 0x90
            };
            byte_vector_t const expected {
              (std::uint8_t)~0x59, (std::uint8_t)~0xEA
            };
            ASSERT_EQUAL(expected, dab::internal::genCRC16(input));
            }
          };

        }

      }

    }

  }

#endif
