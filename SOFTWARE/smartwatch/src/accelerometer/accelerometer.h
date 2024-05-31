#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <stdint.h>

int8_t accel_init(void);

uint8_t accel_read_step_count(uint32_t *step_count);

#endif // ACCELEROMETER_H
