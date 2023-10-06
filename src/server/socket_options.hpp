#ifndef SOCKET_OPTIONS_H_
#define SOCKET_OPTIONS_H_

class SocketOptions {
public:
    static bool SetTimeout(int socket_fd, int timeout_ms);
    static bool SetBufferSize(int socket_fd, int buffer_size);
};

#endif /* SOCKET_OPTIONS_H_ */
