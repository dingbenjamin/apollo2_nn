################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
sensors/s_ADC.obj: ../sensors/s_ADC.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="sensors/s_ADC.d_raw" --obj_directory="sensors" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sensors/s_BLE.obj: ../sensors/s_BLE.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="sensors/s_BLE.d_raw" --obj_directory="sensors" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sensors/s_BodyComm.obj: ../sensors/s_BodyComm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="sensors/s_BodyComm.d_raw" --obj_directory="sensors" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sensors/s_I2C.obj: ../sensors/s_I2C.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="sensors/s_I2C.d_raw" --obj_directory="sensors" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sensors/s_SPI.obj: ../sensors/s_SPI.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="sensors/s_SPI.d_raw" --obj_directory="sensors" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sensors/s_UART.obj: ../sensors/s_UART.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="sensors/s_UART.d_raw" --obj_directory="sensors" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sensors/s_processing.obj: ../sensors/s_processing.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="sensors/s_processing.d_raw" --obj_directory="sensors" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sensors/s_startup.obj: ../sensors/s_startup.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="sensors/s_startup.d_raw" --obj_directory="sensors" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


