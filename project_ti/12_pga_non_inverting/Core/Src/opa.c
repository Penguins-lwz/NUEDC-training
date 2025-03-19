#include "opa.h"

void myOPA_Config(OA_Regs *hopa, DL_OPA_GAIN newGain)
{
	DL_OPA_disable(hopa);
	DL_OPA_setGain(hopa, newGain);
	DL_OPA_setInvertingInputChannel(hopa, newGain == DL_OPA_GAIN_N0_P1 ? DL_OPA_NSEL_RTOP : DL_OPA_NSEL_RTAP);
	DL_OPA_enable(hopa);
}
