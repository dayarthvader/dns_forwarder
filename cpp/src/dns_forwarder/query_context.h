//  DNS_FORWADER 2020
#ifndef DNS_FORWARDER_CPP_SRC_DNS_FORWARDER_QUERY_CONTEXT_H_
#define DNS_FORWARDER_CPP_SRC_DNS_FORWARDER_QUERY_CONTEXT_H_
#include <sys/socket.h>
#include <sys/types.h>  
#include <memory>
#include <future>
#include "util/buffer.h"
#include "dns_forwarder/dns_query.h"
#include "dns_forwarder/dns_response.h"
namespace dns_forwarder_ns {
class QueryContext {
 public:
  QueryContext() {
    server_request_buff_.reset(new Buffer());
  }
  struct sockaddr client_addr_;
  std::shared_ptr<DnsQuery> dns_query_{nullptr};
  std::shared_ptr<DnsResponse> dns_response_{nullptr};
  std::shared_ptr<Buffer> server_request_buff_{nullptr};
  std::shared_ptr<Buffer> server_response_buff_{nullptr};
  std::future<std::shared_ptr<DnsResponse>> future_;
};

}  //  namespace dns_forwarder_ns
#endif  //  DNS_FORWARDER_CPP_SRC_DNS_FORWARDER_QUERY_CONTEXT_H_