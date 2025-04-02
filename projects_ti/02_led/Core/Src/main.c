#include "main.h"
#include "gpio.h"

int main(void)
{
	SYSCFG_DL_init();
	
	while (1)
	{
		LED_R_Toggle; DL_Delay(500);
		LED_R_Toggle; DL_Delay(500);
		LED_G_Toggle; DL_Delay(500);
		LED_G_Toggle; DL_Delay(500);
		LED_B_Toggle; DL_Delay(500);
		LED_B_Toggle; DL_Delay(500);
	}
}
