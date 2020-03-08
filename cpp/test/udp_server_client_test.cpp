//  DNS_FORWADER 2020
#include "util/udp_server.h"
#include <gtest/gtest.h>
#include "util/udp_client.h"
#include <iostream>

static char port[] = "9000";
static char server_ip[] = "127.0.0.1";
static const unsigned char sendbuff_[] =  {0xdb, 0x42, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
                              0x77, 0x77, 0x77, 0x0c, 0x6e, 0x6f, 0x72, 0x74, 0x68, 0x65, 0x61, 0x73, 0x74,
                              0x65, 0x72, 0x6e, 0x03, 0x65, 0x64, 0x75, 0x00, 0x00, 0x01, 0x00, 0x01};
using util_ns::UdpServer;
using util_ns::UdpClient;

class UdpServerClientTest : public ::testing::Test {
 public:
  UdpServerClientTest() {
    udp_server_ = std::unique_ptr<UdpServer>(new UdpServer(server_ip, port));
    udp_client_ = std::unique_ptr<UdpClient>(new UdpClient(server_ip, port));
  }
 protected:
  std::unique_ptr<UdpServer> udp_server_;
  std::unique_ptr<UdpClient> udp_client_;
};

TEST_F(UdpServerClientTest, ReadData) {
  unsigned char recvBuff[1024];  // DNS Query answers are max 550 bytes
  EXPECT_EQ(sizeof(sendbuff_), udp_client_->SendToPeer(&sendbuff_[0], sizeof(sendbuff_)));
  EXPECT_EQ(sizeof(sendbuff_), udp_server_->Read(recvBuff, 1024));
  EXPECT_EQ(0xdb,recvBuff[0]);
  EXPECT_EQ(0x42,recvBuff[1]);
  EXPECT_EQ(sizeof(sendbuff_), udp_server_->SendToPeer(&sendbuff_[0], sizeof(sendbuff_)));
  EXPECT_EQ(sizeof(sendbuff_), udp_client_->Read(recvBuff, 1024));
  EXPECT_EQ(0xdb,recvBuff[0]);
  EXPECT_EQ(0x42,recvBuff[1]);
  EXPECT_EQ(sizeof(sendbuff_), udp_server_->SendToPeer(&sendbuff_[0], sizeof(sendbuff_)));
}

TEST_F(UdpServerClientTest, SendIvalidPeer) {
  EXPECT_EQ(-1, udp_server_->SendToPeer(&sendbuff_[0], sizeof(sendbuff_)));
}
