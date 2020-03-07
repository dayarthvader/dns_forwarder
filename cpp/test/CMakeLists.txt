include_directories ("/usr/local/include/gtest")
add_executable(dns_forwarder_test main_test_all.cpp udp_server_client_test.cpp)
target_link_libraries(dns_forwarder_test util pthread gtest gtest_main)
