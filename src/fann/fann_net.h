#ifndef FANN_FANN_NET_H_
#define FANN_FANN_NET_H_

#include "fann.h"
#include "fann_structs.h"
#include "../definitions.h"

extern const enum fann_nettype_enum network_type;

const extern fann_neuron fann_neurons[NUM_NEURONS];

const extern fann_type fann_weights[NUM_WEIGHTS];

const extern fann_layer fann_layers[NUM_LAYERS];

#endif // FANN_FANN_NET_H_