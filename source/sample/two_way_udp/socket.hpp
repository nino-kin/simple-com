#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <string>

class Socket {
public:
    Socket();
    ~Socket();
    bool Bind(uint16_t port);
    bool Send(const std::string& data, const std::string& dest_ip, uint16_t dest_port);
    bool Receive(std::string& data, std::string& source_ip, uint16_t& source_port);
    void Close();

private:
    int socket_fd;
};

#endif /* SOCKET_HPP_ */
