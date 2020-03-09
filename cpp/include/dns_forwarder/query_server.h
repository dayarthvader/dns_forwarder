//  DNS_FORWADER 2020
#ifndef DNS_FORWARDER_CPP_INCLUDE_DNS_FORWARDER_QUERY_SERVER_
#define DNS_FORWARDER_CPP_INCLUDE_DNS_FORWARDER_QUERY_SERVER_
#include <string>
#include <memory>
#include "udp_server.h"
using util_ns::UdpServer;

namespace dns_forwarder {
class QueryServer {
 public:
  QueryServer();
  void Serve(const std::string& upstream_server_ip, const std::string& upstream_server_port);
 private:
  DnsAnswere ForwardQuery(DnsQuery);
  bool IsDuplicate(uint16_t transactionId);
  void SendAnswere(DnsAnswere);
  UpstreamClient upstream_client_;
  std::unique_ptr<UdpServer> udp_server_{nullptr};
  static const std::string kServerIp{"127.0.0.1"};
  static const std::string kServerPort{"9000"};
};
}  //  namespace dns_forwarder
#endif  //  DNS_FORWARDER_CPP_INCLUDE_DNS_FORWARDER_QUERY_SERVER_