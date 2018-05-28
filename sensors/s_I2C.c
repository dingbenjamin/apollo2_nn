/*
 * I2C.c
 *
 *  Created on: 09. Nov. 2016
 *      Author: Michael
 */

#include <sensors/s_I2C.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/*****************************************************************************
 * global variables
 ******************************************************************************/
extern volatile uint8_t I2C_RX[I2C_RX_BYTES];
extern volatile uint8_t I2C_TX[I2C_TX_BYTES];
extern volatile uint8_t I2C_recBytes;
extern volatile bool I2C_stopSent;
extern volatile bool I2C_2bytesCMD;

/*****************************************************************************
 * constants
 *****************************************************************************/
/* I2C Master Configuration Parameter */
eUSCI_I2C_MasterConfig i2cConfig =
{
        EUSCI_B_I2C_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        48000000,                               // SMCLK = 48MHz
		EUSCI_B_I2C_SET_DATA_RATE_400KBPS,      // Desired I2C Clock of 400khz
        0,                                      // No byte counter threshold
		EUSCI_B_I2C_SEND_STOP_AUTOMATICALLY_ON_BYTECOUNT_THRESHOLD                //Autostop
};


/*******************************************************************************
 * functions																   *
 *******************************************************************************/
/*******************************************************************************
 * @fn      initI2C
 *
 * @brief   initialization of I2C interface
 *
 * @param   void
 *
 * @return  void
 ******************************************************************************/
void initI2C(void) {

    /* Selecting P1.6 and P1.7 in I2C mode */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
                GPIO_PIN6 + GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Initializing I2C Master to SMCLK at 400khz with no autostop */
    MAP_I2C_initMaster(EUSCI_B0_BASE, &i2cConfig);

    /* Set Master in transmit mode */
    MAP_I2C_setMode(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_MODE);

    /* Enable I2C Module to start operations */
    MAP_I2C_enableModule(EUSCI_B0_BASE);

    /* clear Interrupt flags */
    MAP_I2C_clearInterruptFlag(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0 + EUSCI_B_I2C_RECEIVE_INTERRUPT0);
    /* Interrupt registration */
    MAP_I2C_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0);
    MAP_Interrupt_enableInterrupt(INT_EUSCIB0);

    while (MAP_I2C_masterIsStopSent(EUSCI_B0_BASE) == EUSCI_B_I2C_SENDING_STOP)
        ;
}

/*******************************************************************************
 * @fn      I2C_getData
 *
 * @brief   writes received data in I2C RX-Buffer (global)
 *
 * @param   *CMD_code - 2 byte command code
 * 			slaveAddress - 7 bit slave address
 *
 * @return	number of received bytes
 ******************************************************************************/
