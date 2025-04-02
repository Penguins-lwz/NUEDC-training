#include "fft.h"

float32_t FFT_Buffer[2 * FFT_DATA_SIZE];

void RFFT_f32(float32_t *pSrc, float32_t *pDst, float32_t threshold)
{
	for (uint16_t i = 0; i < FFT_DATA_SIZE; ++i)
		FFT_Buffer[2 * i] = pSrc[i],
		FFT_Buffer[2 * i + 1] = 0;
	
	arm_cfft_instance_f32 S;
	arm_cfft_init_f32(&S, FFT_DATA_SIZE);
	arm_cfft_f32(&S, FFT_Buffer, 0, 1);
	arm_cmplx_mag_f32(FFT_Buffer, pDst, FFT_DATA_SIZE / 2);
	
	pDst[0] /= FFT_DATA_SIZE;
	pDst[FFT_DATA_SIZE / 2] = 0;
	for (uint16_t i = 1; i < FFT_DATA_SIZE / 2; ++i)
	{
		pDst[i] /= (FFT_DATA_SIZE / 2);
		if (pDst[i] < threshold) pDst[i + FFT_DATA_SIZE / 2] = 0;
		else arm_atan2_f32(FFT_Buffer[2 * i + 1], FFT_Buffer[2 * i], &pDst[i + FFT_DATA_SIZE / 2]);
	}
}
