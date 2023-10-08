#include "socket_listener.hpp"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "spdlog/spdlog.h"

SocketListener::SocketListener(const std::string& host, const uint16_t port)
    : host(host), port(port), listener_fd(-1), running(false), connection_callback(nullptr) {}

SocketListener::~SocketListener() {
    Stop();
}

bool SocketListener::Start() {
    if (listener_fd != -1 || running) {
        return false; // Invalid if already started
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &(server_address.sin_addr));

    listener_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listener_fd == -1) {
        spdlog::error("Failed to create listener socket.");
        return false;
    }

    if (bind(listener_fd, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        spdlog::error("Failed to bind listener socket.");
        close(listener_fd);
        listener_fd = -1;
        return false;
    }

    if (listen(listener_fd, 5) == -1) {
        spdlog::error("Failed to start listening.");
        close(listener_fd);
        listener_fd = -1;
        return false;
    }

    running = true;
    listener_thread = std::thread(&SocketListener::Listen, this);

    return true;
}

void SocketListener::Stop() {
    if (running) {
        running = false;
        if (listener_thread.joinable()) {
            listener_thread.join();
        }

        if (listener_fd != -1) {
            close(listener_fd);
            listener_fd = -1;
        }
    }
}

void SocketListener::SetConnectionCallback(ConnectionCallback callback) {
    connection_callback = callback;
}

void SocketListener::Listen() {
    while (running) {
        struct sockaddr_in client_address;
        socklen_t client_address_len = sizeof(client_address);
        int client_fd = accept(listener_fd, (struct sockaddr*)&client_address, &client_address_len);
        if (client_fd == -1) {
            spdlog::error("Failed to accept connection.");
            continue;
        }

        if (connection_callback) {
            connection_callback(client_fd);
        } else {
            close(client_fd);
        }
    }
}
