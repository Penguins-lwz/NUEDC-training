#include "main.h"
#include "lcd.h"

int main(void)
{
	SYSCFG_DL_init();
	LCD_Init();
	
	LCD_ClearAll(BLACK);	DL_Delay(200);
	LCD_ClearAll(RED);		DL_Delay(200);
	LCD_ClearAll(ORANGE);	DL_Delay(200);
	LCD_ClearAll(YELLOW);	DL_Delay(200);
	LCD_ClearAll(GREEN);	DL_Delay(200);
	LCD_ClearAll(BLUE);		DL_Delay(200);
	LCD_ClearAll(PURPLE);	DL_Delay(200);
	LCD_ClearAll(WHITE);	DL_Delay(200);
	
	uint16_t xpos = (LCD_W - 128) / 4;
	uint16_t ypos = (LCD_H - 148) / 3;
	
	sprintf(LCD_str, "LCD TEST");
	LCD_ShowString(xpos, ypos + 0, 32, BLACK, WHITE);
	sprintf(LCD_str, "Penguins");
	LCD_ShowString(xpos, ypos + 32, 32, BLACK, WHITE);
	sprintf(LCD_str, "F3216");
	LCD_ShowString(xpos, ypos + 64, 32, BLACK, WHITE);
	sprintf(LCD_str, "F2412");
	LCD_ShowString(xpos, ypos + 96, 24, BLACK, WHITE);
	sprintf(LCD_str, "F1608");
	LCD_ShowString(xpos, ypos + 120, 16, BLACK, WHITE);
	sprintf(LCD_str, "F1206");
	LCD_ShowString(xpos, ypos + 136, 12, BLACK, WHITE);
	
	while (1)
	{
		
	}
}
