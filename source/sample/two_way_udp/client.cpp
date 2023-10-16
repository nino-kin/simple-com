#include "user_config.hpp"
#include "socket.hpp"

#include <iostream>

#include "spdlog/spdlog.h"

int main() {
    Socket socket;
    uint16_t port = NetworkConfig::CLIENT_PORT;

    if (!socket.Bind(port)) {
        return 1;
    }

    std::string server_ip = NetworkConfig::SERVER_ADDR;
    uint16_t server_port = NetworkConfig::SERVER_PORT;

    std::string request = "Hello, Server!";
    if (!socket.Send(request, server_ip, server_port)) {
        return 1;
    }

    std::string response, source_ip;
    uint16_t source_port;
    if (socket.Receive(response, source_ip, source_port)) {
        spdlog::info("Received from server: {0}  (from {1}:{2})", response, source_ip, source_port);
    }

    return 0;
}
