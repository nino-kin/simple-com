# --------------------------------------------------------------
# Required CMake version
# --------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

# --------------------------------------------------------------
# Target name
# --------------------------------------------------------------
set(TARGET_NAME socket)

# --------------------------------------------------------------
# Libraries
# --------------------------------------------------------------
add_library(${TARGET_NAME} STATIC
    socket.cpp
    tcp_socket.cpp
    udp_socket.cpp
)

target_link_libraries(${TARGET_NAME} PRIVATE
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
