# --------------------------------------------------------------
# Required CMake version
# --------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

# --------------------------------------------------------------
# Target name
# --------------------------------------------------------------
set(TARGET_SERVER two_way_udp_server)
set(TARGET_CLIENT two_way_udp_client)

# --------------------------------------------------------------
# Executables
# --------------------------------------------------------------
# --------------------------------------------------
# Server
# --------------------------------------------------
add_executable(${TARGET_SERVER}
    server.cpp
    socket.cpp
)

target_link_libraries(${TARGET_SERVER} PRIVATE
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)

# --------------------------------------------------
# Client
# --------------------------------------------------
add_executable(${TARGET_CLIENT}
    client.cpp
    socket.cpp
)

target_link_libraries(${TARGET_CLIENT} PRIVATE
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)
