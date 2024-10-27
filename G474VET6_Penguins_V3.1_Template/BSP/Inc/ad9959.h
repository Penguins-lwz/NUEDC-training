#ifndef __AD9959_H__
#define __AD9959_H__

#include "main.h"

#define AD9959_Channel_0	0x10
#define AD9959_Channel_1	0x20
#define AD9959_Channel_2	0x40
#define AD9959_Channel_3	0x80

#define AD9959_CS_Set(x)	HAL_GPIO_WritePin(AD9959_CS_GPIO_Port, AD9959_CS_Pin, x)
#define AD9959_RST_Set(x)	HAL_GPIO_WritePin(AD9959_RST_GPIO_Port, AD9959_RST_Pin, x)
#define AD9959_SCL_Set(x)	HAL_GPIO_WritePin(AD9959_SCL_GPIO_Port, AD9959_SCL_Pin, x)
#define AD9959_SDA_Set(x)	HAL_GPIO_WritePin(AD9959_SDA_GPIO_Port, AD9959_SDA_Pin, x)
#define AD9959_UPD_Set(x)	HAL_GPIO_WritePin(AD9959_UPD_GPIO_Port, AD9959_UPD_Pin, x)

void AD9959_Init(void);
void AD9959_Config(uint8_t channel, float freq, float phase);

#endif /* __AD9959_H__ */
