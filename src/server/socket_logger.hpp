#ifndef SOCKET_LOGGER_HPP_
#define SOCKET_LOGGER_HPP_

#include "logger.hpp"
#include "socket.hpp"

class SocketLogger : public Socket {
    public:
        SocketLogger(const std::string& host, const uint16_t port, const std::string& logFilename);
        ~SocketLogger();

        bool connect(const std::string& host, const uint16_t port);
        bool sendLog(const std::string& logMessage, LogLevel logLevel);
        void disconnect();

    private:
        Socket socket_;
        Logger logger_;
};

#endif /* SOCKET_LOGGER_HPP_ */
