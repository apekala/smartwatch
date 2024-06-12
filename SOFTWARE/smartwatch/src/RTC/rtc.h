#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include <time.h>

enum ChannelID {
    RTC_CHANNEL,
    VIBRATION_CHANNEL,
    SCREEN_CHANGE_CHANNEL
};

typedef void (*alarm_cb_t)();

uint8_t rtc_init();

void rtc_set_time(time_t new_time);

#endif  // RTC_H