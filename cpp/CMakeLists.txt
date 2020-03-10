cmake_minimum_required (VERSION 3.6)
project (DNS_FORWARDER C CXX)

set (CMAKE_CXX_STANDARD 14)
option (UNITTEST "Enable/Disable unit test" 0)

include_directories("${PROJECT_SOURCE_DIR}/include/")
include_directories("${PROJECT_SOURCE_DIR}/src/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
message (STATUS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ${CMAKE_BINARY_DIR}")

add_subdirectory("src/dns_forwarder")
add_subdirectory("src/util")

if (SANITIZE)
  set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif()

if (UNITTEST)
  message(STATUS "UNITTEST: ${UNITTEST}")
  add_subdirectory("test") 
else()
  add_subdirectory("src/main")
endif()


