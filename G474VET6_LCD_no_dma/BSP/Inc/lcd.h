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

#define BLACK			0x0000
#define RED				0xF800
#define ORANGE			0xFE00
#define YELLOW			0xFEE0
#define GREEN			0x07E0
#define BLUE			0x001F
#define PURPLE			0xF81F
#define WHITE			0xFFFF

#define LCD_180_inch	180		// 1.80 inch, 128 * 160 px, ST7735S , tbId = 665396916267
#define LCD_114_inch	114		// 1.14 inch, 135 * 240 px, ST7789V3, tbId = 665718901955
#define LCD_169_inch	169		// 1.69 inch, 240 * 280 px, ST7789VW, tbId = 666505851661

/* USER CODE BEGIN Configuration */
#define LCD_SPECS		LCD_180_inch
#define LCD_DIR			1
#define LCD_USE_DMA		0

#if (LCD_USE_DMA)
	#include "spi.h"
	#define LCD_hspi		hspi2
#endif /* LCD_USE_DMA */

/* USER CODE END Configuration */

#if (LCD_SPECS == LCD_180_inch)
	static const uint16_t LCD_PARAMS[4][5] = {
		{0x00, 128, 160, 2, 1},
		{0xA0, 160, 128, 1, 2},
		{0xC0, 128, 160, 2, 1},
		{0x60, 160, 128, 1, 2}};

#elif (LCD_SPECS == LCD_114_inch)
	#define LCD_ENABLE_INVERSION
	static const uint16_t LCD_PARAMS[4][5] = {
		{0x00, 135, 240, 52, 40},
		{0xA0, 240, 135, 40, 52},
		{0xC0, 135, 240, 53, 40},
		{0x60, 240, 135, 40, 53}};

#elif (LCD_SPECS == LCD_169_inch)
	#define LCD_ENABLE_INVERSION
	static const uint16_t LCD_PARAMS[4][5] = {
		{0x00, 240, 280, 0, 20},
		{0xA0, 280, 240, 20, 0},
		{0xC0, 240, 280, 0, 20},
		{0x60, 280, 240, 20, 0}};

#endif /* define LCD_PARAMS */

#define LCD_D			(LCD_PARAMS[LCD_DIR][0])
#define LCD_W			(LCD_PARAMS[LCD_DIR][1])
#define LCD_H			(LCD_PARAMS[LCD_DIR][2])
#define LCD_X			(LCD_PARAMS[LCD_DIR][3])
#define LCD_Y			(LCD_PARAMS[LCD_DIR][4])

void LCD_Init(void);
void LCD_ClearAll(uint16_t color);
void LCD_ClearArea(uint16_t xpos, uint16_t ypos, uint16_t xsize, uint16_t ysize, uint16_t color);
void LCD_ShowString(uint16_t xpos, uint16_t ypos, uint16_t ysize, uint16_t fc, uint16_t bc, const char *format, ...);

#endif /* __LCD_H__ */
