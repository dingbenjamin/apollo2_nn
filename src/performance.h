/*
 * performance.h
 *
 *  Created on: Sep 9, 2017
 *      Author: ferdinandvonhagen
 */

#ifndef PERFORMANCE_H_
#define PERFORMANCE_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

extern const char hexDigits[];
extern uint32_t position;
extern uint32_t timedV[8200];

#define startTime(comment) \
    timedV[position++] = 16777216 - (SysTick_getValue() & 0xFFFFFF) + 0xF000000 + ((comment & 0xF) << 28);

#define stopTime() \
    timedV[position++] = 16777216 - (SysTick_getValue() & 0xFFFFFF);

void calculateTimes(void);

#endif /* PERFORMANCE_H_ */
