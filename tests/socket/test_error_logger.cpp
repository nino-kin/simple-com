#include "gtest/gtest.h"
#include "socket/error_logger.hpp"
#include "socket/socket.hpp"
#include "socket/socket_factory.hpp"
#include "socket/socket_manager.hpp"

TEST(ErrorLoggerTest, UpdateWithoutError) {
    uint16_t dest_port(12345);

    ErrorLogger logger;

    UDPSocketFactory udpFactory;
    SocketManager& manager = SocketManager::getInstance();
    manager.setSocketFactory(&udpFactory);
    manager.addObserver(&logger);
    Socket* socket = manager.getSocket();

    if (!socket->bind(dest_port)) {
        std::cout << "Failed to bind server socket" << std::endl;
    }

    // No error occurs

    testing::internal::CaptureStdout();
    logger.update(socket);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "");

    delete socket;
}
