//  DNS_FORWADER 2020
#ifndef DNS_FORWARDER_CPP_SRC_DNS_FORWARER_UPSTREAM_H_
#define DNS_FORWARDER_CPP_SRC_DNS_FORWARER_UPSTREAM_H_
#include "util/udp_client.h"
#include "util/udp_server.h"
#include "dns_response.h"
#include "dns_query.h"
#include <future>
#include <memory>
using util_ns::UdpClient;
using util_ns::UdpServer;
using dns_forwarder_ns::DnsResponse;
using dns_forwarder_ns::DnsQuery;

namespace dns_forwarder_ns {
class UpstreamForwarder {
 public:
  UpstreamForwarder(const std::string& upstream_server_ip, const std::string& upstream_server_port, std::shared_ptr<DnsQuery> query, std::shared_ptr<struct sockaddr> client_addr, std::shared_ptr<UdpServer> reply_context) : query_(query), client_addr_(client_addr), reply_context_(reply_context){
    udp_client_ = std::make_unique<UdpClient>(upstream_server_ip, upstream_server_port, kUpStreamTimeoutSecs);
  }
  std::future<void> Forward();
 private:
  void Process();
  std::unique_ptr<UdpClient> udp_client_{nullptr};
  std::shared_ptr<UdpServer> reply_context_{nullptr};
  std::shared_ptr<DnsQuery> query_{nullptr};
  std::unique_ptr<Buffer> server_response_buff_{nullptr};
  std::unique_ptr<DnsResponse> dns_response_{nullptr};
  std::shared_ptr<struct sockaddr> client_addr_;
  static const int kUpStreamTimeoutSecs;

};
}  //  namespace dns_forwarder_ns

#endif  //  DNS_FORWARDER_CPP_SRC_DNS_FORWARER_UPSTREAM_H_
