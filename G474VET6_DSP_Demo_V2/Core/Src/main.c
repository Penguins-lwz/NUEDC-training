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
#include "dma.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fir.h"
#include "fft.h"

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
myUART_HandleTypeDef UART_Debug = { .huart = &huart1, .RxMsgUsed = true };

const float32_t FIR_Src[FIR_DATA_SIZE] = {
	97.37595, 102.8701, 107.0632, 115.7156, 112.8137, 120.9769, 131.8534, 135.8663,
	136.6982, 140.7686, 135.6568, 149.9058, 164.5603, 158.7260, 161.0878, 157.4640,
	172.9973, 170.6156, 176.1572, 182.5258, 178.3203, 181.0249, 182.6125, 178.3821,
	175.9829, 187.6253, 170.2639, 180.3092, 179.6441, 167.0814, 179.8682, 169.5874,
	168.4161, 163.7823, 170.4420, 167.3656, 156.3249, 160.3774, 145.6232, 157.3168,
	147.9005, 143.1482, 134.4095, 134.8339, 129.2242, 122.6962, 123.9254, 122.4555,
	109.0197, 103.4569, 105.2480, 90.73779, 91.68613, 82.26148, 84.05266, 63.95621,
	72.33058, 68.32173, 59.93324, 52.12606, 48.76873, 56.44295, 50.35474, 35.90263,
	41.25586, 27.79569, 33.14786, 34.45573, 22.80141, 24.87871, 37.24223, 24.09559,
	23.29873, 16.82225, 19.49873, 25.83471, 20.08144, 21.13774, 20.10887, 13.73600,
	26.75956, 30.28683, 32.54355, 29.01839, 37.21677, 36.10783, 41.62039, 51.82156,
	62.82814, 46.95458, 58.81943, 60.40126, 56.63103, 67.29922, 77.66067, 71.59712,
	80.47699, 97.12698, 82.32030, 96.16405, 98.65028, 108.5120, 121.1670, 111.6934,
	127.7159, 132.4306, 127.0742, 137.0621, 132.6226, 140.9445, 148.5365, 151.0259,
	149.3587, 157.5896, 149.0047, 169.4079, 165.2715, 165.9320, 167.8513, 170.7680,
	179.6987, 180.0555, 184.9248, 185.7071, 177.2023, 175.8836, 175.6466, 175.8648,
	183.7029, 176.3029, 171.5265, 178.4631, 173.1714, 168.7165, 167.1277, 167.8496,
	169.7675, 161.7142, 157.5789, 151.9334, 138.9910, 144.3618, 139.5912, 133.1394,
	124.7168, 122.0185, 112.5537, 110.7819, 110.2562, 107.1652, 98.61960, 93.05727,
	86.12468, 89.47584, 78.97542, 80.34625, 65.86730, 67.30166, 60.77468, 59.04521,
	48.98955, 46.42270, 43.11791, 40.55625, 32.35607, 23.16825, 33.12195, 36.57480,
	27.49097, 29.21676, 23.74328, 25.21216, 24.65200, 15.66970, 22.04746, 22.60270,
	22.43594, 18.46166, 12.58109, 21.79040, 16.85006, 27.88390, 31.69881, 22.93643,
	28.98149, 33.02405, 43.22209, 48.32811, 34.40025, 47.33902, 52.39211, 57.06061,
	63.64711, 62.49414, 77.97583, 78.69530, 77.08333, 86.32769, 84.82511, 91.08455,
	101.0459, 100.8681, 106.2422, 118.7898, 128.4439, 125.3936, 130.6242, 134.8834,
	141.2255, 139.2262, 153.7022, 143.0280, 152.8614, 153.3649, 151.4334, 163.3044,
	169.5087, 162.9072, 176.5519, 174.9892, 174.2517, 179.0402, 173.1825, 175.4147,
	171.8783, 169.9091, 172.0570, 176.2204, 177.4136, 183.1134, 172.4780, 172.0858,
	173.0497, 171.4159, 159.5171, 171.3501, 163.2403, 153.3064, 156.4582, 154.2352,
	151.1559, 139.7792, 137.4884, 129.3983, 129.2695, 128.7628, 129.0656, 118.5724,
	102.5559, 109.3788, 85.55075, 93.86120, 91.64263, 89.22813, 89.44888, 80.63228,
	63.72841, 61.00826, 60.13728, 51.40536, 52.79335, 49.39901, 45.75731, 36.31072,
	39.45294, 37.28062, 38.93726, 26.88294, 22.63256, 30.44208, 29.86901, 18.84386,
	29.89054, 17.83314, 17.41186, 18.12740, 17.73166, 22.37689, 21.12693, 20.23196,
	30.21087, 31.09789, 33.08749, 32.70120, 28.81256, 39.04620, 32.97654, 33.83039,
	42.77185, 55.05226, 53.14226, 64.97464, 59.06367, 60.28303, 67.04616, 73.25116,
	72.27781, 76.69919, 83.41296, 88.91167, 91.73191, 109.9023, 106.8001, 113.0275,
	122.7528, 124.6779, 129.2728, 133.2989, 142.4970, 142.8021, 137.9111, 155.2961,
	145.4413, 156.8111, 165.1119, 168.7759, 160.9698, 169.2674, 179.5972, 182.0624,
	181.1423, 165.3823, 182.5749, 177.3009, 174.9385, 172.7627, 183.3400, 177.7759,
	169.9329, 183.1503, 184.4190, 171.8051, 170.2541, 170.9855, 166.3785, 161.3058,
	164.7292, 148.6742, 153.1690, 142.0047, 155.1859, 139.4671, 144.5837, 131.8801,
	128.3918, 113.8028, 121.1408, 116.4088, 114.7587, 101.5487, 106.9914, 90.39811,
	84.84071, 87.84271, 81.21647, 83.78767, 74.91376, 65.29508, 60.57081, 58.25504,
	62.47421, 50.62748, 42.69118, 32.20371, 35.47786, 33.99130, 24.74129, 32.11010,
	26.77264, 21.14443, 32.65327, 17.53885, 21.20338, 21.12326, 20.58923, 26.66333,
	27.98110, 22.70062, 23.47305, 23.96416, 25.18671, 25.38502, 29.67107, 31.52817,
	24.00382, 41.57773, 29.39296, 48.85111, 45.53511, 50.73574, 58.71353, 62.77955,
	51.86185, 65.52033, 64.41060, 72.57811, 78.23764, 82.79589, 85.31530, 96.97432,
	97.82176, 99.49480, 113.4994, 108.6025, 127.8355, 124.8464, 123.8187, 138.6857,
	139.8004, 142.4440, 148.0693, 144.7021, 153.7317, 161.9369, 169.5283, 168.7515,
	168.4199, 167.6063, 167.0364, 175.6884, 168.6476, 170.6180, 181.2156, 178.7482,
	175.3908, 179.3892, 174.4169, 183.0585, 183.8421, 174.5569, 181.7273, 172.9916,
	167.1003, 176.4912, 168.2241, 162.9544, 166.8029, 163.7961, 157.4670, 145.6913,
	154.1426, 147.2822, 142.0527, 132.1018, 125.0550, 120.2125, 113.8998, 126.2100,
	104.5556, 103.3482, 98.32506, 91.37474, 88.60287, 73.63395, 80.03290, 79.97268,
	79.01387, 67.77341, 56.13708, 57.78803, 51.39963, 46.30546, 43.89710, 48.03640,
	31.91680, 44.99814, 26.13242, 30.44534, 23.62321, 16.22607, 31.78369, 10.94092,
	21.28970, 29.76957, 26.60766, 23.64718, 18.98653, 22.37092, 19.50334, 16.59154,
	22.30162, 24.10853, 13.64228, 30.92260, 38.57094, 32.45867, 42.02431, 42.54689,
	36.39976, 43.23495, 42.60946, 58.92545, 56.89772, 58.96435, 77.04663, 71.07321,
	77.66291, 90.17973, 88.88155, 104.1463, 99.66729, 109.3716, 121.0686, 108.9640,
	127.5039, 122.1756, 125.0820, 139.3633, 133.4678, 140.9098, 150.6745, 156.6930,
	150.1236, 152.9151, 156.3800, 166.9272, 172.9778, 163.9281, 168.5163, 174.8252,
	182.4518, 183.6381, 182.1889, 178.1805, 185.7616, 182.7085, 187.1282, 181.3362,
	179.6048, 170.3098, 181.4897, 179.0489, 178.9533, 180.9635, 170.8397, 162.4179,
	160.0166, 159.1819, 158.9128, 161.4082, 152.4727, 142.7262, 129.7774, 131.3007,
	134.5060, 119.8600, 111.7468, 115.2237, 110.2857, 104.0568, 101.2198, 89.92504,
	85.03304, 85.88800, 80.28461, 72.37584, 65.10618, 62.33925, 56.58879, 57.32026,
	43.18078, 49.04259, 47.24373, 41.46023, 43.26971, 32.75382, 31.16690, 30.13385,
	34.67052, 27.41213, 26.28916, 23.73505, 23.82943, 16.69553, 19.68351, 13.46224,
	18.50213, 22.69586, 26.47890, 20.65873, 20.96244, 32.70152, 21.20834, 36.29262,
	31.60030, 40.44346, 40.41177, 39.12918, 35.65691, 45.60188, 54.32038, 56.90118,
	71.05725, 73.71820, 61.85146, 70.53017, 78.21766, 97.09329, 97.92851, 87.43561,
	94.80290, 102.1922, 108.0195, 114.9619, 106.3327, 122.6930, 130.5194, 135.2054,
	129.4585, 137.6123, 149.6134, 148.2783, 148.9325, 155.4761, 152.7459, 158.2726,
	165.0088, 165.4201, 170.2190, 172.7326, 181.0965, 188.8904, 181.8140, 172.5070,
	172.5251, 176.9207, 180.5163, 177.9654, 187.8499, 177.1344, 167.7879, 172.3201,
	174.0538, 161.4944, 174.7457, 171.0184, 157.4744, 157.1502, 157.2388, 152.3408,
	147.6573, 135.6112, 133.9712, 148.6547, 123.7228, 120.3214, 118.0651, 115.6238,
	102.0745, 100.7319, 98.46876, 91.89931, 78.67442, 84.48637, 72.10534, 82.00717,
	73.20561, 61.13931, 60.16510, 52.83732, 47.20147, 46.64873, 41.90375, 50.79880,
	45.15685, 37.59033, 26.25438, 26.67647, 33.17753, 23.09894, 29.88979, 21.40763,
	23.56838, 17.93852, 30.34013, 17.26442, 17.47089, 21.83335, 14.70368, 20.90120,
	22.55676, 23.58267, 24.28844, 35.65466, 32.76925, 31.87992, 45.03176, 48.93682,
	40.42789, 44.67754, 62.20622, 60.21795, 62.41084, 68.37954, 65.49177, 66.54289,
	72.96865, 83.43566, 85.57089, 91.95457, 95.07531, 108.0927, 103.8378, 117.4740,
	120.0833, 133.3239, 131.7428, 130.9815, 136.6515, 147.6466, 150.5822, 148.2187,
	158.3409, 156.6469, 157.7010, 155.9400, 170.4727, 172.0633, 172.5074, 170.0180,
	181.5532, 183.7947, 184.7920, 185.4948, 175.6472, 178.9055, 182.9460, 181.5844,
	180.0448, 174.0839, 168.2962, 177.9329, 171.3266, 162.1160, 170.4824, 163.1437,
	163.1918, 163.7356, 155.1483, 149.1099, 145.7943, 144.9221, 135.5171, 142.4453,
	120.9124, 120.5395, 119.5177, 114.6017, 110.3015, 107.6901, 90.24635, 96.94422,
	84.58745, 76.18815, 93.25997, 77.58381, 68.53246, 68.09649, 64.68458, 65.80039,
	52.15291, 45.50834, 44.90046, 48.50918, 31.13444, 35.53844, 34.63394, 25.56288,
	27.46021, 27.86333, 22.42501, 27.11198, 14.99134, 18.61507, 22.85051, 19.52163,
	17.85876, 29.03766, 23.40240, 18.12429, 26.48101, 20.05503, 33.97313, 36.82469,
	31.09046, 34.67607, 34.24447, 35.27413, 48.99913, 51.25105, 60.36957, 56.68985,
	55.13515, 65.69605, 76.67919, 73.19436, 76.71909, 78.81924, 90.69193, 93.20833,
	94.53514, 104.3348, 111.8974, 107.4964, 115.4393, 126.7441, 133.5835, 128.6093,
	138.3969, 149.3131, 143.7588, 152.5440, 154.1792, 163.1328, 161.1375, 163.2680,
	166.7497, 174.1591, 177.6743, 175.8427, 167.2441, 178.5573, 176.3179, 174.7231,
	174.3835, 180.3670, 172.9310, 180.6186, 171.5325, 174.1803, 178.8301, 171.9550,
	169.6733, 169.3744, 163.1887, 170.1302, 162.7302, 163.8334, 153.1741, 155.3802,
	146.4998, 143.0479, 141.8208, 130.1919, 133.9815, 115.5337, 123.2014, 116.3309,
	112.5248, 111.1218, 105.6224, 87.64631, 87.81907, 85.40776, 84.01390, 79.77217,
	67.82084, 68.19411, 61.16450, 56.52342, 59.17200, 51.21574, 40.50974, 46.66268,
	36.96143, 27.51148, 28.74710, 24.92471, 28.12440, 25.60986, 24.73533, 19.91413,
	18.98411, 22.71274, 17.93809, 22.56179, 20.06517, 18.48677, 28.08414, 16.05945,
	31.21950, 26.13409, 28.74561, 24.64278, 25.39746, 41.33334, 38.81396, 49.50916,
	44.22907, 58.28380, 46.49612, 56.51082, 59.42354, 65.67959, 74.41576, 76.08542,
	69.37040, 93.41253, 95.97955, 96.09916, 102.4482, 100.3711, 108.8371, 116.0791,
	122.6391, 119.9278, 130.5090, 135.9740, 132.4813, 145.8584, 150.2292, 154.9838,
	152.8047, 161.9230, 162.5253, 168.3987, 170.1055, 169.5918, 179.2676, 173.7630,
	173.9429, 186.7359, 177.8262, 180.7459, 180.7000, 186.0442, 182.0221, 181.4734,
	183.4505, 175.4004, 177.6661, 168.5839, 172.4377, 170.2503, 161.8071, 163.3458,
	157.7044, 154.0640, 148.7402, 142.8176, 138.8016, 140.3127, 151.9686, 129.3891,
	124.1049, 123.8855, 116.8205, 119.7430, 101.2142, 102.4020, 97.76879, 90.61830,
	96.98204, 83.63044, 80.47530, 82.37470, 73.84644, 70.39754, 59.52119, 58.33106,
	54.69233, 50.54659, 37.89833, 40.70695, 30.10147, 37.61708, 29.74796, 34.52642,
	40.47763, 26.04013, 19.19908, 30.65279, 16.38498, 20.41743, 24.31475, 22.09900,
	20.00037, 19.75840, 27.34791, 27.41358, 22.07080, 23.99416, 25.72485, 30.97418,
	30.34330, 32.97958, 35.57299, 35.02300, 35.72745, 39.02536, 55.75761, 52.59317,
	63.47889, 60.67192, 67.73177, 79.14154, 77.35390, 83.42601, 97.81542, 91.98067,
	103.1721, 105.4559, 108.2936, 118.6188, 121.4318, 119.7649, 141.3113, 140.6158,
	150.7037, 149.7822, 139.9115, 144.5985, 152.6690, 146.0639, 169.6007, 165.4434,
	173.0982, 167.2959, 166.8559, 178.2473, 172.5712, 185.4050, 183.7084, 186.7897
};

