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
myPWM_HandleTypeDef myPWM = { .htim = &htim9, .Channel = TIM_CHANNEL_1, .idx = 0 };
myPWMI_HandleTypeDef myPWMI = { .htim = &htim3, .Channel = TIM_CHANNEL_1 };
myADC_HandleTypeDef myADC = { .hadc_ch1 = &hadc2, .hadc_ch2 = &hadc1, .htim = &htim2 };
myDAC_HandleTypeDef myDAC = { .hdac = &hdac, .htim = &htim6, .Channel = DAC_CHANNEL_1, .idx = 0 };
myUART_HandleTypeDef myUART = { .huart = &huart1, .idx = 6 };

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Key_Process(uint8_t keyNum);
void ADC_Process(void);
void UART_LCD_Process(uint8_t type, const char *str);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
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
	switch (++tmp_adc_conv_cplt)
	{
		case 1:
			MODIFY_REG(myADC.hadc_ch1->Instance->CR1, ADC_CR1_RES, ADC_RESOLUTION_12B);
			HAL_ADC_Start_DMA(myADC.hadc_ch1, (uint32_t *)myADC.Data2, 10);
			break;
		case 2:
			__HAL_TIM_SET_AUTORELOAD(myADC.htim, 999);
			HAL_ADC_Start_DMA(myADC.hadc_ch2, (uint32_t *)myADC.Data3, 20);
			break;
		case 3:
			__HAL_TIM_SET_AUTORELOAD(myADC.htim, 99);
			HAL_ADC_Start_DMA(myADC.hadc_ch2, (uint32_t *)myADC.Data4, 200);
			break;
		case 4:
			HAL_TIM_Base_Stop(myADC.htim);
			tmp_adc_conv_cplt = 0;
			ADC_Process();
			break;
	}
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart == myUART.huart && huart->RxEventType != HAL_UART_RXEVENT_HT)
	{
		UART_LCD_Process(2, myUART.RxMsg);
		if (strncmp(myUART.RxMsg, UART_TxHeader, strlen(UART_TxHeader)))
			myUART_Transmit_DMA(&myUART, "%s%s", UART_TxHeader, myUART.RxMsg);
		myUART_Start_Receive_DMA(&myUART);
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
  MX_TIM11_Init();
  MX_TIM9_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM6_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_DAC_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  LCD_Init();
  LCD_ShowString(40, 80, 32, RED, WHITE, "Wait to confirm: workState = %d.", workState);
  LCD_ShowString(40, 120, 32, WHITE, ORANGE, " KEY0         KEY1           KEY2 ");
  LCD_ShowString(136, 120, 32, ORANGE, WHITE, " CHECK ");
  LCD_ShowString(344, 120, 32, ORANGE, WHITE, " STATE++ ");
  LCD_ShowString(584, 120, 32, ORANGE, WHITE, " STATE-- ");
  
  HAL_TIM_Base_Start_IT(&htim11);
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
	static bool tmp_uart_state = true;
	
	if (workState == 0)
	{
		if (keyNum == 0x01 && tmp_work_state < 6 || keyNum == 0x02 && tmp_work_state > 1)
		{
			if (keyNum == 0x01) tmp_work_state++;
			if (keyNum == 0x02) tmp_work_state--;
			LCD_ShowString(40, 80, 32, RED, WHITE, "Wait to confirm: workState = %d.", tmp_work_state);
		}
		if (keyNum == 0x00 && tmp_work_state)
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
				LCD_ShowString(40, 120, 32, BLUE, WHITE, "PinDef: PWM(PE5), PWMI(PB4).               ");
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
				myUART_SetBaudRate(&myUART);
				myUART_Start_Receive_DMA(&myUART);
				LCD_ShowString(40, 160, 32, BLUE, WHITE, "BaudRate: 115200 Bps.                      ");
				LCD_ShowString(40, 120, 32, WHITE, ORANGE, " K0        K1         K2           K3 ");
				LCD_ShowString(104, 120, 32, ORANGE, WHITE, " Baud ");
				LCD_ShowString(264, 120, 32, ORANGE, WHITE, " Tx2/4 ");
				LCD_ShowString(440, 120, 32, ORANGE, WHITE, " CLR/RST ");
				LCD_ShowString(648, 120, 32, ORANGE, WHITE, " QUIT ");
			}
		}
	}
	else if (keyNum == 0x03)
	{
		LED0_Off, LED1_Off, BEEP_Off;
		if (workState == 4) myPWM_Stop(&myPWM), myPWMI_Stop(&myPWMI), myPWM.idx = 0;
		else if (workState == 5) myDAC_Stop_DMA(&myDAC), myDAC.idx = 0, tmp_adc_auto = false;
		else if (workState == 6) myUART.idx = 6, tmp_uart_state = true;
		LCD_ShowString(40, 80, 32, RED, WHITE, "Wait to confirm: workState = %d.", workState);
		LCD_ShowString(40, 120, 32, WHITE, ORANGE, " KEY0         KEY1           KEY2 ");
		LCD_ShowString(136, 120, 32, ORANGE, WHITE, " CHECK ");
		LCD_ShowString(344, 120, 32, ORANGE, WHITE, " STATE++ ");
		LCD_ShowString(584, 120, 32, ORANGE, WHITE, " STATE-- ");
		LCD_ClearArea(40, 160, 720, 200, WHITE);
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
		if (keyNum == 0x00)
		{
			switch (myPWM.idx = (myPWM.idx + 1) % 3)
			{
				case 0: LCD_ShowString(40, 160, 32, BLACK, WHITE, "PWM:  setPulse = 15 us.  "); break;
				case 1: LCD_ShowString(40, 160, 32, BLACK, WHITE, "PWM:  setPulse = 500 us. "); break;
				case 2: LCD_ShowString(40, 160, 32, BLACK, WHITE, "PWM:  setPulse = 1500 us."); break;
			}
			myPWM_SetPulse(&myPWM);
		}
	}
	else if (workState == 5)
	{
		if (++workCnt == 10) workCnt = 0, LED0_Toggle;
		if (keyNum == 0x00) tmp_adc_auto = false;
		if (keyNum == 0x00 || (workCnt == 0 && tmp_adc_auto))
		{
			MODIFY_REG(myADC.hadc_ch1->Instance->CR1, ADC_CR1_RES, ADC_RESOLUTION_8B);
			HAL_ADC_Start_DMA(myADC.hadc_ch1, (uint32_t *)myADC.Data1, 10);
			HAL_TIM_Base_Start(myADC.htim);
		}
		else if (keyNum == 0x01) tmp_adc_auto = !tmp_adc_auto;
		else if (keyNum == 0x02)
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
		if (myUART.huart->RxState != HAL_UART_STATE_BUSY_RX)
		{
			LED0_On, LED1_On;
			if (tmp_uart_state) tmp_uart_state = false, UART_LCD_Process(3, NULL);
			if (keyNum == 0x82) tmp_uart_state = true, UART_LCD_Process(0, NULL), myUART_Start_Receive_DMA(&myUART);
		}
		else
		{
			if (++workCnt == 10)
			{
				workCnt = 0;
				if (myUART.huart->gState != HAL_UART_STATE_BUSY_TX) LED1_Off;
				else LED1_Toggle;
				if (__HAL_DMA_GET_COUNTER(myUART.huart->hdmarx) == UART_BufSize - 1) LED0_Off;
				else LED0_Toggle;
			}
			if (keyNum == 0x00)
			{
				switch (myUART.idx = (myUART.idx + 1) % 12)
				{
					case 0:  LCD_ShowString(40, 160, 32, BLUE, WHITE, "BaudRate: 2400 Bps.   "); break;
					case 1:  LCD_ShowString(40, 160, 32, BLUE, WHITE, "BaudRate: 4800 Bps.   "); break;
					case 2:  LCD_ShowString(40, 160, 32, BLUE, WHITE, "BaudRate: 9600 Bps.   "); break;
					case 3:  LCD_ShowString(40, 160, 32, BLUE, WHITE, "BaudRate: 19200 Bps.  "); break;
					case 4:  LCD_ShowString(40, 160, 32, BLUE, WHITE, "BaudRate: 38400 Bps.  "); break;
					case 5:  LCD_ShowString(40, 160, 32, BLUE, WHITE, "BaudRate: 57600 Bps.  "); break;
					case 6:  LCD_ShowString(40, 160, 32, BLUE, WHITE, "BaudRate: 115200 Bps. "); break;
					case 7:  LCD_ShowString(40, 160, 32, BLUE, WHITE, "BaudRate: 230400 Bps. "); break;
					case 8:  LCD_ShowString(40, 160, 32, BLUE, WHITE, "BaudRate: 460800 Bps. "); break;
					case 9:  LCD_ShowString(40, 160, 32, BLUE, WHITE, "BaudRate: 576000 Bps. "); break;
					case 10: LCD_ShowString(40, 160, 32, BLUE, WHITE, "BaudRate: 921600 Bps. "); break;
					case 11: LCD_ShowString(40, 160, 32, BLUE, WHITE, "BaudRate: 1152000 Bps."); break;
				}
				myUART_SetBaudRate(&myUART);
			}
			else if (keyNum == 0x80)
			{
				myUART.idx = 6;
				LCD_ShowString(40, 160, 32, BLUE, WHITE, "BaudRate: 115200 Bps. ");
				myUART_SetBaudRate(&myUART);
			}
			else if (keyNum == 0x01) UART_LCD_Process(1, UART_Tx1E2);
			else if (keyNum == 0x81) UART_LCD_Process(1, UART_Tx1E4);
			else if (keyNum == 0x02) UART_LCD_Process(0, NULL);
		}
	}
}

