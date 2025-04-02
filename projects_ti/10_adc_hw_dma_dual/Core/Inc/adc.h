#ifndef __ADC_H__
#define __ADC_H__

#include "main.h"

#define ADC_DataSize	1000

typedef struct {
	ADC12_Regs *hadc0;
	ADC12_Regs *hadc1;
	GPTIMER_Regs *htim;
	DL_ADC12_MEM_IDX adcch0;
	DL_ADC12_MEM_IDX adcch1;
	uint8_t dmach0;
	uint8_t dmach1;
	uint16_t pData0[ADC_DataSize];
	uint16_t pData1[ADC_DataSize];
} myADC_HandleTypeDef;

void myADC_Start_DMA(myADC_HandleTypeDef *myhadc);
void myADC_IRQHandler(myADC_HandleTypeDef *myhadc);
void myADC_ConvCpltCallback(myADC_HandleTypeDef *myhadc);

#endif /* __ADC_H__ */
