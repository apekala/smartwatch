#include "watch_controller.h"

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "UI/display.h"
#include "accelerometer/accelerometer.h"

LOG_MODULE_REGISTER(watch_controller, LOG_LEVEL_DBG);


struct WatchState watch_state = {
    .current_time = 0,
    .step_count = 0,
    .notification_count = 0,
    .current_screen_number = 0
};

// temporary function, to be replaced with actual display update
void watch_display_update()
{
    ui_request_refresh();
};

// initialize watch controller
void watch_init()
{
    LOG_INF("Watch controller initializing...");

    sys_slist_init(&watch_state.notification_list);
    LOG_INF("Watch controller initialized");
}

static void delete_oldest_notification()
{
    struct NotificationNode *node = (struct NotificationNode *)sys_slist_peek_tail(&watch_state.notification_list);
    sys_slist_find_and_remove(&watch_state.notification_list, &node->node);
    watch_state.notification_count--;
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
    watch_state.notification_count++;
    LOG_DBG("Notification added to list");

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


// void watch_first_notification(){
//     struct NotificationNode *next_node;
//     watch_state.current_notification_node = SYS_DLIST_CONTAINER(sys_dlist_peek_head(&watch_state.notification_list), next_node, node);
//     LOG_INF("FROM LIST: %s", watch_state.current_notification_node->data.title);
// }

// void watch_next_notification(){
//     struct NotificationNode *next_node;

//     if(watch_state.current_screen_number < watch_state.notification_count){
//     watch_state.current_notification_node = SYS_DLIST_PEEK_NEXT_CONTAINER(&watch_state.notification_list, watch_state.current_notification_node, node);
//     }
// }

// void watch_previous_notification(){
//     // struct NotificationNode *next_node;
//     // sys_dnode_t *prev_node_ptr = sys_dlist_peek_prev(&watch_state.notification_list, &watch_state.current_notification_node->node);
    
//     // if (prev_node_ptr != NULL) {
//     //     watch_state.current_notification_node = SYS_DLIST_CONTAINER(prev_node_ptr, next_node, node);
//     //     // watch_state.current_notification_node = CONTAINER_OF(prev_node_ptr, struct NotificationNode, node);
//     // } else {
//     //     LOG_ERR("No previous node found (current node is head or not in the list)\n");
//     // }

//     if (watch_state.current_notification_node == NULL) {
//         LOG_ERR("Current notification node is NULL\n");
//         return;
//     }

//     // Get the previous node's sys_dnode_t pointer
//     sys_dnode_t *prev_node_ptr = sys_dlist_peek_prev(&watch_state.notification_list, &watch_state.current_notification_node->node);

//     if (prev_node_ptr != NULL) {
//         // Convert sys_dnode_t pointer to NotificationNode pointer
//         struct NotificationNode *previous_node = CONTAINER_OF(prev_node_ptr, struct NotificationNode, node);
//         watch_state.current_notification_node = previous_node;
//         LOG_INF("Switched to previous notification: id=%d, message='%s'\n",
//                 watch_state.current_notification_node->data.notification_id,
//                 watch_state.current_notification_node->data.message);
//     } else {
//         LOG_ERR("No previous node found (current node is head or not in the list)\n");
//     }

// }

void watch_update_current_time(struct tm *new_time)
{
    watch_state.current_time = new_time;
    watch_display_update();
}