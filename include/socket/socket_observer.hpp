#ifndef SOCKET_OBSERVER_HPP_
#define SOCKET_OBSERVER_HPP_

#include "socket.hpp"

class SocketObserver {
public:
    virtual ~SocketObserver() {}
    virtual void update(Socket* socket) = 0;
};

#endif /* SOCKET_OBSERVER_HPP_ */
