//  DNS_FORWADER 2020
#include <gtest/gtest.h>
#include "util/buffer.h"
#include "dns_forwarder/dns_query.h"
using dns_forwarder_ns::DnsQuery;
static const unsigned char sendbuff[] =  {0xdb, 0x42, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
                              0x77, 0x77, 0x77, 0x0c, 0x6e, 0x6f, 0x72, 0x74, 0x68, 0x65, 0x61, 0x73, 0x74,
                              0x65, 0x72, 0x6e, 0x03, 0x65, 0x64, 0x75, 0x00, 0x00, 0x01, 0x00, 0x01};
class DnsQueryTest : public ::testing::Test {
 public:
  DnsQueryTest() {
    buffer_ = std::make_shared<Buffer>();
    memcpy(buffer_->buffer_.data(), sendbuff, sizeof(sendbuff));
    buffer_->BuffeLen(sizeof(sendbuff));
    dnsquery_.reset(new DnsQuery(buffer_));
  }
protected:
  std::unique_ptr<DnsQuery> dnsquery_;
  std::shared_ptr<Buffer> buffer_;
};

TEST_F(DnsQueryTest, CheckTransactionID) {
 EXPECT_EQ(0xdb42, dnsquery_->TransactionId());
}
