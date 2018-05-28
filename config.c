/*
 * config.c
 *
 *  Created on: Sep 9, 2017
 *      Author: ferdinandvonhagen
 */
#include "config.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>


/* UART Configuration Parameter. These are the configuration parameters to
 * make the eUSCI A UART module to operate with a 115200 baud rate. These
 * values were calculated using the online calculator that TI provides
 * at:
 * http://processors.wiki.ti.com/index.php/USCI_UART_Baud_Rate_Gen_Mode_Selection
 */
#if MSCLK==48000000
const eUSCI_UART_Config uartConf =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        187,                                     // BRDIV = 26
        0,                                       // UCxBRF = 0
        4,                                       // UCxBRS = 0
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // MSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION  // Low Frequency Mode
};
#endif

#if MSCLK==24000000
const eUSCI_UART_Config uartConf =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        93,                                      // BRDIV = 26
        0,                                       // UCxBRF = 0
        6,                                       // UCxBRS = 0
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // MSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION  // Low Frequency Mode
};
#endif


#if MSCLK==12000000
const eUSCI_UART_Config uartConf =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        46,                                      // BRDIV = 26
        0,                                       // UCxBRF = 0
        7,                                       // UCxBRS = 0
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // MSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION  // Low Frequency Mode
};
#endif

void init_sys(void)
{
    /* Halting WDT and disabling master interrupts */
    MAP_WDT_A_holdTimer();
    MAP_Interrupt_disableMaster();

    /* Initializes Clock System */
#if MSCLK==48000000
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
#endif

#if MSCLK==24000000
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE0);
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 1);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 1);
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);
#endif

#if MSCLK==12000000
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE0);
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 0);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 0);
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);
#endif

    MAP_CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    MAP_GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN0);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN1);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN1);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN1);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN3);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN6);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN7);
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
            GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configuring SysTick */
    MAP_SysTick_enableModule();
    MAP_SysTick_setPeriod(16777216);
    MAP_SysTick_enableInterrupt();

    /* Enabling MASTER interrupts */
    //MAP_Interrupt_enableMaster();

    /* Configuring UART Module */
    MAP_UART_initModule(EUSCI_A0_BASE, &uartConf);

    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A0_BASE);
}
