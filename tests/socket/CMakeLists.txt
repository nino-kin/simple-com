# --------------------------------------------------------------
# Required CMake version
# --------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

# --------------------------------------------------------------
# Target name
# --------------------------------------------------------------
set(TARGET_NAME test_socket)

# --------------------------------------------------------------
# Executables
# --------------------------------------------------------------
add_executable(
  ${TARGET_NAME}
  test_socket.cpp
  ${CMAKE_SOURCE_DIR}/source/socket/socket.cpp
  ${CMAKE_SOURCE_DIR}/source/socket/udp_socket.cpp
  ${CMAKE_SOURCE_DIR}/source/socket/tcp_socket.cpp
)

# --------------------------------------------------------------
# Target link libraries
# --------------------------------------------------------------
target_link_libraries(
  ${TARGET_NAME} PRIVATE
  GTest::gtest_main
  spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)

# --------------------------------------------------------------
# GoogleTest
# --------------------------------------------------------------
include(GoogleTest)
gtest_discover_tests(${TARGET_NAME})
