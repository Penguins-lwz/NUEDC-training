#include "adc.h"

void myADC_Start_DMA(myADC_HandleTypeDef *myhadc)
{
	DL_DMA_setSrcAddr(DMA, myhadc->dmach, DL_ADC12_getMemResultAddress(myhadc->hadc, myhadc->adcch));
	DL_DMA_setDestAddr(DMA, myhadc->dmach, (uint32_t)myhadc->pData);
	DL_DMA_setTransferSize(DMA, myhadc->dmach, ADC_DataSize);
	DL_DMA_enableChannel(DMA, myhadc->dmach);
	
	DL_Timer_startCounter(myhadc->htim);
}

void myADC_IRQHandler(myADC_HandleTypeDef *myhadc)
{
	switch (DL_ADC12_getPendingInterrupt(myhadc->hadc))
	{
		case DL_ADC12_IIDX_DMA_DONE:
			DL_Timer_stopCounter(myhadc->htim);
			myADC_ConvCpltCallback(myhadc);
			break;
		default:
			break;
	}
}

__WEAK void myADC_ConvCpltCallback(myADC_HandleTypeDef *myhadc)
{
	
}
