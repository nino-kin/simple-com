#include "socket_listener.hpp"
#include "socket_logger.hpp"
#include "socket_event.hpp"
#include "socket_exception.hpp"
#include "socket_utils.hpp"
#include "packet.hpp"
#include "network_config.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/in.h>

#include "spdlog/spdlog.h"

int main() {

        const std::string host = NetworkConfig::HOST_ADDR; // Host address
        const uint16_t port = NetworkConfig::PORT_NO;           // Port number
    try {
        // Set up loggers
        SocketLogger logger(host, port, "server.log");

        // Set up a Socket Listener
        SocketListener listener(host, port);

        listener.SetConnectionCallback([&logger](int client_socket) {
            std::string client_ip = "Unknown";
            std::string client_port = "Unknown";
            sockaddr_in client_info;
            socklen_t addr_len = sizeof(client_info);
            if (getpeername(client_socket, (struct sockaddr*)&client_info, &addr_len) == 0) {
                client_ip = SocketUtils::GetIPAddress(client_info);
                client_port = std::to_string(SocketUtils::GetPort(client_info));
            }

            spdlog::info("Client connected from {0}:{1}", client_ip, client_port);
            logger.SendLog("Client connected from " + client_ip + ":" + client_port, LogLevel::INFO);

            // Create a new Socket for this client
            Socket client_socket_instance;
            client_socket_instance.Connect(client_ip, port); //FIXME(nino-kin 2023/10/08): The process on this line is causing an error. ($./build/src/main 2> error.log)

            // Receive and log data from clients
            std::string received_data;
            while (true) {
                if (!client_socket_instance.Receive(received_data)) {
                    spdlog::error("Error while receiving data from client.");
                    throw SocketException("Error while receiving data from client.");
                }

                if (received_data.empty()) {
                    spdlog::info("Client disconnected.");
                    logger.SendLog("Client disconnected.", LogLevel::INFO);
                    break;
                }

                // Logging of received data
                spdlog::info("Received data from client: {}", received_data);
                logger.SendLog("Received data from client: " + received_data, LogLevel::INFO);

                // Create packets and echo data back to source
                Packet response_packet(received_data);
                response_packet.SetHeader("Response: ");
                client_socket_instance.Send(response_packet.Serialize());
            }
        });

        if (listener.Start()) {
            spdlog::info("Server listening on {0}:{1}", host, port);
        } else {
            spdlog::error("Failed to start the server.");
            return 1;
        }

        while (true) {
            // Nothing to do here.
        }
    } catch (const SocketException& e) {
        spdlog::error("SocketException: {}", e.what());
    } catch (const std::exception& e) {
        spdlog::error("Exception: {}", e.what());
    }

    return 0;
}
