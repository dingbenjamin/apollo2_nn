################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_f32.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q15.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q31.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q7.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_f32.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q15.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q31.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q7.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_f32.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q15.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q31.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q7.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_f32.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q15.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q31.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q7.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_f32.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q15.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q31.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q7.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_f32.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q15.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q31.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q7.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_f32.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q15.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q31.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q7.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q15.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q31.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q7.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_f32.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q15.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q31.c \
../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q7.c 

C_DEPS += \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_f32.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q15.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q31.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q7.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_f32.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q15.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q31.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q7.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_f32.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q15.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q31.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q7.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_f32.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q15.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q31.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q7.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_f32.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q15.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q31.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q7.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_f32.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q15.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q31.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q7.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_f32.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q15.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q31.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q7.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q15.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q31.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q7.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_f32.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q15.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q31.d \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q7.d 

OBJS += \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_f32.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q15.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q31.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q7.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_f32.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q15.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q31.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q7.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_f32.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q15.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q31.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q7.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_f32.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q15.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q31.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q7.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_f32.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q15.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q31.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q7.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_f32.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q15.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q31.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q7.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_f32.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q15.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q31.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q7.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q15.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q31.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q7.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_f32.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q15.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q31.obj \
./CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q7.obj 

OBJS__QUOTED += \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_abs_f32.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_abs_q15.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_abs_q31.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_abs_q7.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_add_f32.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_add_q15.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_add_q31.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_add_q7.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_dot_prod_f32.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_dot_prod_q15.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_dot_prod_q31.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_dot_prod_q7.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_mult_f32.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_mult_q15.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_mult_q31.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_mult_q7.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_negate_f32.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_negate_q15.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_negate_q31.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_negate_q7.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_offset_f32.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_offset_q15.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_offset_q31.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_offset_q7.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_scale_f32.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_scale_q15.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_scale_q31.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_scale_q7.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_shift_q15.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_shift_q31.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_shift_q7.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_sub_f32.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_sub_q15.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_sub_q31.obj" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_sub_q7.obj" 

C_DEPS__QUOTED += \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_abs_f32.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_abs_q15.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_abs_q31.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_abs_q7.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_add_f32.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_add_q15.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_add_q31.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_add_q7.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_dot_prod_f32.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_dot_prod_q15.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_dot_prod_q31.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_dot_prod_q7.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_mult_f32.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_mult_q15.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_mult_q31.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_mult_q7.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_negate_f32.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_negate_q15.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_negate_q31.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_negate_q7.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_offset_f32.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_offset_q15.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_offset_q31.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_offset_q7.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_scale_f32.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_scale_q15.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_scale_q31.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_scale_q7.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_shift_q15.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_shift_q31.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_shift_q7.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_sub_f32.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_sub_q15.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_sub_q31.d" \
"CMSIS\DSP_Lib\Source\BasicMathFunctions\arm_sub_q7.d" 

C_SRCS__QUOTED += \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_f32.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q15.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q31.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_abs_q7.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_f32.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q15.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q31.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_add_q7.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_f32.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q15.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q31.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_q7.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_f32.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q15.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q31.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_mult_q7.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_f32.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q15.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q31.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_negate_q7.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_f32.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q15.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q31.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_offset_q7.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_f32.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q15.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q31.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q7.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q15.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q31.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_shift_q7.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_f32.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q15.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q31.c" \
"../CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_sub_q7.c" 


