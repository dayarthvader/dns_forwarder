//  DNS_FORWADER 2020
#include "dns_response.h"
#include <arpa/inet.h>
#include <cstring>

using dns_forwarder_ns::DnsResponse;

DnsResponse::DnsResponse(std::shared_ptr<Buffer> buffer) : DnsMessageBase(buffer){
  Parse();
}

void DnsResponse::Parse() {
 packet_.transaction_id = ParseTransactionId();
 packet_.flags = ParseFlags();
}

uint16_t DnsResponse::ParseFlags() {
 packet_.flags = ntohs(*reinterpret_cast<uint16_t*>(&buffer_->buffer_.data()[2]));
 if (packet_.flags & 0x000f) {
   error_packet_ = true;
 }
}

uint16_t DnsResponse::TransactionId() {
  return packet_.transaction_id;
}

bool DnsResponse::Error() {
  return error_packet_;
}