void ADC_Process(void)
{
	uint16_t tmp_adc_data_1 = 0;
	uint16_t tmp_adc_data_2 = 0;
	uint16_t tmp_adc_data_min_1 = 0xFFF;
	uint16_t tmp_adc_data_max_1 = 0x000;
	uint16_t tmp_adc_data_min_2 = 0xFFF;
	uint16_t tmp_adc_data_max_2 = 0x000;
	
	for (uint16_t i = 0; i < 10; ++i)
	{
		tmp_adc_data_1 += myADC.Data1[i];
		tmp_adc_data_2 += myADC.Data2[i];
	}
	for (uint16_t i = 0; i < 20; ++i)
	{
		if (tmp_adc_data_min_1 > myADC.Data3[i]) tmp_adc_data_min_1 = myADC.Data3[i];
		if (tmp_adc_data_max_1 < myADC.Data3[i]) tmp_adc_data_max_1 = myADC.Data3[i];
	}
	for (uint16_t i = 0; i < 200; ++i)
	{
		if (tmp_adc_data_min_2 > myADC.Data4[i]) tmp_adc_data_min_2 = myADC.Data4[i];
		if (tmp_adc_data_max_2 < myADC.Data4[i]) tmp_adc_data_max_2 = myADC.Data4[i];
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

/**
  * @param  type  This parameter can be a value of @ref UART_LCD_Process_Type :
  *                 UART_LCD_Process_Clear    = 0x00U,
  *                 UART_LCD_Process_Tx       = 0x01U,
  *                 UART_LCD_Process_Rx       = 0x02U,
  *                 UART_LCD_Process_Warning  = 0x03U
  */
void UART_LCD_Process(uint8_t type, const char *str)
{
	/* Clear area of LCD for all UART_LCD_Process_Type. */
	LCD_ClearArea(424, 160, 192, 40, WHITE);
	LCD_ClearArea(40, 200, 704, 160, WHITE);
	
	if (type == 1 || type == 2)
	{
		uint16_t color = (type == 1) ? GREEN : RED;
		uint16_t strLen = strlen(str);
		LCD_ShowString(424, 160, 32, color, WHITE, "%sLen: %d    ", (type == 1) ? "Tx" : "Rx", strLen);
		LCD_ClearArea(40, 200, 704, 160, WHITE);
		LCD_ShowString(40, 200, 32, color, WHITE, "%s: %s", (type == 1) ? "Tx" : "Rx", str);
		if (strLen > 40)  LCD_ShowString(104, 240, 32, color, WHITE, "%s", str + 40);
		if (strLen > 80)  LCD_ShowString(104, 280, 32, color, WHITE, "%s", str + 80);
		if (strLen > 120) LCD_ShowString(104, 320, 32, color, WHITE, "%s", str + 120);
		if (strLen > 160) LCD_ShowString(696, 320, 32, color, WHITE, "...");
		LCD_ClearArea(744, 200, 48, 160, WHITE);
		if (type == 1) myUART_Transmit_DMA(&myUART, "%s", str);
	}
	
	if (type == 3)
	{
		LCD_ShowString(152, 220, 32, WHITE, RED, " Warning: Baud rate mismatch. ");
		LCD_ShowString(152, 260, 32, WHITE, RED, " Press and hold KEY2 to reset. ");
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
