#ifndef SOCKET_EXCEPTION_HPP_
#define SOCKET_EXCEPTION_HPP_

#include <stdexcept>

#include "spdlog/spdlog.h"

class SocketException : public std::runtime_error {
public:
    explicit SocketException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif /* SOCKET_EXCEPTION_HPP_ */
