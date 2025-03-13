#ifndef __UART_H__
#define __UART_H__

#include "main.h"

#define UART_BufSize	101		// including NUL('\0'), no more than 65536

typedef struct {
	UART_Regs *huart;
	IRQn_Type IRQn;
	char TxMsg[UART_BufSize];
	char RxMsg[UART_BufSize];
	__IOM uint16_t rx_idx;
} myUART_HandleTypeDef;

void myUART_Start_Receive(myUART_HandleTypeDef *myhuart);
void myUART_RxEventCallback(myUART_HandleTypeDef *myhuart);
void myUART_Transmit(myUART_HandleTypeDef *myhuart, const char *format, ...);

#endif /* __UART_H__ */
