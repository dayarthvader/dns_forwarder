//  DNS_FORWADER 2020
#include "dns_forwarder/query_server.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "dns_forwarder/dns_query.h"
#include "dns_forwarder/dns_response.h"
#include "dns_forwarder/upstream.h"
using dns_forwarder_ns::QueryServer;

QueryServer::QueryServer(const std::string& upstream_server_ip, const std::string& upstream_server_port) {
  udp_client_ = std::make_shared<UdpClient>(upstream_server_ip, upstream_server_port, kUpStreamTimeoutSecs);
  udp_server_ = std::make_shared<UdpServer>(kServerIp, kServerPort);
  server_request_buff_ = std::make_shared<Buffer>();
}

void QueryServer::Prepare() {
  dns_query_.reset();
  dns_response_.reset();
}

void QueryServer::Serve() {
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Prepare();
    if (udp_server_->Read(server_request_buff_) < 0) {
      std::cout << "Server read failed\n";
      continue;
    }
    dns_query_ = std::make_shared<DnsQuery>(server_request_buff_);
    uint16_t tx_id = dns_query_->TransactionId();
    if (transaction_history_.find(tx_id) != transaction_history_.end()) {
      std::cout << "Duplicate transaction Detected!\n";
      continue;
    } else {
      transaction_history_.insert(tx_id);
    }
    dns_response_ = dns_forwarder_ns::upstream_ns::Forward(udp_client_, dns_query_);
    if (dns_response_ == nullptr) {
      std::cout << "Upstream forwarding failed\n";
      continue;
    }
    if (dns_response_->Error()) {
      std::cout << "Error DNS response!\n";
      continue;
    }
    if (udp_server_->SendToPeer(dns_response_->Data()) < -1) {
        std::cout << "Server Send failed\n";
    }
  }
}