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
#include "extraction/extraction.h"
#include "fann/fann.h"
#include "fann/test_data.h"
#include "apollo1.h"
#include "am_mcu_apollo.h"
#include "am_hal_gpio.h"
#include "am_bsp.h"
#include "am_util.h"

#define NUM_SAMPLES 683
#define NUM_FEATURES 5
#define NUM_CLASSES 3

#define GPIO_TIMING_PIN 20

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

// Used to toggle a GPIO pin for external timing measurements
// Max frequency for GPIO toggle is 3.7MHz which is approx 135ns
// This is suitable for most microsecond scale measurements
void time_gpio(void (*f)(), uint8_t pin_num) {
	// Initialise the timing output GPIO pin
	am_hal_gpio_pin_config(pin_num, AM_HAL_GPIO_OUTPUT)
	am_hal_gpio_out_enable_bit_set(pin_num);
	
	// Start timing
	am_hal_gpio_out_bit_set(pin_num);
	
	// Run the function
	f();
	
	// End timing
	am_hal_gpio_out_bit_clear(pin_num);
}	

void test_nn_acc(void) {
  int t;
  int corr = 0;
  float *res;
  for (t = 0; t < NUM_SAMPLES; t++) {
    res = fann_run(&test_data_input[t * NUM_FEATURES]);
    if (max_index(res, NUM_CLASSES) == test_data_output[t]) {
      ++corr;
    }
  }

  volatile float acc = 100.0 * corr / (float)NUM_SAMPLES;
	
	am_bsp_debug_printf_enable();
	am_util_stdio_printf("Accuracy: %.4f%%\n", acc);
}

void test_nn_timing(void) {
	int t;
  int corr = 0;
  float *res;
	for (t = 0; t < NUM_SAMPLES; t++) {
		res = fann_run(&test_data_input[t * NUM_FEATURES]);
		if (max_index(res, NUM_CLASSES) == test_data_output[t]) {
			++corr;
		}
	}
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
	am_util_stdio_printf("Performs tests of FANN library on target platform\n");\
	
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
	am_bsp_debug_printf_enable();
	
	// Test classification of 683 points
	am_util_stdio_printf("\ntest_nn_acc start\n");
	test_nn_acc();
	time_gpio(&test_nn_timing, GPIO_TIMING_PIN);
	am_util_stdio_printf("See external measurement for timing");
	am_util_stdio_printf("\ntest_nn_acc end\n");
	
	am_bsp_debug_printf_disable();
	while(1) {
		// Do nothing
	}
}
