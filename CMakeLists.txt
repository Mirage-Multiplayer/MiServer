cmake_minimum_required(VERSION 3.8)
project(MiServer)

set(MiServer_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/MiServer)
set(MiServer_CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include_directories("${MiServer_INCLUDE_DIRS}" "${CMAKE_CURRENT_SOURCE_DIR}/lib/MiRak/include")

list(APPEND CMAKE_MODULE_PATH ${MiServer_CMAKE_MODULE_PATH})

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Compiling with Debug option")
endif()

if(CMAKE_BUILD_TYPE MATCHES Release)
    message("Compiling in Release mode")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MiServer Platform configuration
option(MiServer_PLATFORM_WIN32 "MiServer platform Win32" OFF)
option(MiServer_PLATFORM_UNIX "MiServer platform Unix" OFF)

if(MiServer_PLATFORM_WIN32)
    message("Detected Windows platform")
elseif(MiServer_PLATFORM_UNIX)
    message("Detected Unix platform")
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

if (MSVC)
  add_definitions("/MP")
else()
  set(CMAKE_C_FLAGS "-m32 ${CMAKE_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "-m32 ${CMAKE_CXX_FLAGS}")
endif()

option(MiServer_TESTS_OPT "Build tests" OFF)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

# MiServer lib
add_subdirectory(MiServer)

# MiServer deps
add_subdirectory(lib)

# MiServer tests
if(MiServer_TESTS_OPT)
    add_subdirectory(tests)
    message(STATUS "Tests enabled")
endif()