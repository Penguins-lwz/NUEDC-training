#include "adc.h"

void myADC_Start_DMA(myADC_HandleTypeDef *myhadc)
{
	DL_DMA_setSrcAddr(DMA, myhadc->dmach0, DL_ADC12_getMemResultAddress(myhadc->hadc0, myhadc->adcch0));
	DL_DMA_setDestAddr(DMA, myhadc->dmach0, (uint32_t)myhadc->pData0);
	DL_DMA_setTransferSize(DMA, myhadc->dmach0, ADC_DataSize);
	DL_DMA_enableChannel(DMA, myhadc->dmach0);
	
	DL_DMA_setSrcAddr(DMA, myhadc->dmach1, DL_ADC12_getMemResultAddress(myhadc->hadc1, myhadc->adcch1));
	DL_DMA_setDestAddr(DMA, myhadc->dmach1, (uint32_t)myhadc->pData1);
	DL_DMA_setTransferSize(DMA, myhadc->dmach1, ADC_DataSize);
	DL_DMA_enableChannel(DMA, myhadc->dmach1);
	
	DL_Timer_startCounter(myhadc->htim);
}

void myADC_IRQHandler(myADC_HandleTypeDef *myhadc)
{
	switch (DL_ADC12_getPendingInterrupt(myhadc->hadc0))
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
