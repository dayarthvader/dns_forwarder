//  DNS_FORWADER 2020
#include "util/udp_server.h"
#include <netinet/in.h>

using util_ns::UdpServer;

UdpServer::UdpServer(const std::string& serving_ip, std::string serving_port)
    : serving_ip_(serving_ip), serving_port_(serving_port) {
  if (socket_fd_ = (AF_INET, SOCK_DGRAM, 0) < 0) {
    perror("socket creation failed");
    exit(1);
  }
  memset((char*)&server_addr, 0, sizeof(server_addr));
  server_addr_.sin_family = AF_INET;
  server_addr_.sin_port = htons(atoi(serving_port_));
  server_addr_.sin_addar.s_addr = inet_addr(serving_ip_);
  if (bind(socket_fd_, static_cast<struct sockaddr_in*>(&server_addr_), sizeof(server_addr_)) < 0) {
    perror("bind failed");
    Cleanup();
    exit(1);
  }
}

UdpServer::~UdpServer() { Cleanup(); }

UdpServer::Cleanup() {
  if (socket_fd_ != -1) {
    close(socket_fd_);
  }
  socket_fd_ = -1;
}

int UdpServer::Read(char* buff, int max_data_len) {
  return recvfrom(socket_fd_, buff, max_data_len, 0, static_cast<struct sockaddr_in*>(&client_addr_),
                  sizeof(client_addr_));
}

int UdpServer::SendToPeer(char* buff, int send_len) {
  return sendto(socket_fd_, buff, send_len, 0, static_cast<struct sockaddr_in*>(&client_addr_), sizeof(client_addr_))
}
