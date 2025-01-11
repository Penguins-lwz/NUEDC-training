#include "ad9959.h"

static void AD9959_Transmit(uint8_t pData)
{
	for (uint8_t i = 0; i < 8; ++i)
	{
		AD9959_SDA_Set(pData & (0x80 >> i) ? 1 : 0);
		AD9959_SCL_Set(1);
		AD9959_SCL_Set(0);
	}
	
	AD9959_UPD_Set(1); HAL_Delay(1);
	AD9959_UPD_Set(0); HAL_Delay(1);
}

void AD9959_Init(void)
{
	AD9959_CS_Set(1);
	AD9959_RST_Set(1);
	AD9959_SCL_Set(0);
	AD9959_SDA_Set(0);
	AD9959_UPD_Set(0);
	HAL_Delay(30);
	
	AD9959_RST_Set(0);
	HAL_Delay(30);
	
	AD9959_CS_Set(0);
	
	AD9959_Transmit(0x01);
	AD9959_Transmit(0xD0);
	AD9959_Transmit(0x00);
	AD9959_Transmit(0x00);
	
	AD9959_Transmit(0x02);
	AD9959_Transmit(0x20);
	AD9959_Transmit(0x00);
	
	AD9959_Transmit(0x06);
	AD9959_Transmit(0x00);
	AD9959_Transmit(0x13);
	AD9959_Transmit(0xFF);
	
	AD9959_CS_Set(1);
}

void AD9959_Config(uint8_t channel, float freq, float phase)
{
//	uint32_t regf = freq * (1 << 32) / 500000000 + 0.5f;
	uint32_t regf = freq * 8.589934592 + 0.5f;
	uint16_t regp = phase * (1 << 14) / 360 + 0.5f;
	
	AD9959_CS_Set(0);
	
	AD9959_Transmit(0x00);
	AD9959_Transmit(channel);
	
	AD9959_Transmit(0x04);
	AD9959_Transmit(regf >> 24);
	AD9959_Transmit(regf >> 16);
	AD9959_Transmit(regf >> 8);
	AD9959_Transmit(regf >> 0);
	
	AD9959_Transmit(0x05);
	AD9959_Transmit(regp >> 8);
	AD9959_Transmit(regp >> 0);
	
	AD9959_CS_Set(1);
}
