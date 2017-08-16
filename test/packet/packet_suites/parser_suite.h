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

#ifndef DABIP_TEST_PACKET_PARSER_TESTS
#define DABIP_TEST_PACKET_PARSER_TESTS

#include "dab/packet/packet_parser.h"

#include <cute/cute.h>
#include <cute/cute_suite.h>
#include <cutex/descriptive_suite.h>

namespace dab
  {

  namespace test
    {

    namespace ip
      {

      namespace packet
        {

        CUTE_DESCRIPTIVE_STRUCT(parser_tests)
          {
#define LOCAL_TEST(Test) CUTE_SMEMFUN(parser_tests, Test)
          static cute::suite suite()
            {
            return {
              LOCAL_TEST(assemble),
              LOCAL_TEST(assemble_long),
            };
            }
#undef LOCAL_TEST

          void assemble()
            {
            auto input = byte_vector_t{
              0x12, 0x34, 0x56, 0x78, 0x90
            };
            auto packets = m_generator.build(input);
            auto result = m_parser.parse(packets);

            ASSERT_EQUAL(parse_status::ok, result.first);
            ASSERT_EQUAL(input, result.second);
            }


          void assemble_long()
            {
            auto input = byte_vector_t(512, 0x10);
            auto packets = m_generator.build(input);
            auto splitPackets = split_packets(packets);

            std::pair<parse_status, byte_vector_t> result;
            for (byte_vector_t packet : splitPackets)
              {
              result = m_parser.parse(packet);
              }

            ASSERT_EQUAL(parse_status::ok, result.first);
            ASSERT_EQUAL(input, result.second);
            }

          private:
            packet_generator m_generator{1000};
            packet_parser m_parser{1000};
          };

        }

      }

    }

  }

#endif
