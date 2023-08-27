#include "usb.h"
#include "tusb.h"
#include "keybinds.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include "hardware/flash.h"

#define MAGIC_NUMBER 0xA4A349AC
#define FLASH_TARGET_OFFSET ((256*7) * 1024)
const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);

static volatile keybinds_t keybinds;

static volatile keybinds_t default_keybinds = {
    .ring_left = HID_KEY_D,
    .ring_right = HID_KEY_K,
    .center_left = HID_KEY_F,
    .center_right = HID_KEY_J,
    .select = HID_KEY_ESCAPE,
    .start = HID_KEY_ENTER,
};

static volatile bool write_keybinds_to_flash = false;

keybinds_t keybinds_get() {
    return keybinds;
}

void keybinds_write(keybinds_t binds) {
    multicore_lockout_victim_init();

    keybinds = binds;
    write_keybinds_to_flash = true;
    while (write_keybinds_to_flash);
}

void keybinds_task() {
    if (write_keybinds_to_flash) {

        while (!multicore_lockout_start_timeout_us(1000));
        uint32_t interrupts = save_and_disable_interrupts();

        uint8_t data_to_write[FLASH_PAGE_SIZE] = {0};
        *((uint64_t*)data_to_write) = MAGIC_NUMBER;

        int i = sizeof(uint64_t);
        data_to_write[i++] = keybinds.ring_left;
        data_to_write[i++] = keybinds.ring_right;
        data_to_write[i++] = keybinds.center_left;
        data_to_write[i++] = keybinds.center_right;
        data_to_write[i++] = keybinds.select;
        data_to_write[i++] = keybinds.start;


        flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
        flash_range_program(FLASH_TARGET_OFFSET, data_to_write, FLASH_PAGE_SIZE);

        write_keybinds_to_flash = false;

        restore_interrupts(interrupts);
        while (!multicore_lockout_end_timeout_us(1000));
    }
}

void keybinds_init() {
    uint64_t magic_number = *((uint64_t*)flash_target_contents);

    if (magic_number != MAGIC_NUMBER) {
        keybinds = default_keybinds;
        return;
    }

    int i = sizeof(magic_number);

    keybinds.ring_left = flash_target_contents[i++];
    keybinds.ring_right = flash_target_contents[i++];
    keybinds.center_left = flash_target_contents[i++];
    keybinds.center_right = flash_target_contents[i++];
    keybinds.select = flash_target_contents[i++];
    keybinds.start = flash_target_contents[i++];
}

