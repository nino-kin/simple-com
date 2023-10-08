#include "socket_logger.hpp"

#include "spdlog/spdlog.h"

SocketLogger::SocketLogger(const std::string& host, const uint16_t port, const std::string& logFilename)
    : socket(), logger(logFilename) {
    if (!socket.Connect(host, port)) {
        spdlog::error("Failed to connect to the server.");
    }
}

SocketLogger::~SocketLogger() {
    Disconnect();
}

bool SocketLogger::Connect(const std::string& host, const uint16_t port) {
    return socket.Connect(host, port);
}

bool SocketLogger::SendLog(const std::string& logMessage, LogLevel logLevel) {
    if (!socket.Send(logMessage)) {
        spdlog::error("Failed to send log message.");
        return false;
    }

    // Recorded in log file
    logger.Log(logLevel, logMessage);
    return true;
}

void SocketLogger::Disconnect() {
    socket.Close();
}
