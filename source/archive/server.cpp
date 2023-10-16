#include "socket_archive.hpp"
#include "socket_logger.hpp"
#include "socket_exception.hpp"
#include "can/can_frame.hpp"
#include "network_config.hpp"
#include "data_processor.hpp"

#include "spdlog/spdlog.h"

int main() {
    spdlog::info("Server is running...\n");
    try {
        // 1. Create a Socket
        Socket serverSocket(Socket::Type::UDP);

        // 2. Bind the Socket
        serverSocket.bind(NetworkConfig::PORT);

        // 3. listen() - Not needed for UDP

        while (true) {
            // 4. Block until there are connections from clients - Not needed for UDP

            // 5. Receive Data (request) from client
            CanFrame receivedFrame, replyFrame;
            std::string client_ip;
            uint16_t client_port;
            serverSocket.receive(receivedFrame, client_ip, client_port);

            spdlog::info("Received data from client - can_id: {}, can_dlc: {}, data: [{}, {}, {}, {}, {}, {}, {}, {}]",
                 receivedFrame.id_, receivedFrame.dlc_,
                 receivedFrame.data_[0], receivedFrame.data_[1], receivedFrame.data_[2], receivedFrame.data_[3],
                 receivedFrame.data_[4], receivedFrame.data_[5], receivedFrame.data_[6], receivedFrame.data_[7]);

            // 6. Process request
            replyFrame = DataProcessor::processRequest(receivedFrame);

            // 7. Send Data (reply) to client
            serverSocket.send(replyFrame, client_ip, client_port);

            // 8. close() - Not needed for UDP as it doesn't have a connection setup like TCP
        }
    } catch (const SocketException& e) {
        spdlog::error("SocketException: {}", e.what());
    }

    return 0;
}
