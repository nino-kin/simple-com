#ifndef SOCKET_DECORATOR_HPP_
#define SOCKET_DECORATOR_HPP_

#include "socket.hpp"

class SocketDecorator : public Socket {
    private:
        Socket* wrapped_;

    public:
        SocketDecorator(Socket* wrapped) : wrapped_(wrapped) {}

        bool send(const CanFrame& can_frame, const std::string& dest_ip, uint16_t dest_port) override {
            // Additional functionality
            return wrapped_->send(can_frame, dest_ip, dest_port);
        }

        bool receive(CanFrame& can_frame, std::string& source_ip, uint16_t& source_port) override {
            // Additional functionality
            return wrapped_->receive(can_frame, source_ip, source_port);
        }
};

#endif /* SOCKET_DECORATOR_HPP_ */
