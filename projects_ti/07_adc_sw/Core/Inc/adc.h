#ifndef __ADC_H__
#define __ADC_H__

#include "main.h"

typedef struct {
	ADC12_Regs *hadc;
	DL_ADC12_MEM_IDX ch;
	uint16_t data;
} myADC_HandleTypeDef;

void myADC_Start(myADC_HandleTypeDef *myhadc);
void myADC_IRQHandler(myADC_HandleTypeDef *myhadc);
void myADC_ConvCpltCallback(myADC_HandleTypeDef *myhadc);

#endif /* __ADC_H__ */
