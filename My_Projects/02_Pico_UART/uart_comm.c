#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <stdio.h>

#define UART_ID uart0
#define BAUD_RATE 9600
#define UART_TX_PIN 0
#define UART_RX_PIN 1

int main() {
    // Initialize UART with specific baud rate
    uart_init(UART_ID, BAUD_RATE);
    
    // Set the TX and RX pins
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // Now set up stdio to use this UART
    stdio_uart_init_full(UART_ID, BAUD_RATE, UART_TX_PIN, UART_RX_PIN);
    
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    int count = 0;
    
    while (true) {
        gpio_put(LED_PIN, 1);
        printf("LED ON - Count: %d\n", count++);
        sleep_ms(1000);

        gpio_put(LED_PIN, 0);
        printf("LED OFF\n");
        sleep_ms(1000);
    }
    
    return 0;
}