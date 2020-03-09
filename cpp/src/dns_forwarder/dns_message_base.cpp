//  DNS_FORWADER 2020
#include "dns_message_base.h"
#include <cstring>
using dns_forwarder_ns::DnsMessageBase;

DnsMessageBase::DnsMessageBase(std::shared_ptr<Buffer> buffer) : buffer_(buffer) {
}

uint16_t DnsMessageBase::ParseTransactionId() {
 transaction_id_ = buffer_->buffer_.data()[0];
 transaction_id_ = transaction_id_ << 8;
 transaction_id_ |= buffer_->buffer_.data()[1];  //  ToDo (Daya) consider ntohs ?
 return transaction_id_;
}
