#include "lcd.h"

#if (LCD_USE_DMA)
static uint8_t LCD_BUF[2 * LCD_W * LCD_H];

#else
#define LCD_SCL_WR(x)	HAL_GPIO_WritePin(LCD_SCL_GPIO_Port, LCD_SCL_Pin, x)
#define LCD_SDA_WR(x)	HAL_GPIO_WritePin(LCD_SDA_GPIO_Port, LCD_SDA_Pin, x)

#endif /* LCD_USE_DMA */

#define LCD_RST_WR(x)	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, x)
#define LCD_CS_WR(x)	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, x)
#define LCD_DC_WR(x)	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, x)

static void LCD_Transmit(bool isData, uint8_t *pData, uint16_t Size)
{
	LCD_DC_WR(isData);
	
	#if (LCD_USE_DMA)
	HAL_SPI_Transmit_DMA(&LCD_hspi, pData, Size);
	while (LCD_hspi.State != HAL_SPI_STATE_READY || LCD_hspi.hdmatx->State != HAL_DMA_STATE_READY);
	
	#else
	for (uint16_t i = 0; i < Size; ++i)
		for (uint8_t j = 0; j < 8; ++j)
		{
			LCD_SDA_WR(pData[i] & (0x80 >> j));
			LCD_SCL_WR(1);
			LCD_SCL_WR(0);
		}
	
	#endif
}

static inline void LCD_WR(bool isData, uint8_t data)
{
	LCD_Transmit(isData, &data, 1);
}

static inline void LCD_WR_CMD(uint8_t data)
{
	LCD_WR(0, data);
}

static inline void LCD_WR_DAT8(uint8_t data)
{
	LCD_WR(1, data);
}

static inline void LCD_WR_DAT16(uint16_t data)
{
	LCD_WR(1, data >> 8);
	LCD_WR(1, data & 0xFF);
}

void LCD_Init(void)
{
	LCD_RST_WR(0); HAL_Delay(0);
	LCD_RST_WR(1); HAL_Delay(4);
	
	LCD_CS_WR(0);
	
	// SLPOUT: Exit sleep mode
	LCD_WR_CMD(0x11);
	HAL_Delay(119);
	
	// MADCTL: Set display direction
	LCD_WR_CMD(0x36);
	LCD_WR_DAT8(LCD_D);
	
	// COLMOD: Set color coding format
	LCD_WR_CMD(0x3A);
	LCD_WR_DAT8(0x55);
	
	// INVON: Enable display inversion
	#if defined(LCD_ENABLE_INVERSION)
		LCD_WR_CMD(0x21);
	#endif
	
	// DISPON: Display On
	LCD_WR_CMD(0x29);
	
	LCD_CS_WR(1);
}

static void LCD_SetAddress(uint16_t xpos, uint16_t ypos, uint16_t xsize, uint16_t ysize)
{
	LCD_WR_CMD(0x2A);
	LCD_WR_DAT16(xpos + LCD_X);
	LCD_WR_DAT16(xpos + LCD_X + xsize - 1);
	LCD_WR_CMD(0x2B);
	LCD_WR_DAT16(ypos + LCD_Y);
	LCD_WR_DAT16(ypos + LCD_Y + ysize - 1);
	LCD_WR_CMD(0x2C);
}

#if (LCD_USE_DMA)
static void LCD_WriteBuf(uint16_t xpos, uint16_t ypos, uint16_t color)
{
	uint32_t pnum = xpos + ypos * LCD_W;
	LCD_BUF[2 * pnum] = color >> 8;
	LCD_BUF[2 * pnum + 1] = color & 0xFF;
}

static void LCD_Update(uint16_t xpos, uint16_t ypos, uint16_t xsize, uint16_t ysize)
{
	LCD_CS_WR(0);
	LCD_SetAddress(xpos, ypos, xsize, ysize);
	for (uint16_t i = 0; i < ysize; ++i)
		LCD_Transmit(1, &LCD_BUF[2 * (xpos + (ypos + i) * LCD_W)], 2 * xsize);
	LCD_CS_WR(1);
}

#endif /* LCD_USE_DMA */

void LCD_ClearArea(uint16_t xpos, uint16_t ypos, uint16_t xsize, uint16_t ysize, uint16_t color)
{
	#if (LCD_USE_DMA)
	for (uint32_t i = 0; i < ysize * xsize; ++i)
		LCD_WriteBuf(xpos + i / ysize, ypos + i % ysize, color);
	LCD_Update(xpos, ypos, xsize, ysize);
	
	#else
	LCD_CS_WR(0);
	LCD_SetAddress(xpos, ypos, xsize, ysize);
	for (uint32_t i = 0; i < ysize * xsize; ++i)
		LCD_WR_DAT16(color);
	LCD_CS_WR(1);
	
	#endif /* LCD_USE_DMA */
}

void LCD_ClearAll(uint16_t color)
{
	LCD_ClearArea(0, 0, LCD_W, LCD_H, color);
}

static uint8_t *LCD_SearchFont(uint16_t ysize, char chr)
{
	if (chr < 32 || chr > 126) return NULL;
	if (ysize == 12) return (uint8_t *)font1206[chr - 32];
	if (ysize == 16) return (uint8_t *)font1608[chr - 32];
	if (ysize == 24) return (uint8_t *)font2412[chr - 32];
	if (ysize == 32) return (uint8_t *)font3216[chr - 32];
	return NULL;
}

static void LCD_ShowChar(uint16_t xpos, uint16_t ypos, uint16_t ysize, uint16_t fc, uint16_t bc, char chr)
{
	uint8_t *font = LCD_SearchFont(ysize, chr);
	if (font == NULL) return;
	
	uint8_t xsize = ysize / 2;
	uint8_t ybyte = (ysize + 7) / 8;
	
	#if (LCD_USE_DMA)
	for (uint16_t i = 0; i < ysize; ++i)
		for (uint16_t j = 0; j < xsize; ++j)
			LCD_WriteBuf(xpos + j, ypos + i, font[ybyte * j + i / 8] & (0x01 << (i % 8)) ? fc : bc);
	
	#else
	LCD_SetAddress(xpos, ypos, xsize, ysize);
	for (uint16_t i = 0; i < ysize; ++i)
		for (uint16_t j = 0; j < xsize; ++j)
			LCD_WR_DAT16(font[ybyte * j + i / 8] & (0x01 << (i % 8)) ? fc : bc);
	
	#endif /* LCD_USE_DMA */
}

void LCD_ShowString(uint16_t xpos, uint16_t ypos, uint16_t ysize, uint16_t fc, uint16_t bc, const char *format, ...)
{
	uint16_t xsize = ysize / 2;
	
	char str[48];
	va_list ap;
	va_start(ap, format);
	int xnum = vsnprintf(str, (LCD_W - xpos) / xsize, format, ap);
	va_end(ap);
	
	#if (LCD_USE_DMA)
	for (uint16_t i = 0; i < xnum; ++i)
		LCD_ShowChar(xpos + i * xsize, ypos, ysize, fc, bc, str[i]);
	LCD_Update(xpos, ypos, xnum * ysize / 2, ysize);
	
	#else
	LCD_CS_WR(0);
	for (uint16_t i = 0; i < xnum; ++i)
		LCD_ShowChar(xpos + i * xsize, ypos, ysize, fc, bc, str[i]);
	LCD_CS_WR(1);
	
	#endif /* LCD_USE_DMA */
}
