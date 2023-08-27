#pragma once

typedef struct {
    uint8_t ring_left;
    uint8_t ring_right;
    uint8_t center_left;
    uint8_t center_right;
    uint8_t select;
    uint8_t start;
} settings_t;

void settings_start();

void settings_kill();

volatile extern settings_t settings;
