cmake_minimum_required (VERSION 3.6)
project (DNS_FORWARDER C CXX)

set (CMAKE_CXX_STANDARD 14)
option (UNITTEST "Enable/Disable unit test" 0)
include_directories("${PROJECT_SOURCE_DIR}/include/")

add_subdirectory("src/dns_forwarder")
add_subdirectory("src/util")

if (UNITTEST)
  message(STATUS "UNITTEST: ${UNITTEST}")
  add_subdirectory("test") 
else()
  add_subdirectory("src/main")
endif()


