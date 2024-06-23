#include "watch_controller.h"

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "UI/display.h"
#include "UI/ui_controller.h"
#include "accelerometer/accelerometer.h"

LOG_MODULE_REGISTER(watch_controller, LOG_LEVEL_DBG);

struct WatchState watch_state = {
    .current_time = 0,
    .step_count = 0,
    .notification_count = 0,
    .refresh_in_progress = false,
    .current_screen_number = 0};

// temporary function, to be replaced with actual display update
void watch_display_update() {
    ui_request_refresh();
};

// initialize watch controller
void watch_init() {
    LOG_INF("Watch controller initializing...");

    sys_slist_init(&watch_state.notification_list);
    LOG_INF("Watch controller initialized");
}

static void delete_oldest_notification() {
    struct NotificationNode *node = (struct NotificationNode *)sys_slist_peek_tail(&watch_state.notification_list);
    sys_slist_find_and_remove(&watch_state.notification_list, &node->node);
    watch_state.notification_count--;
    k_free(node);
}

// add notification to the list
void watch_add_notification(struct Notification notification) {
    if (sys_slist_len(&watch_state.notification_list) >= MAX_NOTIFICATIONS) {
        LOG_WRN("Notification list is full, deleting oldest notification");
        delete_oldest_notification();
    }

    struct NotificationNode *notification_node = (struct NotificationNode *)k_malloc(sizeof(struct NotificationNode));
    if (notification_node == NULL) {
        LOG_ERR("Failed to allocate memory for a new notification node");
        return;
    }
    notification_node->data = notification;

    sys_slist_prepend(&watch_state.notification_list, &notification_node->node);
    watch_state.notification_count++;
    LOG_DBG("Notification added to list");

    watch_state.current_screen_number = 1;
    ui_vibrate(100);
    // schedule_main_screen_return();
    k_msleep(10);
    watch_display_update();
}

struct Notification find_notification(uint8_t n) {
    struct NotificationNode *node;
    int count = 0;

    SYS_SLIST_FOR_EACH_CONTAINER(&watch_state.notification_list, node, node) {
        if (count == n) {
            return node->data;
        }
        count++;
    }
}

void watch_update_current_time(struct tm *new_time) {
    watch_state.current_time = new_time;
    if (watch_state.current_screen_number == 0) {
        watch_display_update();
    }
}