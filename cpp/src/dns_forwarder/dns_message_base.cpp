//  DNS_FORWADER 2020
#include "dns_message_base.h"
#include <arpa/inet.h>
#include <cstring>
using dns_forwarder_ns::DnsMessageBase;

DnsMessageBase::DnsMessageBase(std::shared_ptr<Buffer> buffer) : buffer_(buffer) {
}

uint16_t DnsMessageBase::ParseTransactionId() {
 return transaction_id_ = ntohs(*reinterpret_cast<uint16_t*>(buffer_->buffer_.data()));
}
