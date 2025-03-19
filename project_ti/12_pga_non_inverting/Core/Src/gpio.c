#include "gpio.h"

uint8_t Key_Read(void)
{
    static uint16_t cnt = 0;
    static uint8_t num = 0;
    if (KEY1_Trigger) cnt++, num = 1;
    else if (KEY2_Trigger) cnt++, num = 2;
    else if (cnt < 10) cnt = 0, num = 0;
    else if (cnt < 40) { cnt = 0; return num; }
    else { cnt = 0; return num | 0x80; }
    return 0;
}
