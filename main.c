/*
 * -------------------------------------------
 *    MSP432 DriverLib - v3_21_00_05
 * -------------------------------------------
 *
 * --COPYRIGHT--,BSD,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/******************************************************************************
 * MSP432 Emotion Tracker v1.0 Modified for Apollo2
 *
 * Description: tbd
 *
 * Author: Philipp MAYER, Michael PRITZ
 *
 * Modified By: Benjamin DING
 *******************************************************************************/

#include <sensors/s_globals.h>

#define max(a, b)           \
  ({                        \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a > _b ? _a : _b;      \
  })

/* Standard Includes */
#include <arm_math.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "extraction/extraction.h"
#include "fann/fann.h"
#include "fann/test_data.h"

/* global variables */
int cnt = 0;
int cnt_aud = 0;
int cnt_gsr = 0;
int cnt_mot = 0;
uint32_t smclk;
uint32_t mclk;
uint32_t aclk;
uint32_t I2C_xferIndex;
volatile uint16_t T32_time;
volatile uint32_t T32_BCOMM;
volatile uint8_t BodyComm;
volatile char BLE_CMD[BLE_CMD_SIZE];
volatile uint8_t BLE_CMD_N;
volatile uint8_t I2C_TX[I2C_TX_BYTES];
volatile uint8_t I2C_RX[I2C_RX_BYTES];
volatile uint8_t I2C_recBytes;
volatile uint8_t SPI_RX_ECG[SPI_RX_BYTES];
volatile uint8_t SPI_RX_FRAM[SPI_RX_BYTES];
volatile uint8_t SPI_recBytesFRAM;
volatile uint8_t SPI_recBytesECG;
volatile uint16_t ADC_result[ADC_B_SIZE];
volatile uint32_t ECG_cnt;
// flags
volatile bool I2C_stopSent;
volatile bool ECG_DRDY;
volatile bool ADC_DRDY;
volatile bool SENS_STREAM;
volatile bool BLE_REC;
volatile bool FANN_CALC;
// FANN related
float FANN_AudioData[(12 * 12)] = {0};
float FANN_MotX[12] = {0};
float FANN_MotY[12] = {0};
float FANN_MotZ[12] = {0};
float meanX = 0;
float meanY = 0;
float meanZ = 0;
float meanA = 0;
float varX = 0;
float varY = 0;
float varZ = 0;
float varA = 0;

uint8_t BLE_TX[BLE_TX_SIZE] = {0};
uint8_t MotionData[12] = {0};
uint8_t MagData[6] = {0};
uint16_t GSRData[8] = {0};
uint32_t GSRtemp = 0;
uint8_t Status[22] = {0};
uint8_t Temp[2] = {0};
uint16_t i = 0;
uint8_t PKG_sent = 0;
uint8_t hi = 0;
uint8_t lo = 0;
uint32_t Loff = 0;
int16_t MOT_temp = 0;
uint16_t mtime = 0;
int feat[8];

int max_index(float *a, int n) {
  if (n <= 0) return -1;
  int i, max_i = 0;
  float max = a[0];
  for (i = 1; i < n; ++i) {
    if (a[i] > max) {
      max = a[i];
      max_i = i;
    }
  }
  return max_i;
}

void test2(void) {
  init_sys();

  int t;
  int corr;
  float *res;
  GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN0);
  for (t = 0; t < 800; t = t + 8) {
    res = fann_run(&test_data_input[t]);

    if (max_index(res, 3) == test_data_output[t / 8]) {
      ++corr;
    }
  }
  GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);

  volatile float acc = corr / 100.0f;

  while (1) {
    MAP_PCM_gotoLPM4();
  }
}

int main(void) { test2(); }

/*******************************************************************************
 * INTERRUPT ROUTINES                                                          *
 *******************************************************************************/
