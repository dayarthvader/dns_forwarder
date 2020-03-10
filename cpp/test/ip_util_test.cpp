//  DNS_FORWADER 2020
#include <gtest/gtest.h>
#include "util/ip_util.h"

TEST(IpUtilTest, validIp) {
  EXPECT_TRUE(util_ns::ip_util_ns::ValidIp("127.0.0.1"));
}

TEST(IpUtilTest, InvalidIp) {
  EXPECT_FALSE(util_ns::ip_util_ns::ValidIp("127001"));
}