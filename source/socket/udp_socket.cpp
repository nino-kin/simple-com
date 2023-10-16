#include "socket/socket_exception.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>

#include "socket/udp_socket.hpp"

UDPSocket::UDPSocket() {
    socket_fd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd_ < 0) {
        error_flag_ = true;
        throw SocketException("Error creating socket");
    }
}

UDPSocket::~UDPSocket() {
    close();
}

bool UDPSocket::bind(uint16_t port) {
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;                /* IP protocol family.  */
    server_address.sin_port = htons(port);              /* Port number.         */
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); /* Internet address.    */

    if (::bind(socket_fd_, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        error_flag_ = true;
        throw SocketException("Failed to bind");
        return false;
    }
    return true;
}

bool UDPSocket::send(const CanFrame& frame, const std::string& dest_ip, uint16_t dest_port) {
    struct sockaddr_in dest_address;
    dest_address.sin_family = AF_INET;
    dest_address.sin_port = htons(dest_port);
    inet_pton(AF_INET, dest_ip.c_str(), &(dest_address.sin_addr));

    ssize_t bytes_sent = sendto(socket_fd_, &frame, sizeof(CanFrame), 0, (struct sockaddr*)&dest_address, sizeof(dest_address));
    if (bytes_sent < 0) {
        error_flag_ = true;
        throw SocketException("Failed to send CAN data");
        return false;
    }
    return true;
}

bool UDPSocket::receive(CanFrame& frame, std::string& source_ip, uint16_t& source_port) {
    struct sockaddr_in source_address;
    socklen_t source_address_len = sizeof(source_address);

    ssize_t bytes_received = recvfrom(socket_fd_, &frame, sizeof(CanFrame), 0, (struct sockaddr*)&source_address, &source_address_len);
    if (bytes_received < 0) {
        error_flag_ = true;
        throw SocketException("Failed to receive CAN data");
        return false;
    }

    source_ip = inet_ntoa(source_address.sin_addr);
    source_port = ntohs(source_address.sin_port);

    return true;
}

void UDPSocket::close() {
    if (socket_fd_ >= 0) {
        ::close(socket_fd_);
        socket_fd_ = -1;
    }
}
