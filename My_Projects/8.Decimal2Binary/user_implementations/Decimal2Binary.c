#include "../inc/uart_comm.h"
#include "../inc/logger.h"
#include "../inc/user_input.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************
 * USER VARIABLES
 ******************************************************************************/
int temp=0;
int bin_num=0;
int num_dec2bin=0;
int pos_value =1;
/******************************************************************************
 * USER FUNCTION PROTOTYPES
 ******************************************************************************/
void dec2bin();

/******************************************************************************
 * USER FUNCTIONS IMPLEMENTATION
 ******************************************************************************/

// Function to check whether a number is prime or not
void dec2bin(){
    num_dec2bin= get_user_input_int("Enter the Integer: ");
    log_info_string("You entered :");
    log_info_int(num_dec2bin);
    bin_num =0;
    temp=num_dec2bin;
    while(temp>0){
        int bit_val=temp%2;
        bin_num=(bit_val*pos_value) +bin_num;
        pos_value=10*pos_value;
        temp=temp/2;
    }
    log_info_string("The binary equivalent is: ");
    log_info_int(bin_num);
    pos_value=1;
}


/******************************************************************************
 * USER COMMAND HANDLER
 ******************************************************************************/
void handle_user_commands(char *cmd) {
    if (strcmp(cmd, "help") == 0) {
        // Print user-specific help
        printf("  dec2bin -- To convert decimal to binary \n");
        return;
    }
    else if (strcmp(cmd, "dec2bin") == 0) {
        dec2bin();
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