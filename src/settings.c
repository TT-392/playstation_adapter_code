#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "settings.h"
#include "keybinds.h"
#include "usb.h"
#include "utils.h"
#include "tusb.h"
#include "drum.h"

static void settings_process() {
    int i = 0;
    keybinds_t keybinds = keybinds_get();

    printf("Welcome to the 太鼓 drum setup utility\n");
    printf("Your current settings are as follows:\n");
    printf("Ring left: %s\n", key_to_string(keybinds.ring_left));
    printf("Ring right: %s\n", key_to_string(keybinds.ring_right));
    printf("Center left: %s\n", key_to_string(keybinds.center_left));
    printf("Center right: %s\n", key_to_string(keybinds.center_right));
    printf("start: %s\n", key_to_string(keybinds.start));
    printf("select: %s\n", key_to_string(keybinds.select));


    char *ring_left = "ring left";
    char *ring_right = "ring right";
    char *center_left = "center left";
    char *center_right = "center right";
    char *select = "select";
    char *start = "select";

    while (1) {
        volatile uint8_t *active_keybind;
        char *button_string;


        printf("Hit/push the zone/button you want to rebind\n");
        while (1) {
            drum_t drum = drum_read();

            if (drum.ring_left) {
                button_string = ring_left;
                active_keybind = &keybinds.ring_left;
                break;
            } if (drum.ring_right) {
                button_string = ring_right;
                active_keybind = &keybinds.ring_right;
                break;
            } if (drum.center_left) {
                button_string = center_left;
                active_keybind = &keybinds.center_left;
                break;
            } if (drum.center_right) {
                button_string = center_right;
                active_keybind = &keybinds.center_right;
                break;
            } if (drum.select) {
                button_string = select;
                active_keybind = &keybinds.select;
                break;
            } if (drum.start) {
                button_string = start;
                active_keybind = &keybinds.start;
                break;
            }
        }

        printf("Rebinding \"%s\", please type the name of a key: \n", button_string);

        char buffer[60];
        usb_cdc_read_string_capitalized(buffer, sizeof(buffer));
        int key = string_to_key(buffer);

        if (key != -1) {
            printf("%c%s: %s -> %s\n", button_string[0] - ('a'-'A'), button_string + 1, key_to_string(*active_keybind), key_to_string(key));

            *active_keybind = key;

            keybinds_write(keybinds);
            printf("New keybind successfully written to flash storage.\n\n");
        } else {
            printf("Error, unknown key: %s\n", buffer);
        }
    }
}

void settings_kill() {
    sleep_ms(10);
    multicore_reset_core1();
    sleep_ms(10);
}

void settings_start() {
    sleep_ms(10);
    multicore_reset_core1();
    sleep_ms(10);

    multicore_launch_core1(settings_process);
}
