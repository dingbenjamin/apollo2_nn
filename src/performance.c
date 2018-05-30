/*
 * performance.c
 *
 *  Created on: Sep 9, 2017
 *      Author: ferdinandvonhagen
 */

#include "performance.h"


const char hexDigits[] = "0123456789ABCDEF";
uint32_t position = 0;
uint32_t timedV[8200];
const char *commands[10] = {"total", "base", "inner", "outer", "setup", "layer", "neuron", "weights", "activation", "actfunc"};
const unsigned int commandLengths[10] = {5, 4, 5, 5, 5, 5, 6, 7, 10, 7};

unsigned int calculateTime(pos, level)
{
    uint32_t nextPos = pos + 1;
    while(timedV[nextPos] & 0xF000000) {
        nextPos = calculateTime(nextPos, level + 1);
    }

    uint32_t res = 0;
    uint32_t start = timedV[pos] & 0xFFFFFF;
    uint32_t end = timedV[nextPos];
    if(start < end)
    {
        res = end - start;
    }
    else
    {
        res = 16777216 - start + end;
    }

//    MAP_UART_transmitData(EUSCI_A0_BASE, hexDigits[(res >> 20) & 0xf]);
//    MAP_UART_transmitData(EUSCI_A0_BASE, hexDigits[(res >> 16) & 0xf]);
//    MAP_UART_transmitData(EUSCI_A0_BASE, hexDigits[(res >> 12) & 0xf]);
//    MAP_UART_transmitData(EUSCI_A0_BASE, hexDigits[(res >> 8) & 0xf]);
//    MAP_UART_transmitData(EUSCI_A0_BASE, hexDigits[(res >> 4) & 0xf]);
//    MAP_UART_transmitData(EUSCI_A0_BASE, hexDigits[res & 0xf]);
//
//    MAP_UART_transmitData(EUSCI_A0_BASE, ' ');
//
//    uint32_t i;
//    uint8_t command = (timedV[pos] & 0xF0000000) >> 28;
//    const char *commandptr = commands[command];
//    uint32_t length = commandLengths[command];
//    for (i = 0; i < length; ++i)
//    {
//        MAP_UART_transmitData(EUSCI_A0_BASE, commandptr[i]);
//    }
//
//    MAP_UART_transmitData(EUSCI_A0_BASE, '\r');
//    MAP_UART_transmitData(EUSCI_A0_BASE, '\n');

    return nextPos + 1;
}

void calculateTimes()
{
//    MAP_UART_transmitData(EUSCI_A0_BASE, hexDigits[(position >> 28) & 0xf]);
//    MAP_UART_transmitData(EUSCI_A0_BASE, hexDigits[(position >> 24) & 0xf]);
//    MAP_UART_transmitData(EUSCI_A0_BASE, hexDigits[(position >> 20) & 0xf]);
//    MAP_UART_transmitData(EUSCI_A0_BASE, hexDigits[(position >> 16) & 0xf]);
//    MAP_UART_transmitData(EUSCI_A0_BASE, hexDigits[(position >> 12) & 0xf]);
//    MAP_UART_transmitData(EUSCI_A0_BASE, hexDigits[(position >> 8) & 0xf]);
//    MAP_UART_transmitData(EUSCI_A0_BASE, hexDigits[(position >> 4) & 0xf]);
//    MAP_UART_transmitData(EUSCI_A0_BASE, hexDigits[position & 0xf]);
//    MAP_UART_transmitData(EUSCI_A0_BASE, '\r');
//    MAP_UART_transmitData(EUSCI_A0_BASE, '\n');

    if(position > 8200) {
        while(1) {}
    }

    calculateTime(0, 0);

    position = 0;
}

