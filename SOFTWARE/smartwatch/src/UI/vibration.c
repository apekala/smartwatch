#include "vibration.h"

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "power/npm1300.h"

static uint64_t vibration_stop_time;

LOG_MODULE_REGISTER(vibration, LOG_LEVEL_DBG);


#define MY_STACK_SIZE 1024
#define MY_PRIORITY 5

K_THREAD_STACK_DEFINE(vibration_stack_area, MY_STACK_SIZE);


static void vibration_stop_cb(struct k_work *item){
    LOG_ERR("stop brrrrr");
    vibration_stop();
}

struct k_work_delayable vibration_stop_work;

struct k_work_q my_work_q;


void ui_vibration_init(){
    k_work_init_delayable(&vibration_stop_work, vibration_stop_cb);
}


void ui_vibrate(uint16_t time_ms){
    LOG_ERR("start brrrr");
    vibration_start();
    k_work_reschedule(&vibration_stop_work, K_MSEC(time_ms));
    k_msleep(1);
}

