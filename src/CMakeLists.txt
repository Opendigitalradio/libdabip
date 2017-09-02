set(LIBRARY_NAME ${${PROJECT_NAME}_LOWER})

add_library(${LIBRARY_NAME}
  util/crc16.cpp
  packet/packet_generator.cpp
  packet/packet_parser.cpp
  msc_data_group/msc_data_group_generator.cpp
  msc_data_group/msc_data_group_parser.cpp
  )

target_link_libraries(${LIBRARY_NAME}
  ${LIBRARY_NAME}_iface
  )

if(NOT ${${PROJECT_NAME}_UPPER}_HAS_PARENT)
  install(TARGETS ${LIBRARY_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    )
endif()
