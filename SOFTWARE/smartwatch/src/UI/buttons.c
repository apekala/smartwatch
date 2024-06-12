#include "buttons.h"

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#include "vibration.h"
#include "power/npm1300.h"

#define SW0_NODE	DT_ALIAS(sw0)
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);

LOG_MODULE_REGISTER(buttons, LOG_LEVEL_DBG);

void button_pressed(const struct device *dev, struct gpio_callback *cb, gpio_port_pins_t pins)
{
    LOG_INF("button pressed");
    ui_vibrate(200);
}

static struct gpio_callback button_cb_data;

void buttons_init(){
    if (!device_is_ready(button.port)) {
		return -1;
	}
    int ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret < 0) {
		return -1;
	}
    ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
    if (ret < 0) {
		return -1;
	}
    
    gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin)); 	


	ret = gpio_add_callback(button.port, &button_cb_data);
    if (ret < 0) {
		return -1;
	}

    LOG_INF("Buttons initialized");
}