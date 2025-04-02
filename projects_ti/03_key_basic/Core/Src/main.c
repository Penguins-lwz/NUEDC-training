#include "main.h"
#include "gpio.h"

int main(void)
{
	SYSCFG_DL_init();
	
	while (1)
	{
		switch ((KEY1_Trigger << 0) | (KEY2_Trigger << 1))
		{
			/* S1 未按下，S2 未按下 */
			case 0x0: LED_R_Off, LED_G_Off, LED_B_Off; break;
			
			/* S1 已按下，S2 未按下 */
			case 0x1: LED_R_On,  LED_G_Off, LED_B_Off; break;
			
			/* S1 未按下，S2 已按下 */
			case 0x2: LED_R_Off, LED_G_On,  LED_B_Off; break;
			
			/* S1 已按下，S2 已按下 */
			case 0x3: LED_R_Off, LED_G_Off, LED_B_On;  break;
		}
	}
}
