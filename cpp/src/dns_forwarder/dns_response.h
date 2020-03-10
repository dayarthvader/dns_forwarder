//  DNS_FORWADER 2020
#ifndef DNS_FORWARDER_CPP_SRC_DNS_FORWARDER_DNS_RESPONSE_H_
#define DNS_FORWARDER_CPP_SRC_DNS_FORWARDER_DNS_RESPONSE_H_
#include "dns_message_base.h"
#include <array>
using dns_forwarder_ns::DnsMessageBase;
namespace dns_forwarder_ns {
struct ResponsePacket {
  uint16_t transaction_id;
  uint16_t flags;
  // Place holder for extendablility transaction is accessed via base class
};
class DnsResponse : public DnsMessageBase{
 public: 
  DnsResponse(std::shared_ptr<Buffer> buffer);
  uint16_t TransactionId();
  bool Error();
 private:
  virtual void Parse() override;
  uint16_t ParseFlags();
  ResponsePacket packet_;
  bool error_packet_{false};
};
}  //  namespcace dns_forwarder_ns
#endif  //  DNS_FORWARDER_CPP_SRC_DNS_FORWARDER_RESPONSE_H_