
#include "socket_options.hpp"
#include <iostream>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>

#include "spdlog/spdlog.h"

bool SocketOptions::SetTimeout(int socket_fd, int timeout_ms) {
    struct timeval timeout;
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;

    if (setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1 ||
        setsockopt(socket_fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) == -1) {
        spdlog::error("Failed to set socket timeout.");
        return false;
    }
    return true;
}

bool SocketOptions::SetBufferSize(int socket_fd, int buffer_size) {
    if (setsockopt(socket_fd, SOL_SOCKET, SO_RCVBUF, &buffer_size, sizeof(buffer_size)) == -1 ||
        setsockopt(socket_fd, SOL_SOCKET, SO_SNDBUF, &buffer_size, sizeof(buffer_size)) == -1) {
        spdlog::error("Failed to set socket buffer size.");
        return false;
    }
    return true;
}
