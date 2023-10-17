#ifndef SOCKET_ERROR_LOGGER_HPP_
#define SOCKET_ERROR_LOGGER_HPP_

#include "socket_observer.hpp"
#include <iostream>

class ErrorLogger : public SocketObserver {
public:
    void update(Socket* socket) override {
        if (socket->hasError()) {
            std::cout << "Error occurred!" << std::endl;
        }
    }
};

#endif /* SOCKET_ERROR_LOGGER_HPP_ */
