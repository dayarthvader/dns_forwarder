//  DNS_FORWADER 2020
#include "dns_query.h"
using dns_forwarder_ns::DnsQuery;

DnsQuery::DnsQuery(std::shared_ptr<Buffer> buffer) : DnsMessageBase(buffer){
  Parse();
}

void DnsQuery::Parse() {
memset(&packet_,0,sizeof(packet_));
packet_.transaction_id = ParseTransactionId();
}

uint16_t DnsQuery::TransactionId() {
  return packet_.transaction_id;
}