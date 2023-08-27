#pragma once
#include <stdbool.h>

typedef struct {
    bool ring_left;
    bool ring_right;
    bool center_left;
    bool center_right;
    bool select;
    bool start;
} drum_t;

void drum_init();

void drum_read();

volatile extern drum_t drum;
