################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_f32.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_f32.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_f32.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q15.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q15.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q15.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q31.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q31.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q31.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q7.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q7.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q7.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_f32.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_f32.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_f32.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q15.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q15.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q15.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q31.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q31.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q31.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q7.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q7.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q7.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_f32.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_f32.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_f32.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q15.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q15.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q15.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q31.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q31.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q31.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q7.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q7.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q7.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_f32.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_f32.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_f32.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q15.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q15.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q15.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q31.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q31.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q31.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q7.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q7.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q7.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_f32.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_f32.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_f32.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q15.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q15.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q15.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q31.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q31.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q31.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q7.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q7.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q7.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_f32.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_f32.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_f32.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q15.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q15.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q15.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q31.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q31.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q31.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q7.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q7.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q7.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_f32.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_f32.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_f32.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q15.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q15.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q15.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q31.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q31.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q31.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q7.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q7.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q7.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q15.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q15.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q15.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q31.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q31.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q31.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q7.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q7.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q7.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_f32.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_f32.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_f32.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q15.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q15.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q15.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q31.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q31.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q31.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q7.obj: ../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q7.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O4 --opt_for_speed=5 --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432/CMSIS/Include" --include_path="C:/Users/Ben/Documents/src/eth-semester-thesis-2-master/code/firmware_msp432" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source" --include_path="C:/ti/simplelink_msp432p4_sdk_1_60_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.6.0.STS/include" --define=__FPU_PRESENT=1 --define=__TI_ARM__ --define=ARM_MATH_CM4 --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q7.d_raw" --obj_directory="CMSIS/DSP_Lib/Source/BasicMathFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


