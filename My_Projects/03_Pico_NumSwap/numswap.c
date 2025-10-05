#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

// Improved trim function
void trim(char *str) {
    size_t len = strlen(str);
    while (len > 0 && (str[len-1] == '\r' || str[len-1] == '\n' || str[len-1] == ' ' || str[len-1] == '\t')) {
        str[--len] = '\0';
    }
}

// Function to clear input buffer completely
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    // Initialize USB serial (UART console)
    stdio_init_all();
    
    // Wait for USB connection to stabilize
    sleep_ms(2000);
    
    // Initialize LED pin
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    char input[32];  // Larger buffer for safety
    int num1, num2;
    int a, b;
    
    printf("\n\n=== Pico Calculator Ready ===\n");
    printf("Enter 'Hi' to start:\n");
    
    while (true) {
        // Clear the buffer before reading
        memset(input, 0, sizeof(input));
        
        // Read input string - use getchar for more control
        int i = 0;
        int c;
        while (i < sizeof(input) - 1) {
            c = getchar();
            if (c == EOF || c == '\n' || c == '\r') {
                break;
            }
            input[i++] = (char)c;
        }
        input[i] = '\0';
        
        // Skip if empty input
        if (strlen(input) == 0) {
            continue;
        }
        
        // Debug: Show what was received (show hex values too)
        printf("Received: '%s' (length: %d) [HEX: ", input, strlen(input));
        for (int j = 0; j < strlen(input) && j < 10; j++) {
            printf("%02X ", (unsigned char)input[j]);
        }
        printf("]\n");
        
        // Check if input is exactly "Hi" (case-sensitive)
        if (strcmp(input, "Hi") == 0) {
                printf("\nWelcome! Let's calculate!\n");
                printf("Enter number 1: ");
                
                if (scanf("%d", &num1) != 1) {
                    printf("Error reading number 1!\n");
                    clear_input_buffer();
                    continue;
                }
                
                printf("Enter number 2: ");
                if (scanf("%d", &num2) != 1) {
                    printf("Error reading number 2!\n");
                    clear_input_buffer();
                    continue;
                }
                
                // Clear input buffer after scanf
                clear_input_buffer();
                
                // Compute and print operations
                printf("\n--- Results ---\n");
                printf("Addition: %d + %d = %d\n", num1, num2, num1 + num2);
                printf("Subtraction: %d - %d = %d\n", num1, num2, num1 - num2);
                printf("Multiplication: %d * %d = %d\n", num1, num2, num1 * num2);
                if (num2 != 0) {
                    printf("Division: %d / %d = %d\n", num1, num2, num1 / num2);
                } else {
                    printf("Division: Cannot divide by zero!\n");
                }
                
                // Save numbers in variables (for "registers" demo)
                a = num1;
                b = num2;
                
                // Print addresses and values before swap
                printf("\nBefore Swap:\n");
                printf("Address of a: %p, Value: %d\n", (void*)&a, a);
                printf("Address of b: %p, Value: %d\n", (void*)&b, b);
                
                // Swap using XOR (register-based swap)
                a ^= b;
                b ^= a;
                a ^= b;
                
                // Print addresses and values after swap
                printf("\nAfter Swap (using registers):\n");
                printf("Address of a: %p, Value: %d\n", (void*)&a, a);
                printf("Address of b: %p, Value: %d\n", (void*)&b, b);
                
                // Blink LED for feedback
                gpio_put(LED_PIN, 1);
                sleep_ms(200);
                gpio_put(LED_PIN, 0);
                
                printf("\n=== Session complete ===\n");
                printf("Enter 'Hi' again to calculate more:\n\n");
            } else {
                printf("Invalid input. Please enter 'Hi' (case-sensitive).\n");
            }
        }
    
    return 0;
}
