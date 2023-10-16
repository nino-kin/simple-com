#include <netdb.h>
#include <arpa/inet.h>

#include "socket_utils.hpp"

std::string SocketUtils::resolveHostname(const std::string& hostname) {
    struct hostent* he;
    struct in_addr** addr_list;

    if ((he = gethostbyname(hostname.c_str())) == nullptr) {
        herror("gethostbyname");
        return "";
    }

    addr_list = reinterpret_cast<struct in_addr**>(he->h_addr_list);

    for (int i = 0; addr_list[i] != nullptr; i++) {
        return inet_ntoa(*addr_list[i]);
    }

    return "";
}

unsigned short SocketUtils::convertPort(const std::string& port) {
    return static_cast<unsigned short>(std::stoi(port));
}

unsigned short SocketUtils::convertPort(int port) {
    return static_cast<unsigned short>(port);
}

unsigned long SocketUtils::convertIp(const std::string& ip) {
    return inet_addr(ip.c_str());
}

std::string SocketUtils::convertIp(unsigned long ip) {
    return inet_ntoa(*reinterpret_cast<struct in_addr*>(&ip));
}
