add_library(dns_forward STATIC dns_message_base.cpp dns_query.cpp dns_response.cpp upstream.cpp query_server.cpp)
target_link_libraries(dns_forward util)