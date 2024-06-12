#include "rtc.h"

#include <watch_controller/watch_controller.h>
#include <zephyr/drivers/counter.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#define RTC_FREQ 32768
// #define TIME_UPDATE_PERIOD_US 60 * 1000000 //1 minute
#define TIME_UPDATE_PERIOD_S 10                               // 10s
#define TIME_UPDATE_PERIOD_US TIME_UPDATE_PERIOD_S * 1000000  // 10s

LOG_MODULE_REGISTER(RTC, LOG_LEVEL_DBG);

const struct device *rtc = DEVICE_DT_GET(DT_NODELABEL(rtc2));

static uint32_t rtc_top_value = 16777215;

static void time_update_alarm_cb(const struct device *counter_dev,
                                 uint8_t chan_id, uint32_t ticks,
                                 void *user_data);

// static struct counter_top_cfg top_cfg = {
//     .flags = COUNTER_TOP_CFG_RESET_WHEN_LATE};

static struct counter_alarm_cfg time_update_alarm_cfg = {
    .callback = time_update_alarm_cb,
    .flags = COUNTER_ALARM_CFG_ABSOLUTE};

static time_t epoch_offset = 0;

static inline uint64_t ticks_to_seconds(uint32_t ticks) {
    return ticks / RTC_FREQ;
}

static inline uint32_t seconds_to_ticks(uint64_t seconds) {
    return seconds * RTC_FREQ;
}

static inline uint32_t milliseconds_to_ticks(uint64_t seconds) {
    return seconds * RTC_FREQ / 1000;
}

static inline time_t ticks_to_epoch(uint32_t ticks) {
    return ticks_to_seconds(ticks) + epoch_offset;
}

void rtc_set_time(time_t new_time) {
    LOG_INF("Setting time to %lld", new_time);
    int err = 0;

    // update epoch offset
    uint32_t ticks;
    counter_get_value(rtc, &ticks);
    epoch_offset = new_time - ticks_to_seconds(ticks);

    // reset alarm
    err = counter_cancel_channel_alarm(rtc, RTC_CHANNEL);
    if (err) {
        LOG_ERR("counter_cancel_channel_alarm error: %d", err);
    }

    // calculate time for first alarm
    time_t epoch = ticks_to_epoch(ticks);

    // set first alarm
    time_update_alarm_cfg.ticks = ticks - seconds_to_ticks(epoch % TIME_UPDATE_PERIOD_S);
    time_update_alarm_cb(rtc, RTC_CHANNEL, ticks, NULL);
}

static void time_update_alarm_cb(const struct device *counter_dev,
                                 uint8_t chan_id, uint32_t ticks,
                                 void *user_data) {
    int err;

    time_t time = ticks_to_epoch(ticks);

    // set next alarm
    time_update_alarm_cfg.ticks += counter_us_to_ticks(rtc, TIME_UPDATE_PERIOD_US);
    if (time_update_alarm_cfg.ticks >= rtc_top_value) {
        epoch_offset += ticks_to_seconds(rtc_top_value);
        time_update_alarm_cfg.ticks %= (uint32_t)rtc_top_value;
    }

    err = counter_set_channel_alarm(rtc, RTC_CHANNEL, &time_update_alarm_cfg);
    if (err) {
        LOG_ERR("counter_set_channel_alarm error: %d", err);
        return;
    }

    watch_update_current_time(localtime(&time));
    LOG_DBG("%d", ticks);
}

uint8_t rtc_init() {
    int err = 0;

    if (!device_is_ready(rtc)) {
        LOG_ERR("RTC not ready.\n");
        return 0;
    }

    // set top
    //  top_cfg.ticks = RTC_FREQ* 12;
    //  err = counter_set_top_value(rtc, &top_cfg);
    //  if (err)
    //  {
    //      LOG_ERR("counter_set_top_value error: %d", err);
    //      return err;
    //  }

    // get top value
    rtc_top_value = counter_get_top_value(rtc);
    LOG_DBG("read top value: %d", rtc_top_value);

    // set first alarm
    time_update_alarm_cfg.ticks = 0;
    time_update_alarm_cb(rtc, RTC_CHANNEL, 0, NULL);

    // start counter
    err = counter_start(rtc);
    if (err) {
        LOG_ERR("counter_set_channel_alarm error: %d", err);
        return err;
    }

    LOG_INF("RTC initialized, time will be updated every %d seconds", TIME_UPDATE_PERIOD_US / 1000000);
    return err;
}
