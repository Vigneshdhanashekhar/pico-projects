#include "../inc/uart_comm.h"
#include "../inc/logger.h"
#include "../inc/user_input.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************
 * USER VARIABLES
 ******************************************************************************/
int num_fact = 0;
int fact_res = 1; 

/******************************************************************************
 * USER FUNCTION PROTOTYPES
 ******************************************************************************/
void factorialcalc();

/******************************************************************************
 * USER FUNCTIONS IMPLEMENTATION
 ******************************************************************************/

// Function to check whether a number is prime or not
int factcalc(int num){
    if (num < 0) {
        return -1;
    } else if(num==0){
        return 1;
    }
    else{
        return num*factcalc(num-1);
    }
}
void factorialcalc() {
    num_fact=get_user_input_int("Enter A positive Number: ");
    fact_res=factcalc(num_fact);
    log_info_string("The factorial is");
    log_info_int(fact_res);
}


/******************************************************************************
 * USER COMMAND HANDLER
 ******************************************************************************/
void handle_user_commands(char *cmd) {
    if (strcmp(cmd, "help") == 0) {
        // Print user-specific help
        printf("  factorial -- To check factorial of a number \n");
        return;
    }
    else if (strcmp(cmd, "factorial") == 0) {
        factorialcalc();
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