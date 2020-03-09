//  DNS_FORWADER 2020
#include <gtest/gtest.h>
#include <iostream>
#include "util/udp_client.h"
#include "util/udp_server.h"
#include "util/buffer.h"

static char port[] = "9000";
static char server_ip[] = "127.0.0.1";
static const unsigned char sendbuff[] =  {0xdb, 0x42, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
                              0x77, 0x77, 0x77, 0x0c, 0x6e, 0x6f, 0x72, 0x74, 0x68, 0x65, 0x61, 0x73, 0x74,
                              0x65, 0x72, 0x6e, 0x03, 0x65, 0x64, 0x75, 0x00, 0x00, 0x01, 0x00, 0x01};
using util_ns::UdpServer;
using util_ns::UdpClient;
using util_ns::Buffer;

class UdpServerClientTest : public ::testing::Test {
 public:
  UdpServerClientTest() {
    buffer_ = std::make_shared<Buffer>();
    memcpy(buffer_->buffer_.data(), sendbuff, sizeof(sendbuff));
    buffer_->BuffeLen(sizeof(sendbuff));
    udp_server_ = std::unique_ptr<UdpServer>(new UdpServer(server_ip, port));
    udp_client_ = std::unique_ptr<UdpClient>(new UdpClient(server_ip, port, 1));
  }
 protected:
  std::shared_ptr<Buffer> buffer_{nullptr};
  std::unique_ptr<UdpServer> udp_server_{nullptr};
  std::unique_ptr<UdpClient> udp_client_{nullptr};
};

TEST_F(UdpServerClientTest, ReadData) {
  std::shared_ptr<Buffer> recv_buffer = std::make_shared<Buffer>();
  EXPECT_EQ(sizeof(sendbuff), udp_client_->SendToPeer(buffer_));
  EXPECT_EQ(sizeof(sendbuff), udp_server_->Read(recv_buffer));
  EXPECT_EQ(sizeof(sendbuff), recv_buffer->buff_len_);
  EXPECT_EQ(0xdb,recv_buffer->buffer_.data()[0]);
  EXPECT_EQ(0x42,recv_buffer->buffer_.data()[1]);
  EXPECT_EQ(sizeof(sendbuff), udp_server_->SendToPeer(buffer_));
  EXPECT_EQ(sizeof(sendbuff), udp_client_->Read(recv_buffer));
  EXPECT_EQ(0xdb,recv_buffer->buffer_.data()[0]);
  EXPECT_EQ(0x42,recv_buffer->buffer_.data()[1]);
  EXPECT_EQ(sizeof(sendbuff), recv_buffer->buff_len_);
  EXPECT_EQ(sizeof(sendbuff), udp_server_->SendToPeer(buffer_));
}

TEST_F(UdpServerClientTest, SendIvalidPeer) {
  EXPECT_EQ(-1, udp_server_->SendToPeer(buffer_));
}
