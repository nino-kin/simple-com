#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>

class Socket {
public:
    Socket();
    ~Socket();

    bool Connect(const std::string& host, const uint16_t port);
    bool Send(const std::string& data);
    bool Receive(std::string& data);

    void Close();

private:
    int socket_fd;
};

#endif /* SOCKET_H_ */
