#ifndef ERROR_LOGGER_HPP_
#define ERROR_LOGGER_HPP_

#include "socket_observer.hpp"

#include "spdlog/spdlog.h"

class ErrorLogger : public SocketObserver {
public:
    void update(Socket* socket) override {
        if (socket->hasError()) {
            spdlog::error("Error occurred!");
        }
    }
};

#endif /* ERROR_LOGGER_HPP_ */
