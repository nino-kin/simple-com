#ifndef SOCKET_EVENT_HPP_
#define SOCKET_EVENT_HPP_

#include <cstdint>

enum class SocketEventType : uint8_t {
    NONE,
    READ,
    WRITE,
    ERROR
};

class SocketEvent {
    public:
        SocketEvent();
        SocketEvent(SocketEventType type, int fd);

        SocketEventType getType() const;
        int getFd() const;

    private:
        SocketEventType type;
        int fd;
};

#endif /* SOCKET_EVENT_HPP_ */
