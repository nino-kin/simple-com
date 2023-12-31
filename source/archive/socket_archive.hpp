#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include "can/can_frame.hpp"

#include <cstdint>
#include <string>

class Socket {
    public:
        enum class Type {
            UDP,
            TCP
        };

        explicit Socket(Type type);
        ~Socket();

        /// @brief Associate port with local endpoint
        /// @param Port number
        bool bind(uint16_t port);

        /// @brief Establish Connection
        bool connect(const std::string& ipAddress, uint16_t port);

        /// @brief Send data
        /// @param can_fame CAN frame
        /// @param dest_ip Destination IP address
        /// @param dest_port Destination port number
        bool send(const CanFrame& can_frame, const std::string& dest_ip, uint16_t dest_port);

        /// @brief Receive data
        bool receive(CanFrame& can_frame, std::string& source_ip, uint16_t& source_port);

        /// @brief Close the socket
        void close();

        /// @brief Error check
        bool hasError() const;

        /// @brief Get the socket file descriptor
        /// @return The socket file descriptor
        int getSocketFD() const;

    private:
        /// @brief The socket file descriptor
        int socket_fd_;

        /// @brief The socket type
        Type type_;

        /// @brief Error flag
        bool errorFlag_;
};

#endif /* SOCKET_HPP_ */
