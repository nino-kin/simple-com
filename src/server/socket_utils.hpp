#ifndef SOCKET_UTILS_H_
#define SOCKET_UTILS_H_

#include <string>
#include <netinet/in.h>

class SocketUtils {
    public:
        static std::string GetIPAddress(const sockaddr_in& sockaddr);
        static unsigned short GetPort(const sockaddr_in& sockaddr);
        static in_addr ConvertToIPAddress(const std::string& ip_address);
};

#endif /* SOCKET_UTILS_H_ */
