/*
 * BLE.c
 *
 *  Created on: 30. Nov. 2016
 *      Author: Michael
 */

#include <sensors/s_BLE.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/*****************************************************************************
 * global variables
 ******************************************************************************/

/*******************************************************************************
 * @fn      BLE_sendStatusData
 *
 * @brief   sends status data formatted for PC readout via BLE
 *
 * @param   *Data: address of array with data
 *
 * @return	-
 ******************************************************************************/
void BLE_sendStatusData(uint8_t *Data) {

	int i = 0;

	//TODO: check length/pointer

	/* send to CC2650 */
	MAP_UART_transmitData(EUSCI_A2_BASE, 'S');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'T');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'A');
	MAP_UART_transmitData(EUSCI_A2_BASE, ':');
	MAP_UART_transmitData(EUSCI_A2_BASE, HW_VERSION);
	MAP_UART_transmitData(EUSCI_A2_BASE, SW_VERSION);
	for(i = 0; i < 22; i++) {
		MAP_UART_transmitData(EUSCI_A2_BASE, Data[i]);
	}
	MAP_UART_transmitData(EUSCI_A2_BASE, '\r');
	MAP_UART_transmitData(EUSCI_A2_BASE, '\n');
}

/*******************************************************************************
 * @fn      BLE_sendSensorData
 *
 * @brief   sends sensor data formatted for PC readout via BLE (62 bytes pkg.)
 *
 * @param   Data: bytes to transmit
 * 			Size: number of bytes
 *
 * @return	-
 ******************************************************************************/
void BLE_sendSensorData(uint8_t *Data, uint8_t Size) {
	uint8_t i = 0;

	//TODO: check LENGTH (max 62 bytes per package)

	for(i = 0; i < Size; i++) {
		MAP_UART_transmitData(EUSCI_A2_BASE, Data[i]);
	}

}

/*******************************************************************************
 * @fn      BLE_sendMotionData
 *
 * @brief   sends motion data formatted for PC readout via BLE
 *
 * @param   *Data: address of array with data
 *
 * @return	-
 ******************************************************************************/
void BLE_sendMotionData(uint8_t *Data) {

	int i = 0;

	//TODO: check length/pointer

//    MAP_Interrupt_pendInterrupt( INT_PORT2 );
//    MAP_Interrupt_pendInterrupt( INT_T32_INT1 );
//    MAP_Interrupt_pendInterrupt( INT_T32_INT2 );
//    MAP_Interrupt_pendInterrupt( INT_ADC14 );
//    MAP_Interrupt_pendInterrupt( INT_EUSCIB0 );
//    MAP_Interrupt_pendInterrupt( INT_EUSCIA1 );
//    MAP_Interrupt_pendInterrupt( INT_EUSCIA0 );
//    MAP_Interrupt_pendInterrupt( INT_EUSCIA2 );

	/* send to CC2650 */
	MAP_UART_transmitData(EUSCI_A2_BASE, 'M');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'O');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'T');
	MAP_UART_transmitData(EUSCI_A2_BASE, ':');
//	for(i = 0; i < 18; i++) {
//		MAP_UART_transmitData(EUSCI_A2_BASE, Data[i]);
//	}
	for(i = 0; i < 18; i++) {
		MAP_UART_transmitData(EUSCI_A2_BASE, 0x00);
	}
	MAP_UART_transmitData(EUSCI_A2_BASE, '\r');
	MAP_UART_transmitData(EUSCI_A2_BASE, '\n');
}

/*******************************************************************************
 * @fn      BLE_sendTempData
 *
 * @brief   sends temperature data formatted for PC readout via BLE
 *
 * @param   *Data: address of array with data
 *
 * @return	-
 ******************************************************************************/
void BLE_sendTempData(uint8_t *Data) {

	int i = 0;

	//TODO: check length/pointer

	/* send to CC2650 */
	MAP_UART_transmitData(EUSCI_A2_BASE, 'T');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'E');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'M');
	MAP_UART_transmitData(EUSCI_A2_BASE, ':');
//	for(i = 0; i < 2; i++) {
//		MAP_UART_transmitData(EUSCI_A2_BASE, Data[i]);
//	}
	for(i = 0; i < 2; i++) {
		MAP_UART_transmitData(EUSCI_A2_BASE, 0x00);
	}
	MAP_UART_transmitData(EUSCI_A2_BASE, '\r');
	MAP_UART_transmitData(EUSCI_A2_BASE, '\n');

}

/*******************************************************************************
 * @fn      BLE_sendECGData
 *
 * @brief   sends ECG data formatted for PC readout via BLE
 *
 * @param   *Data: address of array with data
 *
 * @return	-
 ******************************************************************************/
