#ifndef SOCKET_LISTENER_HPP_
#define SOCKET_LISTENER_HPP_

class SocketListener {
    public:
        SocketListener(uint16_t port);
        ~SocketListener();

        int acceptConnection();
        void closeSocket();

    private:
        int serverSocket_;
        int clientSocket_;
};

#endif /* SOCKET_LISTENER_HPP_ */
