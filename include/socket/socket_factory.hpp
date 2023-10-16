#ifndef SOCKET_FACTORY_HPP_
#define SOCKET_FACTORY_HPP_

#include "socket.hpp"
#include "udp_socket.hpp"
#include "tcp_socket.hpp"

class SocketFactory {
public:
    virtual ~SocketFactory() {}
    virtual Socket* createSocket() = 0;
};

class UDPSocketFactory : public SocketFactory {
    public:
        Socket* createSocket() override {
            return new UDPSocket();
        }
};

class TCPSocketFactory : public SocketFactory {
    public:
        Socket* createSocket() override {
            return new TCPSocket();
        }
};

#endif /* SOCKET_FACTORY_HPP_ */
