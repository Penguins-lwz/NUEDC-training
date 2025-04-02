/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
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
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc1;

extern ADC_HandleTypeDef hadc2;

/* USER CODE BEGIN Private defines */
#define ADC_DataSize	1000

typedef struct {
	ADC_HandleTypeDef *hadc_master;
	ADC_HandleTypeDef *hadc_slave;
	TIM_HandleTypeDef *htim;
	uint32_t ADC_DualData[ADC_DataSize];
	__IOM bool ConvFinish;
} myADC_HandleTypeDef;

/* USER CODE END Private defines */

void MX_ADC1_Init(void);
void MX_ADC2_Init(void);

/* USER CODE BEGIN Prototypes */
void myADC_DualStart_DMA(myADC_HandleTypeDef *myhadc);
void myADC_DualStop_DMA(myADC_HandleTypeDef *myhadc);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

