/* I2C.h
 *
 *  Created on: 09. Nov. 2016
 *      Author: Michael
 */

#ifndef HEADER_I2C_H_
#define HEADER_I2C_H_

#include <stdbool.h>
#include <stdint.h>
#include "s_globals.h"

/*****************************************************************************
 * Constants																 *
 *****************************************************************************/
//extern const eUSCI_I2C_MasterConfig i2cConfig;

/*****************************************************************************
 * Definition of I2C addresses (7-bit)                                       *
 *****************************************************************************/
#define BQ2742_ADDR		0x55		// r/w bit set in driverlib function
#define TMP112_ADDR 	0x48		// 7bit address is enough
#define MPU925_ADDR		0x68
#define AK8963_ADDR		0x0C

/*****************************************************************************
 * Definition of register addresses  & bit masks                              *
 *****************************************************************************/
#define MPU9250_PWR_MGMT_1	0x6B
#define MPU9250_SLEEP_MASK 	0x40
#define MPU9250_WAKEUP_MASK 0x00

/*****************************************************************************
 * Function prototypes														 *
 *****************************************************************************/
void initI2C(void);
uint8_t I2C_getData(uint8_t CMD_code, uint_fast16_t slaveAddress);
void I2C_write2Byte(uint8_t regAddr, uint8_t configData,  uint_fast16_t SLAVE_ADDR);
void I2C_initMotionSensor(void);
void I2C_sleepMotionSensor(bool sleep);
void I2C_getBatteryStatus(uint8_t *retData);
void I2C_getMotionData(uint8_t *retData);
void I2C_getMagData(uint8_t *retData);
void I2C_initTempSensor();
void I2C_getTempData(uint8_t *retData);
void I2C_sleepTempSensor(bool sleep);

#endif /* HEADER_I2C_H_ */
