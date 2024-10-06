#include "lcd.h"
#include "font.h"

/* Private defines for FSMC communication, related to hardware connectivity. */
/* In this program, we use FSMC_NE4 and FSMC_A6 (in CubeMX), which means:    */
/*     FSMC_Bank1  = 0x60000000UL (fixed)                                    */
/*     LCD_CmdAdd  = 0x60000000UL + (4 - 1) * 0x04000000UL = 0x6C000000UL    */
/*     LCD_DataAdd = 0x6C000000UL | (1UL << (6 + 1))       = 0x6C000080UL    */

#define LCD_Cmd					(*(__IO uint16_t *)0x6C000000UL)
#define LCD_Data				(*(__IO uint16_t *)0x6C000080UL)
#define LCD_WriteCmd(cmd)		(LCD_Cmd = (cmd))
#define LCD_WriteData(data)		(LCD_Data = (data))
#define LCD_Write(cmd, data)	(LCD_Cmd = (cmd), LCD_Data = (data))

uint8_t LCD_Dir;
#define LCD_IsPortrait			(bool)((LCD_Dir & 0x20) == 0)
#define LCD_RangeX				(LCD_IsPortrait ? 480 : 800)
#define LCD_RangeY				(LCD_IsPortrait ? 800 : 480)

static void LCD_InteralInit(void)
{
	HAL_Delay(4);
	
	/* LV2 Page 1 enable */
	LCD_Write(0xF000, 0x55);
	LCD_Write(0xF001, 0xAA);
	LCD_Write(0xF002, 0x52);
	LCD_Write(0xF003, 0x08);
	LCD_Write(0xF004, 0x01);
	
	/* VCOM -2.0375V */
	LCD_Write(0xBE00, 0x00);
	LCD_Write(0xBE01, 0xA3);
	
	/* GAMSET: Gamma Setting */
	LCD_Write(0x2600, 0x01);
	
	/* COLMOD: Interface pixel format (16-bit/pixel) */
	LCD_Write(0x3A00, 0x55);
	
	/* SLPOUT: Sleep out & booster on */
	LCD_WriteCmd(0x1100);
	HAL_Delay(4);
	
	/* DISPON: Display on */
	LCD_WriteCmd(0x2900);
}

void LCD_Init()
{
	LCD_InteralInit();
	LCD_SetDirection(Dir_Rotate90);
	
	LCD_ClearAll(WHITE);
	LCD_ShowString(40, 40, 32, BLACK, WHITE, "F407ZGT6 FSMC Connected.");
	
	HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, 1);
}

void LCD_SetDirection(uint8_t dir)
{
	LCD_Write(0x3600, LCD_Dir = dir);
}

static void LCD_SetArea(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
	static uint16_t _xs = 0xFFFF;
	static uint16_t _ys = 0xFFFF;
	static uint16_t _xe = 0xFFFF;
	static uint16_t _ye = 0xFFFF;
	
	if (_xs != xs) _xs = xs, LCD_Write(0x2A00, xs >> 8), LCD_Write(0x2A01, xs & 0xFF);
	if (_xe != xe) _xe = xe, LCD_Write(0x2A02, xe >> 8), LCD_Write(0x2A03, xe & 0xFF);
	if (_ys != ys) _ys = ys, LCD_Write(0x2B00, ys >> 8), LCD_Write(0x2B01, ys & 0xFF);
	if (_ye != ye) _ye = ye, LCD_Write(0x2B02, ye >> 8), LCD_Write(0x2B03, ye & 0xFF);
	
	LCD_WriteCmd(0x2C00);
}

static uint8_t *LCD_SearchFont(uint16_t ysize, char chr)
{
	if (chr < 32 || chr > 126) return NULL;
	if (ysize == 16) return (uint8_t *)font1608[chr - 32];
	if (ysize == 24) return (uint8_t *)font2412[chr - 32];
	if (ysize == 32) return (uint8_t *)font3216[chr - 32];
	return NULL;
}

void LCD_ClearArea(uint16_t xpos, uint16_t ypos, uint16_t xsize, uint16_t ysize, uint16_t color)
{
	LCD_SetArea(xpos, ypos, xpos + xsize, ypos + ysize);
	for (uint32_t i = 0; i < ysize * xsize; ++i)
		LCD_WriteData(color);
}

void LCD_ClearAll(uint16_t color)
{
	LCD_ClearArea(0, 0, LCD_RangeX, LCD_RangeY, color);
	LCD_ShowFigure(170, 360, 80, 80, ~color, color, github80x80);
	LCD_ShowFigure(290, 375, 320, 80, ~color, color, sign320x80);
	LCD_ShowFigure(640, 40, 120, 64, 0x0109, color, stlogo120x64);
}

static void LCD_ShowPoint(uint16_t xpos, uint16_t ypos, uint16_t color)
{
	LCD_SetArea(xpos, ypos, LCD_RangeX, LCD_RangeY);
	LCD_WriteData(color);
}

static void LCD_ShowChar(uint16_t xpos, uint16_t ypos, uint16_t ysize, uint16_t fc, uint16_t bc, char chr)
{
	uint8_t *font = LCD_SearchFont(ysize, chr);
	if (font == NULL) return;
	for (uint32_t i = 0; i < ysize * ysize / 2; ++i)
		LCD_ShowPoint(xpos + i / ysize, ypos + i % ysize, (font[i / 8] & (0x01 << (i % 8))) ? fc : bc);
}

void LCD_ShowString(uint16_t xpos, uint16_t ypos, uint16_t ysize, uint16_t fc, uint16_t bc, const char *format, ...)
{
	uint16_t xsize = ysize / 2;
	char str[101];
	va_list ap;
	va_start(ap, format);
	int Size = vsnprintf(str, (LCD_RangeX - xpos) / xsize, format, ap);
	if (Size <= 0) Error_Handler();
	va_end(ap);
	for (uint16_t i = 0; i < Size; ++i)
		LCD_ShowChar(xpos + i * xsize, ypos, ysize, fc, bc, str[i]);
}

void LCD_ShowFigure(uint16_t xpos, uint16_t ypos, uint16_t xsize, uint16_t ysize, uint16_t fc, uint16_t bc, const uint8_t *fig)
{
	for (uint32_t i = 0; i < ysize * xsize; ++i)
		LCD_ShowPoint(xpos + i / ysize, ypos + i % ysize, (fig[i / 8] & (0x01 << (i % 8))) ? fc : bc);
}
