/**
 *  @filename   :   epdif.h
 *  @brief      :   Header file of epdif.cpp providing EPD interface functions
 *                  Users have to implement all the functions in epdif.cpp
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

#ifndef EPDIF_H
#define EPDIF_H

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/types.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/logging/log.h>

#define RES DT_ALIAS(respin) //res
#define EPD_CS DT_ALIAS(cspin) //cs
#define EPD_DC DT_ALIAS(dcpin) //dc
#define EPD_BUSY DT_ALIAS(busypin) //busy


static struct gpio_dt_spec RST_PIN = GPIO_DT_SPEC_GET(RES, gpios);
static struct gpio_dt_spec DC_PIN  = GPIO_DT_SPEC_GET(EPD_CS, gpios);
static struct gpio_dt_spec CS_PIN  = GPIO_DT_SPEC_GET(EPD_DC, gpios);
static struct gpio_dt_spec BUSY_PIN = GPIO_DT_SPEC_GET(EPD_BUSY, gpios);


int  EpdIfInit(void);
void EpdIfDigitalWriteRST(int value); 
void EpdIfDigitalWriteDC(int value);
void EpdIfDigitalWriteCS(int value);
int  EpdIfDigitalRead();
void DelayMs(unsigned int delaytime);
void EpdIfSpiTransfer(unsigned char data);


#endif /* EPDIF_H */