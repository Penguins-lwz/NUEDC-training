#include "lcd.h"

#define LCD_SCL_WR(x)	DL_GPIO_writePinsVal(LCD_PORT, LCD_SCL_PIN, x ? LCD_SCL_PIN : 0)
#define LCD_SDA_WR(x)	DL_GPIO_writePinsVal(LCD_PORT, LCD_SDA_PIN, x ? LCD_SDA_PIN : 0)
#define LCD_RST_WR(x)	DL_GPIO_writePinsVal(LCD_PORT, LCD_RST_PIN, x ? LCD_RST_PIN : 0)
#define LCD_CS_WR(x)	DL_GPIO_writePinsVal(LCD_PORT, LCD_CS_PIN, x ? LCD_CS_PIN : 0)
#define LCD_DC_WR(x)	DL_GPIO_writePinsVal(LCD_PORT, LCD_DC_PIN, x ? LCD_DC_PIN : 0)

char LCD_str[48];

static void LCD_WR(bool isData, uint8_t data)
{
	LCD_DC_WR(isData);
	for (uint8_t j = 0; j < 8; ++j)
	{
		LCD_SDA_WR(data & (0x80 >> j));
		LCD_SCL_WR(1);
		LCD_SCL_WR(0);
	}
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
	LCD_RST_WR(0); DL_Delay(1);
	LCD_RST_WR(1); DL_Delay(120);
	
	LCD_CS_WR(0);
	
	// SLPOUT: Exit sleep mode
	LCD_WR_CMD(0x11);
	DL_Delay(120);
	
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

void LCD_ClearArea(uint16_t xpos, uint16_t ypos, uint16_t xsize, uint16_t ysize, uint16_t color)
{
	LCD_CS_WR(0);
	LCD_SetAddress(xpos, ypos, xsize, ysize);
	for (uint32_t i = 0; i < ysize * xsize; ++i)
		LCD_WR_DAT16(color);
	LCD_CS_WR(1);
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
	LCD_SetAddress(xpos, ypos, xsize, ysize);
	for (uint8_t i = 0; i < ysize * xsize / 8; ++i)
		for (uint8_t j = 0; j < 8; ++j)
			LCD_WR_DAT16(font[i] & (0x01 << j) ? fc : bc);
}

void LCD_ShowString(uint16_t xpos, uint16_t ypos, uint16_t ysize, uint16_t fc, uint16_t bc)
{
	uint16_t xsize = ysize / 2;
	LCD_str[(LCD_W - xpos) / xsize] = 0;
	LCD_CS_WR(0);
	for (uint16_t i = 0; LCD_str[i]; ++i)
		LCD_ShowChar(xpos + i * xsize, ypos, ysize, fc, bc, LCD_str[i]);
	LCD_CS_WR(1);
}
