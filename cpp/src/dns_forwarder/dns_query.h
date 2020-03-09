//  DNS_FORWADER 2020
#ifndef DNS_FORWARDER_CPP_SRC_DNS_FORWARDER_DNS_QUERY_H_
#define DNS_FORWARDER_CPP_SRC_DNS_FORWARDER_DNS_QUERY_H_
#include "dns_message_base.h"
#include <memory>
using dns_forwarder_ns::DnsMessageBase;
namespace dns_forwarder_ns {
struct QueryPacket {
  uint16_t transaction_id;
  // Place holder for extendablility transaction is accessed via base class
};
class DnsQuery : public DnsMessageBase {
 public: 
  DnsQuery(std::shared_ptr<Buffer> buffer);
  uint16_t TransactionId();
 private:
  virtual void Parse() override;
  QueryPacket packet_;
};
}  //  namespcace dns_forwarder_ns
#endif  //  DNS_FORWARDER_CPP_SRC_DNS_FORWARDER_DNS_QUERY_H_