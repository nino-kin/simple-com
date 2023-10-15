#include "error_logger.hpp"
#include "socket.hpp"
#include "socket_manager.hpp"
#include "socket_factory.hpp"
#include "socket_exception.hpp"
#include "network_config.hpp"
#include "can/can_frame.hpp"

#include <string>

#include "spdlog/spdlog.h"

/**
 * @brief The main function that runs the client.
 *
 * This function initializes a UDP socket, sends data to the server
 * and receives a reply back from the client.
 *
 * @return The exit status of the program.
 */
int main() {
    spdlog::info("Client is running...\n");
    try {
        // Create a UDP socket factory
        UDPSocketFactory udpFactory;

        // Create a socket manager and set the factory
        SocketManager& manager = SocketManager::getInstance();
        manager.setSocketFactory(&udpFactory);

        // Add an error logger as an observer
        ErrorLogger logger;
        manager.addObserver(&logger);

        // Create a client socket
        Socket* clientSocket = manager.getSocket();

        // Set destination IP and port
        std::string destIP = NetworkConfig::HOST_ADDR;  // Set the server's IP
        uint16_t destPort = NetworkConfig::PORT;        // Set the server's port

        // Prepare data to send
        CanFrame requestFrame = {
            .id_ = 123,  // Any ID
            .rtr_ = 0,   // Dominant
            .dlc_ = 8,   // Length of data to send (8 bytes)
            .data_ = {1, 2, 3, 4, 5, 6, 7, 8} // Data to send
        };
        // Send data
        if (!clientSocket->send(requestFrame, destIP, destPort)) {
            spdlog::error("Failed to send data");
            return 1;
        }

        // Data (reply) from server
        CanFrame receivedFrame;
        std::string source_ip;
        uint16_t source_port;

        clientSocket->receive(receivedFrame, source_ip, source_port);

        // Add logic here to use the data from receivedFrame
        spdlog::info("Received data from server - can_id: {}, can_dlc: {}, data: [{}, {}, {}, {}, {}, {}, {}, {}]",
                 receivedFrame.id_, receivedFrame.dlc_,
                 receivedFrame.data_[0], receivedFrame.data_[1], receivedFrame.data_[2], receivedFrame.data_[3],
                 receivedFrame.data_[4], receivedFrame.data_[5], receivedFrame.data_[6], receivedFrame.data_[7]);

        // Clean up
        delete clientSocket;

    } catch (const SocketException& e) {
        spdlog::error("SocketException: {}", e.what());
    }

    return 0;
}
