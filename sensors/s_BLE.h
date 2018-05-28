/*
 * BLE.h
 *
 *  Created on: 30. Nov. 2016
 *      Author: Michael
 */

#ifndef BLE_H_
#define BLE_H_

#include <stdint.h>
#include "s_globals.h"

/*****************************************************************************
 * Function prototypes														 *
 *****************************************************************************/
void BLE_sendStatusData(uint8_t *Data);
void BLE_sendSensorData(uint8_t *Data, uint8_t Size);
void BLE_sendMotionData(uint8_t *Data);
void BLE_sendTempData(uint8_t *Data);
void BLE_sendECGData(uint8_t *Data);
void BLE_sendGSRData(uint16_t *Data);
void BLE_sendAudioData(uint16_t *Data);
void BLE_sendACK(void);
void BLE_sendNACK(void);
void BLE_sendClap(void);


#endif /* BLE_H_ */
