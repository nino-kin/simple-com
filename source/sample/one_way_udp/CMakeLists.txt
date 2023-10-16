# --------------------------------------------------------------
# Required CMake version
# --------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

# --------------------------------------------------------------
# Target name
# --------------------------------------------------------------
set(TARGET_SERVER one_way_udp_server)
set(TARGET_CLIENT one_way_udp_client)

# --------------------------------------------------------------
# Executables
# --------------------------------------------------------------
add_executable(${TARGET_SERVER}
    server_udp.cpp)

add_executable(${TARGET_CLIENT}
    client_udp.cpp)
