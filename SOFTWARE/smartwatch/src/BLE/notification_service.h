#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include <zephyr/types.h>

/** @brief Step Counter Service UUID. */
#define BT_UUID_NS_VAL BT_UUID_128_ENCODE(0x281A2C20, 0xBA6F, 0x4D44, 0xB52F, 0x9C1347EEABDB)

/** @brief App name UUID. */
#define BT_UUID_NS_APP_TITLE_VAL BT_UUID_128_ENCODE(0x281A2C21, 0xBA6F, 0x4D44, 0xB52F, 0x9C1347EEABDB)
#define BT_UUID_NS_APP_TEXT_VAL BT_UUID_128_ENCODE(0x281A2C22, 0xBA6F, 0x4D44, 0xB52F, 0x9C1347EEABDB)

#define BT_UUID_NS BT_UUID_DECLARE_128(BT_UUID_NS_VAL)
#define BT_UUID_NS_APP_TITLE BT_UUID_DECLARE_128(BT_UUID_NS_APP_TITLE_VAL)
#define BT_UUID_NS_APP_TEXT BT_UUID_DECLARE_128(BT_UUID_NS_APP_TEXT_VAL)

#endif // NOTIFICATION_SERVICE_H