#include "../inc/uart_comm.h"
#include "../inc/logger.h"
#include "../inc/user_input.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************
 * USER VARIABLES
 ******************************************************************************/
int num1=0;
int num2=0;
/******************************************************************************
 * USER FUNCTION PROTOTYPES
 ******************************************************************************/
void gcd2num();

/******************************************************************************
 * USER FUNCTIONS IMPLEMENTATION
 ******************************************************************************/

// Function to check whether a number is prime or not
void gcd2num(){
    num1=get_user_input_int("\nEnter the Number 1:");
    num2=get_user_input_int("\nEnter the Number 2:");
    log_info_string("\nNum1: ");
    log_info_int(num1);
    log_info_string("\nNum2: ");
    log_info_int(num2);
    while(num2!=0){
        int temp=num1;
        num1=num2;
        num2=temp%num2;
    }
    log_info_string("GCD is: ");
    log_info_int(num1);
}


/******************************************************************************
 * USER COMMAND HANDLER
 ******************************************************************************/
void handle_user_commands(char *cmd) {
    if (strcmp(cmd, "help") == 0) {
        // Print user-specific help
        printf("  gcd2num -- To calculate gcd of 2 numbers \n");
        return;
    }
    else if (strcmp(cmd, "gcd2num") == 0) {
        gcd2num();
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