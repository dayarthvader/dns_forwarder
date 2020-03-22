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
  thread_ = std::unique_ptr<std::thread>(new std::thread(&QueryServer::SendResponses, this));
}

QueryServer::~QueryServer() {
  stop_ = true;
  if (thread_->joinable()) {
    thread_->join();
  }
}

void QueryServer::Prepare() {
  //dns_query_.reset();
  //dns_response_.reset();
}

void QueryServer::Serve() {
  while (true) {
   // Prepare();
    QueryContext context;
    if (udp_server_->Read(context.server_request_buff_, &context.client_addr_) < 0) {
      std::cout << "Server read failed\n";
      continue;
    }

    context.dns_query_ = std::make_shared<DnsQuery>(context.server_request_buff_);
    uint16_t tx_id = context.dns_query_->TransactionId();
    if (transaction_history_.find(tx_id) != transaction_history_.end()) {
      std::cout << tx_id << " Duplicate transaction Detected!\n";
      continue;
    } else {
      transaction_history_.insert(tx_id);
      // ToDo  (Daya)
      // How random is the transaction ID? Should you consider deleting very old entries
      // Rotate the history to maxmimum records perhaps?
    }

    context.future_ = std::move(std::async(std::launch::async, dns_forwarder_ns::upstream_ns::Forward, udp_client_, context.dns_query_));
    {
      std::lock_guard<std::mutex> lock(query_context_queue_mtx_);
      std::cout<< "Before push "<< query_context_queue_.size()<<'\n';
      query_context_queue_.push(std::move(context));
      context_queue_condition_var_.notify_one();
    }
  }
}

void QueryServer::SendResponses() {
  while (!stop_) {
    {
      std::unique_lock<std::mutex> lock(query_context_queue_mtx_);
      context_queue_condition_var_.wait(lock);
      query_context_queue_.front().dns_response_ =
        query_context_queue_.front().future_.get();
      if (query_context_queue_.front().dns_response_->Error()) {
        std::cout << query_context_queue_.front().dns_response_->TransactionId() << " Error DNS response!\n";
      }
      if (udp_server_->SendToPeer(query_context_queue_.front().dns_response_->Data(), &query_context_queue_.front().client_addr_) < 0) {
                std::cout << "Server Send failed\n";
      }
      query_context_queue_.pop();
      std::cout<< "After Pop "<< query_context_queue_.size()<<'\n';
    }
  }
}