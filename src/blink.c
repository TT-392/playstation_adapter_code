#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/watchdog.h"

int main() {
    stdio_init_all(); // otherwise picotool reboot won't work

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (1) {
        gpio_put(LED_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_PIN, 0);
        sleep_ms(100);
    }
}

