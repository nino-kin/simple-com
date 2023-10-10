# --------------------------------------------------------------
# Required CMake version
# --------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

# --------------------------------------------------------------
# Include directories
# --------------------------------------------------------------
include_directories(server)
include_directories(data_processor)

# --------------------------------------------------------------
# Target directories
# --------------------------------------------------------------
add_subdirectory(sample)

# --------------------------------------------------------------
# Target name
# --------------------------------------------------------------
set(TARGET_NAME server)
set(MOCK_NAME client)

# --------------------------------------------------------------
# Executables
# --------------------------------------------------------------
# --------------------------------------------------
# Server
# --------------------------------------------------
add_executable(${TARGET_NAME}
    # server/logger.cpp
    server/main.cpp
    server/packet.cpp
    server/socket.cpp
    # server/socket_event.cpp
    # server/socket_listener.cpp
    # server/socket_logger.cpp
    # server/socket_options.cpp
    # server/socket_utils.cpp
    data_processor/data_processor.cpp
)

target_link_libraries(${TARGET_NAME} PRIVATE
    pthread
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)

# --------------------------------------------------
# Client
# --------------------------------------------------
add_executable(${MOCK_NAME}
    client/main.cpp
    server/socket.cpp
)

target_link_libraries(${MOCK_NAME} PRIVATE
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)
