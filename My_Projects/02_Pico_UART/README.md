Configuring UART Baud Rate on Raspberry Pi Pico
Understanding the Current Setup
The stdio_init_all() function initializes both USB and UART serial communication with the following default settings:

Default UART baud rate: 115200
Default USB baud rate: 115200

How to Change the UART Baud Rate
There are two methods to change the UART baud rate on the Raspberry Pi Pico:
Method 1: Using stdio_uart_init_full() (Recommended)
Replace stdio_init_all() with a more specific initialization function to set a custom baud rate.
#include "pico/stdlib.h"
#include <stdio.h>

int main() {
    // Initialize UART0 with 9600 baud rate, TX on GP0, RX on GP1
    stdio_uart_init_full(uart0, 9600, 0, 1);
    stdio_usb_init();  // Also initialize USB if needed
    
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    int count = 0;
    
    while (true) {
        gpio_put(LED_PIN, 1);
        printf("LED ON - Count: %d\n", count++);
        sleep_ms(1000);

        gpio_put(LED_PIN, 0);
        printf("LED OFF\n");
        sleep_ms(1000);
    }
    
    return 0;
}

Method 2: Using CMake Configuration
Add a custom baud rate definition in your CMakeLists.txt before calling pico_sdk_init().
# Set custom UART baud rate (add before pico_sdk_init())
add_compile_definitions(PICO_DEFAULT_UART_BAUD_RATE=9600)

Full CMakeLists.txt with Custom Baud Rate
# Minimum CMake version required
cmake_minimum_required(VERSION 3.13)

# Include the Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Project name
project(my_first_project C CXX ASM)

# Set C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Set custom UART baud rate (BEFORE pico_sdk_init())
add_compile_definitions(PICO_DEFAULT_UART_BAUD_RATE=9600)

# Initialize the Pico SDK
pico_sdk_init()

# Create executable from source file
add_executable(02_Pico_UART
    uart_comm.c
)

# Link necessary libraries
target_link_libraries(02_Pico_UART
    pico_stdlib
)

# Enable USB output and UART output
pico_enable_stdio_usb(02_Pico_UART 1)
pico_enable_stdio_uart(02_Pico_UART 1)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(02_Pico_UART)

Common Baud Rates

9600: Very common for simple projects
19200
38400
57600
115200: Default, fastest standard rate

Important Notes

Baud rate matching: Ensure both the Raspberry Pi Pico and the connected TTL converter use the same baud rate.
Pin connections: By default, UART0 uses:
TX (Transmit): GPIO 0
RX (Receive): GPIO 1


