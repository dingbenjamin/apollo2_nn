cmake_minimum_required(VERSION 3.8)
project(apollo2_nn C)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        extraction/extraction.c
        extraction/extraction.h
        extraction/loop.c
        extraction/loop.h
        fann/fann.c
        fann/fann.h
        fann/fann_conf.h
        fann/fann_net.h
        fann/fann_structs.h
        fann/test_data.h
        data.h
        main.c
        performance.c
        performance.h)

include_directories(
        .
        CMSIS/Include)

add_definitions(-DARM_MATH_CM4 -D__FPU_PRESENT=1)

add_library(CMSISModule STATIC
        CMSIS/Include/arm_common_tables.h
        CMSIS/Include/arm_const_structs.h
        CMSIS/Include/arm_math.h
        CMSIS/Include/cmsis_armcc.h
        CMSIS/Include/cmsis_armclang.h
        CMSIS/Include/cmsis_compiler.h
        CMSIS/Include/cmsis_gcc.h
        CMSIS/Include/cmsis_version.h
        CMSIS/Include/core_armv8mbl.h
        CMSIS/Include/core_armv8mml.h
        CMSIS/Include/core_cm0.h
        CMSIS/Include/core_cm0plus.h
        CMSIS/Include/core_cm23.h
        CMSIS/Include/core_cm3.h
        CMSIS/Include/core_cm33.h
        CMSIS/Include/core_cm4.h
        CMSIS/Include/core_cm7.h
        CMSIS/Include/core_sc000.h
        CMSIS/Include/core_sc300.h
        CMSIS/Include/mpu_armv7.h
        CMSIS/Include/tz_context.h)

set_target_properties(CMSISModule PROPERTIES LINKER_LANGUAGE C)

target_link_libraries(CMSISModule CMSIS/DSP_Lib/Lib/libarm_cortexM4lf_math.a)

add_executable(apollo2_nn ${SOURCE_FILES})

target_link_libraries(apollo2_nn LibsModule)