#ifndef SOCKET_SOCKET_EXCEPTION_HPP_
#define SOCKET_SOCKET_EXCEPTION_HPP_

#include <stdexcept>

class SocketException : public std::runtime_error {
    public:
        explicit SocketException(const std::string& message)
            : std::runtime_error(message) {}
};

#endif /* SOCKET_SOCKET_EXCEPTION_HPP_ */
