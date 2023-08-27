#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "settings.h"
#include "usb.h"
#include "utils.h"
#include "tusb.h"
#include "drum.h"

volatile settings_t settings = {
    .ring_left = HID_KEY_D,
    .ring_right = HID_KEY_K,
    .center_left = HID_KEY_F,
    .center_right = HID_KEY_J,
    .select = HID_KEY_ESCAPE,
    .start = HID_KEY_ENTER,
};

static void settings_process() {
    int i = 0;
    printf("Welcome to the 太鼓 drum setup utility\n");
    printf("Your current settings are as follows:\n");
    printf("Ring left: %s\n", key_to_string(settings.ring_left));
    printf("Ring right: %s\n", key_to_string(settings.ring_right));
    printf("Center left: %s\n", key_to_string(settings.center_left));
    printf("Center right: %s\n", key_to_string(settings.center_right));
    printf("start: %s\n", key_to_string(settings.start));
    printf("select: %s\n", key_to_string(settings.select));


    char *ring_left = "ring left";
    char *ring_right = "ring right";
    char *center_left = "center left";
    char *center_right = "center right";
    char *select = "select";
    char *start = "select";

    while (1) {
        volatile uint8_t *active_setting;
        char *button_string;

        printf("Hit/push the zone/button you want to rebind\n");
        while (1) {
            if (drum.ring_left) {
                button_string = ring_left;
                active_setting = &settings.ring_left;
                break;
            } if (drum.ring_right) {
                button_string = ring_right;
                active_setting = &settings.ring_right;
                break;
            } if (drum.center_left) {
                button_string = center_left;
                active_setting = &settings.center_left;
                break;
            } if (drum.center_right) {
                button_string = center_right;
                active_setting = &settings.center_right;
                break;
            } if (drum.select) {
                button_string = select;
                active_setting = &settings.select;
                break;
            } if (drum.start) {
                button_string = start;
                active_setting = &settings.start;
                break;
            }
        }

        printf("Rebinding \"%s\", please type the name of a key: \n", button_string);

        char buffer[60];
        usb_cdc_read_string_capitalized(buffer, sizeof(buffer));
        int key = string_to_key(buffer);

        if (key != -1) {
            printf("%c%s: %s -> %s\n", button_string[0] - ('a'-'A'), button_string + 1, key_to_string(*active_setting), key_to_string(key));

            *active_setting = key;
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
