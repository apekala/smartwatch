#ifndef WATCH_CONTROLLER_H
#define WATCH_CONTROLLER_H

#include <stdint.h>

#include <zephyr/sys/slist.h>

#define MAX_NOTIFICATIONS 10

#define NOTIFICATION_TITLE_LEN 65
#define NOTIFICATION_TEXT_LEN 240

struct Notification
{
    char title[NOTIFICATION_TITLE_LEN];
    char text[NOTIFICATION_TEXT_LEN];
};

struct WatchState
{
    uint64_t current_time;
    uint32_t step_count;
    sys_slist_t notification_list;
};

extern struct WatchState watch_state;

void watch_init();

void watch_add_notification(struct Notification notification);

#endif // WATCH_CONTROLLER_H
