#include "watch_controller.h"

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(watch_controller, LOG_LEVEL_DBG);

static struct NotificationNode
{
    sys_snode_t node;
    struct Notification data;
};

struct WatchState watch_state = {
    .current_time = 0,
    .step_count = 0,
};

// temporary function, to be replaced with actual display update
void display_update()
{
    LOG_WRN("Display update");
    LOG_WRN("Current time: %s", asctime(watch_state.current_time));
    LOG_WRN("Step count: %d", watch_state.step_count);
    struct NotificationNode *node;
    SYS_SLIST_FOR_EACH_CONTAINER(&watch_state.notification_list, node, node)
    {
        LOG_WRN("Notification: %s | %s", node->data.title, node->data.text);
    }
};

// initialize watch controller
void watch_init()
{
    LOG_INF("Watch controller initializing...");

    sys_slist_init(&watch_state.notification_list);
    LOG_INF("Watch controller initialized");

    display_update();
}

static void delete_oldest_notification()
{
    struct NotificationNode *node = (struct NotificationNode *)sys_slist_peek_tail(&watch_state.notification_list);
    sys_slist_find_and_remove(&watch_state.notification_list, &node->node);
    k_free(node);
}

// add notification to the list
void watch_add_notification(struct Notification notification)
{
    if (sys_slist_len(&watch_state.notification_list) >= MAX_NOTIFICATIONS)
    {
        LOG_WRN("Notification list is full, deleting oldest notification");
        delete_oldest_notification();
    }

    struct NotificationNode *notification_node = (struct NotificationNode *)k_malloc(sizeof(struct NotificationNode));
    if (notification_node == NULL)
    {
        LOG_ERR("Failed to allocate memory for a new notification node");
        return;
    }
    notification_node->data = notification;

    sys_slist_prepend(&watch_state.notification_list, &notification_node->node);
    LOG_DBG("Notification added to list");

    display_update();
}

void watch_update_current_time(struct tm *new_time)
{
    watch_state.current_time = new_time;
    display_update();
}