#ifndef SOCKET_UTILS_HPP_
#define SOCKET_UTILS_HPP_

#include <string>

class SocketUtils {
    public:
        static std::string resolveHostname(const std::string& hostname);
        static unsigned short convertPort(const std::string& port);
        static unsigned short convertPort(int port);
        static unsigned long convertIp(const std::string& ip);
        static std::string convertIp(unsigned long ip);
};


#endif /* SOCKET_UTILS_HPP_ */
