/*
* fann.h
*
*  Created on: Sep 5, 2017
*      Author: ferdinandvonhagen
*/

#ifndef FANN_FANN_H_
#define FANN_FANN_H_

#ifdef FIXEDFANN
typedef int fann_type;
#else
typedef float fann_type;
#endif

/* Function: fann_run
    Will run input through the neural network, returning an array of outputs, the number of which being
    equal to the number of neurons in the output layer.

    See also:
        <fann_test>

    This function appears in FANN >= 1.0.0.
*/
// __attribute__((ramfunc))
fann_type *fann_run(fann_type * input);


#endif /* FANN_FANN_H_ */
