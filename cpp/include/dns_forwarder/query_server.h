//  DNS_FORWADER 2020
#ifndef DNS_FORWARDER_CPP_INCLUDE_DNS_FORWARDER_QUERY_SERVER_H_
#define DNS_FORWARDER_CPP_INCLUDE_DNS_FORWARDER_QUERY_SERVER_H_
#include <future>
#include <string>
#include <memory>
#include <queue>
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

class QueryServer {
 public:
  QueryServer(const std::string& upstream_server_ip, const std::string& upstream_server_port);
  void Serve();
  
 private:
  void ProcessQueue();
  std::shared_ptr<UdpServer> udp_server_{nullptr};
  std::unordered_set<uint16_t> transaction_history_;
  std::queue<std::future<void>> request_track_queue_;
  std::string upstream_server_ip_{""};
  std::string upstream_server_port_{""};
  std::mutex request_track_queue_mutex_;
  std::condition_variable queue_cv_;
  std::unique_ptr<std::thread> process_thread_{nullptr};
  std::atomic<bool> stop_{false};
};
}  //  namespace dns_forwarder
#endif  //  DNS_FORWARDER_CPP_INCLUDE_DNS_FORWARDER_QUERY_SERVER_H_