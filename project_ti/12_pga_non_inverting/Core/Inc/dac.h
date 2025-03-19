#ifndef __DAC_H__
#define __DAC_H__

#include "main.h"

typedef struct {
	GPTIMER_Regs *htim;
	uint32_t clkFreq;
	uint8_t dmach;
} myDAC_HandleTypeDef;

void myDAC_Start_DMA(myDAC_HandleTypeDef *myhdac, float freq);
void myDAC_Stop_DMA(myDAC_HandleTypeDef *myhdac);

#endif /* __DAC_H__ */
