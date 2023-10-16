# --------------------------------------------------------------
# Required CMake version
# --------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

# --------------------------------------------------------------
# Target name
# --------------------------------------------------------------
set(TARGET_NAME server_archive)
set(MOCK_NAME client_archive)

# --------------------------------------------------------------
# Executables
# --------------------------------------------------------------
# --------------------------------------------------
# Server
# --------------------------------------------------
add_executable(${TARGET_NAME}
    # socket/logger.cpp
    server.cpp
    packet.cpp
    socket_archive.cpp
    # socket_event.cpp
    # socket_listener.cpp
    # socket_logger.cpp
    # socket_options.cpp
    # socket_utils.cpp
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
    socket_archive.cpp
)

target_link_libraries(${MOCK_NAME} PRIVATE
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)
