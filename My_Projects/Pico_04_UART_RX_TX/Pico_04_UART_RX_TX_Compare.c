#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <stdio.h>
#include <string.h>
#define UART_ID uart0
#define BAUD_RATE 9600
#define UART_TX_PIN 0
#define UART_RX_PIN 1

int main() {
    // Initialize stdio for console output (USB)
    // stdio_init_all();
    
    // Initialize UART with 115200 baud rate
    uart_init(UART_ID, BAUD_RATE);
    
    // Set the TX and RX pins for UART
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // Configure UART settings (optional, but recommended)
    // uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
    // uart_set_fifo_enabled(UART_ID, true);
    stdio_uart_init_full(UART_ID, BAUD_RATE, UART_TX_PIN, UART_RX_PIN);
    sleep_ms(10000);
    printf("UART Echo Program Started\n");
    printf("Waiting for data at 115200 baud...\n\n");
    char buffer[256];  // Buffer to store incoming string
    int index = 0;
    while (true) {
    if (uart_is_readable(UART_ID)) {
            // Read one character from UART
            char c = uart_getc(UART_ID);
            
            // Echo back to UART (so you see it in TeraTerm)
            // uart_putc(UART_ID, c);
            
            // Check for newline or carriage return (Enter key)
            if (c == '\n' || c == '\r') {
                if (index > 0) {  // Only print if we have data
                    buffer[index] = '\0';  // Null-terminate the string
                    printf("\n\n\nReceived string: %s\n", buffer);
                    if(strcmp(buffer,"Hello")==0){
                        printf("\nHello word is being detected");
                    }
                    sleep_ms(1000);
                    fflush(stdout);
                    index = 0;  // Reset buffer for next input
                }
            }
            else if (index < 255) {  // Prevent buffer overflow
                buffer[index++] = c;  // Add character to buffer
            }
        }
    }
    return 0;
}