uint8_t I2C_getData(uint8_t CMD_code, uint_fast16_t slaveAddress) {

	int i = 0;

	/* reset I2C RX-buffer */
	I2C_stopSent = false;
	//memset(I2C_RX, 0x00, I2C_RX_BYTES);
	for(i = 0; i < I2C_RX_BYTES; i++) {
		I2C_RX[i] = 0x00;
	}

	/* set the number of transmit and receive bytes, dependent on the sensor */
	switch(slaveAddress) {
		/* BQ2742 fuel gauge: 1 Command bytes - 26 data byte */
		case BQ2742_ADDR:
			I2C_2bytesCMD = false;
			I2C_recBytes = 26;
			I2C_TX[0] = CMD_code;
			//I2C_TX[1] = CMD_code[1];
			break;
		/* TMP112 temp sensor: 1 Command byte - 2 data bytes */
		case TMP112_ADDR:
			I2C_2bytesCMD = false;
			I2C_recBytes = 2;
			I2C_TX[0] = CMD_code;
			break;
		/* MPU9250 motion sensor: 1 Command byte - 6 data bytes */
		case MPU925_ADDR:
			I2C_2bytesCMD = false;
			I2C_recBytes = 6;
			I2C_TX[0] = CMD_code;
			break;
		/* AK8963 magnetometer: 1 Command byte - 2 data bytes */
		case AK8963_ADDR:
			I2C_2bytesCMD = false;
			I2C_recBytes = 2;
			I2C_TX[0] = CMD_code;
			break;
	}

	/* Specify slave address */
	MAP_I2C_setSlaveAddress(EUSCI_B0_BASE, slaveAddress);

    /* Making sure the last transaction has been completely sent out */
    while (MAP_I2C_masterIsStopSent(EUSCI_B0_BASE) == EUSCI_B_I2C_SENDING_STOP);

    //MAP_I2C_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0); moved to init
    /* Send start and the first byte of the transmit buffer. We have to send
    * two bytes to clean out whatever is in the buffer from a previous
    * send  */
    MAP_I2C_masterSendMultiByteStart(EUSCI_B0_BASE, I2C_TX[0]);
    //MAP_I2C_masterSendMultiByteNext(EUSCI_B0_BASE, I2C_TX[0]);

    /* wait until stop is sent (processor locked) */
    while(!I2C_stopSent)
    {
        //MAP_PCM_gotoLPM0InterruptSafe();
    }

    //MAP_I2C_clearInterruptFlag(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0 + EUSCI_B_I2C_RECEIVE_INTERRUPT0);
    I2C_stopSent = false;

    /* return number of received bytes, if data transaction is completed */
    //if(I2C_isBusBusy == EUSCI_B_I2C_BUS_NOT_BUSY)
    //	return I2C_recBytes;
    //else
    return I2C_recBytes;

}

/*******************************************************************************
 * @fn      I2C_write2Byte
 *
 * @brief   write 2 Bytes via I2C
 *
 * @param   regAddr: 1st byte = register address of Sensor
 * 			configData: 2nd byte = data to write in register
 * 			SLAVE_ADDR: slave address
 *
 * @return	-
 ******************************************************************************/
void I2C_write2Byte(uint8_t regAddr, uint8_t configData, uint_fast16_t SLAVE_ADDR) {

	MAP_I2C_setSlaveAddress(EUSCI_B0_BASE, SLAVE_ADDR);

	MAP_I2C_masterSendMultiByteStart(EUSCI_B0_BASE, regAddr);
	while (!(MAP_I2C_getInterruptStatus(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0) & EUSCI_B_I2C_TRANSMIT_INTERRUPT0));
	MAP_I2C_clearInterruptFlag(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0 + EUSCI_B_I2C_RECEIVE_INTERRUPT0);
	MAP_I2C_masterSendMultiByteNext(EUSCI_B0_BASE, configData);
	while (!(MAP_I2C_getInterruptStatus(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0) & EUSCI_B_I2C_TRANSMIT_INTERRUPT0));
	MAP_I2C_clearInterruptFlag(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0 + EUSCI_B_I2C_RECEIVE_INTERRUPT0);
	MAP_I2C_masterSendMultiByteStop(EUSCI_B0_BASE);
}

/*******************************************************************************
 * @fn      I2C_initMotionSensor
 *
 * @brief   configures Motion Sensor (MPU9250) via I2C
 *
 * @param   -
 *
 * @return	-
 ******************************************************************************/