float32_t FIR_Dst[FIR_DATA_SIZE];
float32_t FFT_Src[FFT_DATA_SIZE];
float32_t FFT_Dst[FFT_DATA_SIZE];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void ALGO_FIR_Demo(void);
void ALGO_FFT_Demo_1(void);
void ALGO_FFT_Demo_2(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */
  /* Choose demos ------------------------------------------------------------*/
  ALGO_FIR_Demo();
  ALGO_FFT_Demo_1();
  ALGO_FFT_Demo_2();
  
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
void ALGO_FIR_Demo(void)
{
	// The original signal is suppose to be
	// f(t) = 100 + 80 * sin(0.02 * PI * t) + 5 * GaussianNoise,
	// which means the main frequency is wd = 0.02.
	// Ex. Fs = 1 MHz, f = 10 kHz, Vpp = 160 V, Vbias = 100 V.
	FIR_f32((float32_t *)FIR_Src, FIR_Dst);
	
	// Print waveforms before and after filtering. Pay attention to group delay.
	for (uint16_t i = 0; i < FIR_DATA_SIZE - FIR_NUM_TAPS / 2; ++i)
		myUART_Transmit_DMA(&UART_Debug, "FIR[%d]: %.3f, %.3f\n", i, FIR_Src[i], FIR_Dst[i + FIR_NUM_TAPS / 2]);
}

void ALGO_FFT_Demo_1(void)
{
	// Demo data 1 for integral period (without leakage of frequency spectrum)
	for (uint16_t i = 0; i < FFT_DATA_SIZE; ++i)
		FFT_Src[i] = 100,
		FFT_Src[i] += 75 * arm_cos_f32( 2 * PI / FFT_DATA_SIZE * i),
		FFT_Src[i] += 20 * arm_cos_f32( 6 * PI / FFT_DATA_SIZE * i +  60 * PI / 180),
		FFT_Src[i] += 10 * arm_cos_f32(12 * PI / FFT_DATA_SIZE * i - 135 * PI / 180);
	
	// To remove meaningless part, phases with amplitudes below the threshold will be set to 0.
	RFFT_f32(FFT_Src, FFT_Dst, 5e-4);
	
	// Print both amplitude spectrum and phase spectrum simultaneously.
	for (uint16_t i = 0; i < FFT_DATA_SIZE / 2; ++i)
		myUART_Transmit_DMA(&UART_Debug, "FFT[%d]: %.3f, %.3f\n", i, FFT_Dst[i], FFT_Dst[i + FFT_DATA_SIZE / 2] * (180 / PI));
}

void ALGO_FFT_Demo_2(void)
{
	// Demo data 2 for non-integral period (with leakage of frequency spectrum)
	for (uint16_t i = 0; i < FFT_DATA_SIZE; ++i)
		FFT_Src[i] = 100 + 75 * arm_cos_f32(2 * PI / 1000 * i);
	
	// To remove meaningless part, phases with amplitudes below the threshold will be set to 0.
	RFFT_f32(FFT_Src, FFT_Dst, 5e-4);
	
	// Print both amplitude spectrum and phase spectrum simultaneously.
	for (uint16_t i = 0; i < FFT_DATA_SIZE / 2; ++i)
		myUART_Transmit_DMA(&UART_Debug, "FFT[%d]: %.3f, %.3f\n", i, FFT_Dst[i], FFT_Dst[i + FFT_DATA_SIZE / 2] * (180 / PI));
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
