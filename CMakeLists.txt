cmake_minimum_required(VERSION 3.1.2)
project("DABIP"
  LANGUAGES CXX
  VERSION 1.0.1)

string(TOUPPER ${PROJECT_NAME} ${PROJECT_NAME}_UPPER)
string(TOLOWER ${PROJECT_NAME} ${PROJECT_NAME}_LOWER)

option(${${PROJECT_NAME}_UPPER}_ENABLE_TESTS
  "Build and run the ${PROJECT_NAME} unit tests."
  OFF
  )

option(${${PROJECT_NAME}_UPPER}_SKIP_CONAN
  "Skip installing the dependencies for ${PROJECT_NAME} through conan."
  OFF
  )

if(${${${PROJECT_NAME}_UPPER}_ENABLE_TESTS})
  set(CONAN_OPTIONS ${CONAN_OPTIONS} libdabdevice:test=True)
  get_directory_property(${PROJECT_NAME}_HAS_PARENT PARENT_DIRECTORY)
  if(${PROJECT_NAME}_HAS_PARENT)
    set(CONAN_OPTIONS ${CONAN_OPTIONS} PARENT_SCOPE)
  endif()
endif()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")
set(CXX_VERSION "c++11")

include("CompilerSetup")

if(NOT ${${PROJECT_NAME}_UPPER}_SKIP_CONAN)
  include("ConanPackages")
  install_conan_packages(SYSTEM_HEADERS
    PKGOPTS ${CONAN_OPTIONS}
    )
endif()

add_subdirectory("include")
add_subdirectory("src")

if(${${PROJECT_NAME}_UPPER}_ENABLE_TESTS)
  include("CUTE")
  include_directories(SYSTEM
    $<TARGET_PROPERTY:CONAN_PKG::CUTE,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:CONAN_PKG::CUTEX,INTERFACE_INCLUDE_DIRECTORIES>
    )
  add_subdirectory(test)
endif()

install(EXPORT ${PROJECT_NAME}
  DESTINATION "share/${${PROJECT_NAME}_LOWER}/cmake"
  )

export(EXPORT ${PROJECT_NAME})
