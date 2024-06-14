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
#include "UI/ui_controller.h"
#include "UI/display.h"


#define DISPLAY_STACK_SIZE 16384
#define DISPLAY_THREAD_PRIORITY 5

K_THREAD_STACK_DEFINE(display_stack_area, DISPLAY_STACK_SIZE);
struct k_thread display_thread_data;




#define LED0_NODE	DT_ALIAS(led0)
extern const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

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
    k_msleep(1000);
    ui_vibration_init();
    
    ui_vibrate(1000);
    
    watch_init();   
    rtc_init();
    accel_init();
    ble_init();

    k_tid_t my_tid = k_thread_create(&display_thread_data, display_stack_area,
                                K_THREAD_STACK_SIZEOF(display_stack_area),
                                ui_screen_refresh_thread,
                                NULL, NULL, NULL,
                                DISPLAY_THREAD_PRIORITY, 0, K_NO_WAIT);


    ui_init();

    watch_display_update();

    LOG_INF("Initialization complete");

    for(;;){
        gpio_pin_toggle_dt(&led);
        k_msleep(100);
    }

    LOG_INF("end");
    return 0;
}
