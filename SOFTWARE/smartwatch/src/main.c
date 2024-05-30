#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>

#include "BLE/BLE.h"
#include "accelerometer/accelerometer.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

int main(void)
{
    accel_init();
    ble_init();
    return 0;
}
