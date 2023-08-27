#include "pins.h"
#include "pico/stdlib.h"
#include "spi.h"
#include "usb.h"
#include "drum.h"

static const spi_config_t spi_config = {
    .MISO = PIN_DATA,
    .MOSI = PIN_CMD,
    .CLK = PIN_CLK,
    .mode = SPI_BITBANG,
    .frequency = 250000
};


#define ACK_SUCCESS true
#define ACK_FAIL false
static bool wait_for_ack() {
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


void drum_init() {
    gpio_init(PIN_ACK);
    gpio_set_dir(PIN_ACK, GPIO_IN);

    gpio_init(PIN_ATTENTION);
    gpio_set_dir(PIN_ATTENTION, GPIO_OUT);
    gpio_put(PIN_ATTENTION, 1);

    universal_spi_init(spi_config);
}

static drum_t drum = {};

drum_t drum_read() {
    uint8_t in;
    uint8_t data1 = 0xaa;
    uint8_t data2 = 0xaa;
    uint8_t out = 0x80;
    gpio_put(PIN_ATTENTION, 0);
    sleep_us(100);
    universal_spi_write_read_blocking(spi_config, &out, &in, 1);

    if (wait_for_ack() == ACK_FAIL) {
        gpio_put(PIN_ATTENTION, 1);
        return drum;
    }

    out = 0x42;
    universal_spi_write_read_blocking(spi_config, &out, &in, 1);

    if (wait_for_ack() == ACK_FAIL) {
        gpio_put(PIN_ATTENTION, 1);
        return drum;
    }

    out = 0x00;
    universal_spi_write_read_blocking(spi_config, &out, &in, 1);

    if (wait_for_ack() == ACK_FAIL) {
        gpio_put(PIN_ATTENTION, 1);
        return drum;
    }

    out = 0x00;
    universal_spi_write_read_blocking(spi_config, &out, &data1, 1);

    if (wait_for_ack() == ACK_FAIL) {
        gpio_put(PIN_ATTENTION, 1);
        return drum;
    }

    out = 0x00;
    universal_spi_write_read_blocking(spi_config, &out, &data2, 1);


    sleep_us(100);
    gpio_put(PIN_ATTENTION, 1);
    sleep_us(100);

    drum = (drum_t){0};

    if ((data1 & 0x80) == 0)
        drum.select = true;

    if ((data1 & 0x10) == 0)
        drum.start = true;

    if ((data1 & 0x01) == 0)
        drum.center_left = true;

    if ((data2 & 0x20) == 0)
        drum.ring_left = true;

    if ((data2 & 0x04) == 0)
        drum.center_right = true;

    if ((data2 & 0x10) == 0)
        drum.ring_right = true;

    volatile static uint8_t last_data1 = 0;
    volatile static uint8_t last_data2 = 0;

    last_data1 = data1;
    last_data2 = data2;

    return drum;
}
