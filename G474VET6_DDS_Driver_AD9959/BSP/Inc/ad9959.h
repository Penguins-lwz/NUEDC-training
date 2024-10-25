#ifndef __AD9959_H__
#define __AD9959_H__

#include "main.h"

#define DDS_Channel_0			0x10
#define DDS_Channel_1			0x20
#define DDS_Channel_2			0x40
#define DDS_Channel_3			0x80

#define DDS_CS_Set(x)			HAL_GPIO_WritePin(DDS_CS_GPIO_Port, DDS_CS_Pin, x)
#define DDS_RST_Set(x)			HAL_GPIO_WritePin(DDS_RST_GPIO_Port, DDS_RST_Pin, x)
#define DDS_SCL_Set(x)			HAL_GPIO_WritePin(DDS_SCL_GPIO_Port, DDS_SCL_Pin, x)
#define DDS_SDA_Set(x)			HAL_GPIO_WritePin(DDS_SDA_GPIO_Port, DDS_SDA_Pin, x)
#define DDS_UPD_Set(x)			HAL_GPIO_WritePin(DDS_UPD_GPIO_Port, DDS_UPD_Pin, x)

void DDS_Init(void);
void DDS_Config(uint8_t channel, float freq, float phase);

#endif /* __AD9959_H__ */
