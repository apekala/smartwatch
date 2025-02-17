#include "vibration.h"

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "power/npm1300.h"
#include "watch_controller/watch_controller.h"

static uint64_t vibration_stop_time;

LOG_MODULE_REGISTER(vibration, LOG_LEVEL_DBG);

static void vibration_stop_cb(struct k_work *item) {
    vibration_stop();
}

struct k_work_delayable vibration_stop_work;

static void vibration_start_cb(struct k_work *item) {
    vibration_start();
}

struct k_work vibration_start_work;

// struct k_work_q vibration_work_q;

void ui_vibration_init() {
    k_work_init(&vibration_start_work, vibration_start_cb);
    k_work_init_delayable(&vibration_stop_work, vibration_stop_cb);
}

void ui_vibrate(uint16_t time_ms) {
    int res = 0;
    if (!watch_state.refresh_in_progress) {
        res = k_work_submit(&vibration_start_work);
        if (res < 0) {
            LOG_ERR("brrr start work submit error: %d", res);
            return;
        }

        res = k_work_reschedule(&vibration_stop_work, K_MSEC(time_ms));
        if (res < 0) {
            LOG_ERR("brrr stop work reschedule error: %d", res);
        }
    }
    return;
}
