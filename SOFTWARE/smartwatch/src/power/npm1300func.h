#ifndef NPM1300_FUNC_H
#define NPM1300_FUNC_H

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>



#define I2C0_NODE DT_NODELABEL(npm1300)
#define SLEEP_TIME_10MS 10
#define SLEEP_TIME_1000MS 1000

// extern enum mfd_npm1300_event_t {
// 	NPM1300_EVENT_VBUS_DETECTED,
// 	NPM1300_EVENT_VBUS_REMOVED,
// 	NPM1300_EVENT_MAX
// };


typedef struct
{
	const struct device *pmic;
	const struct device *leds;
	const struct device *regulators;
	const struct device *ldsw;
	const struct device *charger;
	struct i2c_dt_spec *i2c_bus;
} NPM1300_Platform;


struct mfd_npm1300_config {
	struct i2c_dt_spec i2c;
	struct gpio_dt_spec host_int_gpios;
	uint8_t pmic_int_pin;
};

struct mfd_npm1300_data {
	struct k_mutex mutex;
	const struct device *dev;
	struct gpio_callback gpio_cb;
	struct k_work work;
	sys_slist_t callbacks;
};

struct event_reg_t {
	uint8_t RegisterAddress[2];
	uint8_t mask;
};



//writing registers
extern uint8_t ADCNTCRSEL[2];		        	// set thermistor 10k

extern uint8_t LEDDRV0MODESEL[2];            	// Select for LED0 mode - Error condition from Charger
extern uint8_t LEDDRV1MODESEL[2];            	// Select for LED1 mode - Charging indicator
extern uint8_t LEDDRV2MODESEL[2];				//Remove or set to "Not used"
extern uint8_t LEDDRV2SET[2];					//Remove
extern uint8_t LEDDRV2CLR[2];					//Remove

extern uint8_t LDSW1LDOSEL[2];
extern uint8_t TASKLDSWSET[2];
extern uint8_t TASKLDSWCLR[2];


uint8_t npm_i2c_write_reg(
	NPM1300_Platform NPM1300_Dev, 
	uint8_t *RegisterAddress,
	uint8_t value);

// uint8_t npm_i2c_read_reg(
// 	NPM1300_Platform NPM1300_Dev,
// 	uint8_t *RegisterAddress,
// 	uint8_t *Rdvalue
// );

uint8_t npm_is_Alive(
	NPM1300_Platform NPM1300_Dev
);


uint8_t npm_configure(
	NPM1300_Platform NPM1300Dev
);

#endif
