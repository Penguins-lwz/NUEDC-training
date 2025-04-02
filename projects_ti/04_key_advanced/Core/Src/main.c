#include "main.h"
#include "gpio.h"

void Key_Process(uint8_t keyNum);

int main(void)
{
	SYSCFG_DL_init();
	
	NVIC_EnableIRQ(TIM_KEY_INST_INT_IRQN);
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

void Key_Process(uint8_t keyNum)
{
	if (keyNum == 0x01) LED_R_On;
	else if (keyNum == 0x02) LED_B_On;
	else if (keyNum == 0x81) LED_R_Off;
	else if (keyNum == 0x82) LED_B_Off;
}
