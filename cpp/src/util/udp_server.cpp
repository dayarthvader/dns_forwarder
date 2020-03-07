//  DNS_FORWADER 2020
#include "util/udp_server.h"
#include <cstring>

using util_ns::UdpServer;

UdpServer::UdpServer(const std::string& serving_ip, std::string serving_port)
    : serving_ip_(serving_ip), serving_port_(serving_port) {
  if ((socket_fd_ = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(1);
  }
  int so_addr_reuse = 1;
  if ((setsockopt(socket_fd_, SOL_SOCKET, SO_REUSEADDR,&so_addr_reuse,sizeof(so_addr_reuse) )) < 0) {
    perror("setsocopt creation failed");
    exit(1);
  }
  memset((char*)&server_addr_, 0, sizeof(server_addr_));
  server_addr_.sin_family = AF_INET;
  server_addr_.sin_port = htons(atoi(serving_port_.c_str()));
  server_addr_.sin_addr.s_addr = inet_addr(serving_ip_.c_str());
  if (bind(socket_fd_, reinterpret_cast<struct sockaddr*>(&server_addr_), sizeof(server_addr_)) < 0) {
    perror("bind failed");
    Cleanup();
    exit(1);
  }
}

UdpServer::~UdpServer() { Cleanup(); }

void UdpServer::Cleanup() {
  if (socket_fd_ != -1) {
    close(socket_fd_);
  }
  socket_fd_ = -1;
}

int UdpServer::Read(unsigned char* buff, int max_data_len) {
  socklen_t rcv_data_len{0};
  return recvfrom(socket_fd_, buff, max_data_len, 0, reinterpret_cast<struct sockaddr*>(&client_addr_),&rcv_data_len);
}

int UdpServer::SendToPeer(unsigned char* buff, int send_len) {
  return sendto(socket_fd_, buff, send_len, 0, reinterpret_cast<struct sockaddr*>(&client_addr_), sizeof(client_addr_));
}
