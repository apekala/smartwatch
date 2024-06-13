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
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>
#include <zephyr/drivers/gpio.h>

#define RES DT_ALIAS(respin) //res
#define EPD_CS DT_ALIAS(cspin) //cs
// #define EPD_CS DT_ALIAS(led2) //cs
#define EPD_DC DT_ALIAS(dcpin) //dc
// #define EPD_DC DT_ALIAS(led1) //dc
#define EPD_BUSY DT_ALIAS(busypin) //busy

struct gpio_dt_spec rst = GPIO_DT_SPEC_GET(RES, gpios);
struct gpio_dt_spec dc = GPIO_DT_SPEC_GET(EPD_DC, gpios);
struct gpio_dt_spec cs = GPIO_DT_SPEC_GET(EPD_CS, gpios);
struct gpio_dt_spec busy = GPIO_DT_SPEC_GET(EPD_BUSY, gpios);

#define SPI_EPD  (SPI_OP_MODE_MASTER | SPI_MODE_CPHA | SPI_MODE_CPOL | SPI_WORD_SET(8) | SPI_LINES_SINGLE | SPI_TRANSFER_MSB)

// Buffers for communication with EPD
__attribute__((aligned(4))) unsigned char epd_rbuf[1];    // buffer for data read from EPD
__attribute__((aligned(4))) unsigned char epd_wbuf[1];    // buffer for data written to EPD

// Buffer structures
struct spi_buf epd_tx_bufs[1];
struct spi_buf epd_rx_bufs[1];

// Buffer arrays
const struct spi_buf_set epd_bptx = {
    .buffers = epd_tx_bufs,
    .count = ARRAY_SIZE(epd_tx_bufs)
};

const struct spi_buf_set epd_bprx = {
    .buffers = epd_rx_bufs,
    .count = ARRAY_SIZE(epd_rx_bufs)
};

// SPI device specification
const struct spi_dt_spec spi_dev = SPI_DT_SPEC_GET(DT_NODELABEL(epd), SPI_EPD, 0);

// LOG_MODULE_REGISTER();


int epdIf_init(void) {
    int ret;
    if (!device_is_ready(spi_dev.bus)) {
        printk("w init spi\n");
        return -1;
    }

    if (!device_is_ready(rst.port) || !device_is_ready(dc.port) ||!device_is_ready(cs.port) ||!device_is_ready(busy.port) ) {
        printk("w init gpio\n");
		return -1;
	}

    ret = gpio_pin_configure_dt(&rst, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("w init rst\n");
		return -1 ;
	}
    ret = gpio_pin_configure_dt(&dc, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("w init dc\n");
		return -1;
	}
    ret = gpio_pin_configure_dt(&cs, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("w init cs\n");
		return - 1;
	}
    ret = gpio_pin_configure_dt(&busy, GPIO_INPUT);
    if (ret < 0) {
        printk("w init busy\n");
		return -1;
	}


    return 0;
}

void epdIf_digital_write_RST(int value) {
    gpio_pin_set_dt(&rst, value);
}
void epdIf_digital_write_DC(int value) {
    gpio_pin_set_dt(&dc, value);
}
void epdIf_digital_write_CS(int value) {
    gpio_pin_set_dt(&cs, value);
}

int epdIf_digital_read() {
    return gpio_pin_get_dt(&busy);
}

void delay_ms(int delaytime) {
    k_msleep(delaytime);
}


void epdIf_spi_transfer(uint8_t data) {
    epd_wbuf[0] = data;
    epd_tx_bufs[0].buf = epd_wbuf;
    epd_rx_bufs[0].buf = epd_rbuf;
    epd_tx_bufs[0].len = 1;
    epd_rx_bufs[0].len = 1;
    epdIf_digital_write_CS(0);
    spi_transceive_dt(&spi_dev, &epd_bptx, &epd_bprx);
    epdIf_digital_write_CS(1);
}
