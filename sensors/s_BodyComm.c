/*
 * BodyComm.c
 *
 *  Created on: 01. Dez. 2016
 *      Author: Michael
 */

#include <sensors/s_BodyComm.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/*****************************************************************************
 * global variables
 ******************************************************************************/
extern volatile uint32_t T32_BCOMM;
extern volatile uint8_t BodyComm;

/*****************************************************************************
 * constants
 *****************************************************************************/
/* TimerA PWM configuration */
Timer_A_PWMConfig pwmConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,				// SMCLK = 48MHz
        TIMER_A_CLOCKSOURCE_DIVIDER_1,			// DIVIDER = 1
        5,										// TIMER PERIODE
        TIMER_A_CAPTURECOMPARE_REGISTER_1,		// CC-REGISTER
        TIMER_A_OUTPUTMODE_RESET_SET,			// PWM output
        3										// CNT PERIODE
};

/*******************************************************************************
 * functions																   *
 *******************************************************************************/
/*******************************************************************************
 * @fn      startBodyComm
 *
 * @brief   initializes TimerA for 8MHz PWM and enables amplifier
 *
 * @param   void
 *
 * @return  void
 ******************************************************************************/
void startBodyComm(void) {

	/* Configuring Timer_A: PWM with 8MHz and 50% duty cycle  */
	MAP_Timer_A_generatePWM(TIMER_A3_BASE, &pwmConfig);

	/* enable output comparator */
	MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN0);

}

/*******************************************************************************
 * @fn      stopBodyComm
 *
 * @brief   stops TimerA and disables amplifier
 *
 * @param   void
 *
 * @return  void
 ******************************************************************************/
void stopBodyComm(void) {

	/* disable TimerA */
	MAP_Timer_A_stopTimer(TIMER_A3_BASE);

	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P10, GPIO_PIN5);

	/* disable output comparator */
	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);

}

/*******************************************************************************
 * @fn      startCarrierBodyComm
 *
 * @brief   enables 8Mhz carrier for body communication and resets timer count
 * 			T32_BCOMM
 *
 * @param   void
 *
 * @return  void
 ******************************************************************************/
void startCarrierBodyComm(void) {

	/* Configuring P10.5 as peripheral output for PWM */
	MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P10, GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION);

	/* reset timer count */
	T32_BCOMM = 0;

}

/*******************************************************************************
 * @fn      stopCarrierBodyComm
 *
 * @brief   disables 8Mhz carrier for body communication and resets timer count
 * 			T32_BCOMM
 *
 * @param   void
 *
 * @return  void
 ******************************************************************************/
void stopCarrierBodyComm(void) {

	/* disable TimerA */
	//MAP_Timer_A_stopTimer(TIMER_A3_BASE);

	/* disable PWM output */
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN5);
	//MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P10, GPIO_PIN5);

	/* reset timer count */
	T32_BCOMM = 0;

}

/*******************************************************************************
 * @fn      sendByteBodyComm
 *
 * @brief   sends a byte via body communication
 *
 * @param   Data: byte to send
 * 			BitTime: time of bit in multiples of 10us
 *
 * @return  void
 ******************************************************************************/
void sendByteBodyComm(uint8_t Data, uint16_t BitTime) {

	uint8_t i;

//	startBodyComm(); 	// produces a peak when comparator is enabled
						// therefore enabled once at startup and not disabled


	// workaround: without this 5 lines, 1st bit slightly longer
	MAP_Timer32_startTimer(TIMER32_1_BASE, false);
	MAP_Interrupt_enableInterrupt(INT_T32_INT2);
	stopCarrierBodyComm();
	while(T32_BCOMM < BitTime);
	MAP_Interrupt_disableInterrupt(INT_T32_INT2);

	for(i = 0; i < 8; i++) {
		if(((Data << i) & (0x80))) {
			MAP_Interrupt_enableInterrupt(INT_T32_INT2);
			startCarrierBodyComm();
			while(T32_BCOMM < BitTime);
			MAP_Interrupt_disableInterrupt(INT_T32_INT2);
		}
		else {
			MAP_Interrupt_enableInterrupt(INT_T32_INT2);
			stopCarrierBodyComm();
			while(T32_BCOMM < BitTime);
			MAP_Interrupt_disableInterrupt(INT_T32_INT2);
		}
	}

	stopCarrierBodyComm();


	MAP_Timer32_haltTimer(TIMER32_1_BASE);

//	stopBodyComm();

}
