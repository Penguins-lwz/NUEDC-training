#include "lcd.h"

#define LCD_Write(IsData, pData)	do { SPI_Buf = pData; LCD_Transmit(IsData, &SPI_Buf, 1); } while (0)
#define LCD_WriteCmd(pData)			do { LCD_Write(0, (pData)); } while (0)
#define LCD_WriteData8(pData)		do { LCD_Write(1, (pData)); } while (0)
#define LCD_WriteData16(pData)		do { LCD_WriteData8((pData) >> 8); LCD_WriteData8((pData) & 0xFF); } while (0)

static uint8_t SPI_Buf;
static uint8_t LCD_Buf[2 * LCD_RangeX * LCD_RangeY];

static void LCD_Transmit(bool IsData, uint8_t *pData, uint16_t Size)
{
	LCD_DC_Set(IsData);
	
	#if (LCD_USE_HARDWARE)
	HAL_SPI_Transmit_DMA(&LCD_SPI, pData, Size);
	while (LCD_SPI.State != HAL_SPI_STATE_READY || LCD_SPI.hdmatx->State != HAL_DMA_STATE_READY);
	
	#else
	for (uint16_t i = 0; i < Size; ++i)
	{
		for (uint8_t j = 0; j < 8; ++j)
		{
			LCD_SDA_Set(pData[i] & (0x80 >> j));
			LCD_SCL_Set(1);
			LCD_SCL_Set(0);
		}
	}
	
	#endif
}

static void LCD_InteralInit(void)
{
	LCD_CS_Set(0);
	
	// SLPOUT: Exit sleep mode
	LCD_WriteCmd(0x11); HAL_Delay(4);
	
	// MADCTL: Set display direction
	LCD_WriteCmd(0x36);
	LCD_WriteData8(LCD_DIR_CODE);
	
	// COLMOD: Set color coding format
	LCD_WriteCmd(0x3A);
	LCD_WriteData8(0x55);
	
	// INVON: Enable display inversion
	LCD_WriteCmd(0x21); 
	
	// DISPON: Display On
	LCD_WriteCmd(0x29);
	
	LCD_CS_Set(1);
}

void LCD_Init(void)
{
	LCD_RST_Set(0); HAL_Delay(0);
	LCD_RST_Set(1); HAL_Delay(4);
	LCD_InteralInit();
}

static void LCD_WriteBuf(uint16_t xpos, uint16_t ypos, uint16_t color)
{
	uint32_t pnum = xpos + ypos * LCD_RangeX;
	LCD_Buf[2 * pnum] = color >> 8;
	LCD_Buf[2 * pnum + 1] = color & 0xFF;
}

static void LCD_Update(uint16_t xpos, uint16_t ypos, uint16_t xsize, uint16_t ysize)
{
	LCD_CS_Set(0);
	
	LCD_WriteCmd(0x2A);
	LCD_WriteData16(xpos + LCD_BIAS_X);
	LCD_WriteData16(xpos + xsize + LCD_BIAS_X - 1);
	
	LCD_WriteCmd(0x2B);
	LCD_WriteData16(ypos + LCD_BIAS_Y);
	LCD_WriteData16(ypos + ysize + LCD_BIAS_Y - 1);
	
	LCD_WriteCmd(0x2C);
	for (uint16_t i = 0; i < ysize; ++i)
		LCD_Transmit(1, &LCD_Buf[2 * (xpos + (ypos + i) * LCD_RangeX)], 2 * xsize);
	
	LCD_CS_Set(1);
}

void LCD_ClearArea(uint16_t xpos, uint16_t ypos, uint16_t xsize, uint16_t ysize, uint16_t color)
{
	for (uint32_t i = 0; i < ysize * xsize; ++i)
		LCD_WriteBuf(xpos + i / ysize, ypos + i % ysize, color);
	LCD_Update(xpos, ypos, xsize, ysize);
}

void LCD_ClearAll(uint16_t color)
{
	LCD_ClearArea(0, 0, LCD_RangeX, LCD_RangeY, color);
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

static void LCD_ShowChar(uint16_t xpos, uint16_t ypos, uint16_t ysize, bool overwrite, uint16_t fc, uint16_t bc, char chr)
{
	uint8_t *font = LCD_SearchFont(ysize, chr);
	if (font == NULL) return;
	
	uint8_t ynum = (ysize + 7) / 8 * 8;
	for (uint32_t i = 0; i < ynum * ysize / 2; ++i)
		if (i % ynum >= ysize) continue;
		else if (font[i / 8] & (0x01 << (i % 8))) LCD_WriteBuf(xpos + i / ynum, ypos + i % ynum, fc);
		else if (overwrite) LCD_WriteBuf(xpos + i / ynum, ypos + i % ynum, bc);
}

void LCD_ShowString(uint16_t xpos, uint16_t ypos, uint16_t ysize, bool overwrite, uint16_t fc, uint16_t bc, const char *format, ...)
{
	uint16_t xsize = ysize / 2;
	
	char str[41];
	va_list ap;
	va_start(ap, format);
	int xnum = vsnprintf(str, (LCD_RangeX - xpos) / xsize, format, ap);
	if (xnum <= 0) Error_Handler();
	va_end(ap);
	
	for (uint16_t i = 0; i < xnum; ++i)
		LCD_ShowChar(xpos + i * xsize, ypos, ysize, overwrite, fc, bc, str[i]);
	LCD_Update(xpos, ypos, xnum * ysize / 2, ysize);
}
