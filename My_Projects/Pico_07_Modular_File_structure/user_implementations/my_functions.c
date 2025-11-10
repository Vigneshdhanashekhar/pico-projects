#include "../inc/uart_comm.h"
#include "../inc/logger.h"
#include "../inc/user_input.h"
#include <stdio.h>
#include <string.h>

/******************************************************************************
 * USER VARIABLES
 ******************************************************************************/
int num1 = 0;
int num2 = 0;

/******************************************************************************
 * USER FUNCTION PROTOTYPES
 ******************************************************************************/
void swap_two_numbers(int *a, int *b);
void command_swap(void);
void command_calculator(void);

/******************************************************************************
 * USER FUNCTIONS IMPLEMENTATION
 ******************************************************************************/

// Function to swap two numbers using call by reference
void swap_two_numbers(int *a, int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

// Swap command handler
void command_swap(void) {
    log_info_string("Starting swap operation...\n");
    
    num1 = get_user_input_int("Enter Number 1: ");
    log_info_string("Number 1 received");
    log_info_int(num1);
    
    num2 = get_user_input_int("Enter Number 2: ");
    log_info_string("Number 2 received");
    log_info_int(num2);
    
    printf("\nBefore swap:\n");
    printf("Num 1: %d\n", num1);
    printf("Num 2: %d\n", num2);
    
    swap_two_numbers(&num1, &num2);
    
    printf("\nAfter swap:\n");
    printf("Num 1: %d\n", num1);
    printf("Num 2: %d\n", num2);
}

// Calculator command handler
void command_calculator(void) {
    float num1_f = get_user_input_float("Enter first number: ");
    float num2_f = get_user_input_float("Enter second number: ");
    
    char operation[10];
    get_user_input_string("Enter operation (+, -, *, /): ", operation, sizeof(operation));
    
    float result;
    if (strcmp(operation, "+") == 0) {
        result = num1_f + num2_f;
        printf("Result: %.2f + %.2f = %.2f\n", num1_f, num2_f, result);
    }
    else if (strcmp(operation, "-") == 0) {
        result = num1_f - num2_f;
        printf("Result: %.2f - %.2f = %.2f\n", num1_f, num2_f, result);
    }
    else if (strcmp(operation, "*") == 0) {
        result = num1_f * num2_f;
        printf("Result: %.2f * %.2f = %.2f\n", num1_f, num2_f, result);
    }
    else if (strcmp(operation, "/") == 0) {
        if (num2_f != 0) {
            result = num1_f / num2_f;
            printf("Result: %.2f / %.2f = %.2f\n", num1_f, num2_f, result);
        } else {
            log_error("Division by zero!");
        }
    }
    else {
        log_error("Invalid operation!");
    }
}

/******************************************************************************
 * USER COMMAND HANDLER
 ******************************************************************************/
void handle_user_commands(char *cmd) {
    if (strcmp(cmd, "help") == 0) {
        // Print user-specific help
        printf("  swap - Swap two numbers\n");
        printf("  calc - Simple calculator\n");
        return;
    }
    
    if (strcmp(cmd, "swap") == 0 || strcmp(cmd, "SWAP") == 0) {
        command_swap();
    }
    else if (strcmp(cmd, "calc") == 0 || strcmp(cmd, "calculator") == 0) {
        command_calculator();
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