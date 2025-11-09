#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    printf("Waiting for data at 115200 baud...\n");
    printf("Type '1' and press Enter to enter Mode-1\n\n");
    
    char buffer[256];  // Buffer to store incoming string
    char buffer1[256];
    int index = 0;
    
    while (true) {
        if (uart_is_readable(UART_ID)) {
            // Read one character from UART
            char c = uart_getc(UART_ID);
            
            // Check for newline or carriage return (Enter key)
            if (c == '\n' || c == '\r') {
                if (index > 0) {  // Only process if we have data
                    buffer[index] = '\0';  // Null-terminate the string
                    
                    // Check if user entered "1" to enter Mode-1
                    if (strcmp(buffer, "1") == 0) {
                        printf("\n=== Entering Mode-1 ===\n");
                        printf("Please enter a number: ");
                        fflush(stdout);
                        
                        // Clear buffer for next input
                        index = 0;
                        
                        // Wait for number input
                        while (true) {
                            if (uart_is_readable(UART_ID)) {
                                char nc = uart_getc(UART_ID);
                                
                                if (nc == '\n' || nc == '\r') {
                                    if (index > 0) {
                                        buffer1[index] = '\0';
                                        
                                        // Convert string to integer
                                        int number = atoi(buffer1);
                                        int result = number * 5;
                                        printf("\n Your entered num in string : %s\n",buffer1);
                                        printf("\n Your choice : %s\n",buffer);
                                        printf("\nYou entered: %d\n", number);
                                        printf("Result (x5): %d\n", result);
                                        printf("\n=== Exiting Mode-1 ===\n");
                                        printf("Back to main loop...\n\n");
                                        fflush(stdout);
                                        
                                        index = 0;
                                        break;  // Exit Mode-1, go back to main loop
                                    }
                                }
                                else if (index < 255) {
                                    buffer1[index++] = nc;
                                }
                            }
                        }
                    }
                    else {
                        // Regular echo functionality
                        printf("\nReceived string: %s\n", buffer);
                        fflush(stdout);
                    }
                    
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