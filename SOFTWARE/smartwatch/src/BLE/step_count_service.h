#ifndef STEP_COUNT_SERVICE_H
#define STEP_COUNT_SERVICE_H

#include <zephyr/types.h>

/** @brief Step Counter Service UUID. */
#define BT_UUID_SCS_VAL BT_UUID_128_ENCODE(0x01118473, 0xE39D, 0x479B, 0xABB5, 0x093493625221)

/** @brief Step count UUID. */
#define BT_UUID_SCS_STEP_COUNT_VAL BT_UUID_128_ENCODE(0x01118474, 0xE39D, 0x479B, 0xABB5, 0x093493625221)

#define BT_UUID_SCS BT_UUID_DECLARE_128(BT_UUID_SCS_VAL)
#define BT_UUID_SCS_STEP_COUNT BT_UUID_DECLARE_128(BT_UUID_SCS_STEP_COUNT_VAL)

#endif // STEP_COUNT_SERVICE_H