#ifndef FANN_FANN_NET_H_
#define FANN_FANN_NET_H_

#include "fann.h"
#include "fann_structs.h"

extern const enum fann_nettype_enum network_type;

#ifdef TEST_EPILEPSY
	const extern fann_neuron fann_neurons[356];

	const extern fann_type fann_weights[15930];

	const extern fann_layer fann_layers[4];
#endif

#ifdef TEST_STRESS
	const extern fann_neuron fann_neurons[112]; 
	 
	const extern fann_type fann_weights[3003]; 

	const extern fann_layer fann_layers[4];
#endif	

#endif // FANN_FANN_NET_H