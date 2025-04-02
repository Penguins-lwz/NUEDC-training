#ifndef __AD9833_H__
#define __AD9833_H__

#include "main.h"

#define AD9833_FORM_SIN			((0 << 5) | (0 << 1) | (0 << 3))
#define AD9833_FORM_TRI			((0 << 5) | (1 << 1) | (0 << 3))
#define AD9833_FORM_MSB			((1 << 5) | (0 << 1) | (1 << 3))
#define AD9833_FORM_MSB_DIV2	((1 << 5) | (0 << 1) | (0 << 3))

#define AD9833_CS_Set(x)		HAL_GPIO_WritePin(AD9833_CS_GPIO_Port, AD9833_CS_Pin, x)
#define AD9833_SCL_Set(x)		HAL_GPIO_WritePin(AD9833_SCL_GPIO_Port, AD9833_SCL_Pin, x)
#define AD9833_SDA_Set(x)		HAL_GPIO_WritePin(AD9833_SDA_GPIO_Port, AD9833_SDA_Pin, x)

void AD9833_Config(uint16_t form, float freq, float phase);

#endif /* __AD9833_H__ */
