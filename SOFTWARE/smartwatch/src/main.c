#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/counter.h>

#include "watch_controller/watch_controller.h"
#include "BLE/BLE.h"
#include "accelerometer/accelerometer.h"
#include "RTC/rtc.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

int main(void)
{
    watch_init();   
    rtc_init();
    rtc_set_time(1717598679);
    accel_init();
    ble_init();

    LOG_INF("Initialization complete");

    k_sleep(K_FOREVER);

    return 0;
}
