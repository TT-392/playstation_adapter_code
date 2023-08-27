#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/bootrom.h"
#include "hardware/spi.h"
#include "pins.h"
#include "usb.h"
#include "tusb.h"
#include "settings.h"
#include "drum.h"
#include "keybinds.h"

int main() {
    usb_init();
    drum_init();
    keybinds_init();


    bool settings_active = false;
    while (1) {
        usb_task();
        keybinds_task();

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


        if (!settings_active) {
            drum_t drum = drum_read();

            uint8_t pressed_keys[6] = {};

            keybinds_t keybinds = keybinds_get();

            if (drum.ring_left) {
                pressed_keys[0] = keybinds.ring_left;
            } if (drum.ring_right) {
                pressed_keys[0] = keybinds.ring_right;
            } if (drum.center_left) {
                pressed_keys[0] = keybinds.center_left;
            } if (drum.center_right) {
                pressed_keys[0] = keybinds.center_right;
            } if (drum.select) {
                pressed_keys[0] = keybinds.select;
            } if (drum.start) {
                pressed_keys[0] = keybinds.start;
            }

            keyboard_update(0, pressed_keys);
        }

    }
}

