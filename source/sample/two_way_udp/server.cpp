#include "user_config.hpp"
#include "socket.hpp"

#include <iostream>

#include "spdlog/spdlog.h"


int main() {
    Socket socket;
    uint16_t port = NetworkConfig::SERVER_PORT;
    if (!socket.Bind(port)) {
        return 1;
    }
    spdlog::info("Socket was associated with a local endpoint.");
    spdlog::info("Waiting to receive data from the client...\n");

    while (true) {
        std::string request, client_ip;
        uint16_t client_port;
        if (socket.Receive(request, client_ip, client_port)) {
            spdlog::info("Received request from {0}:{1}: {2}", client_ip, client_port, request);

            // Process the request (e.g., send a response)
            std::string response = "Hello, Client!";
            if (!socket.Send(response, client_ip, client_port)) {
                return 1;
            }
        }
    }

    return 0;
}
