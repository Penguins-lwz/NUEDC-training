#ifndef __FFT_H__
#define __FFT_H__

#include "main.h"
#include "arm_math.h"
#include "arm_const_structs.h"

// FFT 采样点数，只能取 2 的 4 ~ 12 次幂
#define FFT_LENGTH			4096

void myARM_FFT_Mag(float *pInputData, float *pOutputData);

#endif /* __FFT_H__ */
