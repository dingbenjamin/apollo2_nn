///*
// * -------------------------------------------
// *    MSP432 DriverLib - v3_21_00_05
// * -------------------------------------------
// *
// * --COPYRIGHT--,BSD,BSD
// * Copyright (c) 2016, Texas Instruments Incorporated
// * All rights reserved.
// *
// * Redistribution and use in source and binary forms, with or without
// * modification, are permitted provided that the following conditions
// * are met:
// *
// * *  Redistributions of source code must retain the above copyright
// *    notice, this list of conditions and the following disclaimer.
// *
// * *  Redistributions in binary form must reproduce the above copyright
// *    notice, this list of conditions and the following disclaimer in the
// *    documentation and/or other materials provided with the distribution.
// *
// * *  Neither the name of Texas Instruments Incorporated nor the names of
// *    its contributors may be used to endorse or promote products derived
// *    from this software without specific prior written permission.
// *
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// * --/COPYRIGHT--*/

///******************************************************************************
// * MSP432 Emotion Tracker v1.0 Modified for Apollo2
// *
// * Description: tbd
// *
// * Author: Philipp MAYER, Michael PRITZ
// *
// * Modified By: Benjamin DING
// *******************************************************************************/

//#include <arm_math.h>
//#include <math.h>
//#include <stdbool.h>
//#include <stdint.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include "data.h"
//#include "extraction/extraction.h"
//#include "fann/fann.h"
//#include "fann/test_data.h"

//#define max(a, b)           \
//  ({                        \
//    __typeof__(a) _a = (a); \
//    __typeof__(b) _b = (b); \
//    _a > _b ? _a : _b;      \
//  })

//int max_index(float *a, int n) {
//  if (n <= 0) return -1;
//  int i, max_i = 0;
//  float max = a[0];
//  for (i = 1; i < n; ++i) {
//    if (a[i] > max) {
//      max = a[i];
//      max_i = i;
//    }
//  }
//  return max_i;
//}

//void test(void) {
////  init_sys();

//  int t;
//  int corr;
//  float *res;
////  GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN0);
//  for (t = 0; t < 800; t = t + 8) {
//    res = fann_run(&test_data_input[t]);

//    if (max_index(res, 3) == test_data_output[t / 8]) {
//      ++corr;
//    }
//  }
////  GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);

//  volatile float acc = corr / 100.0f;

////  while (1) {
////    MAP_PCM_gotoLPM4();
////  }
//}

//int main(void) { test(); }

//*****************************************************************************
//
//! @file clkout.c
//!
//! @brief Enables a clock source to clkout and then tracks it on an LED array.
//!
//! This example enables the LFRC to a clkout pin then uses GPIO polling to
//! track its rising edge and toggle an LED at 1 hertz.
//
//*****************************************************************************

//*****************************************************************************
//a
// Copyright (c) 2018, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// Third party software included in this distribution is subject to the
// additional license terms as defined in the /docs/licenses directory.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.12 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_util.h"

//*****************************************************************************
//
// Macro definitions
//
//*****************************************************************************
#define RISING_EDGE_COUNT   500     // Turn 500 Hz (LFRC/2) clkout into 1 Hz blinky

//*****************************************************************************
//
// Main function.
//
//*****************************************************************************
int
main(void)
{
    int32_t iRisingCount, iLEDcount;
    bool bNewClkout, bOldClkout;

    //
    // Set the clock frequency.
    //
    am_hal_clkgen_sysclk_select(AM_HAL_CLKGEN_SYSCLK_MAX);

    //
    // Set the default cache configuration
    //
    am_hal_cachectrl_enable(&am_hal_cachectrl_defaults);

    //
    // Configure the board for low power operation.
    //
    am_bsp_low_power_init();

    //
    // Initialize the printf interface for ITM/SWO output.
    //
    am_util_stdio_printf_init((am_util_stdio_print_char_t) am_bsp_itm_string_print);

    //
    // Initialize the SWO GPIO pin
    //
    am_bsp_pin_enable(ITM_SWO);

    //
    // Enable the ITM.
    //
    am_hal_itm_enable();

    //
    // Enable debug printf messages using ITM on SWO pin
    //
    am_bsp_debug_printf_enable();

    //
    // Clear the terminal and print the banner.
    //
    am_util_stdio_terminal_clear();
    am_util_stdio_printf("CLKOUT to LED Example\n");
    am_util_stdio_printf("\tWalks the board LEDs about once a second based on the CLKOUT "
                         "signal.\n");

    //
    // We are done printing. Disable debug printf messages on ITM.
    //
    am_bsp_debug_printf_disable();

    //
    // Clear the LED.
    //
    am_devices_led_array_init(am_bsp_psLEDs, AM_BSP_NUM_LEDS);

    //
    // Enable the LFRC.
    //
    am_hal_clkgen_osc_start(AM_HAL_CLKGEN_OSC_LFRC);

    //
    // Enable the clockout to the desired pin.
    // And make it readable on the pin with AM_HAL_GPIO_INPEN
    //
    am_hal_gpio_pin_config(AM_BSP_GPIO_CLKOUT_PIN,
                           (AM_BSP_GPIO_CFG_CLKOUT_PIN | AM_HAL_GPIO_INPEN));

    //
    // Initialize clkgen to output the selected clock.
    //
    am_hal_clkgen_clkout_enable(AM_HAL_CLKGEN_CLKOUT_CKSEL_LFRC_DIV2);

    //
    // Initialize LED 0 to on
    //
    am_devices_led_toggle(am_bsp_psLEDs, 0);
    iLEDcount = 1;      // LED 1 is next

    //
    // Initialize loop variables
    //
    iRisingCount = RISING_EDGE_COUNT;
    bOldClkout = false;

    //
    // Loop forever tracking the rising edge of CLKOUT.
    //
    while (1)
    {
        //
        // Grab new clock output value and look for a change.
        //
        bNewClkout = am_hal_gpio_input_bit_read(AM_BSP_GPIO_CLKOUT_PIN);

        //
        // Look for any change.
        //
        if ( bOldClkout != bNewClkout )
        {
            //
            // OK a change occurred.
            //
            bOldClkout = bNewClkout;

            //
            //  Was it rising or falling.
            //
            if ( bNewClkout )
            {
                //
                // It was rising so count them until time to act.
                //
                if (--iRisingCount < 0)
                {
                    //
                    // Act on the time out (walk the 4 LEDs)
                    //
                    am_devices_led_off(am_bsp_psLEDs, 0);
                    am_devices_led_off(am_bsp_psLEDs, 1);
                    am_devices_led_off(am_bsp_psLEDs, 2);
                    am_devices_led_off(am_bsp_psLEDs, 3);
                    am_devices_led_off(am_bsp_psLEDs, 4);
                    am_devices_led_on(am_bsp_psLEDs, iLEDcount);
                    iLEDcount++;
                    iLEDcount %= 5;

                    //
                    // Reset the rising edge count.
                    //
                    iRisingCount = RISING_EDGE_COUNT;
                }
            }
        }

    }

}