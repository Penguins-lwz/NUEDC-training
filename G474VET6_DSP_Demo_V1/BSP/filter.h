#ifndef __FILTER_H__
#define __FILTER_H__

#include "main.h"
#include "arm_math.h"

#define FILTER_SIZE			4096

void myARM_FIR(float *pInputData, float *pOutputData);

#endif /* __FILTER_H__ */
