#ifndef __GPIO_H__
#define __GPIO_H__

#include "main.h"

#define LED_W_On		DL_GPIO_clearPins(LED_W_PORT, LED_W_PIN)
#define LED_R_On		DL_GPIO_setPins(LED_R_PORT, LED_R_PIN)
#define LED_G_On		DL_GPIO_setPins(LED_G_PORT, LED_G_PIN)
#define LED_B_On		DL_GPIO_setPins(LED_B_PORT, LED_B_PIN)

#define LED_W_Off		DL_GPIO_setPins(LED_W_PORT, LED_W_PIN)
#define LED_R_Off		DL_GPIO_clearPins(LED_R_PORT, LED_R_PIN)
#define LED_G_Off		DL_GPIO_clearPins(LED_G_PORT, LED_G_PIN)
#define LED_B_Off		DL_GPIO_clearPins(LED_B_PORT, LED_B_PIN)

#define LED_W_Toggle	DL_GPIO_togglePins(LED_W_PORT, LED_W_PIN)
#define LED_R_Toggle	DL_GPIO_togglePins(LED_R_PORT, LED_R_PIN)
#define LED_G_Toggle	DL_GPIO_togglePins(LED_G_PORT, LED_G_PIN)
#define LED_B_Toggle	DL_GPIO_togglePins(LED_B_PORT, LED_B_PIN)

#define KEY1_Trigger	(DL_GPIO_readPins(KEY_S1_PORT, KEY_S1_PIN) != 0)
#define KEY2_Trigger	(DL_GPIO_readPins(KEY_S2_PORT, KEY_S2_PIN) == 0)

uint8_t Key_Read(void);

#endif /*__GPIO_H__*/
