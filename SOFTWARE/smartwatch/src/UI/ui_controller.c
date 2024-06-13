#include "ui_controller.h"

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "power/npm1300.h"
#include "vibration.h"
#include "watch_controller/watch_controller.h"

#define SW0_NODE DT_ALIAS(sw0)
static const struct gpio_dt_spec button0 = GPIO_DT_SPEC_GET(SW0_NODE, gpios);
#define SW1_NODE DT_ALIAS(sw1)
static const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET(SW1_NODE, gpios);
#define SW2_NODE DT_ALIAS(sw2)
static const struct gpio_dt_spec button2 = GPIO_DT_SPEC_GET(SW2_NODE, gpios);
#define SW3_NODE DT_ALIAS(sw3)
static const struct gpio_dt_spec button3 = GPIO_DT_SPEC_GET(SW3_NODE, gpios);

LOG_MODULE_REGISTER(ui_controller, LOG_LEVEL_DBG);

void button_delete_pressed(const struct device *dev, struct gpio_callback *cb, gpio_port_pins_t pins) {
    LOG_INF("button delete pressed");
    ui_vibrate(200);
}

void button_home_pressed(const struct device *dev, struct gpio_callback *cb, gpio_port_pins_t pins) {
    LOG_INF("button home pressed");
    ui_vibrate(200);
}

void button_up_pressed(const struct device *dev, struct gpio_callback *cb, gpio_port_pins_t pins) {
    ui_vibrate(200);
    LOG_INF("button up pressed");

    if(watch_state.current_screen_number >= 1){
        watch_state.current_screen_number--;
        ui_request_refresh();
    }
}

void button_down_pressed(const struct device *dev, struct gpio_callback *cb, gpio_port_pins_t pins) {
    ui_vibrate(200);
    LOG_INF("button down pressed");
    
    if(watch_state.current_screen_number<watch_state.notification_count){
        watch_state.current_screen_number++;
        ui_request_refresh();
    }
}

static struct gpio_callback button0_cb_data;
static struct gpio_callback button1_cb_data;
static struct gpio_callback button2_cb_data;
static struct gpio_callback button3_cb_data;

int buttons_init() {
    if (!device_is_ready(button0.port) && !device_is_ready(button1.port) && !device_is_ready(button2.port) && !device_is_ready(button3.port)) {
        LOG_ERR("button not ready error");
        return -1;
    }
    int ret = gpio_pin_configure_dt(&button0, GPIO_INPUT);
    ret |= gpio_pin_configure_dt(&button1, GPIO_INPUT);
    ret |= gpio_pin_configure_dt(&button2, GPIO_INPUT);
    ret |= gpio_pin_configure_dt(&button3, GPIO_INPUT);
    if (ret < 0) {
        LOG_ERR("button initialization error");
        return -1;
    }
    ret = gpio_pin_interrupt_configure_dt(&button0, GPIO_INT_EDGE_TO_ACTIVE);
    ret |= gpio_pin_interrupt_configure_dt(&button1, GPIO_INT_EDGE_TO_ACTIVE);
    ret |= gpio_pin_interrupt_configure_dt(&button2, GPIO_INT_EDGE_TO_ACTIVE);
    ret |= gpio_pin_interrupt_configure_dt(&button3, GPIO_INT_EDGE_TO_ACTIVE);
    if (ret < 0) {
        return -1;
    }

    gpio_init_callback(&button0_cb_data, button_delete_pressed, BIT(button0.pin));
    gpio_init_callback(&button1_cb_data, button_home_pressed, BIT(button1.pin));
    gpio_init_callback(&button2_cb_data, button_up_pressed, BIT(button2.pin));
    gpio_init_callback(&button3_cb_data, button_down_pressed, BIT(button3.pin));

    ret = gpio_add_callback(button0.port, &button0_cb_data);
    ret |= gpio_add_callback(button1.port, &button1_cb_data);
    ret |= gpio_add_callback(button2.port, &button2_cb_data);
    ret |= gpio_add_callback(button3.port, &button3_cb_data);
    if (ret < 0) {
        LOG_ERR("button add calback error");
        return -1;
    }

    LOG_INF("Buttons initialized");
}