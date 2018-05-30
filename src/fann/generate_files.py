import sys
import datetime
from math import log

if len(sys.argv) != 2:
    print("Missing argument for filename that should be converted. For example xor_fixed or xor_float!")
    exit(-1)

fname = sys.argv[1].split(".")[0]

try:
    netF = open(fname + '.net', 'r')
    # find out wether it's a fixed or float version
    fann = {}
    firstL = netF.readline()
    fann["nettype"] = "float"
    if "FIX" in firstL:
        print("nettype: fixed")
        fann["nettype"] = "int"
    else:
        print("nettype: float")


    file = netF.readlines()
    for line in file:
        parts = line.strip('\n').split('=')

        # if it is not split then we have an invalid line without an '='
        if(len(parts) != 2):
            continue

        # neuron and connection data have specifiers we need to remove
        if(len(parts[0].split(" ")) > 1):
            parts[0] = parts[0].split(" ")[0]
        
        # store all variables in dictionary
        fann[parts[0]] = parts[1]

    # currently no networks with a connection_rate below 1 are supported
    if float(fann["connection_rate"]) < 1.0:
        print("Currently no networks with a connection_rate below 1.0 are supported")
        exit(-1)

    # reformat neurons and connections
    fann["neurons"] = fann["neurons"].strip("()\r\n ").split(") (")
    fann["connections"] = fann["connections"].strip("()\r\n ").split(") (")

    tot_connections = 0
    fann["generated_neurons"] = []
    for neuron in fann["neurons"]:
        neuron = neuron.split(', ')

        num_inputs = neuron[0]
        activation_function = neuron[1]
        activation_steepness = neuron[2]

        first_connection = tot_connections
        last_connection = first_connection + int(num_inputs)

        fann["generated_neurons"].append("{" + ', '.join((str(first_connection), str(last_connection), activation_steepness, activation_function)) + "}")

        tot_connections = last_connection

    if tot_connections != len(fann["connections"]):
        print("ERROR: tot_connections != len(connections)")
        print(tot_connections)
        print(len(fann["connections"]))
        exit(-1)

    fann["generated_connections"] = []
    for connection in fann["connections"]:
        connection = connection.split(", ")
        fann["generated_connections"].append(connection[1])

    fann["generated_layers"] = []
    layer_num = 0
    fann['layer_sizes'] = fann['layer_sizes'].strip()
    for layer in fann['layer_sizes'].split(' '):
        fann["generated_layers"].append('{' + str(layer_num) + ', ' + str(layer_num + int(layer)) + '}')
        layer_num = layer_num + int(layer)

    if "decimal_point" not in fann:
        fann['decimal_point'] = "1"

    fann["multiplier"] = 1 << int(fann["decimal_point"])
        
    fann["num_input"] = str(int(fann['layer_sizes'].split(' ')[0]) - 1)
    fann["num_output"] = str(int(fann['layer_sizes'].strip(' ').split(' ')[-1]) - 1)

    # calculate sigmoid functions
    multiplier = int(fann["multiplier"])
    precalc_fixed = {}
    precalc_fixed["SIGMOID_RESULTS_0"] = max(int(multiplier / 200.0 + 0.5), 1)
    precalc_fixed["SIGMOID_RESULTS_1"] = max(int(multiplier / 20.0 + 0.5), 1)
    precalc_fixed["SIGMOID_RESULTS_2"] = max(int(multiplier / 4.0 + 0.5), 1)
    precalc_fixed["SIGMOID_RESULTS_3"] = min(multiplier - int(multiplier / 4.0 + 0.5), multiplier - 1)
    precalc_fixed["SIGMOID_RESULTS_4"] = min(multiplier - int(multiplier / 20.0 + 0.5), multiplier - 1)
    precalc_fixed["SIGMOID_RESULTS_5"] = min(multiplier - int(multiplier / 200.0 + 0.5), multiplier - 1)

    precalc_fixed["SIGMOID_SYMMETRIC_RESULTS_0"] = max(int((multiplier / 100.0) - multiplier - 0.5), int(1 - multiplier))
    precalc_fixed["SIGMOID_SYMMETRIC_RESULTS_1"] = max(int((multiplier / 10.0) - multiplier - 0.5), int(1 - multiplier))
    precalc_fixed["SIGMOID_SYMMETRIC_RESULTS_2"] = max(int((multiplier / 2.0) - multiplier - 0.5), int(1 - multiplier))
    precalc_fixed["SIGMOID_SYMMETRIC_RESULTS_3"] = min(multiplier - int(multiplier / 2.0 + 0.5), multiplier - 1)
    precalc_fixed["SIGMOID_SYMMETRIC_RESULTS_4"] = min(multiplier - int(multiplier / 10.0 + 0.5), multiplier - 1)
    precalc_fixed["SIGMOID_SYMMETRIC_RESULTS_5"] = min(multiplier - int(multiplier / 100.0 + 0.5), multiplier - 1)

    for i in range(0, 6):
        precalc_fixed["SIGMOID_VALUES_" + str(i)] = int(((log(multiplier / float(precalc_fixed["SIGMOID_RESULTS_" + str(i)]) - 1) * float(multiplier)) / -2.0) * float(multiplier))
        precalc_fixed["SIGMOID_SYMMETRIC_VALUES_" + str(i)] = int(((log((multiplier - float(precalc_fixed["SIGMOID_SYMMETRIC_RESULTS_" + str(i)])) / float(precalc_fixed["SIGMOID_SYMMETRIC_RESULTS_" + str(i)] + multiplier)) * float(multiplier)) / -2.0) * float(multiplier))

    # generate file contents for fann_conf.h
    saveString = '#ifndef FANN_FANN_CONF_H_\n'
    saveString = saveString + '#define FANN_FANN_CONF_H_\n\n'

    if fann["nettype"] == "int":
        saveString = saveString + '#define FIXEDFANN\n\n'

    for x in precalc_fixed:
        saveString = saveString + '#define ' + x + ' ' + str(precalc_fixed[x]) + '\n'

    saveString = saveString + '\n#define NUM_NEURONS ' + str(len(fann["generated_neurons"])) + '\n'
    saveString = saveString + '#define MULTIPLIER ' + str(fann["multiplier"]) + '\n'
    saveString = saveString + '#define DECIMAL_POINT ' + fann["decimal_point"] + '\n'
    saveString = saveString + '#define NUM_INPUT ' + fann["num_input"] + '\n'
    saveString = saveString + '#define NUM_OUTPUT ' + fann["num_output"] + '\n'
    saveString = saveString + '#define NUM_LAYERS ' + str(len(fann["generated_layers"])) + '\n'
    saveString = saveString + '#define CONNECTION_RATE ' + fann["connection_rate"] + '\n\n'

    saveString = saveString + '\n#endif // FANN_FANN_CONF_H_\n'

    try:
        FW = open('fann_conf.h', "w")
        FW.write(saveString)
        FW.close()
    except IOError:
        print("Could not open write fann_conf.h")
        exit(1)

    # generate file contents for fann_net.h
    saveString = '#ifndef FANN_FANN_NET_H_\n'
    saveString = saveString + '#define FANN_FANN_NET_H_\n\n'

    saveString = saveString + 'const enum fann_nettype_enum network_type = ' + fann["network_type"] + ';\n\n'
    saveString = saveString + 'const fann_neuron fann_neurons[' + str(len(fann["generated_neurons"])) + '] = {' + ', '.join(fann["generated_neurons"]) + '};\n\n'
    saveString = saveString + 'const fann_type fann_weights[' + str(len(fann["generated_connections"])) + '] = {' + ', '.join(fann["generated_connections"]) + '};\n\n'
    saveString = saveString + 'const fann_layer fann_layers[' + str(len(fann["generated_layers"])) + '] = {' + ', '.join(fann["generated_layers"]) + '};\n\n'

    saveString = saveString + '\n#endif // FANN_FANN_NET_H_\n'

    try:
        FW = open('fann_net.h', "w")
        FW.write(saveString)
        FW.close()
    except IOError:
        print("Could not open write fann_net.h")
        exit(1)

    print("generated fann_net.h")
    print("generated fann_conf.h")
    print("NETWORK converted. Please copy the files and/or recompile")
