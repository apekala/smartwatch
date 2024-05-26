/**
 *  @filename   :   epdif.c
 *  @brief      :   Implements EPD interface functions for Zephyr
 *                  Users have to implement all the functions in epdif.c
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     August 10 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "epdif.h"

#define SPI_EPD  (SPI_OP_MODE_MASTER | SPI_MODE_CPHA | SPI_MODE_CPOL | SPI_WORD_SET(8) | SPI_LINES_SINGLE | SPI_TRANSFER_MSB)

// Buffers for communication with EPD
__attribute__((aligned(4))) unsigned char epd_rbuf[10000];    // buffer for data read from EPD
__attribute__((aligned(4))) unsigned char epd_wbuf[10000];    // buffer for data written to EPD

// Buffer structures
struct spi_buf bmp_tx_bufs[1];
struct spi_buf bmp_rx_bufs[1];

// Buffer arrays
const struct spi_buf_set bptx = {
    .buffers = bmp_tx_bufs,
    .count = ARRAY_SIZE(bmp_tx_bufs)
};

// const struct spi_buf_set bprx = {
//     .buffers = bmp_rx_bufs,
//     .count = ARRAY_SIZE(bmp_rx_bufs)
// };

// SPI device specification
const struct spi_dt_spec spi_dev = SPI_DT_SPEC_GET(DT_NODELABEL(epd), SPI_EPD, 0);

LOG_MODULE_REGISTER();


int EpdIfInit(void) {
    
    if (!device_is_ready(spi_dev.bus)) {
        return -1;
    }


    gpio_pin_configure_dt(&RST_PIN, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&DC_PIN, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&CS_PIN, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&BUSY_PIN, GPIO_INPUT);


    return 0;
}

void EpdIfDigitalWriteRST(int value) {
    gpio_pin_set_dt(&RST_PIN, value);
}
void EpdIfDigitalWriteDC(int value) {
    gpio_pin_set_dt(&DC_PIN, value);
}
void EpdIfDigitalWriteCS(int value) {
    gpio_pin_set_dt(&CS_PIN, value);
}

int EpdIfDigitalRead() {
    return gpio_pin_get_dt(&BUSY_PIN);
}

void DelayMs(unsigned int delaytime) {
    k_msleep(delaytime);
}


void EpdIfSpiTransfer(unsigned char data) {
    bool ready = spi_is_ready(&spi_dev);
    LOG_INF("Ready: %i", ready);

    // unsigned char buffer[20] = { 0 };
    // unsigned int length = sizeof(buffer);

    // const struct spi_buf tx_buffer = {
    //     .buf = &data,
    //     .len = 1
    // };

    // const struct spi_buf_set tx_buffers = {
    //     .buffers = &tx_buffer,
    //     .count = 1
    // };

    // int status = spi_write_dt(&spi_dev, &tx_buffers);
    bmp_tx_bufs[0].buf = &data;
    bmp_tx_bufs[0].len = 1;
    

    int status = spi_transceive_dt(&spi_dev, &bptx, NULL);
    LOG_INF("Status: %i", status);
}
