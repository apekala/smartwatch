#include "notification_service.h"

#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/sys/printk.h>
#include <zephyr/types.h>

#include "watch_controller/watch_controller.h"

LOG_MODULE_DECLARE(BLE, LOG_LEVEL_DBG);

struct Notification new_notification = {0};

static void send_if_complete() {
    LOG_DBG("Received notification: %x | %x", *new_notification.title, *new_notification.text);
    if (*new_notification.title != '\0' && *new_notification.text != '\0') {
        // Send notification
        LOG_DBG("Received notification: %s | %s", new_notification.title, new_notification.text);

        watch_add_notification(new_notification);

        // Reset notification
        *new_notification.title = '\0';
        *new_notification.text = '\0';
    }
}

static ssize_t write_title(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf, uint16_t len, uint16_t offset, uint8_t flags) {
    LOG_DBG("Attribute write, handle: %u, conn: %p", attr->handle, (void *)conn);

    if (len > NOTIFICATION_TITLE_LEN) {
        LOG_DBG("Write title: Incorrect data length");
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
    }

    if (offset != 0) {
        LOG_DBG("Write titlr: Incorrect data offset");
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
    }

    strcpy(new_notification.title, (char *)buf);
    // strcpy(new_notification.title, "TitleTitle");
    send_if_complete();

    return len;
}

static ssize_t write_text(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf, uint16_t len, uint16_t offset, uint8_t flags) {
    LOG_DBG("Attribute write, handle: %u, conn: %p", attr->handle, (void *)conn);

    if (len > NOTIFICATION_TEXT_LEN) {
        LOG_DBG("Write text: Incorrect data length");
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
    }

    if (offset != 0) {
        LOG_DBG("Write text: Incorrect data offset");
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
    }

    strcpy(new_notification.text, (char *)buf);
    send_if_complete();

    return len;
}

BT_GATT_SERVICE_DEFINE(my_ns_svc, BT_GATT_PRIMARY_SERVICE(BT_UUID_NS),
                       BT_GATT_CHARACTERISTIC(BT_UUID_NS_APP_TITLE, BT_GATT_CHRC_WRITE, BT_GATT_PERM_WRITE, NULL, write_title, NULL),
                       BT_GATT_CHARACTERISTIC(BT_UUID_NS_APP_TEXT, BT_GATT_CHRC_WRITE, BT_GATT_PERM_WRITE, NULL, write_text, NULL), );
