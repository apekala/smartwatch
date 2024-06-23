/**
 * Copyright (C) 2023 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "bma4_defs.h"
#include "common.h"


#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/logging/log.h>
#include <zephyr/logging/log_ctrl.h>

#include <string.h>
#include <stdio.h>

LOG_MODULE_DECLARE(bma456, LOG_LEVEL_DBG);


#define SPI_BMA  SPI_OP_MODE_MASTER | SPI_MODE_CPHA | SPI_MODE_CPOL  | SPI_WORD_SET(8) | SPI_LINES_SINGLE | SPI_TRANSFER_MSB

// Buffers for communication with bma456
__attribute__((aligned(4))) unsigned char bma456_rbuf[50];    // buffer for data read from bma456
__attribute__((aligned(4))) unsigned char bma456_wbuf[50];    // buffer for data written to bma456


//buffer structures
struct spi_buf bmp_tx_bufs[1];
struct spi_buf bmp_rx_bufs[1];

//buffer array
const struct spi_buf_set bptx = {
		.buffers = bmp_tx_bufs,
		.count = ARRAY_SIZE(bmp_tx_bufs)
	};

const struct spi_buf_set bprx = {
		.buffers = bmp_rx_bufs,
		.count = ARRAY_SIZE(bmp_rx_bufs)
	};

const struct spi_dt_spec bma456_dev = SPI_DT_SPEC_GET(DT_NODELABEL(bma456), SPI_BMA, 0);

/******************************************************************************/
/*!                       Macro definitions                                   */

/*! Read write length varies based on user requirement */
#define BMA4_READ_WRITE_LEN  UINT8_C(46)

/******************************************************************************/
/*!                Static variable definition                                 */

/*! Variable that holds the I2C device address or SPI chip selection */
static uint8_t dev_addr;

/******************************************************************************/
/*!                User interface functions                                   */

/*!
 * I2C read function map to COINES platform
 */
// BMA4_INTF_RET_TYPE bma4_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
// {
//     uint8_t dev_address = *(uint8_t*)intf_ptr;

//     (void)intf_ptr;

//     return coines_read_i2c(COINES_I2C_BUS_0, dev_address, reg_addr, reg_data, (uint16_t)len);
// }

// /*!
//  * I2C write function map to COINES platform
//  */
// BMA4_INTF_RET_TYPE bma4_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
// {
//     uint8_t dev_address = *(uint8_t*)intf_ptr;

//     (void)intf_ptr;

//     return coines_write_i2c(COINES_I2C_BUS_0, dev_address, reg_addr, (uint8_t *)reg_data, (uint16_t)len);
// }

/*!
 * SPI read function map to COINES platform
 */
BMA4_INTF_RET_TYPE bma4_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{

    int ret;
    
    bma456_wbuf[0]= reg_addr | 0x80;
    bma456_wbuf[1]= 0xFF;
    bmp_tx_bufs[0].len=len+2;
    bmp_rx_bufs[0].len=len+2;
    bmp_tx_bufs[0].buf = bma456_wbuf;
    bmp_rx_bufs[0].buf = bma456_rbuf;

    ret = spi_transceive_dt(&bma456_dev, &bptx, &bprx);
    if (ret){
    LOG_ERR("SPI read error address: %d\tlen: %d", reg_addr, len);
    }
    
    for(int i=0; i<len; i++){
        // LOG_WRN("%d: %x", i, bma456_rbuf[i+1]);
        reg_data[i] = bma456_rbuf[i+1];
    }

    return ret;
}

/*!
 * SPI write function map to COINES platform
 */
BMA4_INTF_RET_TYPE bma4_spi_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    bma456_wbuf[0]= reg_addr & 0x7F;
    // bma456_wbuf[1]= val;
    for(int i =0; i<len; i++){
        bma456_wbuf[i+1]=reg_data[i];
    }

    bmp_tx_bufs[0].buf = bma456_wbuf;
    bmp_rx_bufs[0].buf = bma456_rbuf;
    bmp_tx_bufs[0].len=len+1;
    bmp_rx_bufs[0].len=len+1;

    return  spi_transceive_dt(&bma456_dev, &bptx, &bprx);
}

/*!
 * Delay function map to COINES platform
 */
void bma4_delay_us(uint32_t period, void *intf_ptr)
{
    (void) intf_ptr;
    k_usleep(period);
}

/*!
 *  @brief Function to select the interface between SPI and I2C.
 *  Also to initialize coines platform
 */
