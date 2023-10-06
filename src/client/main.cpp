#include "socket.hpp"
#include "socket_exception.hpp"
#include "network_config.hpp"
#include <iostream>

int main() {
    try {
        const std::string host = NetworkConfig::HOST_ADDR; // Host address
        const int port = NetworkConfig::PORT_NO;           // Port number

        // Create a Socket and connect to the server
        Socket socket;
        if (!socket.Connect(host, port)) {
            std::cerr << "Failed to connect to the server." << std::endl;
            return 1;
        }

        // Send data to the server
        std::string message = "Hello, Server!";
        if (!socket.Send(message)) {
            std::cerr << "Failed to send data to the server." << std::endl;
            return 1;
        }

        // Receive and print the server's response
        std::string response;
        if (!socket.Receive(response)) {
            std::cerr << "Failed to receive data from the server." << std::endl;
            return 1;
        }

        std::cout << "Received from server: " << response << std::endl;

        // Close the socket
        socket.Close();
    } catch (const SocketException& e) {
        std::cerr << "SocketException: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
