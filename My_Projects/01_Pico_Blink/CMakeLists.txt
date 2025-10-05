# Minimum CMake version required
cmake_minimum_required(VERSION 3.13)

# Include the Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Project name
project(my_first_project C CXX ASM)

# Set C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# IMPORTANT: Set build type to Debug and disable optimization
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")

# Initialize the Pico SDK
pico_sdk_init()

# Create executable from source file
add_executable(01_Pico_Blink
    blink.c
)

# Link necessary libraries
target_link_libraries(01_Pico_Blink
    pico_stdlib
)

# Enable USB output, disable UART output
pico_enable_stdio_usb(01_Pico_Blink 1)
pico_enable_stdio_uart(01_Pico_Blink 0)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(01_Pico_Blink)
