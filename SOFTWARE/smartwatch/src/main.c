#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/counter.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>

#include "watch_controller/watch_controller.h"
#include "BLE/BLE.h"
#include "accelerometer/accelerometer.h"
#include "RTC/rtc.h"
#include "power/npm1300.h"
#include "UI/vibration.h"

#define LED0_NODE	DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

int main(void)
{
    int ret;
	if (!device_is_ready(led.port)) {
		return -1;
	}
    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return -1;
	}

    gpio_pin_set_dt(&led, 1);

    npm_init();

    // vibration_start();
    // k_msleep(1000);
    // vibration_stop();
    // k_msleep(1000);
    //     vibration_start();
    // k_msleep(1000);
    // vibration_stop();
    k_msleep(1000);
    ui_vibration_init();
    
    ui_vibrate(1000);
    // k_msleep(10);
    LOG_INF("vibrate1");
    k_msleep(500);
    ui_vibrate(1000);
    LOG_INF("vibrate2");

    watch_init();   
    rtc_init();
    accel_init();
    ble_init();


    // ui_vibrate(1000);

    LOG_INF("Initialization complete");

    // k_sleep(K_FOREVER);
    for(;;){
        gpio_pin_toggle_dt(&led);
        k_msleep(100);
    }

    LOG_INF("end");
    return 0;
}
