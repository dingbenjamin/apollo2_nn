/*
 * initBoard.c
 *
 *  Created on: 04. Nov. 2016
 *      Author: Michael
 */

#include <sensors/s_startup.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/*****************************************************************************
 * global variables
 ******************************************************************************/
extern volatile uint16_t T32_time;
extern volatile uint32_t T32_BCOMM;
extern volatile uint32_t ECG_cnt;
extern volatile uint8_t BodyComm;
extern volatile char BLE_CMD[BLE_CMD_SIZE];
extern volatile uint8_t BLE_CMD_N;
/* flags */
extern volatile bool ECG_DRDY;
extern volatile bool ADC_DRDY;
extern volatile bool SENS_STREAM;
extern volatile bool BLE_REC;
extern volatile bool FANN_CALC;


/*******************************************************************************
 * functions
 *******************************************************************************/
/*******************************************************************************
 * @fn      initGPIO
 *
 * @brief   initialization of GPIO ports
 *
 * @param   void
 *
 * @return  void
 ******************************************************************************/
void initGPIO(void) {
	//TODO: initialize unused Pins to GND

	/* Pin directions */
	/* Outputs */
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);		//P1.0 FRAM_SPI_nCS: SPI chip select (low active)
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN4);		//P1.4 FRAM_OE: output enable
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);		//P2.0 ADS1292_SPI_nCS: SPI chip select (low active)
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN6);		//P2.6 ADS1292_START: start conversion
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN7);		//P2.7 ADS1292_RESET: chip reset (low active)
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN1);		//P3.1 CC2650_MRDY: hardware handshake (only used if CC2650 is in power saving mode)
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN0);		//P6.0 touch_out_on: enable PWM amplifier
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN6);		//P6.6 CHRGR_nCE: Battery charger enable (low active)
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN5);		//P10.5 touch_ransmit: PWM output for body communication
	/* Output states @ startup */
	MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);	//P1.0 FRAM_SPI_nCS: cannot be tied to GND permanently
	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN4);	//P1.4 FRAM_OE: output is disabled
	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);	//P2.0 ADS1292_SPI_nCS: tied to GND permanently (only 1 slave)
	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN6);	//P2.6 ADS1292_START: no conversion
	MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);	//P2.7 ADS1292_RESET: no chip reset (low active)
	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN1);	//P3.1 CC2650_MRDY: set to low (not used)
	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);	//P6.0 touch_out_on.: PWM amplifier disabled
	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN6);	//P6.6 CHRGR_nCE: Battery charger enable (low active)
	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P10, GPIO_PIN5);	//P10.5 touch_ransmit: disabled on startup
	/* Inputs */
	MAP_GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN5);		//P2.5 ADS1292_DRDY: data ready interrupt (low active)
	MAP_GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN0);		//P3.0 CC2650_SRDY: hardware handshake (only used if CC2650 is in power saving mode)
	MAP_GPIO_setAsInputPin(GPIO_PORT_P6, GPIO_PIN1);		//P6.1 MPU9250_INT: wake up interrupt of MPU9250
	MAP_GPIO_setAsInputPin(GPIO_PORT_P6, GPIO_PIN4);		//P6.4 TMP112_ALERT: overtemperature alert of TMP112
	MAP_GPIO_setAsInputPin(GPIO_PORT_P6, GPIO_PIN5);		//P6.5 TPS2115_STAT: Power-Mux switch state
	MAP_GPIO_setAsInputPin(GPIO_PORT_P6, GPIO_PIN7);		//P6.7 BQ27425_GPOUT: battery low interrupt
	/* Analog inputs */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN1, GPIO_TERTIARY_MODULE_FUNCTION);		// GSR input
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN3, GPIO_TERTIARY_MODULE_FUNCTION);		// Micro input
    //MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN5, GPIO_TERTIARY_MODULE_FUNCTION);	// i_set of charger, not used at the moment

	/* Input Interrupt registration */
    /* ADS1292 DRDY interrupt */
	MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN5);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN5);
    MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P2, GPIO_PIN5, GPIO_HIGH_TO_LOW_TRANSITION);
    MAP_Interrupt_setPriority(INT_PORT2, 0x40);				//lower priority than INT_EUSCIA1
    MAP_Interrupt_enableInterrupt(INT_PORT2);

}


/*******************************************************************************
 * @fn      initClockSources
 *
 * @brief   start external crystals (LFXT = 32.768 kHz, HFXT = 48 MHz)
 * 			set MCLK and SMCLK to 48 MHz, ACLK to 16.387 kHz
 *
 * @param   void
 *
 * @return  void
 ******************************************************************************/
void initClockSources(void) {

    /* HFXT 48 MHz */
	/* Configuring pins PJ.2 & PJ.3 for peripheral/crystal usage */
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ, GPIO_PIN3 | GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);

    /* needed for following functions and getACLK, getMCLK, etc. (params in Hz) */
    MAP_CS_setExternalClockSourceFrequency(32768,48000000);

    /* Starting HFXT in non-bypass mode without a timeout. VCORE have to
     * be changed to 1 to support the 48MHz frequency */
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);
    MAP_CS_startHFXT(false);

    /* Initializing MCLK & SMCLK to HFXT */
    MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);


    /* LFXT 32.768 kHz */
    /* Configuring pins PJ.0 & PJ.1 for peripheral/crystal usage  */
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Starting LFXT in non-bypass mode without a timeout. */
    MAP_CS_startLFXT(false);

    /* Initializing ACLK to 16kHz */
    MAP_CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_2);

}

/*******************************************************************************
 * @fn      initTimer32
 *
 * @brief   initializes Timer32 modules, interval 1ms, 10us
 *
 * @param   void
 *
 * @return  void
 ******************************************************************************/
void initTimer32(void) {

	uint32_t count1 = 3000; //1ms interval
	uint32_t count2 = 480;	//10us interval

	/* TIMER 1: 1ms interval */
    MAP_Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_16, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    MAP_Timer32_setCount( TIMER32_0_BASE, count1);

    /* Interrupt registration */
    MAP_Timer32_enableInterrupt(TIMER32_0_BASE);
    MAP_Interrupt_enableInterrupt(INT_T32_INT1);

    /* TIMER 2: 10us interval */
    MAP_Timer32_initModule(TIMER32_1_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    MAP_Timer32_setCount( TIMER32_1_BASE, count2);
    MAP_Interrupt_setPriority(INT_EUSCIA1, 0x20);	//higher priority than INT_EUSCIA2 (timer started out of EUSCI A2 interrupt routine)

    // Interrupt enable and start of timer in body communication //
   // MAP_Interrupt_enableInterrupt(INT_T32_INT2);
}

/*******************************************************************************
 * @fn      initGlobals
 *
 * @brief   initializes global variables
 *
 * @param   void
 *
 * @return  void
 ******************************************************************************/
void initGlobals(void) {

	int i = 0;

	/* init received command array */
	for(i = 0; i < BLE_CMD_SIZE; i++) {
		BLE_CMD[i] = 0x00;
	}

	ECG_cnt = 0;			//received ECG values
	BLE_CMD_N = 0;			//index of command buffer
	BodyComm = 0;

	/* timer variables */
	T32_time = 0;
	T32_BCOMM = 0;

	/* flags */
	ECG_DRDY = false;
	ADC_DRDY = false;
	SENS_STREAM = false;
	BLE_REC = false;
	FANN_CALC = false;

}
