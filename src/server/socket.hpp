#ifndef SOCKET_HPP_
#define SOCKET_HPP_

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
    bool bind(const std::string& ipAddress, uint16_t port);

    /// @brief Establish Connection
    bool connect(const std::string& ipAddress, uint16_t port);

    /// @brief Send data
    bool send(const void* data, size_t size);

    /// @brief Receive data
    bool receive(void* buffer, size_t size);

    /// @brief Close the socket
    void close();

    /// @brief Error check
    bool hasError() const;

private:
    /// @brief The socket file descriptor
    int socket_fd_;

    /// @brief The socket type
    Type type_;

    /// @brief Error flag
    bool errorFlag_;
};

#endif /* SOCKET_HPP_ */
