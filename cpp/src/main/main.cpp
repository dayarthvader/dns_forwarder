//  DNS_FORWADER 2020
#include "dns_forwarder/query_server.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
using dns_forwarder_ns::QueryServer;

void Usage(const std::string& error_string) {
  std::cout << error_string <<'\n';
  std::cout << "./dns_forwarder <upstream_ip> <upstream_port>\n";
  exit(0); 
}

bool ValidIp(const std::string& ip) {
    struct sockaddr_in sa;
    int ret = inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
    return (ret != 0);
}

int main(int argc, char** argv) {
  if (argc <3) {
    Usage("Too few arguments");
  }
  std::string upstream_ip(argv[1]);
  std::string upstream_port(argv[2]);
  if (!ValidIp(upstream_ip)) {
    Usage("Please enter valid upstream IPv4 address");
  }
  QueryServer(upstream_ip, upstream_port).Serve();
  return 0;
}