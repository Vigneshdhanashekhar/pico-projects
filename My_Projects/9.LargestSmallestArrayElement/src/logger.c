#include "logger.h"
#include <stdio.h>

/******************************************************************************
 * LOGGING FUNCTIONS
 ******************************************************************************/
void log_error(char *prompt) {
    printf("[ERROR] command: '%s'\n", prompt);
}

void log_system_status(char *prompt) {
    printf("[SYSTEM] command: '%s'\n", prompt);
}

void log_debug(char *prompt) {
    printf("[DEBUG] command: '%s'\n", prompt);
}

void log_warning(char *prompt) {
    printf("[WARNING] command: '%s'\n", prompt);
}

void log_info_int(int value) {
    printf("[INFO] %d\n", value);
}

void log_info_string(char *str) {
    printf("[INFO] %s\n", str);
}

void log_info_float(float value) {
    printf("[INFO] %.2f\n", value);
}

void clear_console(void) {
    // ANSI escape code to clear screen and move cursor to home position
    printf("\033[2J\033[H");
    fflush(stdout);
}