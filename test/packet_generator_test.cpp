//@CMAKE_CUTE_DEPENDENCY=src/util/crc16.cpp
//@CMAKE_CUTE_DEPENDENCY=src/packet/packet_generator.cpp

#include "packet/packet_generator.h"


#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/cute_suite.h>
#include <cute/xml_listener.h>
#include <cute/ide_listener.h>


using namespace dabip;
void test_matching_packets()
  {
  auto msc_dg = byte_vector_t{0x12, 0x34, 0x56, 0x78, 0x90};
  auto packet_gen = packet_generator(1000);
  auto packets = packet_gen.build(msc_dg);

  byte_vector_t should_packets {0x0f, 0xe8, 0x5, 0x12, 0x34, 0x56, 0x78, 0x90, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xae, 0x4e};

  ASSERT(packets == should_packets);
  }

int main(int argc, char * * argv)
  {
  auto testSuite = cute::suite{};

  testSuite += cute::test{test_matching_packets, "Matching packets"};

  auto xmlFile = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xmlFile.out};

  return !cute::makeRunner(listener, argc, argv)(testSuite, "Packets test suite");
  }
