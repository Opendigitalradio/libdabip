//@CMAKE_CUTE_DEPENDENCY=src/util/crc16.cpp
//@CMAKE_CUTE_DEPENDENCY=src/msc_data_group/msc_data_group.cpp

#include "msc_data_group/msc_data_group.h"


#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/cute_suite.h>
#include <cute/xml_listener.h>
#include <cute/ide_listener.h>


using namespace dabip;
void test_matching_msc_data_group()
  {
  byte_vector_t ip_datagram {0x45, 0x00, 0x00, 0x27, 0x00, 0x01, 0x00, 0x00, 0x40, 0x11, 0x0c, 0xa7, 0xc0, 0xa8, 0x01, 0x75, 0xac, 0x00, 0x00, 0x01, 0x22, 0xb8, 0x22, 0xb8, 0x00, 0x13, 0xdd, 0x1e, 0x54, 0x65, 0x73, 0x74, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65,};
  auto gen = msc_data_group_generator{};
  auto msc_dg = gen.build_msc_data_group(ip_datagram);
  byte_vector_t should {0x40, 0x00, 0x45, 0x00, 0x00, 0x27, 0x00, 0x01, 0x00, 0x00, 0x40, 0x11, 0x0c, 0xa7, 0xc0, 0xa8, 0x01, 0x75, 0xac, 0x00, 0x00, 0x01, 0x22, 0xb8, 0x22, 0xb8, 0x00, 0x13, 0xdd, 0x1e, 0x54, 0x65, 0x73, 0x74, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0xc6, 0x89};
  ASSERT(msc_dg == should);
  }

int main(int argc, char * * argv)
  {
  auto testSuite = cute::suite{};

  testSuite += cute::test{test_matching_msc_data_group, "Matching data group"};

  auto xmlFile = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xmlFile.out};

  return !cute::makeRunner(listener, argc, argv)(testSuite, "MSC data group test suite");
  }
