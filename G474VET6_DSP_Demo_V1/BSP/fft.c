#include "fft.h"

// FFT 输入为复数，实际长度是定义长度的两倍
float FFT_Buf[2 * FFT_LENGTH];

void myARM_FFT_Mag(float *pInputData, float *pOutputData)
{
	// 使用复数快速傅里叶变换，偶下标为实部，奇下标为虚部
	for (uint16_t i = 0; i < FFT_LENGTH; ++i)
		FFT_Buf[2 * i] = pInputData[i],
		FFT_Buf[2 * i + 1] = 0;
	
	// 快速傅里叶正变换，复数结果仍保存回 FFT_Buf
	// 参数 1：FFT 参数结构体，DSP 库已预设，根据采样点数选取
	// 参数 2：数据输入数组
	// 参数 3：0 正变换，1 逆变换
	// 参数 4：0 禁用输出反转，1 使能输出反转
	arm_cfft_f32(&arm_cfft_sR_f32_len4096, FFT_Buf, 0, 1);
	
	// 计算复数幅值
	// 参数 1：复数输入数组
	// 参数 2：复数输出数组
	// 参数 3：数据长度
	arm_cmplx_mag_f32(FFT_Buf, pOutputData, FFT_LENGTH);
	
	// 消除采样点数造成的幅值变化，详见《信号与系统》教材
	pOutputData[0] /= FFT_LENGTH;
	for (uint16_t i = 1; i < FFT_LENGTH; ++i)
		pOutputData[i] = 2 * pOutputData[i] / FFT_LENGTH;
}
