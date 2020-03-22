//  DNS_FORWADER 2020
#ifndef DNS_FORWARDER_CPP_INCLUDE_UTIL_UDP_SERVER_H_
#define DNS_FORWARDER_CPP_INCLUDE_UTIL_UDP_SERVER_H_
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <array>
#include <memory>
#include <string>
#include "buffer.h"

namespace util_ns {
class UdpServer {
 public:
  UdpServer(const std::string& serving_ip, const std::string& serving_port);
  ~UdpServer();
  UdpServer() = delete;
  UdpServer(UdpServer&) = delete;
  UdpServer& operator=(const UdpServer&) = delete;
  UdpServer& operator=(UdpServer&&) = delete;
  int Read(std::shared_ptr<Buffer> buffer, struct sockaddr* client_addr);
  int SendToPeer(std::shared_ptr<Buffer> buffer, struct sockaddr* client_addr);

 private:
  void Cleanup();
  std::string serving_ip_{""};
  std::string serving_port_{""};
  struct sockaddr_in server_addr_;
  int socket_fd_{-1};
};
}  //  namespace util_ns
#endif  //  DNS_FORWARDER_CPP_INCLUDE_UTIL_UDP_SERVER_H_

