#ifndef __UART_H__
#define __UART_H__

#include "main.h"

#define UART_BufSize	101		// including NUL('\0'), no more than 65536

typedef struct {
	UART_Regs *huart;
	char TxMsg[UART_BufSize];
	char RxMsg[UART_BufSize];
	uint16_t rx_idx;
} myUART_HandleTypeDef;

void myUART_Transmit(myUART_HandleTypeDef *myhuart, const char *format, ...);
void myUART_IRQHandler(myUART_HandleTypeDef *myhuart);
void myUART_RxEventCallback(myUART_HandleTypeDef *myhuart);

#endif /* __UART_H__ */
