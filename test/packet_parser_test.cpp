//@CMAKE_CUTE_DEPENDENCY=src/util/crc16.cpp
//@CMAKE_CUTE_DEPENDENCY=src/packet/packet_generator.cpp
//@CMAKE_CUTE_DEPENDENCY=src/packet/packet_parser.cpp

#include "packet/packet_generator.h"
#include "packet/packet_parser.h"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/cute_suite.h>
#include <cute/xml_listener.h>
#include <cute/ide_listener.h>


using namespace dabip;
void test_parsing_matches_generated()
  {

  byte_vector_t input {0x12,0x34,0x56,0x78,0x90};
  auto packet_gen = packet_generator(1000);
  auto packets = packet_gen.build(input);
  auto parser = packet_parser(1000);
  auto parsed = parser.parse(packets);

  std::cout << "\n ===parse status=== " << parsed.first << "\n";
  ASSERT(parsed.first == parse_status::ok);
  ASSERT(parsed.second == input);

  }

int main(int argc, char * * argv)
  {
  auto testSuite = cute::suite{};

  testSuite += cute::test{test_parsing_matches_generated, "Matching generated and parsed"};

  auto xmlFile = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xmlFile.out};

  return !cute::makeRunner(listener, argc, argv)(testSuite, "Packets test suite");
  }
