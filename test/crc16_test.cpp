//@CMAKE_CUTE_DEPENDENCY=src/util/crc16.cpp
//
#include "util/crc16.h"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/cute_suite.h>
#include <cute/xml_listener.h>
#include <cute/ide_listener.h>


using namespace dabip;
void test_matching_crc()
  {
  byte_vector_t input {0x12, 0x34, 0x56, 0x78, 0x90};
  auto crc = genCRC16(input);
  byte_vector_t should {(std::uint8_t)~0x59, (std::uint8_t)~0xEA};
  ASSERT(crc == should);
  }

int main(int argc, char * * argv)
  {
  auto testSuite = cute::suite{};

  testSuite += cute::test{test_matching_crc, "Matching crc"};

  auto xmlFile = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xmlFile.out};

  return !cute::makeRunner(listener, argc, argv)(testSuite, "CRC16 test suite");
  }
