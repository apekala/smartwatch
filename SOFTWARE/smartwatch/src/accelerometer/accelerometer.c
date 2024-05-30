#include "accelerometer.h"

#include "bma456w.h"
#include "common.h"

LOG_MODULE_REGISTER(bma456, LOG_LEVEL_DBG);

static struct bma4_dev bma = {0};

int8_t accel_init(void)
{
    /* Variable to store the status of API */
    int8_t rslt;

    /* Interface reference is given as a parameter
     *         For I2C : BMA4_I2C_INTF (not implemented)
     *         For SPI : BMA4_SPI_INTF
     * Variant information given as parameter - BMA45X_VARIANT
     */
    rslt = bma4_interface_init(&bma, BMA4_SPI_INTF, BMA45X_VARIANT);
    bma4_error_codes_print_result("bma4_interface_init", rslt);

    rslt = bma4_soft_reset(&bma);
    bma4_error_codes_print_result("bma456w_soft_reset status", rslt);

    /* Sensor initialization */
    rslt = bma456w_init(&bma);
    bma4_error_codes_print_result("bma456w_init status", rslt);

    /* Upload the configuration file to enable the features of the sensor. */
    rslt = bma456w_write_config_file(&bma);
    bma4_error_codes_print_result("bma456w_write_config status", rslt);

    /* Enable accelerometer to perform feature testing */
    rslt = bma4_set_accel_enable(BMA4_ENABLE, &bma);
    bma4_error_codes_print_result("bma4_set_accel_enable status", rslt);

    rslt = bma456w_feature_enable(BMA456W_STEP_CNTR, BMA4_ENABLE, &bma);
    bma4_error_codes_print_result("bma456w_feature_enable status", rslt);

    rslt = bma456w_map_interrupt(BMA4_INTR1_MAP, BMA456W_STEP_CNTR_INT, BMA4_ENABLE, &bma);
    bma4_error_codes_print_result("bma456w_map_interrupt status", rslt);

    /* Setting watermark level 1, the output step resolution is 20 steps.
     * Eg: 1 means, 1 * 20 = 20. Every 20 steps once output triggers
     */
    rslt = bma456w_step_counter_set_watermark(1, &bma);
    bma4_error_codes_print_result("bma456w_step_counter_set_watermark status", rslt);

    LOG_INF("Step counter feature is enabled\n");

    return rslt;
}

uint8_t accel_read_step_count(uint32_t *step_count)
{
    /* Variable to store the status of API */
    int8_t rslt;

    rslt = bma456w_step_counter_output(step_count, &bma);
    bma4_error_codes_print_result("bma456w_step_counter_output status", rslt);

    LOG_DBG("Step counter value: %d", *step_count);

    return rslt;
}