#include "dac.h"

/* 手册指出 DAC 最大采样率 1 MSPS，但可尝试超频使用 */
#define DAC_maxFreq		1000000
#define DAC_DataSize	(sizeof(pData) / sizeof(uint16_t))

const uint16_t pData[] = {
	2048, 2248, 2447, 2642, 2831, 3013, 3185, 3347,
	3496, 3631, 3750, 3854, 3940, 4007, 4056, 4086,
	4095, 4086, 4056, 4007, 3940, 3854, 3750, 3631,
	3496, 3347, 3185, 3013, 2831, 2642, 2447, 2248,
	2048, 1847, 1648, 1453, 1264, 1082,  910,  748,
	 599,  464,  345,  241,  155,   88,   39,    9,
	   0,    9,   39,   88,  155,  241,  345,  464,
	 599,  748,  910, 1082, 1264, 1453, 1648, 1847
};

void myDAC_Start_DMA(myDAC_HandleTypeDef *myhdac, float freq)
{
	/* 关闭 DMA 以重新配置其参数 */
	myDAC_Stop_DMA(myhdac);
	
	DL_DMA_setSrcAddr(DMA, myhdac->dmach, (uint32_t)pData);
	DL_DMA_setDestAddr(DMA, myhdac->dmach, (uint32_t)&DAC0->DATA0);
	DL_DMA_setTransferSize(DMA, myhdac->dmach, DAC_DataSize);
	DL_DMA_enableChannel(DMA, myhdac->dmach);
	
	/* 采样率过高将被钳位，上限值由 DAC_maxFreq 配置 */
	freq = freq * DAC_DataSize < DAC_maxFreq ? freq * DAC_DataSize : DAC_maxFreq;
	DL_Timer_setLoadValue(myhdac->htim, myhdac->clkFreq / freq - 0.5);
	DL_Timer_startCounter(myhdac->htim);
}

void myDAC_Stop_DMA(myDAC_HandleTypeDef *myhdac)
{
	/* 停止 DAC 转换，引脚以最后一次转换结果直流输出，非接地或高阻态 */
	DL_Timer_stopCounter(myhdac->htim);
	DL_DMA_disableChannel(DMA, myhdac->dmach);
}
