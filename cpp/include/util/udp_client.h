//  DNS_FORWADER 2020
#ifndef DNS_FORWARDER_CPP_INCLUDE_UTIL_UDP_CLIENT_
#define DNS_FORWARDER_CPP_INCLUDE_UTIL_UDP_CLIENT_
#include <sys/socket.h>
#include <array>
#include <string>
namespace util_ns {
class UdpClient {
 public:
  UdpClient(const std::string& server_ip, std::string server_port);
  ~UdpClient();
  UdpClient() = delete;
  UdpClient(UdpClient&) = delete;
  UdpClient& operator=(const UdpClient&) = delete;
  UdpClient& operator=(UdpClient&&) = delete;
  int Read(char* buff, int max_data_len);
  int SendToPeer(char* buff, int send_len);

 private:
  void Cleanup();
  std::string server_ip_{""};
  std::string server_port_{""};
  struct sockaddr_in client_addr_;
  int socket_fd_{-1};
};
}  //  namespace util_ns
#endif  //  DNS_FORWARDER_CPP_INCLUDE_UTIL_UDP_CLIENT_

