#include "socket.hpp"
#include "socket_logger.hpp"
#include "socket_exception.hpp"
#include "can_frame.hpp"
#include "network_config.hpp"

#include "spdlog/spdlog.h"

int main() {
    try {
        // 1. Create a Socket
        Socket clientSocket(Socket::Type::UDP);

        // 2. Connection establishment
        clientSocket.connect(NetworkConfig::HOST_ADDR, NetworkConfig::PORT); // Connect to the server's IP address and port as an example

        // 3. Data request to server
        CanFrame requestFrame = {
            .can_id = 123,  // Any ID
            .can_dlc = 8,   // Length of data to send (8 bytes)
            .data = {1, 2, 3, 4, 5, 6, 7, 8} // Data to send
        };

        clientSocket.send(&requestFrame, sizeof(requestFrame));

        // 4. Data (reply) from server
        CanFrame receivedFrame;
        clientSocket.receive(&receivedFrame, sizeof(receivedFrame));

        // Add logic here to use the data from receivedFrame

        // 5. Close socket
        // No specific close procedure is required, but if necessary, you can use the following:
        // clientSocket.close();

    } catch (const SocketException& e) {
        spdlog::error("SocketException: {}", e.what());
    }

    return 0;
}
