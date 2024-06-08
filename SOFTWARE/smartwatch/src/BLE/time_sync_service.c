#include "time_sync_service.h"

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

#include "RTC/rtc.h"

LOG_MODULE_DECLARE(BLE, LOG_LEVEL_DBG);

static ssize_t write_time(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf, uint16_t len, uint16_t offset, uint8_t flags) {
    LOG_DBG("Attribute write, handle: %u, conn: %p", attr->handle, (void *)conn);

    // change to 64
    int32_t *new_epoch = buf;

    if (len > sizeof(new_epoch)) {
        LOG_ERR("Write time: Incorrect data length");
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
    }

    if (offset != 0) {
        LOG_ERR("Write time: Incorrect data offset");
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
    }

    LOG_ERR("len: %d, data: 0x%d", len, *new_epoch);

    rtc_set_time(*new_epoch);

    return len;
}

BT_GATT_SERVICE_DEFINE(my_tss_svc, BT_GATT_PRIMARY_SERVICE(BT_UUID_TSS),
                       BT_GATT_CHARACTERISTIC(BT_UUID_TSS_UNIX_TIME, BT_GATT_CHRC_WRITE, BT_GATT_PERM_WRITE, NULL, write_time, NULL), );
