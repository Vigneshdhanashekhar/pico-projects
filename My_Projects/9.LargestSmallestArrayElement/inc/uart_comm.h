#ifndef UART_COMM_H
#define UART_COMM_H

#include "pico/stdlib.h"
#include "hardware/uart.h"

/******************************************************************************
 * UART CONFIGURATION
 ******************************************************************************/
#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define BUFFER_SIZE 256
#define STARTUP_DELAY_MS 10000

/******************************************************************************
 * GLOBAL VARIABLES (extern declarations)
 ******************************************************************************/
extern char buffer[BUFFER_SIZE];
extern int buffer_index;

/******************************************************************************
 * FUNCTION PROTOTYPES
 ******************************************************************************/
void uart_communication_init(void);
void process_command(char *cmd);

#endif // UART_COMM_H