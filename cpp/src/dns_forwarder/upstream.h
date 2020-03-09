//  DNS_FORWADER 2020
#ifndef DNS_FORWARDER_CPP_SRC_DNS_FORWARER_UPSTREAM_H_
#define DNS_FORWARDER_CPP_SRC_DNS_FORWARER_UPSTREAM_H_
#include "util/udp_client.h"
#include "dns_response.h"
#include "dns_query.h"
#include <memory>
using util_ns::UdpClient;
using dns_forwarder_ns::DnsResponse;
using dns_forwarder_ns::DnsQuery;

namespace dns_forwarder_ns {
namespace upstream_ns {
  std::shared_ptr<DnsResponse> Forward(std::shared_ptr<UdpClient> udpclient, std::shared_ptr<DnsQuery> query);
}  //  namespace upstream_ns
}  //  namespace dns_forwarder_ns

#endif  //  DNS_FORWARDER_CPP_SRC_DNS_FORWARER_UPSTREAM_H_
