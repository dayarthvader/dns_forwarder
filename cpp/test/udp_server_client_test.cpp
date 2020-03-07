//  DNS_FORWADER 2020
#include "util/udp_server.h"
#include <gtest/gtest.h>
#include "util/udp_client.h"

static int port = 9000;
static char server_ip[] = "127.0.0.1";
using util_ns::UdpServer;

class UdpServerTest : public ::testing::Test {
 public:
  UdpServerTest() {}

 private:
  UdpServer udp_server_(server_ip, port);
  UdpClient udp_client_(server_ip, port);
};

TEST_F(UdpServerTest, ReadData) {
  unsigned char sendbuff[] = {0xdb, 0x42, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
                              0x77, 0x77, 0x77, 0x0c, 0x6e, 0x6f, 0x72, 0x74, 0x68, 0x65, 0x61, 0x73, 0x74,
                              0x65, 0x72, 0x6e, 0x03, 0x65, 0x64, 0x75, 0x00, 0x00, 0x01, 0x00, 0x01};
  unsigned char recvBuff[1024];
  EXPECT_EQ(sizeof(buff), udp_client_.SendToPeer(&buff[0], sizeof(buff)));
  EXPECT_EQ(sizeof(buff), udp_server_.Read(recvBuff, 1024));
}
