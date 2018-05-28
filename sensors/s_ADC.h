/*
 * ADC.h
 *
 *  Created on: 02. Dez. 2016
 *      Author: Michael
 */

#ifndef HEADER_ADC_H_
#define HEADER_ADC_H_

#include <stdbool.h>
#include <stdint.h>
#include "s_globals.h"

/*****************************************************************************
 * Function prototypes														 *
 *****************************************************************************/
void initADC(void);
void ADC_triggerConversion(void);
void ADC_getGSR(uint8_t *Addr);
void ADC_getAudio(uint8_t *Addr);

#endif /* HEADER_ADC_H_ */
