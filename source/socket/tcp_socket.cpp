#include "socket_exception.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>

#include "tcp_socket.hpp"

TCPSocket::TCPSocket() {
    socket_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd_ < 0) {
        error_flag_ = true;
        throw SocketException("Error creating socket");
    }
}

TCPSocket::~TCPSocket() {
    close();
}

bool TCPSocket::bind(uint16_t port) {
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (::bind(socket_fd_, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        error_flag_ = true;
        throw SocketException("Failed to bind");
    }
    return true;
}

bool TCPSocket::listen(int backlog) {
    if (::listen(socket_fd_, backlog) < 0) {
        error_flag_ = true;
        throw SocketException("Failed to listen");
    }
    return true;
}

bool TCPSocket::accept(TCPSocket& clientSocket) {
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    int client_fd = ::accept(socket_fd_, (struct sockaddr*)&client_address, &client_address_len);
    if (client_fd < 0) {
        error_flag_ = true;
        throw SocketException("Failed to accept");
    }

    clientSocket.socket_fd_ = client_fd;
    return true;
}

bool TCPSocket::connect(const std::string& ip_address, uint16_t port) {
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(ip_address.c_str());

    if (::connect(socket_fd_, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        error_flag_ = true;
        throw SocketException("Failed to connect");
    }
    return true;
}

// bool TCPSocket::send(const CanFrame& frame) {
bool TCPSocket::send(const CanFrame& frame, const std::string& dest_ip, uint16_t dest_port) {
    ssize_t bytes_sent = ::send(socket_fd_, &frame, sizeof(CanFrame), 0);
    if (bytes_sent < 0) {
        error_flag_ = true;
        throw SocketException("Failed to send CAN data");
    }
    return true;
}

bool TCPSocket::receive(CanFrame& frame, std::string& source_ip, uint16_t& source_port) {
    ssize_t bytes_received = ::recv(socket_fd_, &frame, sizeof(CanFrame), 0);
    if (bytes_received < 0) {
        error_flag_ = true;
        throw SocketException("Failed to receive CAN data");
    }
    return true;
}

void TCPSocket::close() {
    if (socket_fd_ >= 0) {
        ::close(socket_fd_);
        socket_fd_ = -1;
    }
}
