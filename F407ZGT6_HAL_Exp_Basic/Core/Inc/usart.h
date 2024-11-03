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

/* USER CODE BEGIN Private defines */
#define UART_BufSize	10008		// including NUL('\0')
#define UART_TxHeader	"RxMsg: "

extern const char UART_Tx1E2[];
extern const char UART_Tx1E4[];

typedef struct {
	UART_HandleTypeDef *huart;
	char TxMsg[UART_BufSize];
	char RxMsg[UART_BufSize];
	uint8_t idx;
} myUART_HandleTypeDef;

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void myUART_Start_Receive_DMA(myUART_HandleTypeDef *myhuart);
void myUART_Transmit_DMA(myUART_HandleTypeDef *myhuart, const char *format, ...);
void myUART_SetBaudRate(myUART_HandleTypeDef *myhuart);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

