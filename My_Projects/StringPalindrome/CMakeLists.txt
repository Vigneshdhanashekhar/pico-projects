# Minimum CMake version required
cmake_minimum_required(VERSION 3.13)
add_compile_definitions(PICO_DEFAULT_UART_BAUD_RATE=9600)

# Include the Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Project name
project(my_first_project C CXX ASM)

# Set C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Create executable from all source files
add_executable(StringPali
    src/main.c
    src/uart_comm.c
    src/logger.c
    src/user_input.c
    user_implementations/StringPalindrome.c
    # Add more user implementation files here as needed
    # user_implementations/additional_functions.c
)

# Link necessary libraries
target_link_libraries(StringPali
    pico_stdlib
)

# Enable USB output, disable UART output
pico_enable_stdio_usb(StringPali 0)
pico_enable_stdio_uart(StringPali 1)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(StringPali)