/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dac.c
  * @brief   This file provides code for the configuration
  *          of the DAC instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "dac.h"

/* USER CODE BEGIN 0 */
const uint16_t DAC_Data[DAC_DataSize] = {
    0x746, 0x787, 0x7C8, 0x808, 0x848, 0x887, 0x8C5, 0x903, 0x93F, 0x979,
    0x9B2, 0x9EA, 0xA1F, 0xA53, 0xA84, 0xAB3, 0xAE0, 0xB0A, 0xB32, 0xB57,
    0xB79, 0xB98, 0xBB4, 0xBCD, 0xBE2, 0xBF5, 0xC04, 0xC10, 0xC18, 0xC1D,
    0xC1F, 0xC1D, 0xC18, 0xC10, 0xC04, 0xBF5, 0xBE2, 0xBCD, 0xBB4, 0xB98,
    0xB79, 0xB57, 0xB32, 0xB0A, 0xAE0, 0xAB3, 0xA84, 0xA53, 0xA1F, 0x9EA,
    0x9B2, 0x979, 0x93F, 0x903, 0x8C5, 0x887, 0x848, 0x808, 0x7C8, 0x787,
    0x746, 0x705, 0x6C4, 0x684, 0x644, 0x605, 0x5C6, 0x589, 0x54D, 0x512,
    0x4D9, 0x4A2, 0x46C, 0x439, 0x407, 0x3D8, 0x3AB, 0x381, 0x35A, 0x335,
    0x313, 0x2F4, 0x2D8, 0x2BF, 0x2A9, 0x297, 0x288, 0x27C, 0x273, 0x26E,
    0x26D, 0x26E, 0x273, 0x27C, 0x288, 0x297, 0x2A9, 0x2BF, 0x2D8, 0x2F4,
    0x313, 0x335, 0x35A, 0x381, 0x3AB, 0x3D8, 0x407, 0x439, 0x46C, 0x4A2,
    0x4D9, 0x512, 0x54D, 0x589, 0x5C6, 0x605, 0x644, 0x684, 0x6C4, 0x705
};

const uint16_t DAC_Data_zipped[30] = {
    0x746, 0x848, 0x93F, 0xA1F, 0xAE0, 0xB79, 0xBE2, 0xC18, 0xC18, 0xBE2,
    0xB79, 0xAE0, 0xA1F, 0x93F, 0x848, 0x746, 0x644, 0x54D, 0x46C, 0x3AB,
    0x313, 0x2A9, 0x273, 0x273, 0x2A9, 0x313, 0x3AB, 0x46C, 0x54D, 0x644
};

const uint16_t DAC_arrValue[7] = {
	999, 499, 99, 49, 9, 4, 3
};

/* USER CODE END 0 */

DAC_HandleTypeDef hdac;
DMA_HandleTypeDef hdma_dac1;

/* DAC init function */
void MX_DAC_Init(void)
{

  /* USER CODE BEGIN DAC_Init 0 */

  /* USER CODE END DAC_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC_Init 1 */

  /* USER CODE END DAC_Init 1 */

  /** DAC Initialization
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT1 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_T6_TRGO;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC_Init 2 */

  /* USER CODE END DAC_Init 2 */

}

void HAL_DAC_MspInit(DAC_HandleTypeDef* dacHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(dacHandle->Instance==DAC)
  {
  /* USER CODE BEGIN DAC_MspInit 0 */

  /* USER CODE END DAC_MspInit 0 */
    /* DAC clock enable */
    __HAL_RCC_DAC_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**DAC GPIO Configuration
    PA4     ------> DAC_OUT1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* DAC DMA Init */
    /* DAC1 Init */
    hdma_dac1.Instance = DMA1_Stream5;
    hdma_dac1.Init.Channel = DMA_CHANNEL_7;
    hdma_dac1.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_dac1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_dac1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_dac1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_dac1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_dac1.Init.Mode = DMA_CIRCULAR;
    hdma_dac1.Init.Priority = DMA_PRIORITY_LOW;
    hdma_dac1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_dac1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(dacHandle,DMA_Handle1,hdma_dac1);

  /* USER CODE BEGIN DAC_MspInit 1 */

  /* USER CODE END DAC_MspInit 1 */
  }
}

void HAL_DAC_MspDeInit(DAC_HandleTypeDef* dacHandle)
{

  if(dacHandle->Instance==DAC)
  {
  /* USER CODE BEGIN DAC_MspDeInit 0 */

  /* USER CODE END DAC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DAC_CLK_DISABLE();

    /**DAC GPIO Configuration
    PA4     ------> DAC_OUT1
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4);

    /* DAC DMA DeInit */
    HAL_DMA_DeInit(dacHandle->DMA_Handle1);
  /* USER CODE BEGIN DAC_MspDeInit 1 */

  /* USER CODE END DAC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void myDAC_Start_DMA(myDAC_HandleTypeDef *myhdac)
{
	if (myhdac->idx < 6)
		HAL_DAC_Start_DMA(myhdac->hdac, myhdac->Channel, (uint32_t *)DAC_Data, DAC_DataSize, DAC_ALIGN_12B_R);
	else /* if (myhdac->idx == 6) */
		HAL_DAC_Start_DMA(myhdac->hdac, myhdac->Channel, (uint32_t *)DAC_Data_zipped, 30, DAC_ALIGN_12B_R);
	
	HAL_TIM_Base_Start(myhdac->htim);
}

void myDAC_Stop_DMA(myDAC_HandleTypeDef *myhdac)
{
	HAL_DAC_Stop_DMA(myhdac->hdac, myhdac->Channel);
	HAL_TIM_Base_Stop(myhdac->htim);
}

void myDAC_SetFreq(myDAC_HandleTypeDef *myhdac)
{
	myDAC_Stop_DMA(myhdac);
	__HAL_TIM_SET_AUTORELOAD(myhdac->htim, DAC_arrValue[myhdac->idx]);
	myDAC_Start_DMA(myhdac);
}

/* USER CODE END 1 */
