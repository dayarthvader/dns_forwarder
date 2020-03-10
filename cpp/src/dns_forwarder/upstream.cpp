//  DNS_FORWADER 2020
#include "upstream.h"
#include <iostream>
#include "util/buffer.h"
using util_ns::Buffer;

namespace dns_forwarder_ns {
namespace upstream_ns {
std::shared_ptr<DnsResponse> Forward(std::shared_ptr<UdpClient> udpclient, std::shared_ptr<DnsQuery> query) {
  int ret = udpclient->SendToPeer(query->Data());
  if (ret < 0) {
    std::cout << "Failed forwarding request upstream\n";
    return nullptr;
  }
  std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
  ret = udpclient->Read(buffer);
  if (ret < 0) {
    std::cout << "Failed recieving response from upstream\n";
    return nullptr;
  }
  return std::make_shared<DnsResponse>(buffer);
}
}  //  upstream_ns
}  //  dns_forwarder_ns