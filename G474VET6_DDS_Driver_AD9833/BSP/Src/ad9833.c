#include "ad9833.h"

static void DDS_Transmit(uint16_t pData)
{
	for (uint8_t i = 0; i < 16; ++i)
	{
		DDS_SDA_Set(pData & (0x8000 >> i) ? 1 : 0);
		DDS_SCL_Set(0);
		DDS_SCL_Set(1);
	}
}

void DDS_Config(uint16_t form, float freq, float phase)
{
	uint32_t regf = freq * (1 << 28) / MCLK + 0.5f;
	uint32_t regp = phase * (1 << 12) / 360 + 0.5f;
	
	DDS_CS_Set(0);
	DDS_Transmit(0x2100 | form);
	DDS_Transmit(0x4000 | (regf & 0x3FFF));
	DDS_Transmit(0x4000 | (regf >> 14));
	DDS_Transmit(0xC000 | (regp & 0xFFF));
	DDS_Transmit(0x2000 | form);
	DDS_CS_Set(1);
}
