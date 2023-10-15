#include "socket.hpp"
#include "socket_logger.hpp"
#include "socket_exception.hpp"
#include "can/can_frame.hpp"
#include "network_config.hpp"

#include "spdlog/spdlog.h"

int main() {
    spdlog::info("Client is running...\n");
    try {
        // 1. Create a Socket
        Socket clientSocket(Socket::Type::UDP);

        // 2. Connection establishment (Not needed for UDP)

        // 3. Data request to server
        CanFrame requestFrame = {
            .can_id = 123,  // Any ID
            .can_dlc = 8,   // Length of data to send (8 bytes)
            .data = {1, 2, 3, 4, 5, 6, 7, 8} // Data to send
        };

        clientSocket.send(requestFrame, NetworkConfig::HOST_ADDR, NetworkConfig::PORT);

        // 4. Data (reply) from server
        CanFrame receivedFrame;
        std::string source_ip;
        uint16_t source_port;

        clientSocket.receive(receivedFrame, source_ip, source_port);

        // Add logic here to use the data from receivedFrame
        spdlog::info("Received data from server - can_id: {}, can_dlc: {}, data: [{}, {}, {}, {}, {}, {}, {}, {}]",
                 receivedFrame.can_id, receivedFrame.can_dlc,
                 receivedFrame.data[0], receivedFrame.data[1], receivedFrame.data[2], receivedFrame.data[3],
                 receivedFrame.data[4], receivedFrame.data[5], receivedFrame.data[6], receivedFrame.data[7]);

        // 5. Close socket
        // No specific close procedure is required, but if necessary, you can use the following:
        // clientSocket.close();

    } catch (const SocketException& e) {
        spdlog::error("SocketException: {}", e.what());
    }

    return 0;
}
