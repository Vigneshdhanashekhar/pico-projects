#include "../inc/uart_comm.h"
#include "../inc/logger.h"
#include "../inc/user_input.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************
 * USER VARIABLES
 ******************************************************************************/
char string_tobe_reversed[100];
char *ptr_left;
char *ptr_right;
char tempstr=' ';

/******************************************************************************
 * USER FUNCTION PROTOTYPES
 ******************************************************************************/
void stringreverse();

/******************************************************************************
 * USER FUNCTIONS IMPLEMENTATION
 ******************************************************************************/

// Function to check whether a number is prime or not
void stringreverse(){
    get_user_input_string("Enter the string to be reversed: ",string_tobe_reversed,sizeof(string_tobe_reversed));
    ptr_left = string_tobe_reversed;
    ptr_right = string_tobe_reversed + strlen(string_tobe_reversed)-1;
    while (ptr_left<ptr_right)
    {
        tempstr=*ptr_left;
        *ptr_left=*ptr_right;
        *ptr_right=tempstr;
        ptr_left++;
        ptr_right--;
    }
    log_info_string("Reversed String is ");
    log_info_string(string_tobe_reversed);
    
}


/******************************************************************************
 * USER COMMAND HANDLER
 ******************************************************************************/
void handle_user_commands(char *cmd) {
    if (strcmp(cmd, "help") == 0) {
        // Print user-specific help
        printf("  stringreverse -- To reverse a string \n");
        return;
    }
    else if (strcmp(cmd, "stringreverse") == 0) {
        stringreverse();
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