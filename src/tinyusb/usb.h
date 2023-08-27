#pragma once

#include <stdbool.h>
#include <stdint.h>


void usb_init();

void usb_task();

bool usb_connected();

bool cdc_data_available();

void cdc_get_line(char buffer[101]); // max length of line is 100, + 1 for '\0'

bool cdc_data_available();

void keyboard_update(uint8_t modifiers, uint8_t key_codes[6]);

int cdc_printf(const char *format, ...);

bool usb_cdc_connected();

void usb_cdc_read_string_capitalized(char* buffer, int length);


#define printf cdc_printf

