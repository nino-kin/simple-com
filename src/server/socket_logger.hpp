#ifndef SOCKET_LOGGER_H_
#define SOCKET_LOGGER_H_

#include "socket.hpp"
#include "logger.hpp"

class SocketLogger {
public:
    SocketLogger(const std::string& host, const uint16_t port, const std::string& logFilename);
    ~SocketLogger();

    bool Connect(const std::string& host, const uint16_t port);
    bool SendLog(const std::string& logMessage, LogLevel logLevel);
    void Disconnect();

private:
    Socket socket;
    Logger logger;
};

#endif /* SOCKET_LOGGER_H_ */
