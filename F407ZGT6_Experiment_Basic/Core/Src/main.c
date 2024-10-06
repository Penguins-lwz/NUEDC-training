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
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define VREF			3300

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t workState = 0;
uint16_t workCnt = 0;
myUART_HandleTypeDef UART_Debug = { .huart = &huart1, .RxMsgUsed = true };
myUART_HandleTypeDef UART_Slave = { .huart = &huart3, .RxMsgUsed = true };
myPWM_HandleTypeDef myPWM = { .htim = &htim10, .Channel = TIM_CHANNEL_1, .idx = 0 };
myPWMI_HandleTypeDef myPWMI = { .htim = &htim2, .Channel = TIM_CHANNEL_2 };
myADC_HandleTypeDef myADC = { .hadc_ch1 = &hadc2, .hadc_ch2 = &hadc1, .htim = &htim3, .ConvFinish = false };
myDAC_HandleTypeDef myDAC = { .hdac = &hdac, .htim = &htim6, .Channel = DAC_CHANNEL_1, .idx = 0 };

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Key_Process(uint8_t keyNum);
void ADC_Process(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart == UART_Debug.huart)
	{
		if (UART_Debug.RxMsgUsed == true)
		{
			myUART_Receive_DMA(&UART_Debug);
			if (workState != 6)
				myUART_Transmit_DMA(&UART_Debug, "RxMsg: %s", UART_Debug.UART_RxMsg);
			else /* if (workState == 6) */
			{
				LCD_ClearArea(40, 200, 720, 120, WHITE);
				LCD_ShowString(40, 200, 32, BLACK, WHITE, "RxMsg_UART1: %s", UART_Debug.UART_RxMsg);
			}
		}
		myUART_Start_Receive_DMA(&UART_Debug);
	}
	else if (workState == 6 && huart == UART_Slave.huart)
	{
		if (UART_Slave.RxMsgUsed == true)
		{
			myUART_Receive_DMA(&UART_Slave);
			LCD_ClearArea(40, 200, 720, 120, WHITE);
			LCD_ShowString(40, 200, 32, BLACK, WHITE, "RxMsg_UART3: %s", UART_Slave.UART_RxMsg);
		}
		myUART_Start_Receive_DMA(&UART_Slave);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim11)
	{
		Key_Process(Key_Read());
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	static uint8_t tmp_adc_conv_cplt = 0;
	if (++tmp_adc_conv_cplt == 2)
	{
		tmp_adc_conv_cplt = 0;
		myADC.ConvFinish = true;
		myADC_Stop_DMA(&myADC);
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
  MX_FSMC_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM11_Init();
  MX_TIM10_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM6_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_DAC_Init();
  /* USER CODE BEGIN 2 */
  LCD_Init();
  LCD_ShowString(40, 80, 32, RED, WHITE, "Wait to confirm: workState = %d.", workState);
  LCD_ShowString(40, 120, 32, WHITE, ORANGE, " KEY0         KEY1           KEY2 ");
  LCD_ShowString(136, 120, 32, ORANGE, WHITE, " CHECK ");
  LCD_ShowString(344, 120, 32, ORANGE, WHITE, " STATE++ ");
  LCD_ShowString(584, 120, 32, ORANGE, WHITE, " STATE-- ");
  
  myUART_Transmit_DMA(&UART_Debug, "F407ZGT6 UART1 connected.\n");
  myUART_Start_Receive_DMA(&UART_Debug);
  
  HAL_TIM_Base_Start_IT(&htim11);
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	if (myADC.ConvFinish == true)
	{
		myADC.ConvFinish = false;
		ADC_Process();
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void Key_Process(uint8_t keyNum)
{
	static uint8_t tmp_work_state = 0;
	static bool tmp_adc_auto = false;
	if (workState == 0)
	{
		if (keyNum == 1 && tmp_work_state < 6 || keyNum == 2 && tmp_work_state > 1)
		{
			if (keyNum == 1) tmp_work_state++;
			if (keyNum == 2) tmp_work_state--;
			LCD_ShowString(40, 80, 32, RED, WHITE, "Wait to confirm: workState = %d.", tmp_work_state);
		}
		if (keyNum == 0 && tmp_work_state)
		{
			LCD_ShowString(40, 80, 32, BLACK, WHITE, "Already confirm: workState = %d.", workState = tmp_work_state);
			if (workState < 4)
			{
				LCD_ShowString(40, 120, 32, WHITE, ORANGE, " KEY3 ");
				LCD_ShowString(136, 120, 32, ORANGE, WHITE, " QUIT                                 ");
			}
			else if (workState == 4)
			{
				myPWM_Start(&myPWM), myPWMI_Start(&myPWMI);
				LCD_ShowString(40, 120, 32, BLUE, WHITE, "PinDef: PWM(PF6), PWMI(PB3).               ");
				LCD_ShowString(40, 160, 32, BLACK, WHITE, "PWM:  setPulse = 0 us.   ");
				LCD_ShowString(40, 280, 32, WHITE, ORANGE, " KEY0       KEY3 ");
				LCD_ShowString(136, 280, 32, ORANGE, WHITE, " PWM ");
				LCD_ShowString(312, 280, 32, ORANGE, WHITE, " QUIT ");
			}
			else if (workState == 5)
			{
				myDAC_Start_DMA(&myDAC);
				LCD_ShowString(40, 120, 32, BLUE, WHITE, "PinDef: ADC-DC(PA7), ADC-AC(PA6), DAC(PA4).");
				LCD_ShowString(40, 160, 32, BLACK, WHITE, "DAC: setFreq = 50 Hz.");
				LCD_ShowString(40, 200, 32, BLACK, WHITE, "ADC Results:");
				LCD_ShowString(40, 240, 32, BLACK, WHITE, "DC (8b):     N/A mV  |  AC (1k):     N/A mV");
				LCD_ShowString(40, 280, 32, BLACK, WHITE, "DC (12b):    N/A mV  |  AC (10k):    N/A mV");
				LCD_ShowString(440, 160, 32, WHITE, ORANGE, " K3 ");
				LCD_ShowString(504, 160, 32, ORANGE, WHITE, " QUIT ");
				LCD_ShowString(248, 200, 32, WHITE, ORANGE, " K0          K1        K2 ");
				LCD_ShowString(312, 200, 32, ORANGE, WHITE, " SINGLE ");
				LCD_ShowString(504, 200, 32, ORANGE, WHITE, " AUTO ");
				LCD_ShowString(664, 200, 32, ORANGE, WHITE, " DAC ");
			}
			else if (workState == 6)
			{
				myUART_Start_Receive_DMA(&UART_Slave);
				LCD_ShowString(40, 120, 32, BLUE, WHITE, "PinDef: Master(UART1), Slave(UART3).       ");
				LCD_ShowString(40, 160, 32, WHITE, ORANGE, " K0        K1        K2       K3 ");
				LCD_ShowString(104, 160, 32, ORANGE, WHITE, " MTSR ");
				LCD_ShowString(264, 160, 32, ORANGE, WHITE, " MRST ");
				LCD_ShowString(424, 160, 32, ORANGE, WHITE, " CLR ");
				LCD_ShowString(568, 160, 32, ORANGE, WHITE, " QUIT ");
			}
		}
	}
	else if (keyNum == 3)
	{
		LED0_Off, LED1_Off, BEEP_Off;
		if (workState == 4) myPWM_Stop(&myPWM), myPWMI_Stop(&myPWMI), myPWM.idx = 0;
		else if (workState == 5) myDAC_Stop_DMA(&myDAC), myDAC.idx = 0;
		LCD_ShowString(40, 80, 32, RED, WHITE, "Wait to confirm: workState = %d.", workState);
		LCD_ShowString(40, 120, 32, WHITE, ORANGE, " KEY0         KEY1           KEY2 ");
		LCD_ShowString(136, 120, 32, ORANGE, WHITE, " CHECK ");
		LCD_ShowString(344, 120, 32, ORANGE, WHITE, " STATE++ ");
		LCD_ShowString(584, 120, 32, ORANGE, WHITE, " STATE-- ");
		LCD_ClearArea(40, 160, 720, 160, WHITE);
		tmp_work_state = workState, workState = 0, workCnt = 0;
	}
	else if (workState == 1)
	{
		if (workCnt && ++workCnt > 200) workCnt = 0, BEEP_Off;
		if (workCnt == 0 && KEY0_Trigger) workCnt = 1, BEEP_On;
	}
	else if (workState == 2)
	{
		if (++workCnt == 600) workCnt = 0;
		LED0_Set(workCnt / 100 % 2);
		LED1_Set(workCnt / 15 % 2);
	}
	else if (workState == 3)
	{
		if (KEY0_Trigger) BEEP_On, LED1_Set(++workCnt / 25 % 2);
		else workCnt = 0, LED1_Off, BEEP_Off;
	}
	else if (workState == 4)
	{
		if (++workCnt == 10)
		{
			workCnt = 0, LED0_Toggle;
			LCD_ShowString(40, 200, 32, BLACK, WHITE, "PWMI: getPulse = %d us.         ", myPWMI_GetPulse(&myPWMI) + 1);
			LCD_ShowString(40, 240, 32, BLACK, WHITE, "PWMI: getPeriod = %d us.         ", myPWMI_GetPeriod(&myPWMI) + 1);
		}
		if (keyNum == 0)
		{
			LCD_ShowString(40, 160, 32, BLACK, WHITE, "PWM:  setPulse = %d us.  ", PWM_Pulse[myPWM.idx = (myPWM.idx + 1) % 3]);
			myPWM_SetPulse(&myPWM);
		}
	}
	else if (workState == 5)
	{
		if (keyNum == 0) tmp_adc_auto = false;
		if (++workCnt == 10)
		{
			workCnt = 0, LED0_Toggle;
			if (tmp_adc_auto) myADC_Start_DMA(&myADC);
		}
		if (keyNum == 0) myADC_Start_DMA(&myADC);
		else if (keyNum == 1) tmp_adc_auto = !tmp_adc_auto;
		else if (keyNum == 2)
		{
			switch (myDAC.idx = (myDAC.idx + 1) % 7)
			{
				case 0: LCD_ShowString(40, 160, 32, BLACK, WHITE, "DAC: setFreq = 50 Hz. "); break;
				case 1: LCD_ShowString(40, 160, 32, BLACK, WHITE, "DAC: setFreq = 100 Hz."); break;
				case 2: LCD_ShowString(40, 160, 32, BLACK, WHITE, "DAC: setFreq = 500 Hz."); break;
				case 3: LCD_ShowString(40, 160, 32, BLACK, WHITE, "DAC: setFreq = 1 kHz. "); break;
				case 4: LCD_ShowString(40, 160, 32, BLACK, WHITE, "DAC: setFreq = 5 kHz. "); break;
				case 5: LCD_ShowString(40, 160, 32, BLACK, WHITE, "DAC: setFreq = 10 kHz."); break;
				case 6: LCD_ShowString(40, 160, 32, BLACK, WHITE, "DAC: setFreq = 50 kHz."); break;
			}
			myDAC_SetFreq(&myDAC);
		}
	}
	else if (workState == 6)
	{
		if (keyNum == 0) LED0_Toggle, myUART_Transmit_DMA(&UART_Debug, "TxMsg sent by master(UART1).\n");
		else if (keyNum == 1) LED1_Toggle, myUART_Transmit_DMA(&UART_Slave, "TxMsg sent by slave(UART3).\n");
		else if (keyNum == 2) LCD_ClearArea(40, 200, 720, 120, WHITE);
	}
}

void ADC_Process(void)
{
	uint16_t tmp_adc_data_1 = 0;
	uint16_t tmp_adc_data_2 = 0;
	for (uint16_t i = 0; i < 10; ++i)
	{
		tmp_adc_data_1 += myADC.ADC_Data1[i] >> 4;
		tmp_adc_data_2 += myADC.ADC_Data1[i];
	}
	
	uint16_t tmp_adc_data_min_1 = 0xFFF;
	uint16_t tmp_adc_data_max_1 = 0x000;
	uint16_t tmp_adc_data_min_2 = 0xFFF;
	uint16_t tmp_adc_data_max_2 = 0x000;
	for (uint16_t i = 0; i < ADC_DataSize; ++i)
	{
		if (i % 10 == 0)
		{
			if (tmp_adc_data_min_1 > myADC.ADC_Data2[i]) tmp_adc_data_min_1 = myADC.ADC_Data2[i];
			if (tmp_adc_data_max_1 < myADC.ADC_Data2[i]) tmp_adc_data_max_1 = myADC.ADC_Data2[i];
		}
		if (tmp_adc_data_min_2 > myADC.ADC_Data2[i]) tmp_adc_data_min_2 = myADC.ADC_Data2[i];
		if (tmp_adc_data_max_2 < myADC.ADC_Data2[i]) tmp_adc_data_max_2 = myADC.ADC_Data2[i];
	}
	
	LCD_ShowString(40, 240, 32, BLACK, WHITE, "DC (8b):  %6.1f mV  |  AC (1k):  %6.1f mV",
		(float)tmp_adc_data_1 * VREF / (10 * 0xFF),
		(float)(tmp_adc_data_max_1 - tmp_adc_data_min_1) * VREF / 0xFFF
	);
	LCD_ShowString(40, 280, 32, BLACK, WHITE, "DC (12b): %6.1f mV  |  AC (10k): %6.1f mV",
		(float)tmp_adc_data_2 * VREF / (10 * 0xFFF),
		(float)(tmp_adc_data_max_2 - tmp_adc_data_min_2) * VREF / 0xFFF
	);
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
