include("ExternalDependency")

if(EXTERNAL_DEPS_VIA STREQUAL "conan")
  include("ConanPackages")
  list(APPEND ${${PROJECT_NAME}_UPPER}_DEPS
    CONAN_PKG::libdabcommon
    )

  if(${${PROJECT_NAME}_UPPER}_ENABLE_TESTS)
    list(APPEND CONAN_OPTIONS ${CONAN_OPTIONS} libdabcommon:test=True)
    list(APPEND ${${PROJECT_NAME}_UPPER}_DEPS
      CONAN_PKG::CUTEX
      )
  endif()

  install_conan_packages(SYSTEM_HEADERS
    PKGOPTS ${CONAN_OPTIONS}
    )
elseif(EXTERNAL_DEPS_VIA STREQUAL "git")
  external_dependency(CMAKE
    NAME    "dabcommon"
    REPO    "https://github.com/Opendigitalradio/libdabcommon"
    )

  if(${${PROJECT_NAME}_UPPER}_ENABLE_TESTS)
    set(CUTEX_ENABLE_TESTS OFF)
    external_dependency(CMAKE
      NAME "CUTEX"
      REPO "https://github.com/fmorgner/CUTEX"
      )
  endif()
else()
  message(FATAL_ERROR "Unknown dependency resolution mechanism '${EXTERNAL_DEPS_VIA}'")
endif()
