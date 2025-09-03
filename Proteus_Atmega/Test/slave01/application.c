/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"

uint8 received_data[6];

SPI_Config SPI_Slave =
{
	.spi_mode = SPI_SLAVE_MODE,
	.spi_config.ClockPolarity_ClockPhase = SPI_IDLE_LOW_SAMPLE_RAISING,
	.SPI_InterruptHandler = NULL
};

		
int main(void)
{
	Std_ReturnType ret = E_OK;
	
	
	application_intialize();
	
	
		
	while(1)
	{
		
		for (uint8_t i = 0; i < 5; i++)
		{
			SPI_Read_Byte(&SPI_Slave, &received_data[i]);
		}
		
		
	}
	
	return 0;
}

void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	SPI_Init(&SPI_Slave);
	
	if (ret != E_OK)
	{/*Handle failure*/}
}




