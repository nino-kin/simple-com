#ifndef UDP_SOCKET_HPP_
#define UDP_SOCKET_HPP_

#include "socket.hpp"

class UDPSocket : public Socket {
    public:
        /// @brief Constructor
        UDPSocket();

        /// @brief Destructor
        ~UDPSocket();

        /// @brief Associate port with local endpoint
        /// @param port Port number
        /// @return
        bool bind(uint16_t port) override;

        /// @brief Send data
        /// @param can_fame CAN frame
        /// @param dest_ip Destination IP address
        /// @param dest_port Destination port number
        /// @return Execution result
        bool send(const CanFrame& frame, const std::string& dest_ip, uint16_t dest_port) override;

        /// @brief Receive data
        /// @param frame CAN frame
        /// @param source_ip
        /// @param source_port
        /// @return Execution result
        bool receive(CanFrame& frame, std::string& source_ip, uint16_t& source_port) override;

        /// @brief Close the socket
        void close();
};

#endif /* UDP_SOCKET_HPP_ */
