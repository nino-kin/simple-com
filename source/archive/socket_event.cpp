#include "socket_event.hpp"

SocketEvent::SocketEvent() : type(SocketEventType::NONE), fd(-1) {}

SocketEvent::SocketEvent(SocketEventType type, int fd) : type(type), fd(fd) {}

SocketEventType SocketEvent::getType() const {
    return type;
}

int SocketEvent::getFd() const {
    return fd;
}
