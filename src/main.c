/******************************************************************************
 * FANN Implementation on Apollo2 MCU
 *
 * Author: Philipp MAYER, Michael PRITZ, Ferdinand VON HAGEN
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
#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_util.h"

#define NUM_SAMPLES 100
#define NUM_FEATURES 8
#define NUM_CLASSES 3

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
  int corr = 0;
  float *res;
  for (t = 0; t < NUM_SAMPLES; t++) {
    res = fann_run(&test_data_input[t * NUM_FEATURES]);
    if (max_index(res, NUM_CLASSES) == test_data_output[t]) {
      ++corr;
    }
  }

  volatile float acc = corr / NUM_SAMPLES;
	
	am_bsp_debug_printf_enable();
	am_util_stdio_printf("Accuracy: %.2f", acc);
	am_bsp_debug_printf_disable();
}

void setup(void) {
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
	am_util_stdio_printf("apollo2_nn\n");
	am_util_stdio_printf("\tPerforms tests of FANN library on target platform\n");\
	
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
}
	

int main(void) { 
	setup();
	test();
	while(1) {
		// Do nothing
	}
}
