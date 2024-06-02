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

// LOG_MODULE_REGISTER();


int EpdIfInit(void) {
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
    ret = gpio_pin_configure_dt(&cs, GPIO_OUTPUT_INACTIVE);
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

void EpdIfDigitalWriteRST(int value) {
    gpio_pin_set_dt(&rst, value);
}
void EpdIfDigitalWriteDC(int value) {
    gpio_pin_set_dt(&dc, value);
}
void EpdIfDigitalWriteCS(int value) {
    gpio_pin_set_dt(&cs, value);
}

int EpdIfDigitalRead() {
    return gpio_pin_get_dt(&busy);
}

void DelayMs(int delaytime) {
    k_msleep(delaytime);
}


void EpdIfSpiTransfer(uint8_t data) {
    // LOG_INF("Ready: %i", ready);

    // unsigned char buffer[20] = { 0 };
    // unsigned int length = sizeof(buffer);
    uint8_t tx_buf[1] = { data };

    struct spi_buf tx_bufs[] = {
    {
      .buf = tx_buf,
      .len = sizeof(tx_buf)
    }
  };
  struct spi_buf_set tx = {
    .buffers = tx_bufs,
    .count = ARRAY_SIZE(tx_bufs)
  };

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
    EpdIfDigitalWriteCS(0);
    // spi_transceive_dt(&spi_dev, &bptx, NULL);
    spi_write_dt(&spi_dev, &tx);
    EpdIfDigitalWriteCS(1);
    // LOG_INF("Status: %i", status);
}
