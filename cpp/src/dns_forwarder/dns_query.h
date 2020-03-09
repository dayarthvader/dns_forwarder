//  DNS_FORWADER 2020
#ifndef DNS_FORWARDER_CPP_SRC_DNS_FORWARDER_DNS_QUERY_
#define DNS_FORWARDER_CPP_SRC_DNS_FORWARDER_DNS_QUERY_
#include <array>
static const int kDnsQueryMaxSize = 1024;  // ToDo (Daya) -- Find out the appropriate
                                           //size     from spec
namespace dns_forwarder {
struct QueryPacket {
  uint16_t transaction_id_;
};
class DnsQuery {
 public: 
  DnsQuery(const unsigned char* buff_data, int buff_len);
  uint16_t TransactionId();
 private:
  void Parse();
  std::array<unsigned char, kDnsQueryMaxSize> buffer_;
  QueryPacket packet_;
};
}  //  namespcace dns_forwarder
#endif  //  DNS_FORWARDER_CPP_SRC_DNS_FORWARDER_DNS_QUERY_