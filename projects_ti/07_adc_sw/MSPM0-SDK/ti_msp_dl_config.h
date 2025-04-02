/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the LP_MSPM0G3507
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_LP_MSPM0G3507
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define CPUCLK_FREQ                                                     80000000



/* Defines for TIM_KEY */
#define TIM_KEY_INST                                                     (TIMG0)
#define TIM_KEY_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIM_KEY_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIM_KEY_INST_LOAD_VALUE                                          (9999U)



/* Defines for UART_DEBUG */
#define UART_DEBUG_INST                                                    UART0
#define UART_DEBUG_INST_FREQUENCY                                       40000000
#define UART_DEBUG_INST_IRQHandler                              UART0_IRQHandler
#define UART_DEBUG_INST_INT_IRQN                                  UART0_INT_IRQn
#define GPIO_UART_DEBUG_RX_PORT                                            GPIOA
#define GPIO_UART_DEBUG_TX_PORT                                            GPIOA
#define GPIO_UART_DEBUG_RX_PIN                                    DL_GPIO_PIN_11
#define GPIO_UART_DEBUG_TX_PIN                                    DL_GPIO_PIN_10
#define GPIO_UART_DEBUG_IOMUX_RX                                 (IOMUX_PINCM22)
#define GPIO_UART_DEBUG_IOMUX_TX                                 (IOMUX_PINCM21)
#define GPIO_UART_DEBUG_IOMUX_RX_FUNC                  IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_DEBUG_IOMUX_TX_FUNC                  IOMUX_PINCM21_PF_UART0_TX
#define UART_DEBUG_BAUD_RATE                                            (115200)
#define UART_DEBUG_IBRD_40_MHZ_115200_BAUD                                  (21)
#define UART_DEBUG_FBRD_40_MHZ_115200_BAUD                                  (45)





/* Defines for ADC0 */
#define ADC0_INST                                                           ADC0
#define ADC0_INST_IRQHandler                                     ADC0_IRQHandler
#define ADC0_INST_INT_IRQN                                       (ADC0_INT_IRQn)
#define ADC0_ADCMEM_CH0                                       DL_ADC12_MEM_IDX_0
#define ADC0_ADCMEM_CH0_REF                      DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC0_ADCMEM_CH0_REF_VOLTAGE_V                                        3.3
#define GPIO_ADC0_C0_PORT                                                  GPIOA
#define GPIO_ADC0_C0_PIN                                          DL_GPIO_PIN_27



/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOB)

/* Defines for R: GPIOB.26 with pinCMx 57 on package pin 28 */
#define LED_R_PIN                                               (DL_GPIO_PIN_26)
#define LED_R_IOMUX                                              (IOMUX_PINCM57)
/* Defines for G: GPIOB.27 with pinCMx 58 on package pin 29 */
#define LED_G_PIN                                               (DL_GPIO_PIN_27)
#define LED_G_IOMUX                                              (IOMUX_PINCM58)
/* Defines for B: GPIOB.22 with pinCMx 50 on package pin 21 */
#define LED_B_PIN                                               (DL_GPIO_PIN_22)
#define LED_B_IOMUX                                              (IOMUX_PINCM50)
/* Defines for S1: GPIOA.18 with pinCMx 40 on package pin 11 */
#define KEY_S1_PORT                                                      (GPIOA)
#define KEY_S1_PIN                                              (DL_GPIO_PIN_18)
#define KEY_S1_IOMUX                                             (IOMUX_PINCM40)
/* Defines for S2: GPIOB.21 with pinCMx 49 on package pin 20 */
#define KEY_S2_PORT                                                      (GPIOB)
#define KEY_S2_PIN                                              (DL_GPIO_PIN_21)
#define KEY_S2_IOMUX                                             (IOMUX_PINCM49)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_TIM_KEY_init(void);
void SYSCFG_DL_UART_DEBUG_init(void);
void SYSCFG_DL_ADC0_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
