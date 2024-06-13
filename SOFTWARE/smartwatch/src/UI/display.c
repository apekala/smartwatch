#include "display.h"

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "epd/epd1in54_V2.h"
#include "epd/epdif.h"
#include "epd/epdpaint.h"
#include "epd/imagedata.h"
#include "watch_controller/watch_controller.h"

#define SCREEN_REFRESH_EVENT BIT(0)

LOG_MODULE_DECLARE(ui_controller, LOG_LEVEL_DBG);

static void draw_main_screen() {
    uint8_t image[5000] = {};
    struct Paint paint;

    for (int i = 0; i < 5000; i++) {
        image[i] = 0x00;
    }

    paint_set_image(&paint, image);
    paint_set_width(&paint, 200);
    paint_set_height(&paint, 200);
    paint_set_rotate(&paint, 90);

    char time_str[6];
    sprintf(time_str, "%02d:%02d", watch_state.current_time->tm_hour, watch_state.current_time->tm_min);
    paint_draw_string_at(&paint, 57, 25, time_str, &Font24);

    char date_str[11];
    sprintf(date_str, "%02d-%02d-%04d", watch_state.current_time->tm_mday, watch_state.current_time->tm_mon + 1, watch_state.current_time->tm_year + 1900);
    paint_draw_string_at(&paint, 45, 80, date_str, &Font16);

    char steps_str[6];
    sprintf(steps_str, "%05d", watch_state.step_count);
    paint_draw_string_at(&paint, 200 - 5 * 7 - 20 - 5 * 14, 180, steps_str, &Font20);
    paint_draw_string_at(&paint, 200 - 5 * 7 - 10, 188, "steps", &Font12);

    epd_set_frame_memory(paint_get_image(&paint), 0, 0, paint_get_width(&paint), paint_get_height(&paint));
}

static void draw_notification_screen(struct Notification* notification) {
    uint8_t image[5000] = {};
    struct Paint paint;

    for (int i = 0; i < 5000; i++) {
        image[i] = 0x00;
    }
    paint_set_image(&paint, image);
    paint_set_width(&paint, 200);
    paint_set_height(&paint, 200);
    paint_set_rotate(&paint, 90);

    paint_draw_string_at(&paint, 0, 0, notification->title, &Font24);
    paint_draw_string_at(&paint, 0, 30, notification->text, &Font16);

    epd_set_frame_memory(paint_get_image(&paint), 0, 0, paint_get_width(&paint), paint_get_height(&paint));
}

void display_screen() {
    epd_LDirInit();

    if(watch_state.current_screen_number==0){
        LOG_INF("displaying main screen");

        accel_read_step_count(&watch_state.step_count);
        LOG_DBG("Display update");
        LOG_DBG("Current time: %s", asctime(watch_state.current_time));
        LOG_DBG("Step count: %d", watch_state.step_count);
        LOG_DBG("Notification count: %d", watch_state.notification_count);
        struct NotificationNode *node;
        SYS_SLIST_FOR_EACH_CONTAINER(&watch_state.notification_list, node, node){
            LOG_DBG("Notification: %s | %s", node->data.title, node->data.text);
        }
        draw_main_screen();
    }else{
        struct Notification notification = find_notification(watch_state.current_screen_number);
        LOG_INF("Diplaying notification number %d: %s | %s", watch_state.current_screen_number, notification.text, notification.title);
        draw_notification_screen(&notification);
    }

    epd_display_frame();
    k_msleep(4000);
    epd_sleep();
}

struct k_event refresh_event;

void ui_request_refresh() {
    k_event_set(&refresh_event, SCREEN_REFRESH_EVENT);
}

void ui_screen_refresh_thread() {
    k_event_init(&refresh_event);
    while (true) {
        k_event_wait(&refresh_event, SCREEN_REFRESH_EVENT, false, K_FOREVER);
        k_event_set(&refresh_event, 0);
        display_screen();
        k_msleep(1000);
    }
}
