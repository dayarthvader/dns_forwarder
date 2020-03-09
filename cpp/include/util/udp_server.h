//  DNS_FORWADER 2020
#ifndef DNS_FORWARDER_CPP_INCLUDE_UTIL_UDP_SERVER_
#define DNS_FORWARDER_CPP_INCLUDE_UTIL_UDP_SERVER_
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <array>
#include <string>
namespace util_ns {
class UdpServer {
 public:
  UdpServer(const std::string& serving_ip, const std::string& serving_port);
  ~UdpServer();
  UdpServer() = delete;
  UdpServer(UdpServer&) = delete;
  UdpServer& operator=(const UdpServer&) = delete;
  UdpServer& operator=(UdpServer&&) = delete;
  int Read(unsigned char* buff, int max_data_len);
  int SendToPeer(unsigned const char* buff, int send_len);

 private:
  void Cleanup();
  std::string serving_ip_{""};
  std::string serving_port_{""};
  struct sockaddr_in server_addr_;
  struct sockaddr client_addr_;
  socklen_t rcv_data_len_{0};
  int socket_fd_{-1};
};
}  //  namespace util_ns
#endif  //  DNS_FORWARDER_CPP_INCLUDE_UTIL_UDP_SERVER_

