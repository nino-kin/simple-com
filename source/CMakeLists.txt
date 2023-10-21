# --------------------------------------------------------------
# Required CMake version
# --------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

# --------------------------------------------------------------
# Include directories
# --------------------------------------------------------------
include_directories(socket)
include_directories(data_processor)
include_directories(include)

# --------------------------------------------------------------
# Target directories
# --------------------------------------------------------------
add_subdirectory(sample)
add_subdirectory(data_processor)
add_subdirectory(socket)
add_subdirectory(client)
add_subdirectory(server)
