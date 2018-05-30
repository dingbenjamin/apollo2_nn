/*
 * -------------------------------------------
 *    MSP432 DriverLib - v3_21_00_05
 * -------------------------------------------
 *
 * --COPYRIGHT--,BSD,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

/******************************************************************************
 * MSP432 Emotion Tracker v1.0 Modified for Apollo2
 *
 * Description: tbd
 *
 * Author: Philipp MAYER, Michael PRITZ
 *
 * Modified By: Benjamin DING
 *******************************************************************************/

#include <arm_math.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "extraction/extraction.h"
#include "fann/fann.h"
#include "fann/test_data.h"
#include "apollo1.h"

#define max(a, b)           \
  ({                        \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a > _b ? _a : _b;      \
  })
	
#define EVB_LED0        34
#define EVB_LED1        33
#define EVB_LED2        28
#define EVB_LED3        26
#define EVB_LED4        25

//*****************************************************************************
//
// Set or clear an LED.
// The LEDs on the EVB are common anode (anodes tied high).
// Therefore, they are turned on when the GPIO is cleared.
// Likewise, they are turned off when the GPIO is set.
//
//*****************************************************************************
static void
LED_on(uint32_t ui32LED, bool bOn)
{
    uint32_t ui32Mask;

    if ( ui32LED <= 31 )
    {
        ui32Mask = 0x01 << (ui32LED - 0);

        if ( bOn )
        {
            GPIO->WTCA = ui32Mask;
        }
        else
        {
            GPIO->WTSA = ui32Mask;
        }
    }
    else if ( ui32LED <= 49 )
    {
        ui32Mask = 0x01 << (ui32LED - 32);

        if ( bOn )
        {
            GPIO->WTCB = ui32Mask;
        }
        else
        {
            GPIO->WTSB = ui32Mask;
        }
    }
    else
    {
        // ERROR.
        while (1);
    }

} // LED_on()
	
int max_index(float *a, int n) {
  if (n <= 0) return -1;
  int i, max_i = 0;
  float max = a[0];
  for (i = 1; i < n; ++i) {
    if (a[i] > max) {
      max = a[i];
      max_i = i;
    }
  }
  return max_i;
}

void test(void) {
  int t;
  int corr;
  float *res;
  for (t = 0; t < 800; t = t + 8) {
    res = fann_run(&test_data_input[t]);

    if (max_index(res, 3) == test_data_output[t / 8]) {
      ++corr;
    }
  }

  volatile float acc = corr / 100.0f;
}

int main(void) { 
	test();
	while(1) {
		// Do nothing
	}
}