except IOError:
    print("Could not open " + fname + ".net")
    print("Failed to generate network from file")



try:
    dataF = open(fname + '.data', 'r')
    # generate test data file
    firstLine = dataF.readline().strip(' \r\n').split(' ')
    numSamples = int(firstLine[0])
    numInputs = int(firstLine[1])
    numOutputs = int(firstLine[2])

    contents = dataF.readlines()

    ins = []
    outs = []
    count = 0
    for line in contents:
        line = line.strip(' \r\n').split(' ')
        
        if count % 2:
            # outputs
            if fann["nettype"] == "int":
                line = map(int, line)
            else:
                line = map(float, line)
            outs.append(str(line.index(max(line))))
        else:
            # inputs
            ins.extend(line[0:numInputs])

        count = count + 1

    print("TEST data extracted")

    saveString = '#ifndef FANN_FANN_TEST_DATA_H_\n'
    saveString = saveString + '#define FANN_FANN_TEST_DATA_H_\n\n'
    saveString = saveString + "fann_type test_data_input[" + str(len(ins)) + "] = {" + ', '.join(ins) + "};\n\n"
    saveString =  saveString + "const int test_data_output[" + str(len(outs)) + "] = {" + ', '.join(outs) + "};\n\n"
    saveString = saveString + '\n#endif // FANN_FANN_TEST_DATA_H_\n'

    try:
        FW = open("test_data.h", "w")
        FW.write(saveString)
        FW.close()
    except IOError:
        print("Could not create test_data.h")
        exit(1)

    print("generated test_data.h")
except IOError:
    print("Could not open " + fname + ".data or ")
    print("Failed to generate test_data from file")
    exit(-1)