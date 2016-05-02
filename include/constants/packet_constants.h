#ifndef __DABIP_CONSTANTS__PACKET_CONSTANTS
#define __DABIP_CONSTANTS__PACKET_CONSTANTS

#include <cstdint>
namespace dabip
  {
  namespace constants
    {
    std::uint8_t constexpr kPacketLengths[] {24, 48, 72, 96};
    std::uint8_t constexpr kPacketDataLengths[] {kPacketLengths[0] - 5, kPacketLengths[1] - 5, kPacketLengths[2] - 5, kPacketLengths[3] - 5, };
    }
  }


#endif //__DABIP_CONSTANTS__PACKET_CONSTANTS
