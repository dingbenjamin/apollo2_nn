################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
CMSIS/DSP_Lib/Source/CommonTables/arm_common_tables.obj: ../CMSIS/DSP_Lib/Source/CommonTables/arm_common_tables.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/CommonTables/arm_common_tables.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/CommonTables" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/CommonTables/arm_const_structs.obj: ../CMSIS/DSP_Lib/Source/CommonTables/arm_const_structs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/CommonTables/arm_const_structs.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/CommonTables" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


