/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 PC15 PC8
                           PC9 PC10 PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : KEY_S4_Pin */
  GPIO_InitStruct.Pin = KEY_S4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(KEY_S4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : KEY_S1_Pin KEY_S2_Pin KEY_S3_Pin */
  GPIO_InitStruct.Pin = KEY_S1_Pin|KEY_S2_Pin|KEY_S3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PD2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
uint8_t Key_Read(void)
{
	static uint16_t cnt = 0, idleCnt = 0;
	static uint8_t num = 0x00, lastNum = 0x00;
	
	// 本次触发时长 cnt 递增，间隔空闲时长 idleCnt 清零
	if (KEY1_Trigger) cnt++, idleCnt = 0, num = 0x01;
	else if (KEY2_Trigger) cnt++, idleCnt = 0, num = 0x02;
	else if (KEY3_Trigger) cnt++, idleCnt = 0, num = 0x03;
	else if (KEY4_Trigger) cnt++, idleCnt = 0, num = 0x04;
	
	// 在所有按键空闲时判断，若此前无按键触发
	else if (lastNum == 0x00)
	{
		// cnt < KEY_TH_TAP 视为无效，忽略本次触发
		if (cnt < KEY_TH_TAP) cnt = 0, num = 0x00;
		
		// cnt < KEY_TH_HOLD 视为短按，进入双击等待 lastNum
		else if (cnt < KEY_TH_HOLD) cnt = 0, lastNum = num;
		
		// cnt >= KEY_TH_HOLD 直接宣布长按
		else { cnt = 0; return num | 0x80; }
	}
	
	// 此前有按键触发且空闲时长 idleCnt >= KEY_TH_WAIT 宣布短按
	else if (++idleCnt >= KEY_TH_WAIT) { num = lastNum, lastNum = 0x00; return num | 0x00; }
	
	// cnt < KEY_TH_TAP 视为无效，忽略本次触发
	else if (cnt < KEY_TH_TAP) cnt = 0, num = 0x00;
	
	// cnt >= KEY_TH_TAP 视为第二次触发，若按键与上次相同，宣布双击
	else if (num == lastNum) { cnt = 0, lastNum = 0x00; return num | 0x40; }
	
	return 0x00;
}

/* USER CODE END 2 */
