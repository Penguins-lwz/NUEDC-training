/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dac.h
  * @brief   This file contains all the function prototypes for
  *          the dac.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DAC_H__
#define __DAC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern DAC_HandleTypeDef hdac1;

extern DAC_HandleTypeDef hdac2;

/* USER CODE BEGIN Private defines */
#define DAC_DataSize	100

typedef struct {
	DAC_HandleTypeDef *hdac;
	TIM_HandleTypeDef *htim;
	uint32_t channel;
} myDAC_HandleTypeDef;

typedef struct {
	DAC_HandleTypeDef *hdac;
	TIM_HandleTypeDef *htim;
} myDualDAC_HandleTypeDef;

/* USER CODE END Private defines */

void MX_DAC1_Init(void);
void MX_DAC2_Init(void);

/* USER CODE BEGIN Prototypes */
void myDAC_Start_DMA(myDAC_HandleTypeDef *myhdac);
void myDAC_Stop_DMA(myDAC_HandleTypeDef *myhdac);
void myDAC_DualStart_DMA(myDualDAC_HandleTypeDef *myhdac);
void myDAC_DualStop_DMA(myDualDAC_HandleTypeDef *myhdac);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __DAC_H__ */

