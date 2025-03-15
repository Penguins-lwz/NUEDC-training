#include "main.h"
#include "gpio.h"
#include "adc.h"
#include "uart.h"

myUART_HandleTypeDef myUART = { .huart = UART_DEBUG_INST };
myADC_HandleTypeDef myADC = { .hadc = ADC0_INST, .ch = ADC0_ADCMEM_CH0 };

void Key_Process(uint8_t keyNum);

void myUART_RxEventCallback(myUART_HandleTypeDef *myhuart)
{
	myUART_Transmit(&myUART, "RxMsg: %s", myUART.RxMsg);
}

void myADC_ConvCpltCallback(myADC_HandleTypeDef *myhadc)
{
	/* ADC 转换完成回调函数：逐个打印采样数据 */
	static uint32_t cnt = 0;
	myUART_Transmit(&myUART, "ADC_%d: %d\n", cnt++, myADC.data);
}

int main(void)
{
	/* ADC 在初始化后默认使能，CTL0 ENC == 1 */
	SYSCFG_DL_init();
	NVIC_EnableIRQ(UART_DEBUG_INST_INT_IRQN);
	NVIC_EnableIRQ(TIM_KEY_INST_INT_IRQN);
	NVIC_EnableIRQ(ADC0_INST_INT_IRQN);
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

void ADC0_INST_IRQHandler(void)
{
	myADC_IRQHandler(&myADC);
}

void Key_Process(uint8_t keyNum)
{
	/* 软件每 100 ms 开启一次 ADC，开启方法请转至函数定义查看 */
	static uint16_t cnt = 0;
	if (++cnt == 10) cnt = 0, LED_G_Toggle, myADC_Start(&myADC);
	
	if (keyNum == 0x01) LED_R_On;
	else if (keyNum == 0x02) LED_B_On;
	else if (keyNum == 0x81) LED_R_Off;
	else if (keyNum == 0x82) LED_B_Off;
}
