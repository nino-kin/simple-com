#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include "can/can_frame.hpp"

#include <string>

class Socket {
    public:
        /// @brief Constructor
        Socket() {}

        /// @brief Destructor
        virtual ~Socket() {}

        /// @brief Associate port with local endpoint
        /// @param port Port number
        /// @return Execution result
        virtual bool bind(uint16_t port) = 0;

        /// @brief
        /// @param can_frame
        /// @param dest_ip
        /// @param dest_port
        /// @return Execution result
        virtual bool send(const CanFrame& can_frame, const std::string& dest_ip, uint16_t dest_port) = 0;

        /// @brief
        /// @param can_frame
        /// @param source_ip
        /// @param source_port
        /// @return Execution result
        virtual bool receive(CanFrame& can_frame, std::string& source_ip, uint16_t& source_port) = 0;

        /// @brief Get the socket file descriptor
        /// @return The socket file descriptor
        int getSocketFD() const;

        /// @brief Error check
        bool hasError() const;

    protected:
        /// @brief The socket file descriptor
        int socket_fd_ = -1;

        /// @brief Error flag
        bool error_flag_ = false;
};

#endif /* SOCKET_HPP_ */
