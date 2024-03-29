;******************************************************************************
;
;! @file startup_Apollo1.s
;!
;! @brief Definitions for Apollo1 interrupt handlers, the vector table, and the stack.
;
;******************************************************************************

;******************************************************************************
;
; Copyright (c) 2017, Ambiq Micro
; All rights reserved.
; 
; Redistribution and use in source and binary forms, with or without
; modification, are permitted provided that the following conditions are met:
; 
; 1. Redistributions of source code must retain the above copyright notice,
; this list of conditions and the following disclaimer.
; 
; 2. Redistributions in binary form must reproduce the above copyright
; notice, this list of conditions and the following disclaimer in the
; documentation and/or other materials provided with the distribution.
; 
; 3. Neither the name of the copyright holder nor the names of its
; contributors may be used to endorse or promote products derived from this
; software without specific prior written permission.
; 
; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
; IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
; ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
; LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
; CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
; SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
; INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
; CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
; ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
; POSSIBILITY OF SUCH DAMAGE.
;
; This is part of revision 0 of the AmbiqSuite Development Package.
;
;******************************************************************************

;******************************************************************************
;
; <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;************************************************************************
Stack   EQU     0x00000200

;******************************************************************************
;
; <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;
;******************************************************************************
Heap    EQU     0x00000000

;******************************************************************************
;
; Allocate space for the stack.
;
;******************************************************************************
        AREA    STACK, NOINIT, READWRITE, ALIGN=3
StackMem
        SPACE   Stack
__initial_sp

;******************************************************************************
;
; Allocate space for the heap.
;
;******************************************************************************
        AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
HeapMem
        SPACE   Heap
__heap_limit

;******************************************************************************
;
; Indicate that the code in this file preserves 8-byte alignment of the stack.
;
;******************************************************************************
        PRESERVE8

;******************************************************************************
;
; Place code into the reset code section.
;
;******************************************************************************
        AREA    RESET, CODE, READONLY
        THUMB

;******************************************************************************
;
; The vector table.
;
;******************************************************************************
        EXPORT  __Vectors
__Vectors
        DCD     StackMem + Stack            ; Top of Stack
        DCD     Reset_Handler               ; Reset Handler
        DCD     am_nmi_isr                  ; NMI Handler
        DCD     am_fault_isr                ; Hard Fault Handler
        DCD     am_mpufault_isr             ; The MPU fault handler
        DCD     am_busfault_isr             ; The bus fault handler
        DCD     am_usagefault_isr           ; The usage fault handler
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     am_svcall_isr               ; SVCall handler
        DCD     am_debugmon_isr             ; Debug monitor handler
        DCD     0                           ; Reserved
        DCD     am_pendsv_isr               ; The PendSV handler
        DCD     am_systick_isr              ; The SysTick handler

        ; Peripheral Interrupts
        DCD     am_brownout_isr             ;  0: Reserved
        DCD     am_watchdog_isr             ;  1: Reserved
        DCD     am_clkgen_isr               ;  2: CLKGEN
        DCD     am_vcomp_isr                ;  3: Voltage Comparator
        DCD     am_ioslave_ios_isr          ;  4: I/O Slave general
        DCD     am_ioslave_acc_isr          ;  5: I/O Slave access
        DCD     am_iomaster0_isr            ;  6: I/O Master 0
        DCD     am_iomaster1_isr            ;  7: I/O Master 1
        DCD     am_adc_isr                  ;  8: Reserved
        DCD     am_gpio_isr                 ;  9: GPIO
        DCD     am_ctimer_isr               ; 10: CTIMER
        DCD     am_uart_isr                 ; 11: UART

__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

;******************************************************************************
;
; This is the code that gets called when the processor first starts execution
; following a reset event.
;
;******************************************************************************
Reset_Handler   PROC
                EXPORT  Reset_Handler               [WEAK]
                IMPORT  __main

                ; Enable the FPU.
                MOVW    R0, #0xED88
                MOVT    R0, #0xE000
                LDR     R1, [R0]
                ORR     R1, #0x00F00000
                STR     R1, [R0]
                DSB
                ISB

                ; Branch to main.
                LDR     R0, =__main
                BX      R0

                ENDP

;******************************************************************************
;
; Weak Exception Handlers.
;
;******************************************************************************
am_nmi_isr      PROC
                EXPORT  am_nmi_isr                  [WEAK]
                B       .
                ENDP
am_fault_isr\
                PROC
                EXPORT  am_fault_isr                [WEAK]
                B       .
                ENDP
am_memmanage_isr\
                PROC
                EXPORT  am_memmanage_isr            [WEAK]
                B       .
                ENDP
am_mpufault_isr\
                PROC
                EXPORT  am_mpufault_isr             [WEAK]
                B       .
                ENDP
am_busfault_isr\
                PROC
                EXPORT  am_busfault_isr             [WEAK]
                B       .
                ENDP
am_usagefault_isr\
                PROC
                EXPORT  am_usagefault_isr           [WEAK]
                B       .
                ENDP
am_default_isr\
                PROC
                EXPORT  am_svcall_isr               [WEAK]
                EXPORT  am_debugmon_isr             [WEAK]
                EXPORT  am_pendsv_isr               [WEAK]
                EXPORT  am_systick_isr              [WEAK]
                EXPORT  am_brownout_isr             [WEAK]
                EXPORT  am_adc_isr                  [WEAK]
                EXPORT  am_watchdog_isr             [WEAK]
                EXPORT  am_clkgen_isr               [WEAK]
                EXPORT  am_vcomp_isr                [WEAK]
                EXPORT  am_ioslave_ios_isr          [WEAK]
                EXPORT  am_ioslave_acc_isr          [WEAK]
                EXPORT  am_iomaster0_isr            [WEAK]
                EXPORT  am_iomaster1_isr            [WEAK]
                EXPORT  am_gpio_isr                 [WEAK]
                EXPORT  am_ctimer_isr               [WEAK]
                EXPORT  am_uart_isr                 [WEAK]

am_svcall_isr
am_debugmon_isr
am_pendsv_isr
am_systick_isr
am_brownout_isr
am_adc_isr
am_watchdog_isr
am_clkgen_isr
am_vcomp_isr
am_ioslave_ios_isr
am_ioslave_acc_isr
am_iomaster0_isr
am_iomaster1_isr
am_gpio_isr
am_ctimer_isr
am_uart_isr

                ; all device interrupts go here unless the weak label is over
                ; ridden in the linker hard spin so the debugger will know it
                ; was an unhandled interrupt request a come-from-buffer or
                ; instruction trace hardware would sure be nice if you get here
                B       .

                ENDP

;******************************************************************************
;
; Align the end of the section.
;
;******************************************************************************
                ALIGN

;******************************************************************************
;
; Initialization of the heap and stack.
;
;******************************************************************************
                AREA    |.text|, CODE, READONLY

;******************************************************************************
;
; User Initial Stack & Heap.
;
;******************************************************************************
    IF :DEF: __MICROLIB
        EXPORT  __initial_sp
        EXPORT  __heap_base
        EXPORT  __heap_limit
    ELSE
        IMPORT  __use_two_region_memory
        EXPORT  __user_initial_stackheap
__user_initial_stackheap PROC
        LDR     R0, =HeapMem
        LDR     R1, =(StackMem + Stack)
        LDR     R2, =(HeapMem + Heap)
        LDR     R3, =StackMem
        BX      LR

        ENDP

    ENDIF

;******************************************************************************
;
; Align the end of the section.
;
;******************************************************************************
                ALIGN

;******************************************************************************
;
; All Done
;
;******************************************************************************
                END

