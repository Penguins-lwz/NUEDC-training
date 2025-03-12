#include "main.h"
#include "gpio.h"
#include "uart.h"

myUART_HandleTypeDef myUART = { .huart = UART0, .IRQn = UART0_INT_IRQn };

void Key_Process(uint8_t keyNum);

int main(void)
{
	SYSCFG_DL_init();
	NVIC_EnableIRQ(TIM_KEY_INST_INT_IRQN);
	myUART_Transmit(&myUART, "G3507SPMR UART0 Connected.\n");
	
	DL_Timer_startCounter(TIM_KEY_INST);
	
	/* 阻塞式接收，缓存区满或收到'\n'时退出，不得在按键中断内使用 */
	LED_B_On;
	myUART_Start_Receive(&myUART);
	myUART_Transmit(&myUART, "1: %s", myUART.RxMsg);
	myUART_Start_Receive(&myUART);
	myUART_Transmit(&myUART, "2: %s", myUART.RxMsg);
	LED_B_Off;
	
	while (1)
	{
		LED_G_Toggle; DL_Delay(500);
	}
}

void TIM_KEY_INST_IRQHandler(void)
{
	switch (DL_Timer_getPendingInterrupt(TIM_KEY_INST))
	{
		case DL_TIMER_IIDX_ZERO:
			Key_Process(Key_Read());
			break;
		default:
			break;
	}
}

void UART_DEBUG_INST_IRQHandler(void)
{
	switch (DL_UART_getPendingInterrupt(UART_DEBUG_INST))
	{
		case DL_UART_IIDX_RX:
			myUART_RxEventCallback(&myUART);
			break;
		default:
			break;
	}
}

void Key_Process(uint8_t keyNum)
{
	if (keyNum == 0x01) LED_R_On;
//	else if (keyNum == 0x02) LED_B_On;
	else if (keyNum == 0x81) LED_R_Off;
//	else if (keyNum == 0x82) LED_B_Off;
}
