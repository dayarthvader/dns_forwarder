//  DNS_FORWADER 2020
#include "util/udp_server.h"
#include <cstring>
#include <iostream>
using util_ns::UdpServer;

UdpServer::UdpServer(const std::string& serving_ip, const std::string& serving_port)
    : serving_ip_(serving_ip), serving_port_(serving_port) {
  if ((socket_fd_ = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(1);
  }
  int so_addr_reuse = 1;
  if ((setsockopt(socket_fd_, SOL_SOCKET, SO_REUSEADDR,&so_addr_reuse,sizeof(so_addr_reuse) )) < 0) {
    perror("setsocopt SO_REUSEADDR failed");
    exit(1);
  }
  memset((char*)&server_addr_, 0, sizeof(server_addr_));
  server_addr_.sin_family = AF_INET;
  server_addr_.sin_port = htons(atoi(serving_port_.c_str()));
  server_addr_.sin_addr.s_addr = inet_addr(serving_ip_.c_str());
  if (bind(socket_fd_, (struct sockaddr*)&server_addr_, sizeof(server_addr_)) < 0) {
    perror("bind failed");
    Cleanup();
    exit(1);
  }
}

UdpServer::~UdpServer() {
  Cleanup();
}

void UdpServer::Cleanup() {
  if (socket_fd_ != -1) {
    close(socket_fd_);
  }
  socket_fd_ = -1;
}

int UdpServer::Read(std::shared_ptr<Buffer> buffer, struct sockaddr* client_addr) {
  int ret = -1;
  socklen_t rcv_data_len = sizeof(*client_addr);
  ret = recvfrom(socket_fd_, buffer->buffer_.data(), util_ns::kMsgMaxSize, 0, (struct sockaddr *) client_addr, &rcv_data_len);
  if (ret < 0) {
    perror("Server: recvfrom failed");
    buffer->BuffeLen(0);

  }
  else {
    buffer->BuffeLen(ret);
  }
  return ret;
}

int UdpServer::SendToPeer(std::shared_ptr<Buffer> buffer, struct sockaddr* client_addr) {
  int ret = -1;
  if ((ret = sendto(socket_fd_, buffer->buffer_.data(), buffer->buff_len_, 0, (struct sockaddr *) client_addr, sizeof(*client_addr)))  < 0) {
    perror("Server: sendto failed");
  }
  return ret;
}
