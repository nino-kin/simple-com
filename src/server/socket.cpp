#include "socket.hpp"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "spdlog/spdlog.h"

Socket::Socket() {
    // Initialize a socket
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        spdlog::error("Failed to create socket.");
    }
}

Socket::~Socket() {
    Close();
}

bool Socket::Connect(const std::string& host, const uint16_t port) {
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &(server_address.sin_addr));

    // Connect to server
    if (connect(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        spdlog::error("Failed to connect to the server.");
        return false;
    }
    return true;
}

bool Socket::Send(const std::string& data) {
    ssize_t bytes_sent = send(socket_fd, data.c_str(), data.length(), 0);
    if (bytes_sent == -1) {
        spdlog::error("Failed to send data.");
        return false;
    }
    return true;
}

bool Socket::Receive(std::string& data) {
    const int buffer_size = 1024;
    char buffer[buffer_size];
    memset(buffer, 0, sizeof(buffer));

    ssize_t bytes_received = recv(socket_fd, buffer, buffer_size - 1, 0);
    if (bytes_received == -1) {
        spdlog::error("Failed to receive data.");
        return false;
    }

    data = buffer;
    return true;
}

void Socket::Close() {
    if (socket_fd != -1) {
        close(socket_fd);
        socket_fd = -1;
    }
}
