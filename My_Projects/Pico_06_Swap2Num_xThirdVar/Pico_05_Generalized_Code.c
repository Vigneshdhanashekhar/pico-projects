#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/******************************************************************************
 * UART CONFIGURATION - DO NOT MODIFY
 ******************************************************************************/
#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

/******************************************************************************
 * USER CONFIGURATION - MODIFY AS NEEDED
 ******************************************************************************/
#define BUFFER_SIZE 256
#define STARTUP_DELAY_MS 10000  // Delay before starting (for terminal connection)

/******************************************************************************
 * GLOBAL VARIABLES - ADD YOUR VARIABLES HERE
 ******************************************************************************/
char buffer[BUFFER_SIZE];       // Main input buffer
int buffer_index = 0;           // Current position in buffer

//My Variables
int current_value = 0;//to check
/******************************************************************************
 * FUNCTION PROTOTYPES - DECLARE YOUR FUNCTIONS HERE
 ******************************************************************************/
void uart_communication_init(void);
void process_command(char *cmd);

// Add your function prototypes below this line
// ============================================================================



// ============================================================================

/******************************************************************************
 * UART INITIALIZATION - DO NOT MODIFY
 ******************************************************************************/
void uart_communication_init(void) {
    // Initialize stdio for console output
    stdio_init_all();
    
    // Initialize UART with specified baud rate
    uart_init(UART_ID, BAUD_RATE);
    
    // Set the TX and RX pins for UART
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // Configure UART settings
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(UART_ID, true);
    
    // Wait for terminal connection
    sleep_ms(STARTUP_DELAY_MS);
    
    printf("\n");
    printf("========================================\n");
    printf("  UART Communication Initialized\n");
    printf("  Baud Rate: %d\n", BAUD_RATE);
    printf("========================================\n");
    printf("Ready to receive commands...\n\n");
}

/******************************************************************************
 * Logging function - MODIFY THIS SECTION FOR YOUR APPLICATION
 ******************************************************************************/
void log_error(char *prompt){
    printf("[ERROR] command: '%s'\n", prompt);
}

void log_system_status(char *prompt){
    printf("[SYSTEM] command: '%s'\n", prompt);
}

void log_debug(char *prompt){
    printf("[DEBUG] command: '%s'\n", prompt);
}

void log_warning(char *prompt){
    printf("[WARNING] command: '%s'\n", prompt);
}

void log_info_int(int value){
    printf("[INFO] %d\n", value);
}

void log_info_string(char *str){
    printf("[INFO] %s\n", str);
}

void log_info_float(float value){
    printf("[INFO] %.2f\n", value);
}

void clear_console(void){
    // ANSI escape code to clear screen and move cursor to home position
    printf("\033[2J\033[H");
    fflush(stdout);
}
/******************************************************************************
 * COMMAND PROCESSING - MODIFY THIS SECTION FOR YOUR APPLICATION
 ******************************************************************************/
void process_command(char *cmd) {
    // This function is called whenever a complete command is received
    // Modify this section to handle your specific commands
    
    printf("Received: %s\n", cmd);
    
    // ========================================================================
    // ### AREA TO WORK - ADD YOUR COMMAND HANDLING CODE HERE ###
    // ========================================================================
    
    // Example command structure (remove or modify as needed):
    
    if (strcmp(cmd, "help") == 0) {
        printf("Available commands:\n");
        printf("  help - Show this help message\n");
        // Add your commands here
    }
    else if (strcmp(cmd, "status") == 0) {
        log_system_status("System is running");
        // Add your status reporting here
    }
    else if (strcmp(cmd, "reset") == 0) {
        log_system_status(" Resetting...");
        fflush(stdout);
        sleep_ms(100);
        watchdog_reboot(0, 0, 0);
    }
    else if (strcmp(cmd, "clear") == 0 || strcmp(cmd, "cls") == 0) {
        clear_console();
        printf("Console cleared.\n");
    }
    // Add more command handlers below
    else if (strcmp(cmd, " ") == 0) {
        // Ignore empty commands
        log_system_status(" Void Commmand Entered.");
    }
    
    else {
        log_error("Unknown command");
        printf("\nType 'help' for available commands\n");
    }
    
    
    // Add your custom command handling here:
    
    
    
    
    
    // ========================================================================
    // ### END OF WORK AREA ###
    // ========================================================================
    
    fflush(stdout);  // Ensure output is sent immediately
}

/******************************************************************************
 * YOUR CUSTOM FUNCTIONS - IMPLEMENT YOUR FUNCTIONS HERE
 ******************************************************************************/
// ============================================================================
// ### AREA TO WORK - ADD YOUR FUNCTION IMPLEMENTATIONS HERE ###
// ============================================================================

// Example function structure:
/*
void my_custom_function(void) {
    printf("Executing custom function...\n");
    // Your code here
}
*/





// ============================================================================
// ### END OF WORK AREA ###
// ============================================================================

/******************************************************************************
 * MAIN PROGRAM - UART RECEIVE LOOP (DO NOT MODIFY UNLESS NECESSARY)
 ******************************************************************************/
int main() {
    // Initialize UART communication
    uart_communication_init();
    
    // ========================================================================
    // ### OPTIONAL: ADD INITIALIZATION CODE HERE ###
    // ========================================================================
    
    // Initialize your peripherals, variables, or systems here
    // Examples:
    // - GPIO initialization
    // - I2C/SPI initialization
    // - Timer setup
    // - FreeRTOS task creation
    
    
    
    // ========================================================================
    
    // Main loop - handles UART input
    while (true) {
        if (uart_is_readable(UART_ID)) {
            // Read one character from UART
            char c = uart_getc(UART_ID);
            
            // Check for newline or carriage return (command terminator)
            if (c == '\n' || c == '\r') {
                if (buffer_index > 0) {
                    // Null-terminate the string
                    buffer[buffer_index] = '\0';
                    
                    // Process the received command
                    process_command(buffer);
                    
                    // Reset buffer for next command
                    buffer_index = 0;
                }
            }
            // Prevent buffer overflow
            else if (buffer_index < BUFFER_SIZE - 1) {
                // Add character to buffer
                buffer[buffer_index++] = c;
            }
            else {
                // Buffer overflow warning
                printf("WARNING: Buffer overflow! Command too long.\n");
                buffer_index = 0;  // Reset buffer
            }
        }

        log_info_int(current_value);
        sleep_ms(100);
        current_value+=1;
        // ====================================================================
        // ### OPTIONAL: ADD BACKGROUND TASKS HERE ###
        // ====================================================================
        
        // Add code that needs to run continuously in the main loop
        // Examples:
        // - Sensor readings
        // - LED blinking
        // - State machine updates
        // - Non-blocking delays
        
        
        
        // ====================================================================
    }
    
    return 0;
}