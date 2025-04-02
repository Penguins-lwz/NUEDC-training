#include "ad9833.h"

static void AD9833_Transmit(uint16_t pData)
{
	for (uint8_t i = 0; i < 16; ++i)
	{
		AD9833_SDA_Set(pData & (0x8000 >> i) ? 1 : 0);
		AD9833_SCL_Set(0);
		AD9833_SCL_Set(1);
	}
}

void AD9833_Config(uint16_t form, float freq, float phase)
{
	uint32_t regf = freq * (1 << 28) / 25000000 + 0.5f;
	uint32_t regp = phase * (1 << 12) / 360 + 0.5f;
	
	AD9833_CS_Set(0);
	AD9833_Transmit(0x2100 | form);
	AD9833_Transmit(0x4000 | (regf & 0x3FFF));
	AD9833_Transmit(0x4000 | (regf >> 14));
	AD9833_Transmit(0xC000 | (regp & 0xFFF));
	AD9833_Transmit(0x2000 | form);
	AD9833_CS_Set(1);
}