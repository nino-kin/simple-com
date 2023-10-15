#include "data_processor.hpp"
#include "network_config.hpp"
#include "socket/error_logger.hpp"
#include "socket/socket.hpp"
#include "socket/socket_exception.hpp"
#include "socket/socket_factory.hpp"
#include "socket/socket_manager.hpp"

#include "spdlog/spdlog.h"

/**
 * @brief The main function that runs the server.
 *
 * This function initializes a UDP socket, binds it to a port, receives data from a client, processes the data,
 * and sends a reply back to the client.
 *
 * @return The exit status of the program.
 */
int main() {
    spdlog::info("Server is running...\n");
    try {
        // Create a UDP socket factory
        UDPSocketFactory udpFactory;

        // Create a socket manager and set the factory
        SocketManager& manager = SocketManager::getInstance();
        manager.setSocketFactory(&udpFactory);

        // Add an error logger as an observer
        ErrorLogger logger;
        manager.addObserver(&logger);

        // Create a server socket
        Socket* serverSocket = manager.getSocket();

        // Bind the server socket to a port
        if (!serverSocket->bind(NetworkConfig::PORT)) {
            spdlog::error("Failed to bind server socket");
            return 1;
        }

        while (true) {
            // Receive data
            CanFrame receivedFrame;
            std::string client_ip;
            uint16_t client_port;
            if (!serverSocket->receive(receivedFrame, client_ip, client_port)) {
                spdlog::error("Failed to receive data");
                return false;
            }

            spdlog::info("Received data from client - can_id: {}, can_dlc: {}, data: [{}, {}, {}, {}, {}, {}, {}, {}]",
                receivedFrame.id_, receivedFrame.dlc_,
                receivedFrame.data_[0], receivedFrame.data_[1], receivedFrame.data_[2], receivedFrame.data_[3],
                receivedFrame.data_[4], receivedFrame.data_[5], receivedFrame.data_[6], receivedFrame.data_[7]);

            // Process the received data
            CanFrame replyFrame;
            replyFrame = DataProcessor::processRequest(receivedFrame);

            // Send Data (reply) to client
            serverSocket->send(replyFrame, client_ip, client_port);
        }
        // Clean up
        delete serverSocket;

    } catch (const SocketException& e) {
        spdlog::error("SocketException: {}", e.what());
    }
    return 0;
}
