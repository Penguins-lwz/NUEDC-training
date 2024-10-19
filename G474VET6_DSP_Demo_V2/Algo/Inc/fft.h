#ifndef __FFT_H__
#define __FFT_H__

#include "main.h"
#include "arm_math.h"
#include "arm_const_structs.h"

// Number of samples waited to transform, only 32, 64, ..., 4096 are supported
#define FFT_DATA_SIZE	1024

void RFFT_f32(float32_t *pSrc, float32_t *pDst, float32_t threshold);

#endif /* __FFT_H__ */
