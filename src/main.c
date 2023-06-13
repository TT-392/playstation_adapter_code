#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/bootrom.h"
#include "hardware/spi.h"
#include "pins.h"

#define ACK_SUCCESS true
#define ACK_FAIL false
bool wait_for_ack() {
    int timeout = 100;
    while (gpio_get(PIN_ACK)) {
        sleep_us(1);
        timeout--;
        if (timeout == 0)
            return ACK_FAIL;
    }
    sleep_us(10);

    timeout = 100;
    while (!gpio_get(PIN_ACK)) {
        sleep_us(1);
        timeout--;
        if (timeout == 0)
            return ACK_FAIL;
    }

    return ACK_SUCCESS;
}

int main() {
    stdio_init_all(); // otherwise picotool reboot won't work
    while (!stdio_usb_connected()) {
        sleep_ms(500);
    }
    printf("new\n");

    gpio_set_function(PIN_DATA, GPIO_FUNC_SPI);

    gpio_set_function(PIN_CMD, GPIO_FUNC_SPI);

    gpio_set_function(PIN_CLK, GPIO_FUNC_SPI);

    gpio_init(PIN_ACK);
    gpio_set_dir(PIN_ACK, GPIO_IN);

    gpio_init(PIN_ATTENTION);
    gpio_set_dir(PIN_ATTENTION, GPIO_OUT);
    gpio_put(PIN_ATTENTION, 1);

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    spi_init(spi0, 250000);
    spi_set_format(spi0, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST); // apparently LSB first doesn't exist in rp2040 land, so I guess we'll be flipping all our bytes compared to https://store.curiousinventor.com/guides/PS2/

    uint8_t prev_data1;
    uint8_t prev_data2;
    while (1) {
        uint8_t in;
        uint8_t data1 = 0xaa;
        uint8_t data2 = 0xaa;
        uint8_t out = 0x80;
        gpio_put(PIN_ATTENTION, 0);
        sleep_us(100);
        spi_write_read_blocking(spi0, &out, &in, 1);

        if (wait_for_ack() == ACK_FAIL) {
            gpio_put(PIN_ATTENTION, 1);
            continue;
        }

        out = 0x42;
        spi_write_read_blocking(spi0, &out, &in, 1);

        if (wait_for_ack() == ACK_FAIL) {
            gpio_put(PIN_ATTENTION, 1);
            continue;
        }

        out = 0x00;
        spi_write_read_blocking(spi0, &out, &in, 1);

        if (wait_for_ack() == ACK_FAIL) {
            gpio_put(PIN_ATTENTION, 1);
            continue;
        }

        out = 0x00;
        spi_write_read_blocking(spi0, &out, &data1, 1);

        if (wait_for_ack() == ACK_FAIL) {
            gpio_put(PIN_ATTENTION, 1);
            continue;
        }

        out = 0x00;
        spi_write_read_blocking(spi0, &out, &data2, 1);

        if ((data1 & 0x80) == 0 && (prev_data1 & 0x80))
            printf("select\n");

        if ((data1 & 0x10) == 0 && (prev_data1 & 0x10))
            printf("start\n");

        if ((data1 & 0x01) == 0 && (prev_data1 & 0x01))
            printf("center left\n");

        if ((data2 & 0x20) == 0 && (prev_data2 & 0x20))
            printf("ring left\n");

        if ((data2 & 0x04) == 0 && (prev_data2 & 0x04))
            printf("center right\n");
        
        if ((data2 & 0x10) == 0 && (prev_data2 & 0x10))
            printf("ring right\n");

        prev_data1 = data1;
        prev_data2 = data2;


        sleep_us(100);
        gpio_put(PIN_ATTENTION, 1);
        sleep_us(100);
    }
}

