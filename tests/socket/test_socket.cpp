#include "gtest/gtest.h"
#include "socket/error_logger.hpp"
#include "socket/socket.hpp"
#include "socket/socket_factory.hpp"
#include "socket/socket_manager.hpp"

// TEST(ErrorLoggerTest, UpdateWithError) {
//     ErrorLogger logger;
//     CanFrame frame;
//     std::string dest_ip("");
//     uint16_t dest_port(0);

//     UDPSocketFactory udpFactory;
//     SocketManager& manager = SocketManager::getInstance();
//     manager.setSocketFactory(&udpFactory);
//     manager.addObserver(&logger);
//     Socket* socket = manager.getSocket();

//     if (!socket->bind(dest_port)) {
//         std::cout << "Failed to bind server socket" << std::endl;
//     }

//     socket->send(frame, dest_ip, dest_port);
//     std::cout << "dest_ip:" << dest_ip << std::endl;
//     std::cout << "dest_port: " << dest_port << std::endl;

//     testing::internal::CaptureStdout();

//     logger.update(socket);

//     std::string output = testing::internal::GetCapturedStdout(); // キャプチャした標準出力を取得
//     std::cout << "socket->hasError(): " << socket->hasError() << std::endl;
//     ASSERT_EQ(output, "Error occurred!\n"); // 正しい出力がされたか確認

//     delete socket;
// }

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
