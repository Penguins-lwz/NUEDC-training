#ifndef __GPIO_H__
#define __GPIO_H__

#include "main.h"

#define LED_R_On		DL_GPIO_writePinsVal(LED_PORT, LED_R_PIN, LED_R_PIN)
#define LED_G_On		DL_GPIO_writePinsVal(LED_PORT, LED_G_PIN, LED_G_PIN)
#define LED_B_On		DL_GPIO_writePinsVal(LED_PORT, LED_B_PIN, LED_B_PIN)

#define LED_R_Off		DL_GPIO_writePinsVal(LED_PORT, LED_R_PIN, 0)
#define LED_G_Off		DL_GPIO_writePinsVal(LED_PORT, LED_G_PIN, 0)
#define LED_B_Off		DL_GPIO_writePinsVal(LED_PORT, LED_B_PIN, 0)

#define LED_R_Toggle	DL_GPIO_togglePins(LED_PORT, LED_R_PIN)
#define LED_G_Toggle	DL_GPIO_togglePins(LED_PORT, LED_G_PIN)
#define LED_B_Toggle	DL_GPIO_togglePins(LED_PORT, LED_B_PIN)

#endif /* __GPIO_H__ */
