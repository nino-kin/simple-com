# --------------------------------------------------------------
# Required CMake version
# --------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

# --------------------------------------------------------------
# Executables
# --------------------------------------------------------------
add_executable(udp_client
    udp_client.cpp)

add_executable(udp_server
    udp_server.cpp)
