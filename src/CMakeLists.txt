set(LIB_SOURCES util/crc16.cpp
                packet/packet.cpp
                msc_data_group/msc_data_group.cpp)


add_library(dab_ip_static STATIC ${LIB_SOURCES})
add_library(dab_ip SHARED ${LIB_SOURCES})

#add_executable(demo demo.cpp)
#target_link_libraries(demo dab_ip_static)
