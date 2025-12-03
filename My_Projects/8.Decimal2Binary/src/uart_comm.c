#include "uart_comm.h"
#include "logger.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************
 * GLOBAL VARIABLES (definitions)
 ******************************************************************************/
char buffer[BUFFER_SIZE];
int buffer_index = 0;

/******************************************************************************
 * UART INITIALIZATION
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
 * COMMAND PROCESSING
 ******************************************************************************/
// Forward declaration for user command handler
void handle_user_commands(char *cmd);

void process_command(char *cmd) {
    printf("Received: %s\n", cmd);
    
    // Generic system commands
    if (strcmp(cmd, "help") == 0) {
        printf("Available commands:\n");
        printf("  help   - Show this help message\n");
        printf("  status - Show system status\n");
        printf("  reset  - Reset the system\n");
        printf("  clear  - Clear console\n");
        printf("  cls    - Clear console\n");
        printf("\nUser commands:\n");
        // User can add their help text in handle_user_commands
        handle_user_commands("help");
    }
    else if (strcmp(cmd, "status") == 0) {
        log_system_status("System is running");
    }
    else if (strcmp(cmd, "reset") == 0) {
        log_system_status("Resetting...");
        fflush(stdout);
        sleep_ms(100);
        watchdog_reboot(0, 0, 0);
    }
    else if (strcmp(cmd, "clear") == 0 || strcmp(cmd, "cls") == 0) {
        clear_console();
        log_system_status("Console cleared.\n");
    }
    else {
        // Try user command handler
        handle_user_commands(cmd);
    }
    
    fflush(stdout);
}