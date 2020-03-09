//  DNS_FORWADER 2020
#ifndef DNS_FORWARDER_CPP_INCLUDE_DNS_FORWARDER_QUERY_SERVER_H_
#define DNS_FORWARDER_CPP_INCLUDE_DNS_FORWARDER_QUERY_SERVER_H_
#include <string>
#include <memory>
#include <unordered_set>
#include "util/udp_server.h"
#include "util/udp_client.h"
#include "util/buffer.h"
#include "dns_forwarder/dns_query.h"
#include "dns_forwarder/dns_response.h"

using util_ns::Buffer;
using util_ns::UdpServer;
using util_ns::UdpClient;
using dns_forwarder_ns::DnsResponse;
using dns_forwarder_ns::DnsQuery;

namespace dns_forwarder_ns {
  static const std::string kServerIp{"127.0.0.1"};
  static const std::string kServerPort{"9000"};
  static const int kUpStreamTimeoutSecs = 5;
class QueryServer {
 public:
  QueryServer(const std::string& upstream_server_ip, const std::string& upstream_server_port);
  void Serve();
 private:
  void Prepare();
  std::shared_ptr<UdpClient> udp_client_{nullptr};
  std::shared_ptr<UdpServer> udp_server_{nullptr};
  std::shared_ptr<Buffer> server_request_buff_{nullptr};
  std::shared_ptr<Buffer> server_response_buff_{nullptr};
  std::shared_ptr<DnsQuery> dns_query_{nullptr};
  std::shared_ptr<DnsResponse> dns_response_{nullptr};
  std::unordered_set<uint16_t> transaction_history_;
};
}  //  namespace dns_forwarder
#endif  //  DNS_FORWARDER_CPP_INCLUDE_DNS_FORWARDER_QUERY_SERVER_H_