#ifndef __FIR_H__
#define __FIR_H__

#include "main.h"
#include "arm_math.h"

// Number of filter coefficients in the filter, equal to order + 1
#define FIR_NUM_TAPS	49

// Number of samples waited to filter, including group delay terms
#define FIR_DATA_SIZE	1024

// Number of samples processed per call, ranging from 1 to FIR_DATA_SIZE
#define FIR_BLOCK_SIZE	16

void FIR_f32(float32_t *pSrc, float32_t *pDst);

#endif /* __FIR_H__ */
