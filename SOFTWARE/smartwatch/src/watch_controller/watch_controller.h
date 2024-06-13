#ifndef WATCH_CONTROLLER_H
#define WATCH_CONTROLLER_H

#include <stdint.h>

#include <zephyr/sys/slist.h>

#include <time.h>

#define MAX_NOTIFICATIONS 10

#define NOTIFICATION_TITLE_LEN 65
#define NOTIFICATION_TEXT_LEN 240

#define CURRENT_NODE_CHANGED 0
#define CURRENT_NODE_LAST -1



struct Notification
{
    char title[NOTIFICATION_TITLE_LEN];
    char text[NOTIFICATION_TEXT_LEN];
};

struct NotificationNode
{
    sys_snode_t node;
    struct Notification data;
};


struct WatchState
{
    // data
    struct tm *current_time;
    uint32_t step_count;
    sys_slist_t notification_list;
    uint8_t notification_count;

    //display
    uint8_t current_screen_number; // 0 for main, n>0 for n-th notification
};

extern struct WatchState watch_state;

void watch_init();

void watch_display_update();

void watch_add_notification(struct Notification notification);

struct Notification find_notification(uint8_t n);

void watch_update_current_time(struct tm *new_time);



#endif // WATCH_CONTROLLER_H
