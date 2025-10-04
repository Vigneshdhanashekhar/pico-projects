#include "pico/stdlib.h"

int main() {
    // Initialize GPIO for the onboard LED (GPIO 25 on Pico)
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // Main loop
    while (true) {
        gpio_put(LED_PIN, 1);  // LED on
        sleep_ms(500);          // Wait 500ms
        gpio_put(LED_PIN, 0);  // LED off
        sleep_ms(500);          // Wait 500ms
    }
    
    return 0;
}
