/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "fir.h"
#include "fft.h"
#include "ad9833.h"
#include "ad9959.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
myUART_HandleTypeDef myUART = { .huart = &huart1, .RxMsgUsed = true };
myADC_HandleTypeDef myADC = { .hadc = &hadc5, .htim = &htim6, .ConvFinish = false };
myDAC_HandleTypeDef myDAC = { .hdac = &hdac2, .htim = &htim7, .channel = DAC_CHANNEL_1 };
myDualADC_HandleTypeDef myDualADC = { .hadc_master = &hadc1, .hadc_slave = &hadc2, .htim = &htim6, .ConvFinish = false };
myDualDAC_HandleTypeDef myDualDAC = { .hdac = &hdac1, .htim = &htim7 };

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Key_Process(uint8_t keyNum);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart == myUART.huart)
	{
		if (myUART.RxMsgUsed == true)
		{
			myUART_Receive_DMA(&myUART);
			myUART_Transmit_DMA(&myUART, "RxMsg: %s", myUART.RxMsg);
		}
		myUART_Start_Receive_DMA(&myUART);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim17)
	{
		Key_Process(Key_Read());
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	if (hadc == myADC.hadc)
	{
		myADC_Stop_DMA(&myADC);
		myADC.ConvFinish = true;
	}
	else if (hadc == myDualADC.hadc_master)
	{
		myADC_DualStop_DMA(&myDualADC);
		myDualADC.ConvFinish = true;
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_SPI4_Init();
  MX_TIM17_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC5_Init();
  MX_DAC1_Init();
  MX_DAC2_Init();
  /* USER CODE BEGIN 2 */
  LCD_Init();
  LCD_ClearAll(RED);	HAL_Delay(200);
  LCD_ClearAll(ORANGE);	HAL_Delay(200);
  LCD_ClearAll(YELLOW);	HAL_Delay(200);
  LCD_ClearAll(GREEN);	HAL_Delay(200);
  LCD_ClearAll(BLUE);	HAL_Delay(200);
  LCD_ClearAll(PURPLE);	HAL_Delay(200);
  LCD_ClearAll(WHITE);	HAL_Delay(200);
  LCD_ShowString(16, 16, 32, 0, BLACK, WHITE, "Penguins");
  LCD_ShowString(16, 48, 24, 0, BLACK, WHITE, "Penguins");
  LCD_ShowString(16, 72, 16, 0, BLACK, WHITE, "Penguins");
  LCD_ShowString(16, 88, 12, 0, BLACK, WHITE, "Penguins");
  
  myUART_Transmit_DMA(&myUART, "G474VET6 UART1 Connected.\n");
  myUART_Transmit_DMA(&myUART, "Continuous sending test.\n");
  myUART_Start_Receive_DMA(&myUART);
  HAL_TIM_Base_Start_IT(&htim17);
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	if (myADC.ConvFinish == true)
	{
		for (uint16_t i = 0; i < ADC_DataSize; ++i)
			myUART_Transmit_DMA(&myUART, "ADC[%d]: %d\n", i, myADC.pData[i]);
		myADC.ConvFinish = false;
	}
	if (myDualADC.ConvFinish == true)
	{
		for (uint16_t i = 0; i < ADC_DataSize; ++i)
			myUART_Transmit_DMA(&myUART, "ADC[%d]: %d, %d\n", i, myDualADC.pData[i] & 0xFFFF, myDualADC.pData[i] >> 16);
		myDualADC.ConvFinish = false;
	}
	
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV6;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void Key_Process(uint8_t keyNum)
{
	switch (keyNum)
	{
		case 0x01:
			LED_R_Set(0), LED_G_Set(0), LED_B_Set(0);
			myDAC_Start_DMA(&myDAC);
			break;
		case 0x02:
			LED_R_Set(0), LED_G_Set(0), LED_B_Set(1);
			myDAC_DualStart_DMA(&myDualDAC);
			break;
		case 0x03:
			LED_R_Set(0), LED_G_Set(1), LED_B_Set(0);
			myADC_Start_DMA(&myADC);
			break;
		case 0x04:
			LED_R_Set(0), LED_G_Set(1), LED_B_Set(1);
			myADC_DualStart_DMA(&myDualADC);
			break;
		case 0x81:
			LED_R_Set(1), LED_G_Set(0), LED_B_Set(0);
			myDAC_Stop_DMA(&myDAC);
			break;
		case 0x82:
			LED_R_Set(1), LED_G_Set(0), LED_B_Set(1);
			myDAC_DualStop_DMA(&myDualDAC);
			break;
		case 0x83:
			LED_R_Set(1), LED_G_Set(1), LED_B_Set(0);
			__HAL_TIM_SET_AUTORELOAD(&htim7, 169);
			break;
		case 0x84:
			LED_R_Set(1), LED_G_Set(1), LED_B_Set(1);
			__HAL_TIM_SET_AUTORELOAD(&htim7, 84);
			break;
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
