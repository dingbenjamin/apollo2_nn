/*
 * config.h
 *
 *  Created on: Sep 9, 2017
 *      Author: ferdinandvonhagen
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void init_sys(void);

#define MSCLK 48000000

extern const eUSCI_UART_Config uartConfig;


#endif /* CONFIG_H_ */
