#ifndef __DDS_H__
#define __DDS_H__

#include "main.h"

#define DDS_CH0			0x10
#define DDS_CH1			0x20
#define DDS_CH2			0x40
#define DDS_CH3			0x80

void DDS_Init(void);
void DDS_Config(uint8_t channel, float freq, float phase);

#endif /* __DDS_H__ */
