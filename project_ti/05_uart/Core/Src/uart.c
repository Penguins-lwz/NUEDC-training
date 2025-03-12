#include "uart.h"

void myUART_Start_Receive(myUART_HandleTypeDef *myhuart)
{
	NVIC_EnableIRQ(myhuart->IRQn);
	memset(myhuart->RxMsg, 0, UART_BufSize);
	while (myhuart->rx_idx < UART_BufSize);
	NVIC_DisableIRQ(myhuart->IRQn);
	myhuart->rx_idx = 0;
}

void myUART_Transmit(myUART_HandleTypeDef *myhuart, const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	vsnprintf(myhuart->TxMsg, UART_BufSize, format, ap);
	va_end(ap);
	
	for (uint16_t i = 0; myhuart->TxMsg[i]; ++i)
		DL_UART_transmitDataBlocking(myhuart->huart, myhuart->TxMsg[i]);
}

void myUART_RxEventCallback(myUART_HandleTypeDef *myhuart)
{
	myhuart->RxMsg[myhuart->rx_idx] = DL_UART_receiveData(myhuart->huart);
	myhuart->rx_idx = myhuart->RxMsg[myhuart->rx_idx] == '\n' ? \
	                  UART_BufSize : myhuart->rx_idx + 1;
}
