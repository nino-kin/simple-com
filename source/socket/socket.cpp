#include "socket/socket.hpp"

int Socket::getSocketFD() const {
    return socket_fd_;
}

bool Socket::hasError() const {
    return error_flag_;
}
