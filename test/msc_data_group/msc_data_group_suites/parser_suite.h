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

#ifndef DABIP_TEST_MSC_DATA_GROUP_PARSER_TESTS
#define DABIP_TEST_MSC_DATA_GROUP_PARSER_TESTS

#include "dab/msc_data_group/msc_data_group_parser.h"

#include <cute/cute.h>
#include <cute/cute_suite.h>
#include <cutex/descriptive_suite.h>

namespace dab
  {

  namespace test
    {

    namespace ip
      {

      namespace msc_data_group
        {

        CUTE_DESCRIPTIVE_STRUCT(parser_tests)
          {
#define LOCAL_TEST(Test) CUTE_SMEMFUN(parser_tests, Test)
          static cute::suite suite()
            {
            return {
              LOCAL_TEST(datagram_unwrapping),
            };
            }
#undef LOCAL_TEST

          void datagram_unwrapping()
            {
            byte_vector_t wrapped {
              0x40, 0x00, 0x45, 0x00, 0x00, 0x27, 0x00, 0x01,
              0x00, 0x00, 0x40, 0x11, 0x0c, 0xa7, 0xc0, 0xa8,
              0x01, 0x75, 0xac, 0x00, 0x00, 0x01, 0x22, 0xb8,
              0x22, 0xb8, 0x00, 0x13, 0xdd, 0x1e, 0x54, 0x65,
              0x73, 0x74, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67,
              0x65, 0xc6, 0x89,
            };

            byte_vector_t const expected {
              0x45, 0x00, 0x00, 0x27, 0x00, 0x01, 0x00, 0x00,
              0x40, 0x11, 0x0c, 0xa7, 0xc0, 0xa8, 0x01, 0x75,
              0xac, 0x00, 0x00, 0x01, 0x22, 0xb8, 0x22, 0xb8,
              0x00, 0x13, 0xdd, 0x1e, 0x54, 0x65, 0x73, 0x74,
              0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65,
            };

            auto result = m_parser.parse(wrapped);

            ASSERT_EQUAL(parse_status::ok, result.first);
            ASSERT_EQUAL(expected, result.second);
            }

          private:
            msc_data_group_parser m_parser{};
          };

        }

      }

    }

  }

#endif
