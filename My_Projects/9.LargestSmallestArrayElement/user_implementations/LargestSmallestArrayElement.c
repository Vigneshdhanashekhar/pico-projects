#include "../inc/uart_comm.h"
#include "../inc/logger.h"
#include "../inc/user_input.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************
 * USER VARIABLES
 ******************************************************************************/
int maximum_val = 0;
int array_size = 0;
int minimum_val = 1;
int temp_var=0;
/******************************************************************************
 * USER FUNCTION PROTOTYPES
 ******************************************************************************/
void maxminarray();

/******************************************************************************
 * USER FUNCTIONS IMPLEMENTATION
 ******************************************************************************/

// Function to check whether a number is prime or not
void maxminarray() {
    array_size=get_user_input_int("Enter the number of elements in the array");
    if(0>array_size){
        log_error("Array  Size cannot be less than Zero");
        return;
    }
    temp_var=get_user_input_int("Enter the value for 1st Element:");
    maximum_val=temp_var;
    minimum_val=temp_var;
    for(int i=1;i<array_size;i++){
        temp_var=get_user_input_int("Enter the value for consecutive Elements:");
        if (maximum_val<temp_var){
            maximum_val=temp_var;
        }
        if (minimum_val>temp_var){
            minimum_val=temp_var;
        }
    }
    log_info_string("Maximum Value in the array is ");
    log_info_int(maximum_val);
    log_info_string("Minimum Value in the array is ");
    log_info_int(minimum_val);

}


/******************************************************************************
 * USER COMMAND HANDLER
 ******************************************************************************/
void handle_user_commands(char *cmd) {
    if (strcmp(cmd, "help") == 0) {
        // Print user-specific help
        printf("  maxmin -- To convert find max and min of a array \n");
        return;
    }
    else if (strcmp(cmd, "maxmin") == 0) {
        maxminarray();
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