#ifndef __MAIN_H__
#define __MAIN_H__

#include "ti_msp_dl_config.h"
#include "stdio.h"
#include "string.h"
#include "stdarg.h"

#define DL_Delay(xms)	delay_cycles(CPUCLK_FREQ / 1000 * (xms))

#endif /*__MAIN_H__*/
