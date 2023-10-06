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

            std::cout << "Client connected from " << client_ip << ":" << client_port << std::endl;
            logger.SendLog("Client connected from " + client_ip + ":" + client_port, LogLevel::INFO);

            // Create a new Socket for this client
            Socket client_socket_instance;
            client_socket_instance.Connect(client_ip, port);

            // Receive and log data from clients
            std::string received_data;
            while (true) {
                if (!client_socket_instance.Receive(received_data)) {
                    std::cerr << "Error while receiving data from client." << std::endl;
                    throw SocketException("Error while receiving data from client.");
                }

                if (received_data.empty()) {
                    std::cout << "Client disconnected." << std::endl;
                    logger.SendLog("Client disconnected.", LogLevel::INFO);
                    break;
                }

                // Logging of received data
                std::cout << "Received data from client: " << received_data << std::endl;
                logger.SendLog("Received data from client: " + received_data, LogLevel::INFO);

                // Create packets and echo data back to source
                Packet response_packet(received_data);
                response_packet.SetHeader("Response: ");
                client_socket_instance.Send(response_packet.Serialize());
            }
        });

        if (listener.Start()) {
            std::cout << "Server listening on " << host << ":" << port << std::endl;
        } else {
            std::cerr << "Failed to start the server." << std::endl;
            return 1;
        }

        while (true) {
            // Nothing to do here.
        }
    } catch (const SocketException& e) {
        std::cerr << "SocketException: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
