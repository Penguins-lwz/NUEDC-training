#include "main.h"
#include "gpio.h"
#include "uart.h"

myUART_HandleTypeDef myUART = { .huart = UART0 };

void Key_Process(uint8_t keyNum);

void myUART_RxEventCallback(myUART_HandleTypeDef *myhuart)
{
	/* 回环模式：加前缀后返回上位机 */
	myUART_Transmit(&myUART, "RxMsg: %s", myUART.RxMsg);
}

int main(void)
{
	SYSCFG_DL_init();
	NVIC_EnableIRQ(UART0_INT_IRQn);
	NVIC_EnableIRQ(TIM_KEY_INST_INT_IRQN);
	myUART_Transmit(&myUART, "G3507SPMR UART0 Connected.\n");
	DL_Timer_startCounter(TIM_KEY_INST);
	
	while (1)
	{
		
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
	myUART_IRQHandler(&myUART);
}

void Key_Process(uint8_t keyNum)
{
	static uint16_t cnt = 0;
	if (++cnt == 10) cnt = 0, LED_G_Toggle;
	
	if (keyNum == 0x01) LED_R_On;
	else if (keyNum == 0x02) LED_B_On;
	else if (keyNum == 0x81) LED_R_Off;
	else if (keyNum == 0x82) LED_B_Off;
}