/*******************************************************************************
 * @fn      T32_INT1_IRQHandler                                                *
 *                                                                             *
 * @brief   Timer_32_1 interrupt                                               *
 *          counts in 1ms intervall                                            *
 *                                                                             *
 * @param   void                                                               *
 *                                                                             *
 * @return  void                                                               *
 *******************************************************************************/
void T32_INT1_IRQHandler(void) {
  MAP_Timer32_clearInterruptFlag(TIMER32_0_BASE);
  T32_time++;
}

/*******************************************************************************
 * @fn      T32_INT2_IRQHandler                                                *
 *                                                                             *
 * @brief   Timer_32_1 interrupt                                               *
 *          counts in 10us intervall    (for bit time measurement in body comm)*
 *          enabled in body comm routine                                       *
 *                                                                             *
 * @param   void                                                               *
 *                                                                             *
 * @return  void                                                               *
 *******************************************************************************/
void T32_INT2_IRQHandler(void) {
  MAP_Timer32_clearInterruptFlag(TIMER32_1_BASE);
  T32_BCOMM++;
}

/*******************************************************************************
 * @fn      PORT2_IRQHandler                                                   *
 *                                                                             *
 * @brief   ADS1292 DRDY interrupt P2.5, fires every 4ms                       *
 *                                                                             *
 * @param   void                                                               *
 *                                                                             *
 * @return  void                                                               *
 *******************************************************************************/
void PORT2_IRQHandler(void) {
  uint32_t status;

  status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
  MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, status);

  if (status & GPIO_PIN5) {
    SPI_recBytesECG = 0;
    ECG_DRDY = true;
    ECG_cnt++;
  }
}

/*******************************************************************************
 * @fn      ADC14_IRQHandler                                                   *
 *                                                                             *
 * @brief   ADC: Interrupt routine places result (GSR, Micro) in ADC-Buffer    *
 *                                                                             *
 * @param   void                                                               *
 *                                                                             *
 * @return  void                                                               *
 *******************************************************************************/
void ADC14_IRQHandler(void) {
  uint64_t status = MAP_ADC14_getEnabledInterruptStatus();
  MAP_ADC14_clearInterruptFlag(status);

  if (status & ADC_INT0) {
    /* ADC_result: 1st byte -> Micro, 2nd -> GSR */
    ADC_result[1] = MAP_ADC14_getResult(ADC_MEM0);
  }
}

/*******************************************************************************
 * @fn      EUSCIA0_IRQHandler                                                 *
 *                                                                             *
 * @brief   SPI: EUSCIA0 receive interrupt (FM25V10G)                          *
 *                                                                             *
 * @param   void                                                               *
 *                                                                             *
 * @return  void                                                               *
 *******************************************************************************/
void EUSCIA0_IRQHandler(void) {
  uint32_t status = MAP_SPI_getEnabledInterruptStatus(EUSCI_A0_BASE);  // uint8_t
  uint8_t TX = 0x00;

  MAP_SPI_clearInterruptFlag(EUSCI_A0_BASE, status);

  if (status & EUSCI_A_SPI_RECEIVE_INTERRUPT) {
    // while (!(MAP_SPI_getInterruptStatus(EUSCI_A0_BASE,
    // EUSCI_A_SPI_TRANSMIT_INTERRUPT)));
    if (SPI_recBytesFRAM < 9) {
      MAP_SPI_transmitData(EUSCI_A0_BASE, TX);
    }
    SPI_RX_FRAM[SPI_recBytesFRAM++] = MAP_SPI_receiveData(EUSCI_A0_BASE);
  }
}

/*******************************************************************************
 * @fn      EUSCIA1_IRQHandler                                                 *
 *                                                                             *
 * @brief   SPI: EUSCIA1 receive interrupt (ADS1292)                           *
 *                                                                             *
 * @param   void                                                               *
 *                                                                             *
 * @return  void                                                               *
 *******************************************************************************/
