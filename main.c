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

int streamer(void) {
  // Stop Watchdog
  MAP_WDT_A_holdTimer();

  // MPU initialization
  initGPIO();
  initClockSources();
  initTimer32();
  initUART();
  // initI2C();
  initSPI();
  initADC();
  initGlobals();

  // Sensor configuration */
  // I2C_initMotionSensor();
  SPI_initECG();
  // I2C_initTempSensor();

  /* enable body communication */
  // startBodyComm();

  /* reduce power consumption - turn off sensors/transmitter */
  // I2C_sleepMotionSensor(true);
  SPI_sleepECG(true);
  // I2C_sleepTempSensor(true);
  stopBodyComm();

  // enable FPU
  MAP_FPU_enableModule();
  MAP_FPU_setRoundingMode(FPU_ROUND_NEAREST);

  // FANN declarations
  fann_type *calc_out;
  fann_type input[4] = {0};
  // struct fann *ann = fann_create_from_data(&ann);     //remove printf instr.
  // in fann_create_from_data

  for (i = 0; i < 48000; ++i) {
    __delay_cycles(1000);
  }

  // Interrupts enable
  MAP_Interrupt_enableMaster();

  // start 1st Timer32 in continuous mode
  MAP_Timer32_startTimer(TIMER32_0_BASE, false);

#if DEBUG
  smclk = CS_getSMCLK();
  mclk = CS_getMCLK();
  aclk = CS_getACLK();
#endif

  // MAP_Interrupt_disableInterrupt(INT_T32_INT2);
  // MAP_Timer32_haltTimer(TIMER32_0_BASE);
  SENS_STREAM = true;
  FANN_CALC = false;
  /* activate sensors */
  // I2C_sleepMotionSensor(false);
  SPI_sleepECG(false);
  __delay_cycles(1000);
  // I2C_sleepTempSensor(false);
  MAP_Interrupt_enableInterrupt(INT_EUSCIB0);
  SPI_startStreamECG();

  while (1) {
    /* send battery status via BLE every second at startup and whenever other
     * streaming is deactivated (status subroutine) */
    if ((T32_time >= 1000)) {
      T32_time = 0;
      // I2C_getBatteryStatus(&Status[0]);
      // BLE_sendStatusData(&Status[0]);
    }

    /* Data acquisition and BLE transmission (raw sensor data, 125 Hz)
     * synchronized with ECG readout (250 Hz) */
    if (ECG_DRDY) {
      ECG_DRDY = false;
      /* init BLE TX array */
      BLE_TX[0] = 'E';
      BLE_TX[1] = 'M';
      BLE_TX[2] = 'O';
      BLE_TX[3] = ':';
      BLE_TX[60] = '\r';
      BLE_TX[61] = '\n';
      /* send sensor data every 8ms (acquisition 2x4ms time slots) */
      if (PKG_sent < 125) {
        /* ECG Data */
        SPI_singleReadECG();
        for (i = 0; i < 3; ++i) {
          BLE_TX[(5 + 3 * (ECG_cnt - 1) + i)] = SPI_RX_ECG[(6 + i)];
        }
        /* 2nd time slot (4ms duration) */
        if (ECG_cnt == 2) {
          ECG_cnt = 0;
          PKG_sent++;
          /* LOFF */
          Loff = (SPI_RX_ECG[0] << 16) | (SPI_RX_ECG[1] << 8) | (SPI_RX_ECG[2]);
          hi = ((uint8_t)(Loff >> 15)) & 0x1F;
          BLE_TX[4] = hi;
          /* GSR - moving average */
          // ADC_getAudio(&BLE_TX[(36+2*i)]);
          /* shift left array with old values and sum it up */
          for (i = 0; i < 7; i++) {
            GSRData[i] = GSRData[i + 1];
            GSRtemp += GSRData[i];
          }
          GSRData[7] = ADC_result[1];
          GSRtemp += GSRData[7];
          /* divide by 8 */
          GSRtemp = GSRtemp >> 3;
          lo = (uint8_t)(GSRtemp);
          hi = ((uint8_t)(GSRtemp >> 8));

          BLE_TX[11] = hi;
          BLE_TX[12] = lo;

          /* FEATURE EXTRACTION */
          int ecg0 = (BLE_TX[5] << 16) + (BLE_TX[6] << 8) + BLE_TX[7];
          int ecg1 = (BLE_TX[8] << 16) + (BLE_TX[9] << 8) + BLE_TX[10];

          int sgsr = smoothgsr((hi << 8) + lo);
          int secg = smoothecg(ecg0, ecg1);

          if (gsrdetection(sgsr, mtime)) {
            sgsr = 0;
          }

          if (peakdetection(secg, ecg0, ecg1, mtime)) {
            secg = 0;  // max(ecg0, ecg1);
          }

          BLE_TX[13] = (sgsr >> 16) & 0xFF;
          BLE_TX[14] = (sgsr >> 8) & 0xFF;
          BLE_TX[15] = (sgsr)&0xFF;
          BLE_TX[16] = (secg >> 16) & 0xFF;
          BLE_TX[17] = (secg >> 8) & 0xFF;
          BLE_TX[18] = (secg)&0xFF;
          BLE_TX[51] = (mtime >> 8) & 0xFF;
          BLE_TX[52] = (mtime)&0xFF;

          ++mtime;

          /*BLE TRANSMIT (every 8ms) */
          BLE_sendSensorData(&BLE_TX[0], 62);
          MAP_ADC14_toggleConversionTrigger();

          if (mtime == 3750) {
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);
            extractfeatures(feat, mtime);
            float f[8];
            float *s = f;
            extractfeatures2(mtime, f);
            s = fann_run(s);
            mtime = 0;
            resetExtraction(sgsr, mtime);
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
            BLE_TX[19] = (feat[0] >> 24) & 0xFF;
            BLE_TX[20] = (feat[0] >> 16) & 0xFF;
            BLE_TX[21] = (feat[0] >> 8) & 0xFF;
            BLE_TX[22] = (feat[0]) & 0xFF;
            BLE_TX[23] = (feat[1] >> 24) & 0xFF;
            BLE_TX[24] = (feat[1] >> 16) & 0xFF;
            BLE_TX[25] = (feat[1] >> 8) & 0xFF;
            BLE_TX[26] = (feat[1]) & 0xFF;
            BLE_TX[27] = (feat[2] >> 24) & 0xFF;
            BLE_TX[28] = (feat[2] >> 16) & 0xFF;
            BLE_TX[29] = (feat[2] >> 8) & 0xFF;
            BLE_TX[30] = (feat[2]) & 0xFF;
            BLE_TX[31] = (feat[3] >> 24) & 0xFF;
            BLE_TX[32] = (feat[3] >> 16) & 0xFF;
            BLE_TX[33] = (feat[3] >> 8) & 0xFF;
            BLE_TX[34] = (feat[3]) & 0xFF;
            BLE_TX[35] = (feat[4] >> 24) & 0xFF;
            BLE_TX[36] = (feat[4] >> 16) & 0xFF;
            BLE_TX[37] = (feat[4] >> 8) & 0xFF;
            BLE_TX[38] = (feat[4]) & 0xFF;
            BLE_TX[39] = (feat[5] >> 24) & 0xFF;
            BLE_TX[40] = (feat[5] >> 16) & 0xFF;
            BLE_TX[41] = (feat[5] >> 8) & 0xFF;
            BLE_TX[42] = (feat[5]) & 0xFF;
            BLE_TX[43] = (feat[6] >> 24) & 0xFF;
            BLE_TX[44] = (feat[6] >> 16) & 0xFF;
            BLE_TX[45] = (feat[6] >> 8) & 0xFF;
            BLE_TX[46] = (feat[6]) & 0xFF;
            BLE_TX[47] = (feat[7] >> 24) & 0xFF;
            BLE_TX[48] = (feat[7] >> 16) & 0xFF;
            BLE_TX[49] = (feat[7] >> 8) & 0xFF;
            BLE_TX[50] = (feat[7]) & 0xFF;
            BLE_TX[53] = max_index(s, 3) & 0xFF;
          }
        }
      } else {
        SPI_singleReadECG();  // must be done to reset ADS1292 DRDY
        if (ECG_cnt == 2) {
          ECG_cnt = 0;
          PKG_sent = 0;
        }
      }
    }

    // MAP_PCM_gotoLPM0();
  }
}

