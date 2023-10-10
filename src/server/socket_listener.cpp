#include "socket_exception.hpp"
#include "socket_utils.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "spdlog/spdlog.h"

#include "socket_listener.hpp"

SocketListener::SocketListener(int port) : serverSocket_(-1), clientSocket_(-1) {
    // Create a TCP socket
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket_ < 0) {
        throw SocketException("Failed to create socket");
    }

    // Set socket options (optional)
    int opt = 1;
    if (setsockopt(serverSocket_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        throw SocketException("Failed to set socket options");
    }

    // Bind the socket
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket_, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        throw SocketException("Failed to bind socket");
    }

    // Start listening
    if (listen(serverSocket_, 1) < 0) {
        throw SocketException("Failed to listen for connections");
    }

    // Accept the first connection
    sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    clientSocket_ = accept(serverSocket_, (struct sockaddr*)&clientAddress, &clientAddressLength);
    if (clientSocket_ < 0) {
        throw SocketException("Failed to accept connection");
    }
}

SocketListener::~SocketListener() {
    closeSocket();
}

int SocketListener::acceptConnection() {
    if (clientSocket_ < 0) {
        throw SocketException("No active connection");
    }

    return clientSocket_;
}

void SocketListener::closeSocket() {
    if (clientSocket_ >= 0) {
        close(clientSocket_);
        clientSocket_ = -1;
    }

    if (serverSocket_ >= 0) {
        close(serverSocket_);
        serverSocket_ = -1;
    }
}
