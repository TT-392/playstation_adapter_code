#pragma once

typedef struct {
    uint8_t ring_left;
    uint8_t ring_right;
    uint8_t center_left;
    uint8_t center_right;
    uint8_t select;
    uint8_t start;
} keybinds_t;

keybinds_t keybinds_get();

void keybinds_write(keybinds_t keybinds);

void keybinds_task();

void keybinds_init();
