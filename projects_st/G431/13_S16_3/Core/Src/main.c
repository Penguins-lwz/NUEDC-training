/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum {
	DATA    = 0x01,
	RECD    = 0x02,
	PARA_H  = 0x04 | 0x20,
	PARA_L  = 0x04 | 0x40,
	PARA_HM = 0x04 | 0x08,
	PARA_LM = 0x04 | 0x10
} LcdPageTypeDef;

typedef enum {
	NONE = 0,
	HIGH = 1,
	LOW  = 2
} AlarmTypeDef;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t  ledState  = 0x01;
uint8_t  lcdPage   = DATA;
uint16_t rate;
uint16_t maxRate   = 30;
uint16_t minRate   = 200;
uint16_t alarmCnt  = 0;
uint16_t highLimit = 100;
uint16_t lowLimit  = 60;
uint16_t tmpHigh   = 100;
uint16_t tmpLow    = 60;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
float LinearMap(float x, float xmin, float xmax, float ymin, float ymax);
void LCD_ShowString(uint8_t Line, const char *format, ...);
void Key_Process(uint8_t keyNum);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim17)
	{
		Key_Process(Key_Read());
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
  MX_TIM17_Init();
  MX_TIM3_Init();
  MX_ADC2_Init();
  /* USER CODE BEGIN 2 */
  LED_WR(ledState);
  LCD_Init();
  LCD_Clear(Black);
  LCD_SetBackColor(Black);
  LCD_SetTextColor(White);
  
  HAL_ADC_Start(&hadc2);
  HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_Base_Start_IT(&htim17);
  
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV3;
  RCC_OscInitStruct.PLL.PLLN = 20;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void LCD_ShowString(uint8_t Line, const char *format, ...)
{
	char str[21];
	va_list ap;
	va_start(ap, format);
	int xnum = vsnprintf(str, 21, format, ap);
	va_end(ap);
	while (xnum < 20) str[xnum++] = 32;
	LCD_DisplayStringLine(Line, (uint8_t *)str);
}

void Key_Process(uint8_t keyNum)
{
	if (keyNum == 0x01)
	{
		if (lcdPage == DATA) lcdPage = RECD;
		else if (lcdPage == RECD) lcdPage = PARA_H;
		else lcdPage = DATA, tmpHigh = highLimit, tmpLow = lowLimit;
	}
	else if (keyNum == 0x02)
	{
		if (lcdPage == PARA_H) lcdPage = PARA_L;
		else if (lcdPage == PARA_L) lcdPage = PARA_H;
		else if (lcdPage == PARA_HM) lcdPage = PARA_LM;
		else if (lcdPage == PARA_LM) lcdPage = PARA_HM;
	}
	else if (keyNum == 0x03)
	{
		if (lcdPage == PARA_H) lcdPage = PARA_HM;
		else if (lcdPage == PARA_L) lcdPage = PARA_LM;
		else if (lcdPage == PARA_HM) lcdPage = PARA_H, highLimit = tmpHigh, lowLimit = tmpLow;
		else if (lcdPage == PARA_LM) lcdPage = PARA_L, highLimit = tmpHigh, lowLimit = tmpLow;
	}
	else if (keyNum == 0x04 && lcdPage == DATA) alarmCnt = 0;
	
	static uint8_t timeCnt = 0;
	if (++timeCnt < 10) return;
	timeCnt = 0;
	
	ledState = lcdPage & 0x1F;
	rate = LinearMap(1000000.0 / (TIM3->CCR1 + 1), 1000, 2000, 30, 200) + 0.5;
	if (rate < minRate) minRate = rate;
	if (rate > maxRate) maxRate = rate;
	
	static uint8_t alarmTime = 0;
	static uint8_t preAlarm = NONE;
	uint8_t curAlarm = NONE;
	if (rate < lowLimit) curAlarm = LOW;
	if (rate > highLimit) curAlarm = HIGH;
	if (curAlarm != preAlarm && curAlarm != NONE) alarmCnt += 1, alarmTime = 1;
	if (alarmTime) alarmTime = (alarmTime + 1) % 51, ledState |= 0x20;
	preAlarm = curAlarm;
	
	if (lcdPage == PARA_HM) tmpHigh = LinearMap(ADC2->DR, 4095 * 1.0 / 3.3, 4095 * 3.0 / 3.3, 60, 150) + 0.5;
	if (lcdPage == PARA_LM) tmpLow = LinearMap(ADC2->DR, 4095 * 1.0 / 3.3, 4095 * 3.0 / 3.3, 60, 150) + 0.5;
	
	LED_WR(ledState);
	if (lcdPage == DATA)
	{
		LCD_ShowString(Line1, "       HEART        ");
		LCD_ShowString(Line3, "      Rate:%d", rate);
		LCD_ShowString(Line4, "       Con:%d", alarmCnt);
	}
	else if (lcdPage == RECD)
	{
		LCD_ShowString(Line1, "       RECORD       ");
		LCD_ShowString(Line3, "       Max:%d", maxRate);
		LCD_ShowString(Line4, "       Min:%d", minRate);
	}
	else
	{
		LCD_ShowString(Line1, "        PARA        ");
		LCD_ShowString(Line3, "      High:%d", tmpHigh);
		LCD_ShowString(Line4, "       Low:%d", tmpLow);
	}
}

float LinearMap(float x, float xmin, float xmax, float ymin, float ymax)
{
	if (x <= xmin) return ymin;
	if (x >= xmax) return ymax;
	return ymin + (x - xmin) * (ymax - ymin) / (xmax - xmin);
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
