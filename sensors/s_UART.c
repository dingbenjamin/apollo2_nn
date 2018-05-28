/*
 * UART.c
 *
 *  Created on: 09. Nov. 2016
 *      Author: Michael
 */

#include <sensors/s_UART.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/*******************************************************************************
 * constants definition
 *******************************************************************************/
/* UART Configuration Parameter. These are the configuration parameters to
 * make the eUSCI A UART module to operate with a 921 600 baud rate. These
 * values were calculated using the online calculator that TI provides
 * at:
 *http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
 */
const eUSCI_UART_Config uartConfig =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          		// SMCLK Clock Source
        3,                                     			// BRDIV = 3
        4,                                       		// UCxBRF = 4
        2,                                       		// UCxBRS = 2
        EUSCI_A_UART_NO_PARITY,                  		// No Parity
        EUSCI_A_UART_LSB_FIRST,                  		// LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               		// One stop bit
        EUSCI_A_UART_MODE,                       		// UART mode
		EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION	// Oversampling
};


/*******************************************************************************
 * functions
 *******************************************************************************/

/*******************************************************************************
 * @fn      initUART
 *
 * @brief   initialization of UART interface (EUSCI_A2, CC2650 communication)
 *
 * @param   void
 *
 * @return  void
 ******************************************************************************/
void initUART(void) {

    /* Selecting P3.2 and P3.3 in UART mode */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configuring UART module */
    MAP_UART_initModule(EUSCI_A2_BASE, &uartConfig);

    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A2_BASE);

    /* Receive Interrupt registration */
    MAP_UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_setPriority(INT_EUSCIA2, 0x40);	//lower priority than T32_INT2
    MAP_Interrupt_enableInterrupt(INT_EUSCIA2);
}