void I2C_initMotionSensor(void) {

	uint8_t regAddr;
	uint8_t configData;

	MAP_Interrupt_disableInterrupt(INT_EUSCIB0);

	/* Specify slave address: MPU9250 */
	//MAP_I2C_setSlaveAddress(EUSCI_B0_BASE, MPU925_ADDR);

	/* MPU9250 */
	/* sets gyro range to +-1000°/s */
	regAddr = 0x1B;
	configData = 0x10;
	I2C_write2Byte(regAddr, configData, MPU925_ADDR);
	_delay_cycles(1200);


	/* sets accelerometer range to +-4g */
	regAddr = 0x1C;
	configData = 0x08;
	I2C_write2Byte(regAddr, configData, MPU925_ADDR);
	_delay_cycles(1200);


	/* activates magnetometer AK8963  */
	regAddr = 0x37;
	configData = 0x22;
	I2C_write2Byte(regAddr, configData, MPU925_ADDR);
	_delay_cycles(1200);

	regAddr = 0x38;
	configData = 0x01;
	I2C_write2Byte(regAddr, configData, MPU925_ADDR);
	_delay_cycles(1200);

	/* AK8963 */
	/* set continuous mode 1 - 8 Hz samplerate */
	regAddr = 0x0A;
	configData = 0x02;
	I2C_write2Byte(regAddr, configData, AK8963_ADDR);
	_delay_cycles(1200);

	MAP_Interrupt_enableInterrupt(INT_EUSCIB0);
}

/*******************************************************************************
 * @fn      I2C_sleepMotionSensor
 *
 * @brief   puts motion sensor (MPU 9250) into/out of sleep mode
 *
 * @param   sleep: true for sleep mode, false for normal mode
 *
 * @return	-
 ******************************************************************************/
void I2C_sleepMotionSensor(bool sleep) {

	MAP_Interrupt_disableInterrupt(INT_EUSCIB0);

	if (sleep)
		I2C_write2Byte(MPU9250_PWR_MGMT_1, MPU9250_SLEEP_MASK, MPU925_ADDR);
	else
		I2C_write2Byte(MPU9250_PWR_MGMT_1, MPU9250_WAKEUP_MASK, MPU925_ADDR);

	MAP_Interrupt_enableInterrupt(INT_EUSCIB0);
}

/*******************************************************************************
 * @fn      I2C_getBatteryStatus
 *
 * @brief   reads battery status from BQ2742 (1 measurement)
 *
 * @param   *retData: address of array to place data
 *
 * @return	-
 ******************************************************************************/
void I2C_getBatteryStatus(uint8_t *retData) {

	uint8_t CMD = 0x04;

	/* read data */
	I2C_getData(CMD, BQ2742_ADDR);
	//_delay_cycles(50);

	/* BQ sends Low Byte first */
	/* cell voltage */
	retData[0] = I2C_RX[1];
	retData[1] = I2C_RX[0];
	/* flags */
	retData[2] = I2C_RX[3];
	retData[3] = I2C_RX[2];
	/* Nominal Available Capacity */
	retData[4] = I2C_RX[5];
	retData[5] = I2C_RX[4];
	/* Full Available Capacity */
	retData[6] = I2C_RX[7];
	retData[7] = I2C_RX[6];
	/* Remaining Capacity */
	retData[8] = I2C_RX[9];
	retData[9] = I2C_RX[8];
	/* Full Charge Capacity */
	retData[10] = I2C_RX[11];
	retData[11] = I2C_RX[10];
	/* Average Current */
	retData[12] = I2C_RX[13];
	retData[13] = I2C_RX[12];
	/* Standby Current */
	retData[14] = I2C_RX[15];
	retData[15] = I2C_RX[14];
	/* Max Load Current */
	retData[16] = I2C_RX[17];
	retData[17] = I2C_RX[16];
	// skip 2 bytes
	/* Average Power */
	retData[18] = I2C_RX[21];
	retData[19] = I2C_RX[20];
	/* State of Charge */
	retData[20] = I2C_RX[25];
	retData[21] = I2C_RX[24];

}

/*******************************************************************************
 * @fn      I2C_getMotionData
 *
 * @brief   reads motion data from MPU9250 and magnetometer separately from
 * 			AK8963 (1 measurement)
 *
 * @param   *retData: address of array to place data
 *
 * @return	-
 ******************************************************************************/
