/*
 * SPI.h
 *
 *  Created on: 11. Nov. 2016
 *      Author: Michael
 */

#ifndef HEADER_SPI_H_
#define HEADER_SPI_H_

#include <stdbool.h>
#include "s_globals.h"

/*****************************************************************************
 * Definition of register adresses  & bit masks                              *
 *****************************************************************************/
#define ECG_WAKEUP 			0x02
#define ECG_STANDBY 		0x04
#define ECG_RESET 			0x06
#define ECG_START 			0x08
#define ECG_STOP 			0x0A
#define ECG_OFFSETCAL		0x1A
#define ECG_RDATAC 			0x10
#define ECG_SDATAC 			0x11
#define ECG_RDATA 			0x12
#define ECG_RREG 			0x20
#define ECG_WREG 			0x40

/*****************************************************************************
 * Function prototypes														 *
 *****************************************************************************/
void initSPI(void);
void testFRAM(void);
void testECG(void);
void SPI_initECG(void);
void SPI_startStreamECG(void);
void SPI_stopStreamECG(void);
void SPI_sleepECG(bool sleep);
void SPI_singleReadECG(void);

#endif /* HEADER_SPI_H_ */
