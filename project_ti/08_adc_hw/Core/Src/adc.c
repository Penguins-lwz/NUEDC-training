#include "adc.h"

void myADC_Start(myADC_HandleTypeDef *myhadc)
{
	DL_ADC12_startConversion(myhadc->hadc);
	DL_Timer_startCounter(myhadc->htim);
}

void myADC_IRQHandler(myADC_HandleTypeDef *myhadc)
{
	switch (DL_ADC12_getPendingInterrupt(myhadc->hadc))
	{
		case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
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
