# --------------------------------------------------------------
# Required CMake version
# --------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

# --------------------------------------------------------------
# Target name
# --------------------------------------------------------------
set(TARGET_NAME new_server)
set(MOCK_NAME new_client)

# --------------------------------------------------------------
# Executables
# --------------------------------------------------------------
# --------------------------------------------------
# Server
# --------------------------------------------------
add_executable(${TARGET_NAME}
    server.cpp
    socket.cpp
    tcp_socket.cpp
    udp_socket.cpp
    ${CMAKE_SOURCE_DIR}/source/data_processor/data_processor.cpp
)

target_link_libraries(${TARGET_NAME} PRIVATE
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)

# --------------------------------------------------
# Client
# --------------------------------------------------
add_executable(${MOCK_NAME}
    client.cpp
    socket.cpp
    tcp_socket.cpp
    udp_socket.cpp
)

target_link_libraries(${MOCK_NAME} PRIVATE
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)
