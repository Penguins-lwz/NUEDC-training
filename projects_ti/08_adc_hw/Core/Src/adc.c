#include "adc.h"

void myADC_Start(myADC_HandleTypeDef *myhadc)
{
	/* 硬件触发时，开启 TIM 以周期性配置 CTL1 SC = 1，后同软件触发 */
	DL_Timer_startCounter(myhadc->htim);
}

void myADC_IRQHandler(myADC_HandleTypeDef *myhadc)
{
	switch (DL_ADC12_getPendingInterrupt(myhadc->hadc))
	{
		case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
			
			/* 未使用 FIFO，自 MEMRES 读取 ADC 转换结果 */
			myhadc->data = DL_ADC12_getMemResult(myhadc->hadc, myhadc->ch);
			myADC_ConvCpltCallback(myhadc);
			break;
		default:
			break;
	}
}

__WEAK void myADC_ConvCpltCallback(myADC_HandleTypeDef *myhadc)
{
	
}
