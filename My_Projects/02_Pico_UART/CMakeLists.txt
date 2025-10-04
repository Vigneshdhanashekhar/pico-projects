# Minimum CMake version required
cmake_minimum_required(VERSION 3.13)

# Include the Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Project name
project(my_first_project C CXX ASM)

# Set C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

# Create executable from source file
add_executable(uart_comm
    uart_comm.c
)

# Link necessary libraries
target_link_libraries(uart_comm
    pico_stdlib
)

# Enable USB output, disable UART output
pico_enable_stdio_usb(uart_comm 1)
pico_enable_stdio_uart(uart_comm 1)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(uart_comm)
