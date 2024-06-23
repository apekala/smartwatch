#include "npm1300func.h"

#include "UI/epd/epdif.h"
// const struct event_reg_t event_reg[NPM1300_EVENT_MAX] = {
// 	[NPM1300_EVENT_VBUS_DETECTED] = {{0x00, 0x16U}, 0x01U},
// 	[NPM1300_EVENT_VBUS_REMOVED] = {{0x00, 0x16U}, 0x02U}
// 	};

// writing registers
//  0 - No thermistor, 1 - 10k, 2 - 47k, 3 - 100k
uint8_t ADCNTCRSEL[2] = {0x05, 0x0A};
// 0 - Charger error, 1 - Charger indicator, 2 - host, 3 - not used
uint8_t LEDDRV0MODESEL[2] = {0x0A, 0x00};
uint8_t LEDDRV1MODESEL[2] = {0x0A, 0x01};
uint8_t LEDDRV2MODESEL[2] = {0x0A, 0x02};
uint8_t LEDDRV2SET[2] = {0x0A, 0x07};
uint8_t LEDDRV2CLR[2] = {0x0A, 0x08};

uint8_t LDSW1LDOSEL[2] = {0x08, 0x08};
uint8_t TASKLDSWSET[2] = {0x08, 0x00};
uint8_t TASKLDSWCLR[2] = {0x08, 0x01};

// K_MUTEX_DEFINE(i2c_mutex);

uint8_t npm_i2c_write_reg(
    NPM1300_Platform NPM1300_Dev,
    uint8_t *RegisterAddress,
    uint8_t value) {
    uint8_t status = 0;
    uint8_t WrData[3];
    WrData[0] = RegisterAddress[0];
    WrData[1] = RegisterAddress[1];
    WrData[2] = value;

    status |= i2c_write_dt(NPM1300_Dev.i2c_bus, WrData, 3);
    return status;
}

// uint8_t npm_i2c_read_reg
// (
//     NPM1300_Platform NPM1300_Dev,
// 	uint8_t *RegisterAddress,
// 	uint8_t *RdData
// ){
//     uint8_t status = 0;
//     uint8_t test_buf[1];

//     printk("alive?\n");
//     printk("Reg address: 0x%x, 0x%x\n", RegisterAddress[0], RegisterAddress[1]);

//     // status |= i2c_write_read_dt(&(NPM1300_Dev.i2c_dev.bus), RegisterAddress, 2, test_buf, 1);
//     status |= i2c_write_read_dt(&(NPM1300_Dev.i2c_dev.bus), RegisterAddress, 2, RdData, 1);

//     printk("sent\n");
//     return status;
// }

uint8_t npm_is_Alive(
    NPM1300_Platform NPM1300_Dev) {
    uint8_t status = 0;
    status |= !device_is_ready(NPM1300_Dev.leds);
    status |= !device_is_ready(NPM1300_Dev.pmic);
    status |= !device_is_ready(NPM1300_Dev.regulators);
    status |= !device_is_ready(NPM1300_Dev.ldsw);
    status |= !device_is_ready(NPM1300_Dev.charger);
    return status;
}

uint8_t npm_configure(
    NPM1300_Platform NPM1300_Dev) {
    uint8_t status = 0;
    status |= npm_i2c_write_reg(NPM1300_Dev, LEDDRV0MODESEL, 0);
    status |= npm_i2c_write_reg(NPM1300_Dev, LEDDRV1MODESEL, 1);
    status |= npm_i2c_write_reg(NPM1300_Dev, LEDDRV2MODESEL, 2);  // Remove or change to "Not used"
    status |= npm_i2c_write_reg(NPM1300_Dev, LEDDRV2SET, 1);      // Remove
    // status |= npm_i2c_write_reg(NPM1300_Dev, LEDDRV2CLR, 1);		//Remove
    // status |= npm_i2c_write_reg(NPM1300_Dev, ADCNTCRSEL, 1);     //Set
    status |= npm_i2c_write_reg(NPM1300_Dev, LDSW1LDOSEL, 0);
    return status;
}

// void event_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
// {
// 	if (pins & BIT(NPM1300_EVENT_VBUS_DETECTED)) {
// 		printk("Vbus connected\n");
// 	}
// 	if (pins & BIT(NPM1300_EVENT_VBUS_REMOVED)) {
// 		printk("Vbus removed\n");
// 	}
// }

// uint8_t npm_configure_events(
// 	NPM1300_Platform NPM1300Dev
// ){
//     uint8_t status = 0;
//     struct gpio_callback event_cb;

//     gpio_init_callback(&event_cb, event_callback,
// 				   BIT(NPM1300_EVENT_VBUS_DETECTED) | BIT(NPM1300_EVENT_VBUS_REMOVED));

//     for (int i = 0; i < NPM1300_EVENT_MAX; i++){
//         // status |= npm_i2c_write_reg(NPM1300Dev,);
//     }
// }
