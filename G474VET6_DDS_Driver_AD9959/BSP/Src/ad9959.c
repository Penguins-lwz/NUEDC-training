#include "ad9959.h"

static void DDS_Transmit(uint8_t pData)
{
	for (uint8_t i = 0; i < 8; ++i)
	{
		DDS_SDA_Set(pData & (0x80 >> i));
		DDS_SCL_Set(1);
		DDS_SCL_Set(0);
	}
	
	DDS_UPD_Set(1); HAL_Delay(1);
	DDS_UPD_Set(0); HAL_Delay(1);
}

void DDS_Init(void)
{
	DDS_CS_Set(1);
	DDS_RST_Set(1);
	DDS_SCL_Set(0);
	DDS_SDA_Set(0);
	DDS_UPD_Set(0);
	HAL_Delay(30);
	
	DDS_RST_Set(0);
	HAL_Delay(30);
	
	DDS_CS_Set(0);
	
	DDS_Transmit(0x01);
	DDS_Transmit(0xD0);
	DDS_Transmit(0x00);
	DDS_Transmit(0x00);
	
	DDS_Transmit(0x02);
	DDS_Transmit(0x20);
	DDS_Transmit(0x00);
	
	DDS_Transmit(0x06);
	DDS_Transmit(0x00);
	DDS_Transmit(0x13);
	DDS_Transmit(0xFF);
	
	DDS_CS_Set(1);
}

void DDS_Config(uint8_t channel, float freq, float phase)
{
//	uint32_t regf = freq * (1 << 32) / 500000000 + 0.5f;
	uint32_t regf = freq * 8.589934592 + 0.5f;
	uint16_t regp = phase * (1 << 14) / 360 + 0.5f;
	
	DDS_CS_Set(0);
	
	DDS_Transmit(0x00);
	DDS_Transmit(channel);
	
	DDS_Transmit(0x04);
	DDS_Transmit(regf >> 24);
	DDS_Transmit(regf >> 16);
	DDS_Transmit(regf >> 8);
	DDS_Transmit(regf >> 0);
	
	DDS_Transmit(0x05);
	DDS_Transmit(regp >> 8);
	DDS_Transmit(regp >> 0);
	
	DDS_CS_Set(1);
}
