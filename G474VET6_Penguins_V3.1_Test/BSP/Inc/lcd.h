#ifndef __LCD_H__
#define __LCD_H__

#include "main.h"
#include "font.h"

/* CubeMX Configuration Guide (SPI with DMA)                 */
/* Mode:              Transmit Only Master (Software NSS)    */
/* Basic Parameters:  Motorola, 8 Bits, MSB First            */
/* Clock Parameters:  42.5 Mbit/s, CPOL = LOW, CPHA = 1 Edge */
/* DMA Settings:      SPIx_TX, Normal, Byte, Byte            */
/* GPIO Settings:     High Speed (Include using analog SPI)  */
/* Remain default for unmentioned parameters.                */

#define BLACK					((uint16_t)0x0000)
#define RED						((uint16_t)0xF800)
#define ORANGE					((uint16_t)0xFE00)
#define YELLOW					((uint16_t)0xFEE0)
#define GREEN					((uint16_t)0x07E0)
#define BLUE					((uint16_t)0x001F)
#define PURPLE					((uint16_t)0xF81F)
#define WHITE					((uint16_t)0xFFFF)

/* USER CODE BEGIN Configuration */
#define LCD_DIR					3	// x(0..3): Rotate x * 90 degree
#define LCD_USE_HARDWARE		1	// 0: Analog SPI, 1: Hardware SPI
#if (LCD_USE_HARDWARE)
  #include "spi.h"
  #define LCD_SPI				hspi4
#endif /* LCD_USE_HARDWARE */
/* USER CODE END Configuration */

#if (LCD_DIR == 0)
  #define LCD_DIR_CODE			((uint8_t)0x00)
  #define LCD_BIAS_X			((uint16_t)52)
  #define LCD_BIAS_Y			((uint16_t)40)
#elif (LCD_DIR == 1)
  #define LCD_DIR_CODE			((uint8_t)0xA0)
  #define LCD_BIAS_X			((uint16_t)40)
  #define LCD_BIAS_Y			((uint16_t)52)
#elif (LCD_DIR == 2)
  #define LCD_DIR_CODE			((uint8_t)0xC0)
  #define LCD_BIAS_X			((uint16_t)53)
  #define LCD_BIAS_Y			((uint16_t)40)
#elif (LCD_DIR == 3)
  #define LCD_DIR_CODE			((uint8_t)0x60)
  #define LCD_BIAS_X			((uint16_t)40)
  #define LCD_BIAS_Y			((uint16_t)53)
#endif

#if (LCD_DIR % 2 == 0)
  #define LCD_RangeX			((uint16_t)135)
  #define LCD_RangeY			((uint16_t)240)
#elif (LCD_DIR % 2 == 1)
  #define LCD_RangeX			((uint16_t)240)
  #define LCD_RangeY			((uint16_t)135)
#endif

#define LCD_RST_Set(x)			HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, x)
#define LCD_CS_Set(x)			HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, x)
#define LCD_DC_Set(x)			HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, x)
#if (LCD_USE_HARDWARE == 0)
  #define LCD_SCL_Set(x)		HAL_GPIO_WritePin(LCD_SCL_GPIO_Port, LCD_SCL_Pin, x)
  #define LCD_SDA_Set(x)		HAL_GPIO_WritePin(LCD_SDA_GPIO_Port, LCD_SDA_Pin, x)
#endif /* LCD_USE_HARDWARE */

void LCD_Init(void);
void LCD_ClearAll(uint16_t color);
void LCD_ClearArea(uint16_t xpos, uint16_t ypos, uint16_t xsize, uint16_t ysize, uint16_t color);
void LCD_ShowString(uint16_t xpos, uint16_t ypos, uint16_t ysize, bool overwrite, uint16_t fc, uint16_t bc, const char *format, ...);

#endif /* __LCD_H__ */
