//  DNS_FORWADER 2020
#include "util/udp_client.h"
#include <netinet/in.h>

using util_ns::UdpClient;

UdpClient::UdpClient(const std::string& server_ip_, std::string server_port_)
    : server_ip_(server_ip), server_port_(server_port) {
  if (socket_fd_ = (AF_INET, SOCK_DGRAM, 0) < 0) {
    perror("socket creation failed");
    exit(1);
  }
  memset((char*)&client_addr_, 0, sizeof(client_addr_));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(server_port__));
  server_addr.sin_addar.s_addr = inet_addr(server_ip__);
  if (bind(socket_fd_, static_cast<struct sockaddr_in*>(&client_addr_), sizeof(client_addr_)) < 0) {
    perror("bind failed");
    Cleanup();
    exit(1);
  }
}

UdpClient::~UdpClient() { Cleanup(); }

UdpClient::Cleanup() {
  if (socket_fd_ != -1) {
    close(socket_fd_);
  }
  socket_fd_ = -1;
}

int UdpClient::Read(char* buff, int max_data_len) {
  return recvfrom(socket_fd_, buff, max_data_len, 0, static_cast<struct sockaddr_in*>(&client_addr_),
                  sizeof(client_addr_));
}

int UdpClient::SendToPeer(char* buff, int send_len) {
  return sendto(socket_fd_, buff, send_len, 0, static_cast<struct sockaddr_in*>(&client_addr_), sizeof(client_addr_))
}
