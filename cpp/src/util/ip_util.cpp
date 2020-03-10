#include "util/ip_util.h"
#include <arpa/inet.h>
#include <sys/socket.h>
namespace util_ns {
namespace ip_util_ns {
  bool ValidIp(const std::string& ip) {
    struct sockaddr_in sa;
    int ret = inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
    return (ret != 0);
  }
}
}