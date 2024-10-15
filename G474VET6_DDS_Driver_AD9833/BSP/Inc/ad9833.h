#ifndef __AD9833_H__
#define __AD9833_H__

#include "main.h"

/* CubeMX Configuration Guide (SPI without DMA)               */
/* Mode:              Transmit Only Master (Software NSS)     */
/* Basic Parameters:  Motorola, 16 Bits, MSB First            */
/* Clock Parameters:  42.5 Mbit/s, CPOL = HIGH, CPHA = 1 Edge */
/* DMA Settings:      N/A                                     */
/* GPIO Settings:     High Speed (Include using analog SPI)   */
/* Remain default for unmentioned parameters.                 */

/* USER CODE BEGIN Configuration */
#define MCLK					25000000
#define DDS_USE_HARDWARE		0	// 0: Analog SPI, 1: Hardware SPI
#if (DDS_USE_HARDWARE)
  #include "spi.h"
  #define DDS_SPI				hspi1
#endif /* DDS_USE_HARDWARE */
/* USER CODE END Configuration */

#define DDS_FORM_SIN			((0 << 5) | (0 << 1) | (0 << 3))
#define DDS_FORM_TRI			((0 << 5) | (1 << 1) | (0 << 3))
#define DDS_FORM_MSB			((1 << 5) | (0 << 1) | (1 << 3))
#define DDS_FORM_MSB_DIV2		((1 << 5) | (0 << 1) | (0 << 3))

#define DDS_CS_Set(x)			HAL_GPIO_WritePin(DDS_CS_GPIO_Port, DDS_CS_Pin, x)
#if (DDS_USE_HARDWARE == 0)
  #define DDS_SCL_Set(x)		HAL_GPIO_WritePin(DDS_SCL_GPIO_Port, DDS_SCL_Pin, x)
  #define DDS_SDA_Set(x)		HAL_GPIO_WritePin(DDS_SDA_GPIO_Port, DDS_SDA_Pin, x)
#endif /* DDS_USE_HARDWARE */

void DDS_Config(uint16_t form, float freq, float phase);

#endif /* __AD9833_H__ */
