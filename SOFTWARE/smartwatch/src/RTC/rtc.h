#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include <time.h>

uint8_t rtc_init();

void rtc_set_time(time_t new_time);

#endif // RTC_H