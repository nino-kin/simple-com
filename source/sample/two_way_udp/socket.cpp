#include "socket.hpp"
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "spdlog/spdlog.h"

Socket::Socket() {
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd == -1) {
        spdlog::error("Failed to create socket.");
    }
}

Socket::~Socket() {
    Close();
}

bool Socket::Bind(uint16_t port) {
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;         /* IP protocol family.  */
    server_address.sin_port = htons(port);       /* Port number.         */
    server_address.sin_addr.s_addr = INADDR_ANY; /* Internet address.    */

    if (bind(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        spdlog::error("Failed to bind socket.");
        return false;
    }

    return true;
}

bool Socket::Send(const std::string& data, const std::string& dest_ip, uint16_t dest_port) {
    struct sockaddr_in dest_address;
    dest_address.sin_family = AF_INET;
    dest_address.sin_port = htons(dest_port);
    inet_pton(AF_INET, dest_ip.c_str(), &(dest_address.sin_addr));

    ssize_t bytes_sent = sendto(socket_fd, data.c_str(), data.length(), 0, (struct sockaddr*)&dest_address, sizeof(dest_address));
    if (bytes_sent == -1) {
        spdlog::error("Failed to send data.");
        return false;
    }

    return true;
}

bool Socket::Receive(std::string& data, std::string& source_ip, uint16_t& source_port) {
    const int buffer_size = 2048;
    char buffer[buffer_size];
    memset(buffer, 0, sizeof(buffer));

    struct sockaddr_in source_address;
    socklen_t source_address_len = sizeof(source_address);

    ssize_t bytes_received = recvfrom(socket_fd, buffer, buffer_size - 1, 0, (struct sockaddr*)&source_address, &source_address_len);
    if (bytes_received == -1) {
        spdlog::error("Failed to receive data.");
        return false;
    }

    data = buffer;
    source_ip = inet_ntoa(source_address.sin_addr);
    source_port = ntohs(source_address.sin_port);

    return true;
}

void Socket::Close() {
    if (socket_fd != -1) {
        close(socket_fd);
        socket_fd = -1;
    }
}
