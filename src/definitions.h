#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#ifdef TEST_STRESS
	#ifdef TEST_EPILEPSY
		#error Only one of stress/epilepsy tests can be defined
	#endif
#endif

#ifdef TEST_STRESS
	#include "../data/stress_data.h"
	#define NUM_TEST_SAMPLES 683
	#define NUM_NEURONS 112
	#define MULTIPLIER 2
	#define DECIMAL_POINT 1
	#define NUM_INPUT 5
	#define NUM_OUTPUT 3
	#define NUM_LAYERS 4
	#define NUM_WEIGHTS 3003
	#define CONNECTION_RATE 1.000000
#endif

#ifdef TEST_EPILEPSY
	#include "../data/epilepsy_data.h"
	#define NUM_TEST_SAMPLES 100
	#define NUM_NEURONS 234
	#define MULTIPLIER 2
	#define DECIMAL_POINT 1
	#define NUM_INPUT 178
	#define NUM_OUTPUT 2
	#define NUM_LAYERS 4
	#define CONNECTION_RATE 1.000000
	#define NUM_WEIGHTS 7592
#endif

#ifdef TEST_FEATURE_EXTRACTION
	#include "../data/feature_extraction_data.h"
#endif

#endif // DEFINITIONS_H_