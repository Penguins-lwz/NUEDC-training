#ifndef __AD9833_H__
#define __AD9833_H__

#include "main.h"

#define MCLK					25000000

#define DDS_FORM_SIN			((0 << 5) | (0 << 1) | (0 << 3))
#define DDS_FORM_TRI			((0 << 5) | (1 << 1) | (0 << 3))
#define DDS_FORM_MSB			((1 << 5) | (0 << 1) | (1 << 3))
#define DDS_FORM_MSB_DIV2		((1 << 5) | (0 << 1) | (0 << 3))

#define DDS_CS_Set(x)			HAL_GPIO_WritePin(DDS_CS_GPIO_Port, DDS_CS_Pin, x)
#define DDS_SCL_Set(x)			HAL_GPIO_WritePin(DDS_SCL_GPIO_Port, DDS_SCL_Pin, x)
#define DDS_SDA_Set(x)			HAL_GPIO_WritePin(DDS_SDA_GPIO_Port, DDS_SDA_Pin, x)

void DDS_Config(uint16_t form, float freq, float phase);

#endif /* __AD9833_H__ */
