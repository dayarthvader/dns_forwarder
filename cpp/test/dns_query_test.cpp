//  DNS_FORWADER 2020
#include <gtest/gtest.h>
#include "dns_forwarder/dns_query.h"
using dns_forwarder::DnsQuery;
static const unsigned char sendbuff_[] =  {0xdb, 0x42, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
                              0x77, 0x77, 0x77, 0x0c, 0x6e, 0x6f, 0x72, 0x74, 0x68, 0x65, 0x61, 0x73, 0x74,
                              0x65, 0x72, 0x6e, 0x03, 0x65, 0x64, 0x75, 0x00, 0x00, 0x01, 0x00, 0x01};
class DnsQueryTest : public ::testing::Test {
 public:
  DnsQueryTest() {
    dnsquery_.reset(new DnsQuery(sendbuff_, sizeof(sendbuff_)));
  }
protected:
  std::unique_ptr<DnsQuery> dnsquery_;
};

TEST_F(DnsQueryTest, CheckTransactionID) {
 EXPECT_EQ(0xdb42, dnsquery_->TransactionId());
}

TEST_F(DnsQueryTest, WrongLenBuffer) {
  EXPECT_ANY_THROW(dnsquery_.reset(new DnsQuery(sendbuff_, 1025)));
}