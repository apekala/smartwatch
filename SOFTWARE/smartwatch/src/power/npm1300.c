#include "npm1300.h"

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include "power/npm1300func.h"

LOG_MODULE_REGISTER(NMP1300, LOG_LEVEL_DBG);

static NPM1300_Platform NPM1300_Dev;

void npm_init(){
    uint8_t status = 0;


	NPM1300_Dev.pmic = DEVICE_DT_GET(DT_NODELABEL(npm1300_ek_pmic));

	const struct mfd_npm1300_config *config = NPM1300_Dev.pmic->config;
	NPM1300_Dev.i2c_bus = &config->i2c;

	status = npm_is_Alive(NPM1300_Dev);
    if(status){
        LOG_ERR("Dead");
    }
	status = npm_configure(NPM1300_Dev);
    if(status){
        LOG_ERR("configure error");
    }

	LOG_INF("PMIC initialized");
}

void vibration_start(){
    uint8_t status = npm_i2c_write_reg(NPM1300_Dev, TASKLDSWSET, 1);
    k_msleep(10);
    if(status){
        LOG_ERR("LDSW set error %d", status);
    }
}

void vibration_stop(){
    uint8_t status = npm_i2c_write_reg(NPM1300_Dev, TASKLDSWCLR, 1);
    k_msleep(10);
    if(status){
        LOG_ERR("LDSW clr error");
    }
}