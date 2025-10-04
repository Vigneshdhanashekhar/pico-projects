#include "pico/stdlib.h"
#include <stdio.h>

int main() {
    // Initialize USB serial
    stdio_init_all();
    
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