void I2C_getMotionData(uint8_t *retData) {

	uint8_t CMD = 0;
	int i, j = 0;

	/* acceleration data, incremental read 6 byte */
	CMD = 0x3B;
	i = I2C_getData(CMD, MPU925_ADDR);
	for(j = 0; j < i; j++) {
		retData[j] = I2C_RX[j];
	}
	//_delay_cycles(500);

	/* gyro data, incremental read 6 byte */
	CMD = 0x43;
	i = I2C_getData(CMD, MPU925_ADDR);
	for(j = 0; j < i; j++) {
		retData[(j+6)] = I2C_RX[j];
	}
	//_delay_cycles(500);

	/* magnetometer data */
//	CMD = 0x02;
//	i = I2C_getData(CMD, AK8963_ADDR);
//	_delay_cycles(1200);		//delay is crucial
//	// check if new data is available
//	if((I2C_RX[0] << 7) > 0) {
//
//		//		CMD = 0x01;				//workaround: read register before x-axis MAG
////	 	i = I2C_getData(CMD, AK8963_ADDR);
////	 	//MotionData[12] = I2C_RX[1];
////	 	//MotionData[13] = I2C_RX[0];
////	 	_delay_cycles(1200);
//
//	    CMD = 0x03;				//x-axis MAG (high and low byte switched)
//	 	i = I2C_getData(CMD, AK8963_ADDR);
//	 	retData[12] = I2C_RX[1];
//	 	retData[13] = I2C_RX[0];
//	 	//_delay_cycles(600);
//
//	    CMD = 0x05;				//y-axis MAG  (high and low byte switched)
//	   	i = I2C_getData(CMD, AK8963_ADDR);
//	   	retData[14] = I2C_RX[1];
//	   	retData[15] = I2C_RX[0];
//	    //_delay_cycles(600);
//
//	    CMD = 0x07;				//z-axis MAG  (high and low byte switched)
//	    i = I2C_getData(CMD, AK8963_ADDR);
//	    retData[16] = I2C_RX[1];
//	    retData[17] = I2C_RX[0];
//	    //_delay_cycles(600);
//
//	    CMD = 0x09;			// must be done at end of magnetometer readout (data protection)
//	    i = I2C_getData(CMD, AK8963_ADDR);
//	    //_delay_cycles(600);
//	}

}


/*******************************************************************************
 * @fn      I2C_getMagData
 *
 * @brief   reads magnetometer data if new measurement is available
 *
 * @param   *retData: address of array to place data
 *
 * @return	-
 ******************************************************************************/
void I2C_getMagData(uint8_t *retData) {

	uint8_t CMD = 0x02;

	I2C_getData(CMD, AK8963_ADDR);
	_delay_cycles(1200);		//delay is crucial
	/* check if new data is available */
	if((I2C_RX[0] << 7) > 0) {
		CMD = 0x03;				//x-axis MAG (high and low byte switched)
		I2C_getData(CMD, AK8963_ADDR);
		retData[0] = I2C_RX[1];
		retData[1] = I2C_RX[0];
		//_delay_cycles(600);

		CMD = 0x05;				//y-axis MAG  (high and low byte switched)
		I2C_getData(CMD, AK8963_ADDR);
		retData[2] = I2C_RX[1];
		retData[3] = I2C_RX[0];
		//_delay_cycles(600);

		CMD = 0x07;				//z-axis MAG  (high and low byte switched)
		I2C_getData(CMD, AK8963_ADDR);
		retData[4] = I2C_RX[1];
		retData[5] = I2C_RX[0];
		//_delay_cycles(600);

		CMD = 0x09;			// must be done at end of magnetometer readout (data protection)
		I2C_getData(CMD, AK8963_ADDR);
		//_delay_cycles(600);
	}
}

/*******************************************************************************
 * @fn      I2C_initTempSensor
 *
 * @brief   sets sampling rate of temperature sensor (TMP112) to 8 Hz
 *
 * @param
 *
 * @return	-
 ******************************************************************************/
