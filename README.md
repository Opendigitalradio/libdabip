libdabip
========

**libdabip** provides the facilities to package and segment IP datagrams for
transmission via DAB/DAB+. It can be used to create MSC datagroups and
packetmode packets as well as reassemble them and reproduce the original IP
datagram.

This library can be used on the receiver as well as the sender side to either
decode transmitted data or to provide data for ODRDabMux for transmission via
DAB.

Code example:
-------------

```cpp
#include <dabip.h>
#include <types/common_types.h>

#include <future>

void data_callback(dab::byte_vector_t const & data, dab::packet_parser & packetParser)
  {
  auto result = packetParser.parse(data);

  if(result.first == dab::parse_status::ok)
    {
    auto datagroupParser = dab::msc_data_group_parser{};
    result = datagroupParser.parse(result.second);

    if(result.first == dab::parse_status::ok)
      {
      // Process the decoded data in result.second
      }
    else
      {
      // Handle datagroup error
      }
    }
  else if(result.first != dab::parse_status::incomplete)
    {
    // Handle packet error
    }
  }

int main(int argc, char * * argv)
  {
  // Create a packet_parser for address 1000
  auto packetParser = dab::packet_parser{1000};

  /*
   * Asynchronously acquire data from a DAB ensemble
   * an register data_callback as a callback for data
   * processing.
   */
  }
```

Building:
---------

You first need to check out the source code and the respective submodules:

```
$ git clone --recursive https://github.com/Opendigitalradio/libdabip.git
```

Like the other members of the **libdabXYZ** family, **libdabip** uses CMake
as it build environment. There are several configuration option that
you can choose from when building **libdabip**:

| Option                         | Default | Comment                                                 |
| ------------------------------ | ------- | ------------------------------------------------------- |
| `BUILD_DOCUMENTATION`          | **OFF**     | Build the **libdabip** documentation.                       |
| `BUILD_DOCUMENTATION_ONLY`     | **OFF**     | Only build the documentation.                           |
| `BUILD_INTERNAL_DOCUMENTATION` | **OFF**     | Generate the developer documentation.                   |
| `CMAKE_BUILD_TYPE`             | **Debug**   | The type of binary to produce.                          |
| `DOCUMENTATION_FOR_THESIS`     | **OFF**     | Build the documentation for the inclusion in the thesis |
| `WITH_ADDRESS_SANITIZER`       | **OFF**     | Include additional memory checks (**slow**)                 |
| `WITH_COMMON_TESTS`            | **OFF**     | Build and run the common library tests.                 |
| `WITH_UNDEFINED_SANITIZER`     | **OFF**     | Check for undefined behavior.                           |

To build the library, enter the `build` directory and run cmake or ccmake to
configure the build environment to you liking. Afterward, you can use
`cmake --build .` to build the library. Depending on your selection, the built
library will be in the directory `products/{Debug|Release}/lib`. If you chose
to build the documentation, the pdf will be found in
`dabip_doc/latex/refman.pdf`.

You can use this library as a subproject in any CMake based project.
