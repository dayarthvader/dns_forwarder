//  DNS_FORWADER 2020
#include "upstream.h"
#include <iostream>
#include "util/buffer.h"
using util_ns::Buffer;
using dns_forwarder_ns::UpstreamForwarder;
const int UpstreamForwarder::kUpStreamTimeoutSecs = 5;

void UpstreamForwarder::Process() {
  std::cout << query_->TransactionId() << " fowarding" << std::this_thread::get_id() << "\n";
  int ret = udp_client_->SendToPeer(query_->Data());
  if (ret < 0) {
    std::cout << "Failed forwarding request upstream\n";
    return;
  }
  std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
  ret = udp_client_->Read(buffer);
  if (ret < 0) {
    std::cout << "Failed recieving response from upstream" << std::this_thread::get_id() << "\n";
    return;
  }
  DnsResponse dns_response(buffer);
  std::cout << dns_response.TransactionId() << " upstream response received\n";
    if (dns_response.Error()) {
      std::cout << "Error DNS response of" << dns_response.TransactionId() << "\n";
    }

    if (reply_context_->SendToPeer(dns_response.Data(), client_addr_) < 0) {
        std::cout << "Server Send failed\n";
    }
  std::cout << dns_response.TransactionId() << " response sent downstream" << std::this_thread::get_id() << "\n";
}

std::future<void> UpstreamForwarder::Forward() {
  std::async(std::launch::async, [this](){Process();});
}