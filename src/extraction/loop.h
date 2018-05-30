/*
 * loop.h
 *
 *  Created on: Oct 6, 2017
 *      Author: ferdinandvonhagen
 */

#ifndef EXTRACTION_LOOP_H_
#define EXTRACTION_LOOP_H_

#include <stdint.h>

void loop(
    int * pSrc,
    uint32_t blockSize,
    int * nn50res,
    int * meanrrres,
    int * rmssdres);


#endif /* EXTRACTION_LOOP_H_ */
