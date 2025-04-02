/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
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
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern TIM_HandleTypeDef htim2;

extern TIM_HandleTypeDef htim3;

extern TIM_HandleTypeDef htim6;

extern TIM_HandleTypeDef htim9;

extern TIM_HandleTypeDef htim11;

/* USER CODE BEGIN Private defines */
typedef struct {
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
	uint8_t idx;
} myPWM_HandleTypeDef;

typedef struct {
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
} myPWMI_HandleTypeDef;

/* USER CODE END Private defines */

void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM6_Init(void);
void MX_TIM9_Init(void);
void MX_TIM11_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* USER CODE BEGIN Prototypes */
void myPWM_Start(myPWM_HandleTypeDef *myPWM);
void myPWM_Stop(myPWM_HandleTypeDef *myPWM);
void myPWM_SetPulse(myPWM_HandleTypeDef *myPWM);

void myPWMI_Start(myPWMI_HandleTypeDef *myPWMI);
void myPWMI_Stop(myPWMI_HandleTypeDef *myPWMI);
uint32_t myPWMI_GetPeriod(myPWMI_HandleTypeDef *myPWMI);
uint32_t myPWMI_GetPulse(myPWMI_HandleTypeDef *myPWMI);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

