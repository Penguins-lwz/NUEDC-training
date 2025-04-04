/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#define LED_WR(val)		do { GPIOC->ODR |= 0xFF00;     \
						     GPIOC->ODR ^= (val) << 8; \
						     GPIOD->ODR |= 0x0004;     \
						     GPIOD->ODR &= 0xFFFB;     \
						   } while (0)

#define KEY1_Trigger	(HAL_GPIO_ReadPin(KEY_S1_GPIO_Port, KEY_S1_Pin) == 0)
#define KEY2_Trigger	(HAL_GPIO_ReadPin(KEY_S2_GPIO_Port, KEY_S2_Pin) == 0)
#define KEY3_Trigger	(HAL_GPIO_ReadPin(KEY_S3_GPIO_Port, KEY_S3_Pin) == 0)
#define KEY4_Trigger	(HAL_GPIO_ReadPin(KEY_S4_GPIO_Port, KEY_S4_Pin) == 0)

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
uint8_t Key_Read(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

