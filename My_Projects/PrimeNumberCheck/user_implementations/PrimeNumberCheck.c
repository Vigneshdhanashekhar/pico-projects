#include "../inc/uart_comm.h"
#include "../inc/logger.h"
#include "../inc/user_input.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************
 * USER VARIABLES
 ******************************************************************************/
int Prime_num_var = 0;

int status=0;
/******************************************************************************
 * USER FUNCTION PROTOTYPES
 ******************************************************************************/
void primenumbercheck();

/******************************************************************************
 * USER FUNCTIONS IMPLEMENTATION
 ******************************************************************************/

// Function to check whether a number is prime or not

void primenumbercheck(){
    Prime_num_var=get_user_input_int("Enter the number: ");
    for(int j=2;j<=Prime_num_var/2;j++){
        if(Prime_num_var%j==0){
            status=1;
            break;
        }
        else{
            status=0;
        }
    }
    if (status==1){
        log_info_string("It is a Composite Number");
    }
    else
    {
        log_info_string("It is a Prime Number");
    }
    
}

/******************************************************************************
 * USER COMMAND HANDLER
 ******************************************************************************/
void handle_user_commands(char *cmd) {
    if (strcmp(cmd, "help") == 0) {
        // Print user-specific help
        printf("  primecheck -- To check whether a number is prime or not \n");
        return;
    }
    else if (strcmp(cmd, "primecheck") == 0) {
        primenumbercheck();
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