void EUSCIA1_IRQHandler(void) {
  uint32_t status = MAP_SPI_getEnabledInterruptStatus(EUSCI_A1_BASE);  // uint8_t

  MAP_SPI_clearInterruptFlag(EUSCI_A1_BASE, status);

  if (status & EUSCI_A_SPI_RECEIVE_INTERRUPT) {
    SPI_RX_ECG[SPI_recBytesECG++] = MAP_SPI_receiveData(EUSCI_A1_BASE);
  }
}

/*******************************************************************************
 * @fn      EUSCIA2_IRQHandler                                                 *
 *                                                                             *
 * @brief   UART: EUSCIA2 receive interrupt (CC2650)                           *
 *                                                                             *
 * @param   void                                                               *
 *                                                                             *
 * @return  void                                                               *
 *******************************************************************************/
void EUSCIA2_IRQHandler(void) {
  uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A2_BASE);

  MAP_UART_clearInterruptFlag(EUSCI_A2_BASE, status);

  if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG) {
    BLE_CMD[BLE_CMD_N] = MAP_UART_receiveData(EUSCI_A2_BASE);
    BLE_REC = true;
  }
}

/*******************************************************************************
 * @fn      EUSCIB0_IRQHandler                                                 *
 *                                                                             *
 * @brief   I2C: The repeated start and transmit/receive operations happen     *
 *          within this ISR.                                                   *
 *                                                                             *
 * @param   void                                                               *
 *                                                                             *
 * @return  void                                                               *
 *******************************************************************************/
void EUSCIB0_IRQHandler(void) {
  uint_fast16_t status;

  status = MAP_I2C_getEnabledInterruptStatus(EUSCI_B0_BASE);
  MAP_I2C_clearInterruptFlag(EUSCI_B0_BASE, status);

  /* If we reached the transmit interrupt, it means we are at index 1 of
   * the transmit buffer. When doing a repeated start, before we reach the
   * last byte we will need to change the mode to receive mode, set the start
   * condition send bit, and then load the final byte into the TXBUF.
   */
  if (status & EUSCI_B_I2C_TRANSMIT_INTERRUPT0) {
    if (I2C_2bytesCMD) {
      MAP_I2C_masterSendMultiByteNext(EUSCI_B0_BASE, I2C_TX[1]);
    }
    MAP_I2C_disableInterrupt(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0);
    MAP_I2C_setMode(EUSCI_B0_BASE, EUSCI_B_I2C_RECEIVE_MODE);
    I2C_xferIndex = 0;
    MAP_I2C_masterReceiveStart(EUSCI_B0_BASE);
    MAP_I2C_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_I2C_RECEIVE_INTERRUPT0);
  }

  /* Receives bytes into the receive buffer. If we have received all bytes,
   * send a STOP condition */
  if (status & EUSCI_B_I2C_RECEIVE_INTERRUPT0) {
    if (I2C_xferIndex == I2C_recBytes - 2) {
      MAP_I2C_masterReceiveMultiByteStop(EUSCI_B0_BASE);
      I2C_RX[I2C_xferIndex++] =
          MAP_I2C_masterReceiveMultiByteNext(EUSCI_B0_BASE);
    } else if (I2C_xferIndex == I2C_recBytes - 1) {
      I2C_RX[I2C_xferIndex++] =
          MAP_I2C_masterReceiveMultiByteNext(EUSCI_B0_BASE);
      MAP_I2C_disableInterrupt(EUSCI_B0_BASE, EUSCI_B_I2C_RECEIVE_INTERRUPT0);
      MAP_I2C_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_INTERRUPT0);
      MAP_I2C_setMode(EUSCI_B0_BASE, EUSCI_B_I2C_TRANSMIT_MODE);
      I2C_xferIndex = 0;
      I2C_stopSent = true;
    } else {
      I2C_RX[I2C_xferIndex++] =
          MAP_I2C_masterReceiveMultiByteNext(EUSCI_B0_BASE);
    }
  }
}
