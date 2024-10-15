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
#define LED_R_On		HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, 0)
#define LED_G_On		HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, 0)
#define LED_B_On		HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, 0)

#define LED_R_Off		HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, 1)
#define LED_G_Off		HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, 1)
#define LED_B_Off		HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, 1)

#define LED_R_Set(x)	HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, x)
#define LED_G_Set(x)	HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, x)
#define LED_B_Set(x)	HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, x)

#define LED_R_Toggle	HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin)
#define LED_G_Toggle	HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin)
#define LED_B_Toggle	HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin)

#define KEY1_Trigger	(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0)
#define KEY2_Trigger	(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0)
#define KEY3_Trigger	(HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == 0)
#define KEY4_Trigger	(HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin) == 0)

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
uint8_t Key_Read(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

