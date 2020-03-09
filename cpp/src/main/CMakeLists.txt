add_executable(dns_forwarder main.cpp)
target_link_libraries(dns_forwarder util dns_forward pthread gtest gtest_main)