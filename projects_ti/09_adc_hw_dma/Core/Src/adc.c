#include "adc.h"

void myADC_Start_DMA(myADC_HandleTypeDef *myhadc)
{
	/* DMA 转运模式为单次，源地址、目标地址、转运量可能被修改，再次使用需重新配置
	 * DMA 寻址模式为 Fixed to Block，实际上在 DMA 转运完成后
	 *   源地址：不会被修改，可以只配置一次，但此处为精简程序统一重新配置
	 *   目标地址：会被修改，将由目标数组头地址移动至目标数组尾地址
	 *   转运量：会被修改，将由目标数组大小（总转运量）减少至 0
	 */
	DL_DMA_setSrcAddr(DMA, myhadc->dmach, DL_ADC12_getMemResultAddress(myhadc->hadc, myhadc->adcch));
	DL_DMA_setDestAddr(DMA, myhadc->dmach, (uint32_t)myhadc->pData);
	DL_DMA_setTransferSize(DMA, myhadc->dmach, ADC_DataSize);
	
	/* DMA 在转运完成指定数量数据后向 ADC 发送 DMA_DONE 并自动关闭 DMA，需重新开启 */
	DL_DMA_enableChannel(DMA, myhadc->dmach);
	
	DL_Timer_startCounter(myhadc->htim);
}

void myADC_IRQHandler(myADC_HandleTypeDef *myhadc)
{
	switch (DL_ADC12_getPendingInterrupt(myhadc->hadc))
	{
		case DL_ADC12_IIDX_DMA_DONE:
			
			/* 关闭 TIM 以停止 ADC 触发信号，即使此时 DMA 已停止工作 */
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
