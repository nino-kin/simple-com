#ifndef SOCKET_MANAGER_HPP_
#define SOCKET_MANAGER_HPP_

#include "socket.hpp"
#include "socket_factory.hpp"
#include "socket_observer.hpp"

#include <vector>

class SocketManager {
public:
    static SocketManager& getInstance() {
        static SocketManager instance;
        return instance;
    }

    Socket* getSocket() {
        return socketFactory_->createSocket();
    }

    void setSocketFactory(SocketFactory* factory) {
        socketFactory_ = factory;
    }

    void addObserver(SocketObserver* observer) {
        observers_.push_back(observer);
    }

    void notifyObservers(Socket* socket) {
        for (auto observer : observers_) {
            observer->update(socket);
        }
    }

private:
    SocketFactory* socketFactory_;
    std::vector<SocketObserver*> observers_;

    SocketManager() : socketFactory_(nullptr) {
        // Initialize the factory based on the application's needs
        // For example, socketFactory_ = new UDPSocketFactory();
        // Or socketFactory_ = new TCPSocketFactory(); for TCP sockets
    }

    ~SocketManager() {
        // delete socketFactory_;
        // for (auto observer : observers_) {
        //     delete observer;
        // }
    }
};

#endif /* SOCKET_MANAGER_HPP_ */
