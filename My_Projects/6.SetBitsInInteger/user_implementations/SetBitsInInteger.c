#include "../inc/uart_comm.h"
#include "../inc/logger.h"
#include "../inc/user_input.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************
 * USER VARIABLES
 ******************************************************************************/
int num_to_find_setbits;
int temp=0;
int count=0;
/******************************************************************************
 * USER FUNCTION PROTOTYPES
 ******************************************************************************/
void setbitsint();

/******************************************************************************
 * USER FUNCTIONS IMPLEMENTATION
 ******************************************************************************/

// Function to check whether a number is prime or not
void setbitsint(){
    num_to_find_setbits= get_user_input_int("Enter the Integer: ");
    log_info_string("You entered :");
    log_info_int(num_to_find_setbits);
    temp=num_to_find_setbits;
    while(temp>0){
        int bit_val=temp%2;
        if (bit_val==1){
            count++;
        }
        temp=temp/2;
    }
    log_info_string("The no of setbits is: ");
    log_info_int(count);
    count=0;
}


/******************************************************************************
 * USER COMMAND HANDLER
 ******************************************************************************/
void handle_user_commands(char *cmd) {
    if (strcmp(cmd, "help") == 0) {
        // Print user-specific help
        printf("  setbitsint -- To find the no of bits set in a integer \n");
        return;
    }
    else if (strcmp(cmd, "setbitsint") == 0) {
        setbitsint();
    }
    else {
        log_error("Unknown command");
        log_system_status("Type 'help' for available commands\n");
    }
}

/******************************************************************************
 * OPTIONAL: USER INITIALIZATION
 ******************************************************************************/
// Uncomment the define below to enable user_init()
// #define USER_INIT_ENABLED

void user_init(void) {
    // Add your initialization code here
    // Examples:
    // - GPIO initialization
    // - I2C/SPI initialization
    // - Timer setup
    
    log_system_status("User initialization complete");
}

/******************************************************************************
 * OPTIONAL: USER BACKGROUND TASKS
 ******************************************************************************/
// Uncomment the define below to enable user_background_tasks()
// #define USER_BACKGROUND_TASKS_ENABLED

void user_background_tasks(void) {
    // Add code that runs continuously in the main loop
    // Examples:
    // - Sensor readings
    // - LED blinking
    // - State machine updates
}