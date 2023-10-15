# --------------------------------------------------------------
# Required CMake version
# --------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

# --------------------------------------------------------------
# Target name
# --------------------------------------------------------------
set(TARGET_NAME data_processor)

# --------------------------------------------------------------
# Libraries
# --------------------------------------------------------------
add_library(${TARGET_NAME} STATIC
    data_processor.cpp
)

target_link_libraries(${TARGET_NAME} PRIVATE
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
