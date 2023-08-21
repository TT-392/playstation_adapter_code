#include "spi.h"
#include <stdint.h>
#include "pico/stdlib.h"

uint64_t delay_us = 0;

void universal_spi_init(spi_config_t config) {
    gpio_init(config.MOSI);
    gpio_set_dir(config.MOSI, GPIO_OUT);
    gpio_init(config.MISO);
    gpio_set_dir(config.MISO, GPIO_IN);
    gpio_init(config.CLK);
    gpio_set_dir(config.CLK, GPIO_OUT);
    gpio_put(config.CLK, 1);
    gpio_put(config.MOSI, 1);
    delay_us = 1000000 / config.frequency / 2;
}

// all bytes are msb first to keep things compatible with the sdk functions
void universal_spi_write_read_blocking(spi_config_t config, uint8_t *out, uint8_t *in, int length) {
    if (config.mode == SPI_BITBANG) {
        for (int b = 0; b < length; b++) {
            in[b] = 0;

            for (int i = 7; i >= 0; i--) {
                gpio_put(config.CLK, 0);
                gpio_put(config.MOSI, (out[b] >> i) & 1);
                sleep_us(delay_us);

                gpio_put(config.CLK, 1);
                in[b] |= gpio_get(config.MISO) << i;
                sleep_us(delay_us);
            }
        }
    }
}

