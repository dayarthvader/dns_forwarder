cmake_minimum_required (VERSION 3.6)
project (DNS_FORWARDER C CXX)

set (CMAKE_CXX_STANDARD 14)
option (UNITTEST "Enable/Disable unit test" 0)

set(CMAKE_RUNTIME_OUTPUT_DIR ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIR ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIR ${CMAKE_BINARY_DIR})
include_directories("${PROJECT_SOURCE_DIR}/include/")

add_subdirectory("src/dns_forwarder")
add_subdirectory("src/util")

if (UNITTEST)
  message(STATUS "UNITTEST: ${UNITTEST}")
  set(CMAKE_RUNTIME_OUTPUT_DIR ${CMAKE_BINARY_DIR})
  add_subdirectory("test") 
else()
  add_subdirectory("src/main")
endif()


