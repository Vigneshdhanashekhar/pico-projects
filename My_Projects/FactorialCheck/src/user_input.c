#include "user_input.h"
#include "uart_comm.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/******************************************************************************
 * USER INPUT FUNCTIONS
 ******************************************************************************/

// Helper function to get integer input from user
int get_user_input_int(char *prompt) {
    static char input_buffer[32];
    static int input_index = 0;
    static bool waiting_for_input = false;
    
    if (!waiting_for_input) {
        log_info_string(prompt);
        waiting_for_input = true;
        input_index = 0;
    }
    
    while (true) {
        if (uart_is_readable(UART_ID)) {
            char c = uart_getc(UART_ID);
            
            if (c == '\n' || c == '\r') {
                if (input_index > 0) {
                    input_buffer[input_index] = '\0';
                    int value = atoi(input_buffer);
                    waiting_for_input = false;
                    input_index = 0;
                    return value;
                }
            }
            else if (input_index < 31) {
                input_buffer[input_index++] = c;
            }
        }
        sleep_ms(10);
    }
}

// Helper function to get float input from user
float get_user_input_float(char *prompt) {
    static char input_buffer[32];
    static int input_index = 0;
    static bool waiting_for_input = false;
    
    if (!waiting_for_input) {
        log_info_string(prompt);
        waiting_for_input = true;
        input_index = 0;
    }
    
    while (true) {
        if (uart_is_readable(UART_ID)) {
            char c = uart_getc(UART_ID);
            
            if (c == '\n' || c == '\r') {
                if (input_index > 0) {
                    input_buffer[input_index] = '\0';
                    float value = atof(input_buffer);
                    waiting_for_input = false;
                    input_index = 0;
                    return value;
                }
            }
            else if (input_index < 31) {
                input_buffer[input_index++] = c;
            }
        }
        sleep_ms(10);
    }
}

// Helper function to get string input from user
void get_user_input_string(char *prompt, char *output_buffer, int max_length) {
    static char input_buffer[BUFFER_SIZE];
    static int input_index = 0;
    static bool waiting_for_input = false;
    
    if (!waiting_for_input) {
        log_info_string(prompt);
        waiting_for_input = true;
        input_index = 0;
    }
    
    while (true) {
        if (uart_is_readable(UART_ID)) {
            char c = uart_getc(UART_ID);
            
            if (c == '\n' || c == '\r') {
                if (input_index > 0) {
                    input_buffer[input_index] = '\0';
                    strncpy(output_buffer, input_buffer, max_length - 1);
                    output_buffer[max_length - 1] = '\0';
                    waiting_for_input = false;
                    input_index = 0;
                    return;
                }
            }
            else if (input_index < BUFFER_SIZE - 1) {
                input_buffer[input_index++] = c;
            }
        }
        sleep_ms(10);
    }
}