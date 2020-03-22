//  DNS_FORWADER 2020
#include "dns_forwarder/query_server.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "dns_forwarder/dns_query.h"
#include "dns_forwarder/dns_response.h"
#include "dns_forwarder/upstream.h"
using dns_forwarder_ns::QueryServer;

QueryServer::QueryServer(const std::string& upstream_server_ip, const std::string& upstream_server_port): upstream_server_ip_(upstream_server_ip), upstream_server_port_(upstream_server_port) {
  udp_server_ = std::make_shared<UdpServer>(kServerIp, kServerPort);
  process_thread_.reset(new std::thread(&QueryServer::ProcessQueue, this));
}

void QueryServer::ProcessQueue() {
  while (!stop_) {
    std::unique_lock<std::mutex> lock(request_track_queue_mutex_);
    queue_cv_.wait(lock, [&]()->bool{!request_track_queue_.empty();});
    if (request_track_queue_.front().valid()) {
      request_track_queue_.front().get();
    }
    request_track_queue_.pop();
  }
}

void QueryServer::Serve() {
  std::shared_ptr<struct sockaddr> client_addr = std::make_shared<struct sockaddr>();
  while (true) {
    std::shared_ptr<Buffer> request_buffer = std::make_shared<Buffer>();
    if (udp_server_->Read(request_buffer, client_addr) < 0) {
      std::cout << "Server read failed\n";
      continue;
    }

    std::shared_ptr<DnsQuery> dns_query = std::make_shared<DnsQuery>(request_buffer);
    uint16_t tx_id = dns_query->TransactionId();
    if (transaction_history_.find(tx_id) != transaction_history_.end()) {
      std::cout << "Duplicate transaction Detected!\n";
      continue;
    } else {
      transaction_history_.insert(tx_id);
      // ToDo  (Daya)
      // How random is the transaction ID? Should you consider deleting very old entries
      // Rotate the history to maxmimum records perhaps?
    }
    dns_forwarder_ns::UpstreamForwarder forwarder(upstream_server_ip_, upstream_server_port_, dns_query, client_addr, udp_server_);
    {
      std::unique_lock<std::mutex> lock(request_track_queue_mutex_);
      request_track_queue_.push(std::move(forwarder.Forward()));
      queue_cv_.notify_one();
    }
  }
}