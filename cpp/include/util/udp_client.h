//  DNS_FORWADER 2020
#ifndef DNS_FORWARDER_CPP_INCLUDE_UTIL_UDP_CLIENT_H_
#define DNS_FORWARDER_CPP_INCLUDE_UTIL_UDP_CLIENT_H_
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <array>
#include <memory>
#include <string>
#include "buffer.h"

namespace util_ns {
class UdpClient {
 public:
  UdpClient(const std::string& server_ip, const std::string& server_port, const int wait_time_sec);
  ~UdpClient();
  UdpClient() = delete;
  UdpClient(UdpClient&) = delete;
  UdpClient& operator=(const UdpClient&) = delete;
  UdpClient& operator=(UdpClient&&) = delete;
  int Read(std::shared_ptr<Buffer> buffer);
  int SendToPeer(std::shared_ptr<Buffer> buffer);

 private:
  void Cleanup();
  std::string server_ip_{""};
  std::string server_port_{""};
  struct sockaddr_in server_addr_;
  int socket_fd_{-1};
};
}  //  namespace util_ns
#endif  //  DNS_FORWARDER_CPP_INCLUDE_UTIL_UDP_CLIENT_H_

