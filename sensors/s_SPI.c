/*
 * SPI.c
 *
 *  Created on: 11. Nov. 2016
 *      Author: Michael
 */

#include <sensors/s_SPI.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/*****************************************************************************
 * global variables
 ******************************************************************************/
extern volatile uint8_t SPI_RX_FRAM[SPI_RX_BYTES];
extern volatile uint8_t SPI_RX_ECG[SPI_RX_BYTES];
extern volatile uint8_t SPI_recBytesFRAM;
extern volatile uint8_t SPI_recBytesECG;
//extern volatile ECG_State ECG_current_state;

/*****************************************************************************
 * constants
 *****************************************************************************/
/* SPI Master Configuration Parameter for ECG Sensor (ADS1292R) */
const eUSCI_SPI_MasterConfig spiMasterConfig_ECG =
{
        EUSCI_A_SPI_CLOCKSOURCE_SMCLK,             	// SMCLK Clock Source
        48000000,                             		// SMCLK = HFXT = 48 MHz
        1000000,                                   	// SPICLK = 1MHz
        EUSCI_A_SPI_MSB_FIRST,                     	// MSB First
		EUSCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,    // Phase
        EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW, 	// LOW polarity
        EUSCI_A_SPI_3PIN                           	// 3Wire SPI Mode
};

/* SPI Master Configuration Parameter for FRAM (FM25V10G)*/
const eUSCI_SPI_MasterConfig spiMasterConfig_FRAM =
{
        EUSCI_A_SPI_CLOCKSOURCE_SMCLK,             	// SMCLK Clock Source
        48000000,                             		// SMCLK = HFXT = 48 MHz
		6000000,                                   // SPICLK = 6 MHz
        EUSCI_A_SPI_MSB_FIRST,                     	// MSB First
		EUSCI_A_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,    // Phase
        EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW, 	// LOW polarity
		EUSCI_A_SPI_3PIN                     		// 3Wire SPI Mode
};


/*******************************************************************************
 * functions																   *
 *******************************************************************************/
/*******************************************************************************
 * @fn      initSPI
 *
 * @brief   initialization of SPI interfaces
 *
 * @param   void
 *
 * @return  void
 *******************************************************************************/
void initSPI(void) {

	/* ECG SENSOR: ADS1292 */
	/* Selecting P2.1, P2.2 and P2.3 in SPI mode */
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    /* Configuring SPI in 3wire master mode */
    MAP_SPI_initMaster(EUSCI_A1_BASE, &spiMasterConfig_ECG);
    /* Enable SPI module */
    MAP_SPI_enableModule(EUSCI_A1_BASE);

    /* Interrupt registration */
    MAP_SPI_enableInterrupt(EUSCI_A1_BASE, EUSCI_A_SPI_RECEIVE_INTERRUPT);
    MAP_Interrupt_setPriority(INT_EUSCIA1, 0x20);	//higher priority than INT_PORT2
    MAP_Interrupt_enableInterrupt(INT_EUSCIA1);

    /* Polling to see if the TX buffer is ready */
    //while (!(MAP_SPI_getInterruptStatus(EUSCI_A1_BASE,EUSCI_A_SPI_TRANSMIT_INTERRUPT)));


	/* FRAM: FM25V10G */
	/* Selecting P1.1, P1.2 and P1.3 in SPI mode */
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    /* Configuring SPI in 3wire master mode */
    MAP_SPI_initMaster(EUSCI_A0_BASE, &spiMasterConfig_FRAM);
    /* Enable SPI module */
    MAP_SPI_enableModule(EUSCI_A0_BASE);

    /* Interrupt registration */
    MAP_SPI_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_SPI_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA0);

    /* Polling to see if the TX buffer is ready */
    //while (!(MAP_SPI_getInterruptStatus(EUSCI_A0_BASE,EUSCI_A_SPI_TRANSMIT_INTERRUPT)));
}


/*******************************************************************************
 * @fn      testFRAM(void)
 *
 * @brief   reads the ID register of the FRAM
 *
 * @param   -
 *
 * @return  -
 *******************************************************************************/
void testFRAM(void) {

	uint8_t TXData = 0x9F;

	SPI_recBytesFRAM = 0;

	/* enable output of level shifter */
	MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN4);

	_delay_cycles(500000);

	/* Polling to see if the TX buffer is ready */
	while (!(MAP_SPI_getInterruptStatus(EUSCI_A0_BASE,EUSCI_A_SPI_TRANSMIT_INTERRUPT)));
	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
	MAP_SPI_transmitData(EUSCI_A0_BASE, TXData);

	while(SPI_recBytesFRAM != 10);

	/* disable CS */
	MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);

	/* disable output of level shifter */
	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN4);

}

/*******************************************************************************
 * @fn      testECG(void)
 *
 * @brief   ECG test routine
 *
 * @param   -
 *
 * @return  -
 *******************************************************************************/
void testECG(void) {

//	uint8_t stopCode = 0x11;
	SPI_recBytesECG = 0;

	/* Chip reset */
	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);
	_delay_cycles(100);
	MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);
	_delay_cycles(1000);

