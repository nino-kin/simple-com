#include "socket.hpp"
#include "socket_exception.hpp"
#include "network_config.hpp"

#include <iostream>

#include "spdlog/spdlog.h"

int main() {
    try {
        const std::string host = NetworkConfig::HOST_ADDR; // Host address
        const int port = NetworkConfig::PORT_NO;           // Port number

        // Create a Socket and connect to the server
        Socket socket;
        if (!socket.Connect(host, port)) {
            spdlog::error("Failed to connect to the server.");
            return 1;
        }

        // Send data to the server
        std::string message = "Hello, Server!";
        if (!socket.Send(message)) {
            spdlog::error("Failed to send data to the server.");
            return 1;
        }
        spdlog::info("Send message from client!");  // TODO(ninokin): debug        

        // Receive and print the server's response
        std::string response;
        if (!socket.Receive(response)) {
            spdlog::error("Failed to receive data from the server.");
            return 1;
        }

        spdlog::info("Received from server: {}", response);

        // Close the socket
        socket.Close();
    } catch (const SocketException& e) {
        spdlog::error("SocketException: {}", e.what());
        return 1;
    } catch (const std::exception& e) {
        spdlog::error("Exception: {}", e.what());
        return 1;
    }

    return 0;
}
