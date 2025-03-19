#include "uart.h"

void myUART_Transmit(myUART_HandleTypeDef *myhuart, const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	vsnprintf(myhuart->TxMsg, UART_BufSize, format, ap);
	va_end(ap);
	
	for (uint16_t i = 0; myhuart->TxMsg[i]; ++i)
		DL_UART_transmitDataBlocking(myhuart->huart, myhuart->TxMsg[i]);
}

void myUART_IRQHandler(myUART_HandleTypeDef *myhuart)
{
	switch (DL_UART_getPendingInterrupt(myhuart->huart))
	{
		case DL_UART_IIDX_RX:
			if (myhuart->rx_idx < UART_BufSize - 1)
			{
				char data = DL_UART_receiveData(myhuart->huart);
				myhuart->RxMsg[myhuart->rx_idx++] = data;
				if (myhuart->rx_idx == UART_BufSize - 1 || data == '\n')
				{
					myUART_RxEventCallback(myhuart);
					memset(myhuart->RxMsg, 0, UART_BufSize);
					myhuart->rx_idx = 0;
				}
			}
			break;
		default:
			break;
	}
}

__WEAK void myUART_RxEventCallback(myUART_HandleTypeDef *myhuart)
{
	
}
