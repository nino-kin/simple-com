#include <gtest/gtest.h>
#include "socket_archive.hpp"
#include "can/can_frame.hpp"
#include <thread>

class SocketTest : public ::testing::Test {
    protected:
        SocketTest() : socket(Socket::Type::UDP) {}

        Socket socket;
};

TEST_F(SocketTest, Creation) {
    EXPECT_GE(socket.getSocketFD(), 0);
}

TEST_F(SocketTest, Binding) {
    ASSERT_TRUE(socket.bind(5555));
}

TEST_F(SocketTest, SendingAndReceiving) {
    CanFrame frameToSend = {
        .id_ = 123,
        .rtr_ = 0,
        .dlc_ = 8,
        .data_ = {1, 2, 3, 4, 5, 6, 7, 8}
    };

    std::string destIP = "127.0.0.1";
    uint16_t destPort = 5555;

    // Create a server socket
    Socket serverSocket(Socket::Type::UDP);
    serverSocket.bind(destPort);

    // Create a new thread to receive data as a server socket
    std::thread receiveThread([&serverSocket, &frameToSend, &destIP, &destPort]() {
        CanFrame receivedFrame;
        std::string sourceIP;
        uint16_t sourcePort;

        serverSocket.receive(receivedFrame, sourceIP, sourcePort);

        ASSERT_EQ(frameToSend.id_, receivedFrame.id_);
        ASSERT_EQ(frameToSend.rtr_, receivedFrame.rtr_);
        ASSERT_EQ(frameToSend.dlc_, receivedFrame.dlc_);
        for (int i = 0; i < DLC_MAX_SIZE; ++i) {
            ASSERT_EQ(frameToSend.data_[i], receivedFrame.data_[i]);
        }
    });

    // 4. Send data
    socket.send(frameToSend, destIP, destPort);

    // 5. Wait for receiving standby thread to terminate
    receiveThread.join();
}
