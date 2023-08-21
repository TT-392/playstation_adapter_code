#include <stdint.h>
#include "pico/stdlib.h"

enum spi_mode {
    SPI_BITBANG
};


typedef struct {
    uint MOSI;
    uint MISO;
    uint CLK;
    enum spi_mode mode;
    uint frequency;
} spi_config_t;

void universal_spi_init(spi_config_t config);

// all bytes are msb first to keep things compatible with the sdk functions
void universal_spi_write_read_blocking(spi_config_t config, uint8_t *out, uint8_t *in, int length);
