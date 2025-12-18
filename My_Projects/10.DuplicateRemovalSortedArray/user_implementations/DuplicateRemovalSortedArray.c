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
void getarray();
int removeduplicate(int arr[],int size);
/******************************************************************************
 * USER FUNCTIONS IMPLEMENTATION
 ******************************************************************************/

// Function to check whether a number is prime or not
int removeduplicate(int arr[], int size){
    int j=0;
    for(int i=1;i<size;i++){
        if(arr[j]!=arr[i]){
            j++;
            arr[j]=arr[i];
        }
    }
    return(j+1);
}
void getarray() {
    array_size=get_user_input_int("Enter the number of elements in the array");
    int array_element[array_size];
    for(int i=0;i<array_size;i++){
        array_element[i]=get_user_input_int("Enter the value for consecutive Elements:");
    }
    log_info_string("Displaying the duplicate filtered numbers");
    // for(int i=0;i<array_size;i++){
    //     log_info_int(array_element[i]);
    // }
    int filtered_Array_size=removeduplicate(array_element,array_size);
    for(int i=0;i<filtered_Array_size;i++){
        log_info_int(array_element[i]);
    }
}


/******************************************************************************
 * USER COMMAND HANDLER
 ******************************************************************************/
void handle_user_commands(char *cmd) {
    if (strcmp(cmd, "help") == 0) {
        // Print user-specific help
        printf("  redupi -- To remove duplicate elements of a sorted array \n");
        return;
    }
    else if (strcmp(cmd, "remdupi") == 0) {
        getarray();
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