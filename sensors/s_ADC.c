/*
 * ADC.c
 *
 *  Created on: 02. Dez. 2016
 *      Author: Michael
 */

#include <sensors/s_ADC.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/*****************************************************************************
 * global variables
 ******************************************************************************/
extern volatile uint16_t ADC_result[ADC_B_SIZE];
extern volatile bool ADC_DRDY;


/*******************************************************************************
 * functions																   *
 *******************************************************************************/
/*******************************************************************************
 * @fn      initADC
 *
 * @brief   initialization of ADC
 * 			2 channel readout with no repeat (software triggered)
 *
 * @param   void
 *
 * @return  void
 ******************************************************************************/
void initADC(void) {

	/* Initializing ADC to 8.2kHz (ACLK/2), for eventual use in repeat mode */
	MAP_ADC14_enableModule();
//	MAP_ADC14_initModule(ADC_CLOCKSOURCE_ACLK, ADC_PREDIVIDER_1, ADC_DIVIDER_2,0);
//	MAP_ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_2,0);
	MAP_ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_4,0);

	/* Configuring ADC Memory (ADC_MEM0 - ADC_MEM1 (A2, A4)  with no repeat */
	MAP_ADC14_configureSingleSampleMode(ADC_MEM0, true);
	MAP_ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A4, false);		//GSR
	//MAP_ADC14_configureConversionMemory(ADC_MEM2, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A0, false);		//i_set of charger

    /* Setting up the sample timer to automatically step through the sequence */
    MAP_ADC14_enableSampleTimer(ADC_MANUAL_ITERATION);

    MAP_ADC14_enableConversion();
    MAP_ADC14_toggleConversionTrigger();

    /* Enabling the interrupt when a conversion reaches end of sequence (ADC_MEM1 -> INT1) */
    MAP_ADC14_enableInterrupt(ADC_INT0);

    /* Interrupt Registration */
    MAP_Interrupt_enableInterrupt(INT_ADC14);

}

/*******************************************************************************
 * @fn      ADC_triggerConversion
 *
 * @brief   triggers readout of 2 channels (GSR, Micro) and waits until data
 * 			is ready
 *
 * @param   void
 *
 * @return  void
 ******************************************************************************/
void ADC_triggerConversion(void) {

	MAP_ADC14_toggleConversionTrigger();

	/* waiting for Data ready flag */
	//while(!ADC_DRDY) {}
	ADC_DRDY = false;

}

/*******************************************************************************
 * @fn      ADC_getGSR
 *
 * @brief   reads GSR data from ADC buffer and split it in 2 bytes for BLE
 * 			transmission
 *
 * @param   Addr: Data is put to this address
 *
 * @return  void
 ******************************************************************************/
void ADC_getGSR(uint8_t *Addr) {

	uint8_t hi, lo = 0;

	/* GSR data @ 2nd position of ADC readout */
	hi = ((uint8_t)(ADC_result[1] >> 8));
	lo = (uint8_t)(ADC_result[1]);

	/* put Data at the given address, MSB first */
	Addr[0] = hi;
	Addr[1] = lo;
}

/*******************************************************************************
 * @fn      ADC_getAudio
 *
 * @brief   reads Audio data from ADC buffer and split it in 2 bytes for BLE
 * 			transmission
 *
 * @param   Addr: Data is put to this address
 *
 * @return  void
 ******************************************************************************/
void ADC_getAudio(uint8_t *Addr) {

	uint8_t hi, lo = 0;

	/* Audio data @ 1st position of ADC readout */
	hi = ((uint8_t)(ADC_result[0] >> 8));
	lo = (uint8_t)(ADC_result[0]);

	/* put Data at the given address, MSB first */
	Addr[0] = hi;
	Addr[1] = lo;
}


