/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */
#define UART_BufSize	255		// No more than 255

typedef struct {
	UART_HandleTypeDef *huart;
	char UART_TxBuf[UART_BufSize];
	char UART_RxBuf[UART_BufSize];
	char UART_RxMsg[UART_BufSize];
	__IOM bool RxMsgUsed;
} myUART_HandleTypeDef;

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void myUART_Start_Receive_DMA(myUART_HandleTypeDef *myhuart);
void myUART_Transmit_DMA(myUART_HandleTypeDef *myhuart, const char *format, ...);
void myUART_Receive_DMA(myUART_HandleTypeDef *myhuart);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

