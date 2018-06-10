#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#if defined TEST_STRESS && defined TEST_EPILEPSY
	#error Only one of stress/epilepsy/emotion tests can be defined
#endif

#if defined TEST_EMOTION && defined TEST_EPILEPSY
	#error Only one of stress/epilepsy/emotion tests can be defined
#endif
	
#if defined TEST_STRESS && defined TEST_EPILEPSY
	#error Only one of stress/epilepsy/emotion tests can be defined
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
	#define CONNECTION_RATE 1.000000
	#define NUM_WEIGHTS 3003
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

#ifdef TEST_EMOTION
	#include "../data/emotion_data.h"
	#define NUM_TEST_SAMPLES 227
	#define NUM_NEURONS 97
	#define MULTIPLIER 2
	#define DECIMAL_POINT 1
	#define NUM_INPUT 25
	#define NUM_OUTPUT 4
	#define NUM_LAYERS 5
	#define CONNECTION_RATE 1.000000
	#define NUM_WEIGHTS 1558
#endif

#ifdef TEST_FEATURE_EXTRACTION
	#include "../data/feature_extraction_data.h"
#endif

#endif // DEFINITIONS_H_