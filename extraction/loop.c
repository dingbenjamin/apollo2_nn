/*
 * loop.c
 *
 *  Created on: Oct 6, 2017
 *      Author: ferdinandvonhagen
 *
 *      FROM CMSIS
 */

// NN50 detection

#include "loop.h"
#include <stdint.h>


void loop(
    int * pSrc,
    uint32_t blockSize,
    int * nn50res,
    int * meanrrres,
    int * rmssdres)
{
    int in;
    uint32_t blkCnt;                               /* loop counter */

    int lastrr = *pSrc;

    int nn50;
    int meanrr;
    int rmssd;


    /* Run the below code for Cortex-M4 and Cortex-M3 */

    /*loop Unrolling */
    blkCnt = blockSize >> 2u;

    /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
    ** a second loop below computes the remaining 1 to 3 samples. */
    while (blkCnt > 0u)
    {
        in = *pSrc++;
        if(abs(in - lastrr) > 6) {
            nn50 = nn50 + 1;
        }
        lastrr = in;
        meanrr += in;
        rmssd += in * in;

        in = *pSrc++;
        if(abs(in - lastrr) > 6) {
            nn50 = nn50 + 1;
        }
        lastrr = in;
        meanrr += in;
        rmssd += in * in;

        in = *pSrc++;
        if(abs(in - lastrr) > 6) {
            nn50 = nn50 + 1;
        }
        lastrr = in;
        meanrr += in;
        rmssd += in * in;

        in = *pSrc++;
        if(abs(in - lastrr) > 6) {
            nn50 = nn50 + 1;
        }
        lastrr = in;
        meanrr += in;
        rmssd += in * in;

        /* Decrement the loop counter */
        blkCnt--;
    }

    /* If the blockSize is not a multiple of 4, compute any remaining output samples here.
    ** No loop unrolling is used. */
    blkCnt = blockSize % 0x4u;

    while (blkCnt > 0u)
    {
        in = *pSrc++;
        if(abs(in - lastrr) > 6) {
            nn50 = nn50 + 1;
        }
        lastrr = in;
        meanrr += in;
        rmssd += in * in;

        /* Decrement the loop counter */
        blkCnt--;
    }

    /* Store the results in 16.48 format  */
    *nn50res = nn50;
    *meanrrres = meanrr;
    *rmssdres = rmssd;
}


