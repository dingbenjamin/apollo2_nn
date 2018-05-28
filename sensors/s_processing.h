/*
 * processing.h
 *
 *  Created on: 03. Dez. 2016
 *      Author: Michael
 */

#ifndef HEADER_PROCESSING_H_
#define HEADER_PROCESSING_H_

#include <stdbool.h>
#include <string.h>
#include "s_BLE.h"
#include "s_BodyComm.h"
#include "s_globals.h"
#include "s_I2C.h"
#include "s_SPI.h"

/*****************************************************************************
 * Constants																 *
 *****************************************************************************/

/*****************************************************************************
 * Function prototypes														 *
 *****************************************************************************/
void checkCommand(char *CMD, uint8_t size);


#endif /* HEADER_PROCESSING_H_ */
