//  DNS_FORWADER 2020
#include "dns_query.h"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
using dns_forwarder::DnsQuery;

DnsQuery::DnsQuery(const unsigned char* buff_data, int buff_len) {
  if (buff_len > kDnsQueryMaxSize) {
    throw std::length_error{"buffer length error"};
  }
  memcpy(buffer_.data(), buff_data, sizeof(unsigned char)* buff_len);
  Parse();
}

void DnsQuery::Parse() {
 packet_.transaction_id_ = buffer_[0];
 packet_.transaction_id_ = packet_.transaction_id_ << 8;
 packet_.transaction_id_ |=  buffer_[1];  //  ToDo (Daya) consider ntohs ?
}

uint16_t DnsQuery::TransactionId() {
  return packet_.transaction_id_;
}