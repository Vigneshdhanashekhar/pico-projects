cmake_minimum_required(VERSION 3.13)

project(logic_testing C)

# Set C standard
set(CMAKE_C_STANDARD 11)

# Include mock headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mock)

# Create executable
add_executable(test_logic_lse
    test_logic_lse.c
)

# Optional: Add compiler warnings
target_compile_options(test_logic_lse PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)