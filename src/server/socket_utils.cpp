#include "socket_utils.hpp"
#include <arpa/inet.h>

std::string SocketUtils::GetIPAddress(const sockaddr_in& sockaddr) {
    char ip_buffer[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(sockaddr.sin_addr), ip_buffer, INET_ADDRSTRLEN);
    return std::string(ip_buffer);
}

unsigned short SocketUtils::GetPort(const sockaddr_in& sockaddr) {
    return ntohs(sockaddr.sin_port);
}

in_addr SocketUtils::ConvertToIPAddress(const std::string& ip_address) {
    in_addr result;
    inet_pton(AF_INET, ip_address.c_str(), &(result.s_addr));
    return result;
}
