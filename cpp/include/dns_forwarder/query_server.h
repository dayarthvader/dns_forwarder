//  DNS_FORWADER 2020
#ifndef DNS_FORWARDER_CPP_INCLUDE_DNS_FORWARDER_QUERY_SERVER_H_
#define DNS_FORWARDER_CPP_INCLUDE_DNS_FORWARDER_QUERY_SERVER_H_
#include <future>
#include <string>
#include <memory>
#include <unordered_set>
#include <queue>
#include "util/udp_server.h"
#include "util/udp_client.h"
#include "dns_forwarder/query_context.h"


using util_ns::Buffer;
using util_ns::UdpServer;
using util_ns::UdpClient;
using dns_forwarder_ns::QueryContext;

namespace dns_forwarder_ns {
 static const std::string kServerIp{"127.0.0.1"};
 static const std::string kServerPort{"9000"};
 static const int kUpStreamTimeoutSecs = 5;

class QueryServer {
 public:
  QueryServer(const std::string& upstream_server_ip, const std::string& upstream_server_port);
  ~QueryServer();
  QueryServer(const QueryServer&) = delete;
  QueryServer(const QueryServer&&) = delete;
  QueryServer& operator=(const QueryServer&) = delete;
  QueryServer& operator=(const QueryServer&&) = delete;
  void Serve();
  
 private:
  void Prepare();
  void SendResponses();
  std::queue<QueryContext> query_context_queue_;
  std::mutex query_context_queue_mtx_;
  std::condition_variable context_queue_condition_var_;
  std::atomic<bool> stop_{false};
  std::unique_ptr<std::thread> thread_{nullptr};
  std::shared_ptr<UdpClient> udp_client_{nullptr};
  std::shared_ptr<UdpServer> udp_server_{nullptr};
  std::unordered_set<uint16_t> transaction_history_;
};
}  //  namespace dns_forwarder
#endif  //  DNS_FORWARDER_CPP_INCLUDE_DNS_FORWARDER_QUERY_SERVER_H_