#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

int main() {
    // Initialize USB serial (UART console)
    stdio_init_all();
    
    // Initialize LED pin
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    char input[10];  // Buffer for reading "Hi"
    int num1, num2;  // User numbers
    int a, b;        // Variables for register/address demo
    
    printf("Pico Calculator Ready. Enter 'Hi' to start:\n");
    
    while (true) {
        // Read input string from UART (up to 9 chars + null)
        fgets(input, sizeof(input), stdin);
        
        // Remove newline if present
        input[strcspn(input, "\n")] = 0;
        
        // Check if input is exactly "Hi"
        if (strcmp(input, "Hi") == 0) {
            printf("Welcome! Enter number 1: ");
            scanf("%d", &num1);
            printf("Enter number 2: ");
            scanf("%d", &num2);
            
            // Clear input buffer after scanf
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            
            // Compute and print operations
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
            printf("Before Swap:\n");
            printf("Address of a: %p, Value: %d\n", (void*)&a, a);
            printf("Address of b: %p, Value: %d\n", (void*)&b, b);
            
            // Swap using registers (XOR trick: no temp var, uses CPU registers)
            a ^= b;
            b ^= a;
            a ^= b;
            
            // Print addresses and values after swap
            printf("After Swap (using registers):\n");
            printf("Address of a: %p, Value: %d\n", (void*)&a, a);
            printf("Address of b: %p, Value: %d\n", (void*)&b, b);
            
            // Blink LED for feedback
            gpio_put(LED_PIN, 1);
            sleep_ms(200);
            gpio_put(LED_PIN, 0);
            
            printf("Session complete. Enter 'Hi' again or reset.\n\n");
        } else {
            printf("Invalid input. Enter 'Hi' to start.\n");
        }
    }
    
    return 0;
}