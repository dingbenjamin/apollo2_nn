/*
 * initBoard.h
 *
 *  Created on: 04. Nov. 2016
 *      Author: Michael
 */

#ifndef INITBOARD_H_
#define INITBOARD_H_

#include "s_globals.h"

/*****************************************************************************
 * Constants																 *
 *****************************************************************************/


/*****************************************************************************
 * Function prototypes														 *
 *****************************************************************************/
void initGPIO(void);
void initClockSources(void);
void initSysTick(void);
void initTimer32(void);
void initGlobals(void);


#endif /* INITBOARD_H_ */
