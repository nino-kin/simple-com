#include "spdlog/spdlog.h"

#include "socket_logger.hpp"

SocketLogger::SocketLogger(const std::string& host, const uint16_t port, const std::string& logFilename)
    : socket_(Type::UDP), logger_(logFilename) {
    if (!socket_.connect(host, port)) {
        spdlog::error("Failed to connect to the server.");
    }
}

SocketLogger::~SocketLogger() {
    disconnect();
}

bool SocketLogger::connect(const std::string& host, const uint16_t port) {
    return socket_.connect(host, port);
}

bool SocketLogger::sendLog(const std::string& logMessage, LogLevel logLevel) {
    if (!socket_.send(logMessage, logMessage.length)) {
        spdlog::error("Failed to send log message.");
        return false;
    }

    // Recorded in log file
    logger_.log(logLevel, logMessage);
    return true;
}

void SocketLogger::disconnect() {
    socket_.close();
}
