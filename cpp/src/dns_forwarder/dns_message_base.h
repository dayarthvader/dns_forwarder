//  DNS_FORWADER 2020
#ifndef DNS_FORWARDER_CPP_SRC_DNS_FORWARDER_DNS_MESSAGE_BASE_H_
#define DNS_FORWARDER_CPP_SRC_DNS_FORWARDER_DNS_MESSAGE_BASE_H_
#include <array>
#include <cstring>
#include <memory>
#include "util/buffer.h"

using util_ns::Buffer;
namespace dns_forwarder_ns {
class DnsMessageBase {
 public:
  DnsMessageBase(std::shared_ptr<Buffer> buffer);
  std::shared_ptr<Buffer> Data() {return buffer_;}
  
 protected:
  uint16_t ParseTransactionId();
  std::shared_ptr<Buffer> buffer_;
  int data_len_{0};
  virtual void Parse() = 0;
  uint16_t transaction_id_{0};
  uint16_t TransactionId(){return transaction_id_;}
};
}  //  dns_forwarder_ns
#endif  //  DNS_FORWARDER_CPP_SRC_DNS_FORWARDER_DNS_MESSAGE_BASE_H_