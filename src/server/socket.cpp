#include "socket_exception.hpp"

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
        spdlog::error("{} is an undefined socket type.", type_);
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

bool Socket::bind(const std::string& ipAddress, uint16_t port) {
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;                           /* IP protocol family.  */
    server_address.sin_port = htons(port);                         /* Port number.         */
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); /* Internet address.    */
    // TODO(nino-kin): only clients on the same computer could connect to your server.
    // server_address.sin_addr.s_addr = inet_addr(ipAddress.c_str()); /* Internet address.    */

    if (::bind(socket_fd_, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        spdlog::error("Failed to bind socket.");
        errorFlag_ = true;
        throw SocketException("Failed to bind");
    }
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

bool Socket::send(const void* data, size_t size) {

    ssize_t sent_bytes = ::send(socket_fd_, data, size, 0);
    if (sent_bytes < 0) {
        spdlog::error("Error sending data.");
        errorFlag_ = true;
        throw SocketException("Failed to send data");
        return false;
    }
    return true;
}

bool Socket::receive(void* buffer, size_t size) {
    ssize_t received_bytes = ::recv(socket_fd_, buffer, size, 0);
    if (received_bytes < 0) {
        spdlog::error("Error receiving data.");
        errorFlag_ = true;
        throw SocketException("Failed to receive data");
        return false;
    }
    return true;
}

void Socket::close() {
    if (socket_fd_ < 0) {
        ::close(socket_fd_);
        socket_fd_ = -1;
    }
}

bool Socket::hasError() const {
    return errorFlag_;
}
