#include "main.h"
#include "dds.h"

int main(void)
{
	SYSCFG_DL_init();
	
	DDS_Init();
	DDS_Config(DDS_CH0, 5000000, 0);
	DDS_Config(DDS_CH1, 5000000, 90);
	DDS_Config(DDS_CH2, 5000000, 180);
	DDS_Config(DDS_CH3, 5000000, 270); 
	
	while (1)
	{
		
	}
}
