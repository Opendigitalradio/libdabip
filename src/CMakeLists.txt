set(LIB_SOURCES util/crc16.cpp
                packet/packet_generator.cpp
                packet/packet_parser.cpp
                msc_data_group/msc_data_group_generator.cpp
                msc_data_group/msc_data_group_parser.cpp)

add_library(${PROJECT_NAME}_static STATIC ${LIB_SOURCES})
target_link_libraries(${PROJECT_NAME}_static ${DABCOMMON_LIBRARIES})

add_library(${PROJECT_NAME} SHARED ${LIB_SOURCES})
target_link_libraries(${PROJECT_NAME} ${DABCOMMON_LIBRARIES})
