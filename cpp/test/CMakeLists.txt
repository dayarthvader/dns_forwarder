include_directories ("/usr/local/include/gtest")
add_executable(dns_forwarder_test main_test_all.cpp udp_server_client_test.cpp dns_query_test.cpp dns_response_test.cpp ip_util_test.cpp)
target_link_libraries(dns_forwarder_test util dns_forward pthread gtest gtest_main)
