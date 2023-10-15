#ifndef TCP_SOCKET_HPP_
#define TCP_SOCKET_HPP_

#include "socket.hpp"

class TCPSocket : public Socket {
public:
    TCPSocket();
    ~TCPSocket();

    /// @brief Associate port with local endpoint
    /// @param port Port number
    bool bind(uint16_t port) override;

    /// @brief
    /// @param backlog
    /// @return Execution result
    bool listen(int backlog);

    /// @brief
    /// @param clientSocket
    /// @return Execution result
    bool accept(TCPSocket& clientSocket);

    /// @brief
    /// @param ip_address
    /// @param port
    /// @return Execution result
    bool connect(const std::string& ip_address, uint16_t port);

    /// @brief Send data
    /// @param frame CAN frame
    /// @param dest_ip Destination IP address
    /// @param dest_port Destination port
    /// @return Execution result
    // bool send(const CanFrame& frame);
    // TODO:  Destination IP address and  Destination port are not used.
    bool send(const CanFrame& frame, const std::string& dest_ip, uint16_t dest_port) override;

    /// @brief Receive data
    /// @param frame CAN frame
    /// @param dest_ip Source IP address
    /// @param dest_port Source port
    /// @return Execution result
    // bool receive(CanFrame& frame);
    // TODO:  Source IP address and  Source port are not used.
    bool receive(CanFrame& frame, std::string& source_ip, uint16_t& source_port) override;

    /// @brief Close the socket
    void close();
};

#endif /* TCP_SOCKET_HPP_ */
