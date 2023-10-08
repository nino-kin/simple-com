# --------------------------------------------------------------
# Required CMake version
# --------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

# --------------------------------------------------------------
# Include directories
# --------------------------------------------------------------
include_directories(server)

# --------------------------------------------------------------
# Target directories
# --------------------------------------------------------------
add_subdirectory(sample)

# --------------------------------------------------------------
# Packages
# --------------------------------------------------------------
# --------------------------------------------------
# spdlog
# --------------------------------------------------
# cf. https://github.com/gabime/spdlog
# cf. https://discourse.cmake.org/t/use-external-libraries-using-fetchcontent/2710
include(FetchContent)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.12.0
)
FetchContent_GetProperties(spdlog)
if(NOT spdlog_POPULATED)
    message("Cloning spdlod")
    FetchContent_Populate(spdlog)
    add_subdirectory(
        ${spdlog_SOURCE_DIR}
        ${spdlog_BINARY_DIR}
    )
endif()

# --------------------------------------------------------------
# Target name
# --------------------------------------------------------------
set(TARGET_NAME main)
set(MOCK_NAME fake_client)

# --------------------------------------------------------------
# Executables
# --------------------------------------------------------------
# --------------------------------------------------
# Server
# --------------------------------------------------
add_executable(${TARGET_NAME}
    server/logger.cpp
    server/main.cpp
    server/packet.cpp
    server/socket.cpp
    server/socket_event.cpp
    server/socket_exception.cpp
    server/socket_listener.cpp
    server/socket_logger.cpp
    server/socket_options.cpp
    server/socket_utils.cpp
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
