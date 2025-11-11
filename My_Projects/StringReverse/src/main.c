#include "uart_comm.h"
#include "logger.h"
#include <stdio.h>

/******************************************************************************
 * USER INITIALIZATION (optional)
 ******************************************************************************/
void user_init(void);  // Forward declaration

/******************************************************************************
 * USER BACKGROUND TASKS (optional)
 ******************************************************************************/
void user_background_tasks(void);  // Forward declaration

/******************************************************************************
 * MAIN PROGRAM
 ******************************************************************************/
int main() {
    // Initialize UART communication
    uart_communication_init();
    
    // User initialization (if defined)
    #ifdef USER_INIT_ENABLED
    user_init();
    #endif
    
    // Main loop - handles UART input
    while (true) {
        if (uart_is_readable(UART_ID)) {
            char c = uart_getc(UART_ID);
            
            if (c == '\n' || c == '\r') {
                if (buffer_index > 0) {
                    buffer[buffer_index] = '\0';
                    process_command(buffer);
                    buffer_index = 0;
                }
            }
            else if (buffer_index < BUFFER_SIZE - 1) {
                buffer[buffer_index++] = c;
            }
            else {
                printf("WARNING: Buffer overflow! Command too long.\n");
                buffer_index = 0;
            }
        }
        
        sleep_ms(10);
        
        // User background tasks (if defined)
        #ifdef USER_BACKGROUND_TASKS_ENABLED
        user_background_tasks();
        #endif
    }
    
    return 0;
}