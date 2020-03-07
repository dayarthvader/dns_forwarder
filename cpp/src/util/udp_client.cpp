//  DNS_FORWADER 2020
#include "util/udp_client.h"
#include <cstring>

using util_ns::UdpClient;

UdpClient::UdpClient(const std::string& server_ip, std::string server_port)
    : server_ip_(server_ip), server_port_(server_port) {
  if ((socket_fd_ = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(1);
  }
  memset((char*)&client_addr_, 0, sizeof(client_addr_));
  client_addr_.sin_family = AF_INET;
  client_addr_.sin_port = htons(atoi(server_port_.c_str()));
  client_addr_.sin_addr.s_addr = inet_addr(server_ip_.c_str());
}

UdpClient::~UdpClient() { Cleanup(); }

void UdpClient::Cleanup() {
  if (socket_fd_ != -1) {
    close(socket_fd_);
  }
  socket_fd_ = -1;
}

int UdpClient::Read(unsigned char* buff, int max_data_len) {
  socklen_t rcv_data_len{0};
  return recvfrom(socket_fd_, buff, max_data_len, 0, reinterpret_cast<struct sockaddr*>(&client_addr_), &rcv_data_len);
}

int UdpClient::SendToPeer(unsigned char* buff, int send_len) {
  return sendto(socket_fd_, buff, send_len, 0, reinterpret_cast<struct sockaddr*>(&client_addr_), sizeof(client_addr_));
}