void test4(void) {
  init_sys();
  while (1) {
    P6OUT |= BIT0;
    P6OUT &= ~BIT0;
    /*
     * Fucking Slow:
     * MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN0);
     * MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
     */
  }
}

void test3(void) {
  init_sys();
  int i, m, d;
  while (1) {
    GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN0);
    for (i = 0; i < 100; ++i) {
      arm_max_q31(test_data_output, 626, &m, &d);
    }
    GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);

    GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);
    for (i = 0; i < 100; ++i) {
      arm_max2_q31(test_data_output, 626, &m);
    }
    GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN1);
  }
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

void test(void) {
  init_sys();

  int i, t, secg, sgsr;
  float f[8];
  int mtime = 0;
  while (1) {
    GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN0);
    resetExtraction(sgsr, mtime);
    for (t = 0; t < 3; ++t) {
      for (i = 0; i < 1024; i = i + 3) {
        int i1 = data[i];
        int i2 = data[i + 1];
        int i3 = data[i + 2];

        GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN1);
        sgsr = smoothgsr(i3);
        secg = smoothecg(i1, i2);
        gsrdetection(sgsr, mtime);
        peakdetection(secg, i1, i2, mtime);
        ++mtime;
        GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN1);
      }
    }
    GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
    extractfeatures2(mtime, f);
    GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN0);
    float *s = fann_run(f);
    mtime = 0;
    GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0);
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
