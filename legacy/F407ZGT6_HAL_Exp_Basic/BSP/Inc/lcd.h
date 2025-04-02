#ifndef __LCD_H
#define __LCD_H

#include "main.h"

#define Dir_Rotate0			((uint8_t)0x00)
#define Dir_Rotate90		((uint8_t)0xA0)
#define Dir_Rotate180		((uint8_t)0xC0)
#define Dir_Rotate270		((uint8_t)0x60)

#define BLACK				((uint16_t)0x0000)
#define RED					((uint16_t)0xF800)
#define ORANGE				((uint16_t)0xFE00)
#define YELLOW				((uint16_t)0xFEE0)
#define GREEN				((uint16_t)0x07E0)
#define BLUE				((uint16_t)0x001F)
#define PURPLE				((uint16_t)0xF81F)
#define WHITE				((uint16_t)0xFFFF)

void LCD_Init();
void LCD_SetDirection(uint8_t dir);

void LCD_ClearAll(uint16_t color);
void LCD_ClearArea(uint16_t xpos, uint16_t ypos, uint16_t xsize, uint16_t ysize, uint16_t color);
void LCD_ShowString(uint16_t xpos, uint16_t ypos, uint16_t ysize, uint16_t fc, uint16_t bc, const char *format, ...);
void LCD_ShowFigure(uint16_t xpos, uint16_t ypos, uint16_t xsize, uint16_t ysize, uint16_t fc, uint16_t bc, const uint8_t *fig);

#endif /* __LCD_H */
