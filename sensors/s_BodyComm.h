/*
 * BodyComm.h
 *
 *  Created on: 01. Dez. 2016
 *      Author: Michael
 */

#ifndef HEADER_BODYCOMM_H_
#define HEADER_BODYCOMM_H_

#include <stdbool.h>
#include <stdint.h>
#include "s_globals.h"

/*****************************************************************************
 * Function prototypes														 *
 *****************************************************************************/
void startBodyComm(void);
void stopBodyComm(void);
void startCarrierBodyComm(void);
void stopCarrierBodyComm(void);
void sendByteBodyComm(uint8_t Data, uint16_t BitTime);


#endif /* HEADER_BODYCOMM_H_ */
