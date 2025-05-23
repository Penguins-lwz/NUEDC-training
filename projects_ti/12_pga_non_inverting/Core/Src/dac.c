#include "dac.h"

#define DAC_maxFreq		1000000
#define DAC_DataSize	(sizeof(pData) / sizeof(uint16_t))

const uint16_t pData[] = {
	0x400, 0x464, 0x4C7, 0x529, 0x588, 0x5E2, 0x639, 0x689,
	0x6D4, 0x717, 0x753, 0x787, 0x7B2, 0x7D3, 0x7EC, 0x7FB,
	0x800, 0x7FB, 0x7EC, 0x7D3, 0x7B2, 0x787, 0x753, 0x717,
	0x6D4, 0x689, 0x639, 0x5E2, 0x588, 0x529, 0x4C7, 0x464,
	0x400, 0x39B, 0x338, 0x2D7, 0x278, 0x21D, 0x1C7, 0x176,
	0x12C, 0x0E8, 0x0AD, 0x079, 0x04E, 0x02C, 0x014, 0x005,
	0x000, 0x005, 0x014, 0x02C, 0x04E, 0x079, 0x0AD, 0x0E8,
	0x12C, 0x176, 0x1C7, 0x21D, 0x278, 0x2D7, 0x338, 0x39B
};

void myDAC_Start_DMA(myDAC_HandleTypeDef *myhdac, float freq)
{
	myDAC_Stop_DMA(myhdac);
	
	DL_DMA_setSrcAddr(DMA, myhdac->dmach, (uint32_t)pData);
	DL_DMA_setDestAddr(DMA, myhdac->dmach, (uint32_t)&DAC0->DATA0);
	DL_DMA_setTransferSize(DMA, myhdac->dmach, DAC_DataSize);
	DL_DMA_enableChannel(DMA, myhdac->dmach);
	
	freq = freq * DAC_DataSize < DAC_maxFreq ? freq * DAC_DataSize : DAC_maxFreq;
	DL_Timer_setLoadValue(myhdac->htim, myhdac->clkFreq / freq - 0.5);
	DL_Timer_startCounter(myhdac->htim);
}

void myDAC_Stop_DMA(myDAC_HandleTypeDef *myhdac)
{
	DL_Timer_stopCounter(myhdac->htim);
	DL_DMA_disableChannel(DMA, myhdac->dmach);
}