void BLE_sendECGData(uint8_t *Data) {

	int i = 0;

	//TODO: check length/pointer

	/* send to CC2650 */
	MAP_UART_transmitData(EUSCI_A2_BASE, 'E');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'C');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'G');
	MAP_UART_transmitData(EUSCI_A2_BASE, ':');
//	for(i = 0; i < 9; i++) {
//		MAP_UART_transmitData(EUSCI_A2_BASE, Data[i]);
//	}
	for(i = 0; i < 9; i++) {
		MAP_UART_transmitData(EUSCI_A2_BASE, 0x00);
	}
	MAP_UART_transmitData(EUSCI_A2_BASE, '\r');
	MAP_UART_transmitData(EUSCI_A2_BASE, '\n');

}

/*******************************************************************************
 * @fn      BLE_sendGSRData
 *
 * @brief   sends GSR data formatted for PC readout via BLE
 *
 * @param   *retData: address of array with data (uint16)
 *
 * @return	-
 ******************************************************************************/
void BLE_sendGSRData(uint16_t *Data) {

//	uint8_t hi,lo = 0;

	// TODO: check length of array/pointer

	/* GSR data @ 2nd position of ADC readout */
//	hi = ((uint8_t)(Data[1] >> 8));
//	lo = (uint8_t)(Data[1]);

	/* send to CC2650 */
	MAP_UART_transmitData(EUSCI_A2_BASE, 'G');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'S');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'R');
	MAP_UART_transmitData(EUSCI_A2_BASE, ':');
//	MAP_UART_transmitData(EUSCI_A2_BASE, hi);
//	MAP_UART_transmitData(EUSCI_A2_BASE, lo);
	MAP_UART_transmitData(EUSCI_A2_BASE, '\r');
	MAP_UART_transmitData(EUSCI_A2_BASE, '\n');

}

/*******************************************************************************
 * @fn      BLE_sendAudioData
 *
 * @brief   sends audio data formatted for PC readout via BLE
 *
 * @param   *retData: address of array with data (uint16)
 *
 * @return	-
 ******************************************************************************/
void BLE_sendAudioData(uint16_t *Data) {

//	uint8_t hi,lo = 0;

	/* Ausio data @ 1st position of ADC readout */
//	hi = ((uint8_t)(Data[0] >> 8));
//	lo = (uint8_t)(Data[0]);

	/* send to CC2650 */
	MAP_UART_transmitData(EUSCI_A2_BASE, 'A');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'U');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'D');
	MAP_UART_transmitData(EUSCI_A2_BASE, ':');
//	MAP_UART_transmitData(EUSCI_A2_BASE, hi);
//	MAP_UART_transmitData(EUSCI_A2_BASE, lo);
	MAP_UART_transmitData(EUSCI_A2_BASE, 0x00);
	MAP_UART_transmitData(EUSCI_A2_BASE, 0x00);
	MAP_UART_transmitData(EUSCI_A2_BASE, '\r');
	MAP_UART_transmitData(EUSCI_A2_BASE, '\n');

}

/*******************************************************************************
 * @fn      BLE_sendACK
 *
 * @brief   sends acknowledge via BLE to the PC
 *
 * @param   -
 *
 * @return	-
 ******************************************************************************/
void BLE_sendACK(void) {

	/* send acknowledge to CC2650 */
	MAP_UART_transmitData(EUSCI_A2_BASE, '\n');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'A');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'C');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'K');
	MAP_UART_transmitData(EUSCI_A2_BASE, '\n');

}

/*******************************************************************************
 * @fn      BLE_sendACK
 *
 * @brief   sends not acknowledge via BLE to the PC
 *
 * @param   -
 *
 * @return	-
 ******************************************************************************/
void BLE_sendNACK(void) {

	/* send not acknowledge to CC2650 */
	MAP_UART_transmitData(EUSCI_A2_BASE, '\n');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'N');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'A');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'C');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'K');
	MAP_UART_transmitData(EUSCI_A2_BASE, '\n');

}

/*******************************************************************************
 * @fn      BLE_sendClap
 *
 * @brief   sends clap command via BLE to the PC
 *
 * @param   -
 *
 * @return	-
 ******************************************************************************/
void BLE_sendClap(void) {

	/* send clap to CC2650 */
	//MAP_UART_transmitData(EUSCI_A2_BASE, '\n');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'C');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'L');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'A');
	MAP_UART_transmitData(EUSCI_A2_BASE, 'P');
	MAP_UART_transmitData(EUSCI_A2_BASE, '\r');
	MAP_UART_transmitData(EUSCI_A2_BASE, '\n');

}


