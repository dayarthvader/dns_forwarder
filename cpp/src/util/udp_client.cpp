//  DNS_FORWADER 2020
#include "util/udp_client.h"
#include <cstring>
#include <iostream>

using util_ns::UdpClient;

UdpClient::UdpClient(const std::string& server_ip, const std::string& server_port, const int wait_time_sec)
    : server_ip_(server_ip), server_port_(server_port) {
  if ((socket_fd_ = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(1);
  }
  struct timeval tv;
  tv.tv_sec = wait_time_sec;
  tv.tv_usec = 0;
  if (setsockopt(socket_fd_, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
    perror("Error");
  }
  memset((char*)&server_addr_, 0, sizeof(server_addr_));
  server_addr_.sin_family = AF_INET;
  server_addr_.sin_port = htons(atoi(server_port_.c_str()));
  server_addr_.sin_addr.s_addr = inet_addr(server_ip_.c_str());
}

UdpClient::~UdpClient() {
  Cleanup();
}

void UdpClient::Cleanup() {
  if (socket_fd_ != -1) {
    close(socket_fd_);
  }
  socket_fd_ = -1;
}

int UdpClient::Read(std::shared_ptr<Buffer> buffer) {
  struct sockaddr remote_addr_;
  socklen_t rcv_data_len = sizeof(remote_addr_);
  int ret = recvfrom(socket_fd_, buffer->buffer_.data(), util_ns::kMsgMaxSize, 0, reinterpret_cast<struct sockaddr*>(&remote_addr_), &rcv_data_len);
  if (ret < 0) {
    perror("Client read failed");
    buffer->BuffeLen(0);
  } else {
    buffer->BuffeLen(ret);
  }
  return ret;
}

int UdpClient::SendToPeer(std::shared_ptr<Buffer> buffer) {
  return sendto(socket_fd_, buffer->buffer_.data(), buffer->buff_len_, 0, reinterpret_cast<struct sockaddr*>(&server_addr_), sizeof(server_addr_));
}
