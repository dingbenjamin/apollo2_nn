/*
 * globals.h
 *
 *  Created on: 10. Nov. 2016
 *      Author: Michael
 */

#ifndef HEADER_GLOBALS_H_
#define HEADER_GLOBALS_H_

#include <stdbool.h>
#include <stdint.h>

/*****************************************************************************
 * Global definitions														 *
 *****************************************************************************/
#define HW_VERSION		0x0B
#define SW_VERSION		0x0B

#define I2C_RX_BYTES    26		//size I2C input buffer
#define I2C_TX_BYTES	2		//size I2C transmit buffer
#define SPI_RX_BYTES    13		//size SPI input buffer
//#define SPI_TX_BYTES	3		//size SPI transmit buffer
#define ADC_B_SIZE		2		//ADC readout buffer
#define BLE_CMD_SIZE	10		//received command buffer (BLE)
#define BLE_TX_SIZE		62		//BLE transmission package size
#define TIME_WINDOW 	3000	//time window for data acquisition (in ms)

/*****************************************************************************
 * Global typedef															 *
 *****************************************************************************/
//typedef enum {
//	CONTINUOUS,
//	SINGLE_SHOT,
//	OFF
//} ECG_State;

/*****************************************************************************
 * Global variables															 *
 *****************************************************************************/
/* timer variables */
volatile uint16_t T32_time;		//counts to max TIME_WINDOW
volatile uint32_t T32_BCOMM;	// body comm. timer

volatile uint8_t BodyComm;
volatile char BLE_CMD[BLE_CMD_SIZE];
volatile uint8_t BLE_CMD_N;
volatile uint8_t I2C_RX[I2C_RX_BYTES];
volatile uint8_t I2C_TX[I2C_TX_BYTES];
volatile uint8_t I2C_recBytes;
volatile uint8_t SPI_RX_FRAM[SPI_RX_BYTES];
volatile uint8_t SPI_RX_ECG[SPI_RX_BYTES];
volatile uint8_t SPI_recBytesFRAM;
volatile uint8_t SPI_recBytesECG;
volatile uint16_t ADC_result[ADC_B_SIZE];
volatile uint32_t ECG_cnt;
//volatile ECG_State ECG_current_state;

/* flags */
volatile bool BLE_REC;
volatile bool ECG_DRDY;
volatile bool ADC_DRDY;
volatile bool SENS_STREAM;
volatile bool FANN_CALC;
volatile bool I2C_stopSent;
volatile bool I2C_2bytesCMD;


#endif /* HEADER_GLOBALS_H_ */
