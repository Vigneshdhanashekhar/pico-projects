#include "pico/stdlib.h"

int main() {
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    int blink_count = 0;  // Add counter
    
    while (true) {
        blink_count++;              // Increment counter
        gpio_put(LED_PIN, 1);       // ● Breakpoint with condition: blink_count == 5
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
    }
    
    return 0;
}