void I2C_initTempSensor(void) {

	/* set sample rate in control register to 8 Hz*/
	uint8_t CMD = 0x01;
	uint8_t hi = 0x60;
	uint8_t lo = 0xE0;

	MAP_Interrupt_disableInterrupt(INT_EUSCIB0);

	MAP_I2C_setSlaveAddress(EUSCI_B0_BASE, TMP112_ADDR);

	MAP_I2C_masterSendMultiByteStart(EUSCI_B0_BASE, CMD);
	while (!(MAP_I2C_getInterruptStatus(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0) & EUSCI_B_I2C_TRANSMIT_INTERRUPT0));
	MAP_I2C_clearInterruptFlag(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0 + EUSCI_B_I2C_RECEIVE_INTERRUPT0);
	MAP_I2C_masterSendMultiByteNext(EUSCI_B0_BASE, hi);
	while (!(MAP_I2C_getInterruptStatus(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0) & EUSCI_B_I2C_TRANSMIT_INTERRUPT0));
	MAP_I2C_clearInterruptFlag(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0 + EUSCI_B_I2C_RECEIVE_INTERRUPT0);
	MAP_I2C_masterSendMultiByteNext(EUSCI_B0_BASE, lo);
	while (!(MAP_I2C_getInterruptStatus(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0) & EUSCI_B_I2C_TRANSMIT_INTERRUPT0));
	MAP_I2C_clearInterruptFlag(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0 + EUSCI_B_I2C_RECEIVE_INTERRUPT0);
	MAP_I2C_masterSendMultiByteStop(EUSCI_B0_BASE);

	MAP_Interrupt_enableInterrupt(INT_EUSCIB0);

}

/*******************************************************************************
 * @fn      I2C_getTempData
 *
 * @brief   reads temperature data from TMP112 (1 measurement)
 *
 * @param   *retData: address of array to place data
 *
 * @return	-
 ******************************************************************************/
void I2C_getTempData(uint8_t *retData) {

	uint8_t CMD = 0x00;
	I2C_getData(CMD, TMP112_ADDR);
	retData[0] = I2C_RX[0];
	retData[1] = I2C_RX[1];

}

/*******************************************************************************
 * @fn      I2C_sleepTempSensor
 *
 * @brief   puts temperature sensor (TMP112) into/out of sleep mode
 *
 * @param   sleep: true for sleep mode, false for normal mode
 *
 * @return	-
 ******************************************************************************/
void I2C_sleepTempSensor(bool sleep) {

	uint8_t CMD = 0x01;
	uint8_t hi = 0x00;
	uint8_t lo = 0xE0;

	/* set SD bit of 16 bit control register either to 1 or 0 */
	if(sleep)
		hi = 0x61;
	else
		hi = 0x60;

	MAP_Interrupt_disableInterrupt(INT_EUSCIB0);

	MAP_I2C_setSlaveAddress(EUSCI_B0_BASE, TMP112_ADDR);

	MAP_I2C_masterSendMultiByteStart(EUSCI_B0_BASE, CMD);
	while (!(MAP_I2C_getInterruptStatus(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0) & EUSCI_B_I2C_TRANSMIT_INTERRUPT0));
	MAP_I2C_clearInterruptFlag(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0 + EUSCI_B_I2C_RECEIVE_INTERRUPT0);
	MAP_I2C_masterSendMultiByteNext(EUSCI_B0_BASE, hi);
	while (!(MAP_I2C_getInterruptStatus(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0) & EUSCI_B_I2C_TRANSMIT_INTERRUPT0));
	MAP_I2C_clearInterruptFlag(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0 + EUSCI_B_I2C_RECEIVE_INTERRUPT0);
	MAP_I2C_masterSendMultiByteNext(EUSCI_B0_BASE, lo);
	while (!(MAP_I2C_getInterruptStatus(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0) & EUSCI_B_I2C_TRANSMIT_INTERRUPT0));
	MAP_I2C_clearInterruptFlag(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0 + EUSCI_B_I2C_RECEIVE_INTERRUPT0);
	MAP_I2C_masterSendMultiByteStop(EUSCI_B0_BASE);

	MAP_Interrupt_enableInterrupt(INT_EUSCIB0);

}



