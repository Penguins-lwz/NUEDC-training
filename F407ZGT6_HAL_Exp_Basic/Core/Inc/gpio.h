/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define LED0_On			HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, 0)
#define LED1_On			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0)
#define BEEP_On			HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, 1)

#define LED0_Off		HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, 1)
#define LED1_Off		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1)
#define BEEP_Off		HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, 0)

#define LED0_Set(x)		HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, x)
#define LED1_Set(x)		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, x)

#define LED0_Toggle		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin)
#define LED1_Toggle		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin)

#define KEY0_Trigger	(HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == 0)
#define KEY1_Trigger	(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0)
#define KEY2_Trigger	(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0)
#define KEY3_Trigger	(HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == 1)

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
uint8_t Key_Read(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

