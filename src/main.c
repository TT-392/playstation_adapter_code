#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/bootrom.h"
#include "hardware/spi.h"
#include "pins.h"
#include "usb.h"
#include "settings.h"
#include "drum.h"

int main() {
    usb_init();
    drum_init();


    uint8_t prev_data1;
    uint8_t prev_data2;
    bool settings_active = false;
    while (1) {
        usb_task();

        if (usb_cdc_connected()) {
            if (!settings_active) {
                settings_start();
                settings_active = true;
            }
        } else {
            if (settings_active) {
                settings_kill();
                settings_active = false;
            }
        }


        drum_read();

    }
}