//	/* Chip select enable*/
//	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
//	_delay_cycles(300);
//
//	/* Stop read continuous */
//	MAP_SPI_transmitData(EUSCI_A1_BASE, stopCode);
//	_delay_cycles(600);
//
//	/* Chip select disable*/
//	MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
//	_delay_cycles(1000);
//
//	/* Chip select enable*/
//	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
//	_delay_cycles(300);
//	/* read register 0x00 */
//	/* OPCODE 1: 0x20 */
//	MAP_SPI_transmitData(EUSCI_A1_BASE, 0x20);
//	_delay_cycles(600);
//	/* OPCODE 2: 0x00 (read 1 byte)*/
//	//while (!(MAP_SPI_getInterruptStatus(EUSCI_A1_BASE,EUSCI_A_SPI_TRANSMIT_INTERRUPT)));
//	MAP_SPI_transmitData(EUSCI_A1_BASE, 0x00);
//	 /* clocks for 1 read */
//	//while (!(MAP_SPI_getInterruptStatus(EUSCI_A1_BASE,EUSCI_A_SPI_TRANSMIT_INTERRUPT)));
//	_delay_cycles(600);
//	MAP_SPI_transmitData(EUSCI_A1_BASE, 0x00);
//
//	/* Chip select disable*/
//	_delay_cycles(1000);
//	MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
//
//	_delay_cycles(1000);
//
//	/* Start read continuous */
//	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
//	_delay_cycles(300);
//	MAP_SPI_transmitData(EUSCI_A1_BASE, 0x10);
//	_delay_cycles(600);
//	MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
//	_delay_cycles(1000);
//
//	SPI_recBytesECG = 0;
}

/*******************************************************************************
 * @fn      SPI_initECG
 *
 * @brief   initializes ADS1292 registers via SPI
 *
 * @param   -
 *
 * @return  -
 *******************************************************************************/
void SPI_initECG(void) {

	uint8_t i = 0;
	uint8_t ADS1292R_Register_Settings[13] = {
		//OPCODE 1
		0x41,
		//OPCODE 2
		0x0B,
	   	//CONFIG1 (250 Hz samplerate)
		0x01,
	    //CONFIG2 (enable lead-off detection)
	    0xE0,
	    //LOFF (70 % threshold)
	    0xF0,
		//CH1SET (PGA gain = 6)
	    0x00,
		//CH2SET (PGA gain = 6)
	    0x00,
		//RLD_SENS (default)
		0x2C,
		//LOFF_SENS (default)
		0x0F,
	    //LOFF_STAT (CH1,2 pos + neg)
	    0x00,
	    //RESP1 (Resp enable)
	    0xEA,
		//RESP2
		0x03,
		//GPIO (Inputs)
	    0x0C
	};

	SPI_recBytesECG = 0;

	/* Chip reset */
	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);
	_delay_cycles(100);
	MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);
	_delay_cycles(1000);

	/* Stop read continuous */
	//CS permanently low
	MAP_SPI_transmitData(EUSCI_A1_BASE, ECG_SDATAC);
	_delay_cycles(600);

	/* register write: WREG */
	for(i = 0; i < 13; i++) {
		MAP_SPI_transmitData(EUSCI_A1_BASE, ADS1292R_Register_Settings[i]);
		_delay_cycles(500);
	}
	SPI_recBytesECG = 0;
	_delay_cycles(1000);

	/* read registers for confirmation: RREG */
	MAP_SPI_transmitData(EUSCI_A1_BASE, 0x21);
	_delay_cycles(500);
	MAP_SPI_transmitData(EUSCI_A1_BASE, 0x0B);
	_delay_cycles(500);
	for(i = 0; i < 11; i++) {
		MAP_SPI_transmitData(EUSCI_A1_BASE, 0x00);
		_delay_cycles(500);
	}

	/* enable continuous read again */
	MAP_SPI_transmitData(EUSCI_A1_BASE, ECG_RDATAC);
	_delay_cycles(500);

	/* reset counters */
	SPI_recBytesECG = 0;
	ECG_cnt = 0;
}

/*******************************************************************************
 * @fn      SPI_startStreamECG
 *
 * @brief   starts to stream ECG data via SPI continuously
 *
 * @param   -
 *
 * @return  -
 *******************************************************************************/
void SPI_startStreamECG(void) {

//	ECG_current_state = CONTINUOUS;

	/* set start pin P2.6 high */
	MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);

	SPI_recBytesECG = 0;
	ECG_cnt = 0;

}

/*******************************************************************************
 * @fn      SPI_stopStreamECG
 *
 * @brief   stops stream of ECG data via SPI
 *
 * @param   -
 *
 * @return  -
 *******************************************************************************/
void SPI_stopStreamECG(void) {

//	ECG_current_state = OFF;

	/* set start pin P2.6 low */
	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN6);

}

/*******************************************************************************
 * @fn      SPI_sleepECG
 *
 * @brief   puts ECG sensor (ADS1292) into/out of sleep mode
 *
 * @param   sleep: true for sleep mode, false for normal mode
 *
 * @return	-
 ******************************************************************************/
void SPI_sleepECG(bool sleep) {

	SPI_recBytesECG = 0;

	if (sleep)
		MAP_SPI_transmitData(EUSCI_A1_BASE, ECG_STANDBY);
	else {
		MAP_SPI_transmitData(EUSCI_A1_BASE, ECG_WAKEUP);
		/* wait 10 ms after wakeup */
		_delay_cycles(480000);
	}

	SPI_recBytesECG = 0;
}

/*******************************************************************************
 * @fn      SPI_singleReadECG
 *
 * @brief   provides 9 SPI clockcycles for single readout
 *
 * @param   -
 *
 * @return	-
 ******************************************************************************/
void SPI_singleReadECG(void) {

	//ECG = on
	int i = 0;

	SPI_recBytesECG = 0;

	/* provide clock */
	for(i = 0; i < 9; i++) {
		MAP_SPI_transmitData(EUSCI_A1_BASE, 0x00);
		_delay_cycles(300);
	}

	while (SPI_recBytesECG < 8);
}
