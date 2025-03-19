#include "opa.h"

void myOPA_Config(OA_Regs *hopa, DL_OPA_GAIN newGain)
{
	DL_OPA_setGain(hopa, newGain);
}
