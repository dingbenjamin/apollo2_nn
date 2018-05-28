/*
 * processing.c
 *
 *  Created on: 03. Dez. 2016
 *      Author: Michael
 */

#include <sensors/s_processing.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/*****************************************************************************
 * global variables
 ******************************************************************************/
//extern volatile bool ECG_ON;
//extern volatile bool MOT_ON;
//extern volatile bool GSR_ON;
//extern volatile bool TEM_ON;
extern volatile bool SENS_STREAM;
extern volatile bool FANN_CALC;
extern volatile uint16_t T32_time;

/*****************************************************************************
 * constants
 *****************************************************************************/
/* available commands */
const char SENS_ON_CMD[6] = "SEN:ON";
const char FANN_CALC_ON[4] = "OBC:";
//const char ECG_ON_CMD[6] = "ECG:ON";
//const char ECG_OFF_CMD[6] = "ECG:OF";
//const char MOT_ON_CMD[6] = "MOT:ON";
//const char MOT_OFF_CMD[6] = "MOT:OF";
//const char GSR_ON_CMD[6] = "GSR:ON";
//const char GSR_OFF_CMD[6] = "GSR:OF";
//const char TEM_ON_CMD[6] = "TEM:ON";
//const char TEM_OFF_CMD[6] = "TEM:OF";
//const char AUD_ON_CMD[6] = "AUD:ON";
//const char AUD_OFF_CMD[6] = "AUD:OF";
const char BODY_C[4] = "BOD:";


/*******************************************************************************
 * functions																   *
 *******************************************************************************/
/*******************************************************************************
 * @fn      checkCommand
 *
 * @brief   checks the received command (BLE) and sets the associated flags
 *
 * @param   CMD: array with command code + data
 *
 * @return  void
 ******************************************************************************/
void checkCommand(char *CMD, uint8_t size) {

	/* command has to be shorter than buffer size (BLE_CMD_SIZE) and must be
	 * terminated with '\n' */

	uint8_t data = 0;
	uint16_t bitTime = 0;

	/* Sensor stream on */
	if(strncmp(CMD,SENS_ON_CMD,6) == 0) {
		MAP_Interrupt_disableInterrupt(INT_T32_INT2);
		MAP_Timer32_haltTimer(TIMER32_0_BASE);
		SENS_STREAM = true;
		FANN_CALC = false;
		/* activate sensors */
	    I2C_sleepMotionSensor(false);
	    SPI_sleepECG(false);
	    I2C_sleepTempSensor(false);
		SPI_startStreamECG();
	}

	/* send byte via body communication
	 * 1st byte after command is byte to send
	 * 2nd byte after command is time of bit  */
	if((strncmp(CMD,BODY_C,4) == 0) && (size == 8)) {
		/* disable sensor stream and start Timer32_0 (battery information streaming) */
//		SENS_STREAM = false;
//		T32_time = 0;
//		MAP_Timer32_startTimer(TIMER32_0_BASE, false);
		startBodyComm();		// produces spike -> test
		/* enable Timer32_1 interrupt for body comm */
		MAP_Interrupt_enableInterrupt(INT_T32_INT2);
		data = (uint8_t)CMD[4];
		bitTime = (uint16_t)CMD[5];
		sendByteBodyComm(data, bitTime);
//		BLE_sendACK();
		stopBodyComm();
	}

	/* FANN onboard calculation
	 * initiates data acquisition and activates neural network */
	if(strncmp(CMD,FANN_CALC_ON,4) == 0) {
		MAP_Interrupt_disableInterrupt(INT_T32_INT2);
		MAP_Timer32_startTimer(TIMER32_0_BASE, false);
		SENS_STREAM = false;
		FANN_CALC = true;
		/* activates motion sensor */
	    I2C_sleepMotionSensor(false);
	    T32_time = 0;
	}

}

