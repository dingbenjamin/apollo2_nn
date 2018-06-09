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
#include "fann/fann_structs.h"
#include "fann/fann_net.h"
#include "apollo1.h"
#include "am_mcu_apollo.h"
#include "am_hal_gpio.h"
#include "am_bsp.h"
#include "am_util.h"

#define NUM_SAMPLES 683
#define NUM_FEATURES 5
#define NUM_CLASSES 3
#define NUM_NEURONS 112
#define ACTIVATION_FUNCTION FANN_SIGMOID_SYMMETRIC_STEPWISE
#define TIMING_SEPARATOR_TOGGLES 10000

#define GPIO_TIMING_PIN_1 34
#define GPIO_TIMING_PIN_2 35

#define TEST_STRESS
#define TEST_EPILEPSY
//#define TEST_FEATURE_EXTRACTION

#ifdef TEST_STRESS
	#include "../data/stress_data.h"
#endif

#ifdef TEST_EPILEPSY
	#include "../data/epilepsy_data.h"
#endif

#ifdef TEST_FEATURE_EXTRACTION
	#include "../data/feature_extraction_data.h"
#endif

void timing_separator() {
	int i;
	for (i = 0; i < TIMING_SEPARATOR_TOGGLES; i++) {
		am_hal_gpio_out_bit_toggle(GPIO_TIMING_PIN_1);
		am_hal_gpio_out_bit_toggle(GPIO_TIMING_PIN_2);
  }
	am_hal_gpio_out_bit_clear(GPIO_TIMING_PIN_1);
	am_hal_gpio_out_bit_clear(GPIO_TIMING_PIN_2);
}

void set_neuron_activation_function(enum fann_activationfunc_enum activation) {
	int i;
	for (i = 0; i < NUM_NEURONS; i++) {
		if (fann_neurons[i].activation_function != FANN_LINEAR) {
			fann_neurons[i].activation_function = activation;
		}
	}
}

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

void test_stress_fann(void) {
	#ifdef TEST_STRESS
		int t;
		int corr = 0;
		float *res;
		
		// Start timing
		am_hal_gpio_out_bit_set(GPIO_TIMING_PIN_1);
		
		for (t = 0; t < NUM_SAMPLES; t++) {
			res = fann_run(&test_stress_data_input[t * NUM_FEATURES]);
			if (max_index(res, NUM_CLASSES) == test_stress_data_output[t]) {
				++corr;
			}
		}
		
		// End Timing
		am_hal_gpio_out_bit_clear(GPIO_TIMING_PIN_1);

		volatile float acc = 100.0 * corr / (float)NUM_SAMPLES;
		
		am_bsp_debug_printf_enable();
		am_util_stdio_printf("Accuracy: %.4f%%\n", acc);
		am_util_stdio_printf("See external measurement for timing");
	#else
		am_util_stdio_printf("Test skipped");
	#endif
}


void test_feature_extraction(void) {
	#ifdef TEST_FEATURE_EXTRACTION
		int i, t, secg, sgsr;
		float f[8];
		int mtime = 0;

		// Start timing pin 1
		am_hal_gpio_out_bit_set(GPIO_TIMING_PIN_1);
		resetExtraction(sgsr, mtime);
		for (t = 0; t < 3; ++t) {
			for (i = 0; i < 1024; i = i + 3) {
				int i1 = data[i];
				int i2 = data[i + 1];
				int i3 = data[i + 2];
				am_hal_gpio_out_bit_set(GPIO_TIMING_PIN_2); // Start timing pin 2
				sgsr = smoothgsr(i3);
				secg = smoothecg(i1, i2);
				gsrdetection(sgsr, mtime);
				peakdetection(secg, i1, i2, mtime);
				++mtime;
				am_hal_gpio_out_bit_clear(GPIO_TIMING_PIN_1); // End timing pin 2
			}
		}
		am_hal_gpio_out_bit_clear(GPIO_TIMING_PIN_1); // Mark timing pin 1
		extractfeatures2(mtime, f);
		am_hal_gpio_out_bit_set(GPIO_TIMING_PIN_1); // Mark timing pin 1
		float *s = fann_run(f);
		am_util_stdio_printf("Accuracy: %.4f%%\n", s);
		mtime = 0;
		am_hal_gpio_out_bit_clear(GPIO_TIMING_PIN_1); // End timing pin 1
		am_util_stdio_printf("See external measurement for timing");
	#else
		am_util_stdio_printf("Test skipped");
	#endif
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
	// Initialise the timing output GPIO pin
	// Max frequency for GPIO toggle is 3.7MHz which is approx 135ns
	// This is suitable for most microsecond scale measurements
	//
	am_hal_gpio_pin_config(GPIO_TIMING_PIN_1, AM_HAL_GPIO_OUTPUT)
	am_hal_gpio_out_enable_bit_set(GPIO_TIMING_PIN_1);
	am_hal_gpio_pin_config(GPIO_TIMING_PIN_2, AM_HAL_GPIO_OUTPUT)
	am_hal_gpio_out_enable_bit_set(GPIO_TIMING_PIN_2);

	//
	// Clear the terminal and print the banner.
	//
	am_util_stdio_terminal_clear();
	am_util_stdio_printf("apollo2_nn\n");
	am_util_stdio_printf("Performs tests of FANN library on target platform\n\n");\
	
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
	
	// Test classification of 683 points
	am_util_stdio_printf("\nSTART: test_stress_fann\n");
	set_neuron_activation_function(ACTIVATION_FUNCTION);
	test_stress_fann();
	am_util_stdio_printf("\nEND: test_stress_fann\n");
	
	am_util_stdio_printf("\n");
	timing_separator();
	
	// Test feature extraction of data
	am_util_stdio_printf("\nSTART: test_feature_extraction\n");
	test_feature_extraction();
	am_util_stdio_printf("\nEND:test_feature_extraction\n");
	
	am_util_stdio_printf("\n");
	
	am_util_stdio_printf("\nTests complete\n");
	timing_separator();
	
	am_bsp_debug_printf_disable();
	while(1) {
		// Do nothing
	}
}
