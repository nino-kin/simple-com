#include "socket_exception.hpp"
#include "can_frame.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>

#include "spdlog/spdlog.h"

#include "socket.hpp"

Socket::Socket(Type type) : socket_fd_(-1), type_(type), errorFlag_(false) {
    if (type_ == Type::UDP) {
        socket_fd_ = socket(AF_INET, SOCK_DGRAM, 0);
    } else if (type_ == Type::TCP) {
        socket_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    } else {
        spdlog::error("An undefined socket type is declared.");
    }

    if (socket_fd_ < 0) {
        spdlog::error("Error creating socket.");
        errorFlag_ = true;
        throw SocketException("Failed to create socket");
    }
}

Socket::~Socket() {
    close();
}

bool Socket::bind(uint16_t port) {
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;                           /* IP protocol family.  */
    server_address.sin_port = htons(port);                         /* Port number.         */
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); /* Internet address.    */

    if (::bind(socket_fd_, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        spdlog::error("Failed to bind socket.");
        errorFlag_ = true;
        throw SocketException("Failed to bind");
        return false;
    }
    return true;
}

bool Socket::connect(const std::string& ipAddress, uint16_t port) {
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(ipAddress.c_str());

    if (::connect(socket_fd_, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        spdlog::error("Error connecting to server.");
        errorFlag_ = true;
        throw SocketException("Failed to connect");
        return false;
    }
    return true;
}

bool Socket::send(const CanFrame& can_frame, const std::string& dest_ip, uint16_t dest_port) {
    struct sockaddr_in dest_address;
    dest_address.sin_family = AF_INET;
    dest_address.sin_port = htons(dest_port);
    inet_pton(AF_INET, dest_ip.c_str(), &(dest_address.sin_addr));

    ssize_t bytes_sent = sendto(socket_fd_, &can_frame, sizeof(CanFrame), 0, (struct sockaddr*)&dest_address, sizeof(dest_address));
    if (bytes_sent < 0) {
        spdlog::error("Failed to send CAN data.");
        errorFlag_ = true;
        throw SocketException("Failed to send CAN data");
        return false;
    }
    return true;
}

bool Socket::receive(CanFrame& can_frame, std::string& source_ip, uint16_t& source_port) {
    struct sockaddr_in source_address;
    socklen_t source_address_len = sizeof(source_address);

    ssize_t bytes_received = recvfrom(socket_fd_, &can_frame, sizeof(CanFrame), 0, (struct sockaddr*)&source_address, &source_address_len);
    if (bytes_received < 0) {
        spdlog::error("Failed to receive CAN data.");
        errorFlag_ = true;
        throw SocketException("Failed to receive CAN data");
        return false;
    }

    source_ip = inet_ntoa(source_address.sin_addr);
    source_port = ntohs(source_address.sin_port);

    return true;
}

void Socket::close() {
    if (socket_fd_ >= 0) {
        ::close(socket_fd_);
        socket_fd_ = -1;
    }
}

bool Socket::hasError() const {
    return errorFlag_;
}
