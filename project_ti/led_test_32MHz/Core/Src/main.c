#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init();

    while (1) {
		DL_GPIO_togglePins(LED_PORT, LED_W_PIN);
		delay_cycles(3200000);
    }
}
