#include "step_count_service.h"

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#include <zephyr/logging/log.h>

#include "accelerometer/accelerometer.h"
#include "watch_controller/watch_controller.h"

LOG_MODULE_DECLARE(BLE, LOG_LEVEL_DBG);


static ssize_t read_step_count(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset)
{
    LOG_DBG("Attribute read, handle: %u, conn: %p", attr->handle, (void *)conn);

    accel_read_step_count(&watch_state.step_count);

    return bt_gatt_attr_read(conn, attr, buf, len, offset, attr->user_data, sizeof(&watch_state.step_count));
}

BT_GATT_SERVICE_DEFINE(my_scs_svc, BT_GATT_PRIMARY_SERVICE(BT_UUID_SCS),
                       BT_GATT_CHARACTERISTIC(BT_UUID_SCS_STEP_COUNT, BT_GATT_CHRC_READ, BT_GATT_PERM_READ, read_step_count, NULL, &watch_state.step_count), );
