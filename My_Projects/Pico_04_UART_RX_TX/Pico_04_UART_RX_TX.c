#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <stdio.h>

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

int main() {
    // Initialize stdio for console output (USB)
    stdio_init_all();
    
    // Initialize UART with 115200 baud rate
    uart_init(UART_ID, BAUD_RATE);
    
    // Set the TX and RX pins for UART
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // Configure UART settings (optional, but recommended)
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(UART_ID, true);
    sleep_ms(10000);
    printf("UART Echo Program Started\n");
    printf("Waiting for data at 115200 baud...\n\n");
    
    while (true) {
        // Check if data is available from UART
        if (uart_is_readable(UART_ID)) {
            // Read one character from UART
            char c = uart_getc(UART_ID);
            sleep_ms(1000);
            printf("\n\n\n");
            // Print the received character to console
            printf("%c", c);
            fflush(stdout); // Ensure immediate output
        }
    }
    
    return 0;
}