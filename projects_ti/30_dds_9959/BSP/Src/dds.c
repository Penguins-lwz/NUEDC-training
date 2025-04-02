#include "dds.h"

#define DDS_SCL_WR(x)	DL_GPIO_writePinsVal(DDS_PORT, DDS_SCL_PIN, x ? DDS_SCL_PIN : 0)
#define DDS_SDA_WR(x)	DL_GPIO_writePinsVal(DDS_PORT, DDS_SDA_PIN, x ? DDS_SDA_PIN : 0)
#define DDS_UPD_WR(x)	DL_GPIO_writePinsVal(DDS_PORT, DDS_UPD_PIN, x ? DDS_UPD_PIN : 0)
#define DDS_RST_WR(x)	DL_GPIO_writePinsVal(DDS_PORT, DDS_RST_PIN, x ? DDS_RST_PIN : 0)
#define DDS_CS_WR(x)	DL_GPIO_writePinsVal(DDS_PORT, DDS_CS_PIN, x ? DDS_CS_PIN : 0)

static void DDS_WR(uint8_t data)
{
	for (uint8_t j = 0; j < 8; ++j)
	{
		DDS_SDA_WR(data & (0x80 >> j));
		DDS_SCL_WR(1);
		DDS_SCL_WR(0);
	}
	
	DDS_UPD_WR(1);
	DDS_UPD_WR(0);
}

void DDS_Init(void)
{
	DDS_CS_WR(1);
	DDS_RST_WR(1);
	DDS_SCL_WR(0);
	DDS_SDA_WR(0);
	DDS_UPD_WR(0);
	
	DDS_RST_WR(0);
	
	DDS_CS_WR(0);
	
	DDS_WR(0x01);
	DDS_WR(0xD0);
	DDS_WR(0x00);
	DDS_WR(0x00);
	
	DDS_WR(0x02);
	DDS_WR(0x20);
	DDS_WR(0x00);
	
	DDS_WR(0x06);
	DDS_WR(0x00);
	DDS_WR(0x13);
	DDS_WR(0xFF);
	
	DDS_CS_WR(1);
}

void DDS_Config(uint8_t channel, float freq, float phase)
{
//	uint32_t regf = freq * (1 << 32) / 500000000 + 0.5f;
	uint32_t regf = freq * 8.589934592 + 0.5f;
	uint16_t regp = phase * (1 << 14) / 360 + 0.5f;
	
	DDS_CS_WR(0);
	
	DDS_WR(0x00);
	DDS_WR(channel);
	
	DDS_WR(0x04);
	DDS_WR(regf >> 24);
	DDS_WR(regf >> 16);
	DDS_WR(regf >> 8);
	DDS_WR(regf >> 0);
	
	DDS_WR(0x05);
	DDS_WR(regp >> 8);
	DDS_WR(regp >> 0);
	
	DDS_CS_WR(1);
}
