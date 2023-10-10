#ifndef SOCKET_LISTENER_HPP_
#define SOCKET_LISTENER_HPP_

class SocketListener {
public:
    SocketListener(int port);
    ~SocketListener();

    int acceptConnection();
    void closeSocket();

private:
    int serverSocket_;
    int clientSocket_;
};

#endif /* SOCKET_LISTENER_HPP_ */