int8_t bma4_interface_init(struct bma4_dev *bma, uint8_t intf, enum bma4_variant variant)
{
    int8_t rslt = BMA4_OK;

    if (bma != NULL)
    {
        /* Bus configuration : I2C */
        if (intf == BMA4_I2C_INTF)
        {
            LOG_ERR("I2C unavailable");
            // LOG_ERR("I2C Interface \n");

            // /* To initialize the user I2C function */
            // dev_addr = BMA4_I2C_ADDR_PRIMARY;
            // bma->intf = BMA4_I2C_INTF;
            // bma->bus_read = bma4_i2c_read;
            // bma->bus_write = bma4_i2c_write;

            // /* SDO to Ground */
            // (void)coines_set_pin_config(COINES_SHUTTLE_PIN_22, COINES_PIN_DIRECTION_OUT, COINES_PIN_VALUE_LOW);

            // /* Make CSB pin HIGH */
            // (void)coines_set_pin_config(COINES_SHUTTLE_PIN_21, COINES_PIN_DIRECTION_OUT, COINES_PIN_VALUE_HIGH);
            // coines_delay_msec(100);

            // /* SDO pin is made low */
            // (void)coines_set_pin_config(COINES_SHUTTLE_PIN_SDO, COINES_PIN_DIRECTION_OUT, COINES_PIN_VALUE_LOW);

            // (void)coines_config_i2c_bus(COINES_I2C_BUS_0, COINES_I2C_STANDARD_MODE);
        }
        /* Bus configuration : SPI */
        else if (intf == BMA4_SPI_INTF)
        {
            

            /* To initialize the user SPI function */
            // dev_addr = COINES_SHUTTLE_PIN_7; // chyba niepotrzebne
            bma->intf = BMA4_SPI_INTF;
            bma->bus_read = bma4_spi_read;
            bma->bus_write = bma4_spi_write;
            // (void)coines_config_spi_bus(COINES_SPI_BUS_0, COINES_SPI_SPEED_7_5_MHZ, COINES_SPI_MODE0);
            LOG_INF("SPI interface configured");
        }

        /* Assign variant information */
        bma->variant = variant;

        /* Assign device address to interface pointer */
        bma->intf_ptr = &dev_addr;

        /* Configure delay in microseconds */
        bma->delay_us = bma4_delay_us;

        /* Configure max read/write length (in bytes) ( Supported length depends on target machine) */
        bma->read_write_len = BMA4_READ_WRITE_LEN;

        /* Set Performance mode status */
        bma->perf_mode_status = BMA4_DISABLE;

        k_msleep(100);

        // (void)coines_set_shuttleboard_vdd_vddio_config(3300, 3300);

        k_msleep(200);
    }
    else
    {
        rslt = BMA4_E_NULL_PTR;
    }

    return rslt;

}
/*!
 *  @brief Prints the execution status of the APIs.
 */
void bma4_error_codes_print_result(const char api_name[], int8_t rslt)
{
    if (rslt != BMA4_OK)
    {
        LOG_ERR("%s\t", api_name);
        if (rslt == BMA4_E_NULL_PTR)
        {
            LOG_ERR("Error [%d] : Null pointer\r\n", rslt);
        }
        else if (rslt == BMA4_E_COM_FAIL)
        {
            LOG_ERR("Error [%d] : Communication failure\r\n", rslt);
        }
        else if (rslt == BMA4_E_CONFIG_STREAM_ERROR)
        {
            LOG_ERR("Error [%d] : Invalid configuration stream\r\n", rslt);
        }
        else if (rslt == BMA4_E_SELF_TEST_FAIL)
        {
            LOG_ERR("Error [%d] : Self test failed\r\n", rslt);
        }
        else if (rslt == BMA4_E_INVALID_SENSOR)
        {
            LOG_ERR("Error [%d] : Device not found\r\n", rslt);
        }
        else if (rslt == BMA4_E_OUT_OF_RANGE)
        {
            LOG_ERR("Error [%d] : Out of Range\r\n", rslt);
        }
        else if (rslt == BMA4_E_AVG_MODE_INVALID_CONF)
        {
            LOG_ERR("Error [%d] : Invalid bandwidth and ODR combination in Accel Averaging mode\r\n", rslt);
        }
        else
        {
            /* For more error codes refer "*_defs.h" */
            LOG_ERR("Error [%d] : Unknown error code\r\n", rslt);
        }
    }
}

/*!
 *  @brief Deinitializes coines platform
 *
 *  @return void.
 */
void bma4_coines_deinit(void)
{
    // (void)fflush(stdout);
    // coines_delay_msec(200);

    // (void)coines_set_shuttleboard_vdd_vddio_config(0, 0);
    // coines_delay_msec(1000);

    // /* Coines interface reset */
    // coines_soft_reset();
    // coines_delay_msec(1000);
    // (void)coines_close_comm_intf(COINES_COMM_INTF_USB, NULL);
}
