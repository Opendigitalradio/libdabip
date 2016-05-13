#include "util/vector_helpers.h"
#include "common/common_types.h"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/cute_suite.h>
#include <cute/xml_listener.h>
#include <cute/ide_listener.h>

using namespace dab::types;
using namespace dab::__internal_dabip;

void test_split_vector()
  {
  auto input = byte_vector_t{0x12, 0x34, 0x56, 0x78, 0x90};
  auto splitted = split_vector(input, 3);
  auto should_first = byte_vector_t{0x12, 0x34, 0x56};
  auto should_second = byte_vector_t{0x78, 0x90};
  ASSERT(splitted.first  == should_first);
  ASSERT(splitted.second == should_second);
  }

int main(int argc, char * * argv)
  {
  auto testSuite = cute::suite{};

  testSuite += cute::test{test_split_vector, "Test split_vector"};

  auto xmlFile = cute::xml_file_opener{argc, argv};
  auto listener = cute::xml_listener<cute::ide_listener<>>{xmlFile.out};

  return !cute::makeRunner(listener, argc, argv)(testSuite, "Vector_helpers test suite");
  }
