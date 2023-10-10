#include "socket.hpp"
#include "socket_logger.hpp"
#include "socket_exception.hpp"
#include "can_frame.hpp"
#include "network_config.hpp"

#include "spdlog/spdlog.h"

int main() {
    try {
        // 1. Create a Socket
        Socket serverSocket(Socket::Type::UDP); // Create a UDP Socket

        // 2. Bind the Socket
        // serverSocket.bind("127.0.0.1", 5555); // Bind to IP address 127.0.0.1 and port 5555 as an example
        serverSocket.bind(NetworkConfig::HOST_ADDR, NetworkConfig::PORT); // Bind to IP address 127.0.0.1 and port 5555 as an example

        // 3. listen() - Not needed for UDP

        while (true) {
            // 4. Block until there are connections from clients - Not needed for UDP

            // 5. Receive Data (request) from client
            CanFrame receivedFrame;
            serverSocket.receive(&receivedFrame, sizeof(receivedFrame));

            // 6. Process request
            // Add logic to process receivedFrame here

            // 7. Send Data (reply) to client
            CanFrame replyFrame = {}; // Initialize a CanFrame for the reply
            serverSocket.send(&replyFrame, sizeof(replyFrame));

            // 8. close() - Not needed for UDP as it doesn't have a connection setup like TCP
        }
    } catch (const SocketException& e) {
        spdlog::error("SocketException: {}", e.what());
    }

    return 0;
}
