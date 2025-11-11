#include "../inc/uart_comm.h"
#include "../inc/logger.h"
#include "../inc/user_input.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************
 * USER VARIABLES
 ******************************************************************************/
char string_tobe_reversed[100];
char string_reversed[100];
char *ptr_left;
char *ptr_right;
char tempstr=' ';

/******************************************************************************
 * USER FUNCTION PROTOTYPES
 ******************************************************************************/
void stringreverse(char *string_tobe_reversed);
void stringpalindrome();
/******************************************************************************
 * USER FUNCTIONS IMPLEMENTATION
 ******************************************************************************/

// Function to check whether a number is prime or not
void stringreverse(char *string_func_input){
    ptr_left = string_func_input;
    ptr_right = string_func_input + strlen(string_func_input)-1;
    while (ptr_left<ptr_right)
    {
        tempstr=*ptr_left;
        *ptr_left=*ptr_right;
        *ptr_right=tempstr;
        ptr_left++;
        ptr_right--;
    }
    log_info_string("Reversed String is ");
    log_info_string(string_func_input);
    // return  string_func_input;
    
}
void stringpalindrome(){
    get_user_input_string("Enter the string to be reversed: ",string_tobe_reversed,sizeof(string_tobe_reversed));
    strcpy(string_reversed,string_tobe_reversed);
    stringreverse(string_reversed);
    if(strcmp(string_reversed,string_tobe_reversed)==0){
        log_info_string("String is a palindrome");
    }
    else{
        log_info_string("String is not a palindrome");
    }
}

/******************************************************************************
 * USER COMMAND HANDLER
 ******************************************************************************/
void handle_user_commands(char *cmd) {
    if (strcmp(cmd, "help") == 0) {
        // Print user-specific help
        printf("  stringpali -- To check whether a string is palindrome or not\n");
        return;
    }
    else if (strcmp(cmd, "stringpali") == 0) {
        stringpalindrome();
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