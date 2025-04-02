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
const uint32_t DAC_DualData[DAC_DataSize] = {
	0x04CC0800, 0x04CE0866, 0x04D308CD, 0x04DB0932, 0x04E60997,
	0x04F509FA, 0x05060A5A, 0x051A0AB9, 0x05320B15, 0x054C0B6D,
	0x05690BC2, 0x05880C14, 0x05AA0C61, 0x05CF0CAA, 0x05F50CEE,
	0x061E0D2D, 0x06490D67, 0x06750D9B, 0x06A30DCA, 0x06D20DF2,
	0x07020E15, 0x07340E32, 0x07660E48, 0x07990E59, 0x07CC0E62,
	0x08000E66, 0x08330E62, 0x08660E59, 0x08990E48, 0x08CB0E32,
	0x08FD0E15, 0x092D0DF2, 0x095C0DCA, 0x098A0D9B, 0x09B60D67,
	0x09E10D2D, 0x0A0A0CEE, 0x0A300CAA, 0x0A550C61, 0x0A770C14,
	0x0A960BC2, 0x0AB30B6D, 0x0ACD0B15, 0x0AE50AB9, 0x0AF90A5A,
	0x0B0A09FA, 0x0B190997, 0x0B240932, 0x0B2C08CD, 0x0B310866,
	0x0B3207FF, 0x0B310799, 0x0B2C0732, 0x0B2406CD, 0x0B190668,
	0x0B0A0605, 0x0AF905A5, 0x0AE50546, 0x0ACD04EA, 0x0AB30492,
	0x0A96043D, 0x0A7703EB, 0x0A55039E, 0x0A300355, 0x0A0A0311,
	0x09E102D2, 0x09B60298, 0x098A0264, 0x095C0235, 0x092D020D,
	0x08FD01EA, 0x08CB01CD, 0x089901B7, 0x086601A6, 0x0833019D,
	0x0800019A, 0x07CC019D, 0x079901A6, 0x076601B7, 0x073401CD,
	0x070201EA, 0x06D2020D, 0x06A30235, 0x06750264, 0x06490298,
	0x061E02D2, 0x05F50311, 0x05CF0355, 0x05AA039E, 0x058803EB,
	0x0569043D, 0x054C0492, 0x053204EA, 0x051A0546, 0x050605A5,
	0x04F50605, 0x04E60668, 0x04DB06CD, 0x04D30732, 0x04CE0799
};

/* USER CODE END 0 */

DAC_HandleTypeDef hdac1;
DMA_HandleTypeDef hdma_dac1_ch1;

/* DAC1 init function */
void MX_DAC1_Init(void)
{

  /* USER CODE BEGIN DAC1_Init 0 */

  /* USER CODE END DAC1_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC1_Init 1 */

  /* USER CODE END DAC1_Init 1 */

  /** DAC Initialization
  */
  hdac1.Instance = DAC1;
  if (HAL_DAC_Init(&hdac1) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT1 config
  */
  sConfig.DAC_HighFrequency = DAC_HIGH_FREQUENCY_INTERFACE_MODE_AUTOMATIC;
  sConfig.DAC_DMADoubleDataMode = DISABLE;
  sConfig.DAC_SignedFormat = DISABLE;
  sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
  sConfig.DAC_Trigger = DAC_TRIGGER_T7_TRGO;
  sConfig.DAC_Trigger2 = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_EXTERNAL;
  sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT2 config
  */
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC1_Init 2 */

  /* USER CODE END DAC1_Init 2 */

}

void HAL_DAC_MspInit(DAC_HandleTypeDef* dacHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(dacHandle->Instance==DAC1)
  {
  /* USER CODE BEGIN DAC1_MspInit 0 */

  /* USER CODE END DAC1_MspInit 0 */
    /* DAC1 clock enable */
    __HAL_RCC_DAC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**DAC1 GPIO Configuration
    PA4     ------> DAC1_OUT1
    PA5     ------> DAC1_OUT2
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* DAC1 DMA Init */
    /* DAC1_CH1 Init */
    hdma_dac1_ch1.Instance = DMA1_Channel4;
    hdma_dac1_ch1.Init.Request = DMA_REQUEST_DAC1_CHANNEL1;
    hdma_dac1_ch1.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_dac1_ch1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_dac1_ch1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_dac1_ch1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_dac1_ch1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_dac1_ch1.Init.Mode = DMA_CIRCULAR;
    hdma_dac1_ch1.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_dac1_ch1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(dacHandle,DMA_Handle1,hdma_dac1_ch1);

  /* USER CODE BEGIN DAC1_MspInit 1 */

  /* USER CODE END DAC1_MspInit 1 */
  }
}

void HAL_DAC_MspDeInit(DAC_HandleTypeDef* dacHandle)
{

  if(dacHandle->Instance==DAC1)
  {
  /* USER CODE BEGIN DAC1_MspDeInit 0 */

  /* USER CODE END DAC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DAC1_CLK_DISABLE();

    /**DAC1 GPIO Configuration
    PA4     ------> DAC1_OUT1
    PA5     ------> DAC1_OUT2
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4|GPIO_PIN_5);

    /* DAC1 DMA DeInit */
    HAL_DMA_DeInit(dacHandle->DMA_Handle1);
  /* USER CODE BEGIN DAC1_MspDeInit 1 */

  /* USER CODE END DAC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void myDAC_DualStart_DMA(myDAC_HandleTypeDef *myhdac)
{
	HAL_DACEx_DualStart_DMA(myhdac->hdac, DAC_CHANNEL_1, DAC_DualData, DAC_DataSize, DAC_ALIGN_12B_R);
	HAL_TIM_Base_Start(myhdac->htim);
}

void myDAC_DualStop_DMA(myDAC_HandleTypeDef *myhdac)
{
	HAL_DACEx_DualStop_DMA(myhdac->hdac, DAC_CHANNEL_1);
	HAL_TIM_Base_Stop(myhdac->htim);
}

/* USER CODE END 1 */
