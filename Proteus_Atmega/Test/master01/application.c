/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"

void writeRegister(uint8 reg, uint8* value, uint8 len);
void transmitSync(uint8* dataout,uint8 len);

SPI_Config SPI_Master =
{
	.spi_mode = SPI_MASTER_MODE,
	.spi_config.SCKFrequency= SPI_MASTER_FOSC_DIV2,
	.spi_config.ClockPolarity_ClockPhase = SPI_IDLE_LOW_SAMPLE_RAISING,
	.SPI_InterruptHandler = NULL
};

pin_config_t SPI_SS =
{
	.port = PORTB_INDEX,
	.pin = GPIO_PIN4,
	.direction = GPIO_DIRECTION_OUTPUT,
	.logic = GPIO_HIGH
};
		
int main(void)
{
	Std_ReturnType ret = E_OK;
	
	uint8 rx_address[5] = {0xD7,0xD7,0xD7,0xD7,0xD7};
	
	application_intialize();
	
	
	
	
	
		
	while(1)
	{
		
		writeRegister(RX_ADDR_P0,rx_address,5);
		
	}
	
	return 0;
}

void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	
	SPI_Init(&SPI_Master);
	
	if (ret != E_OK)
	{/*Handle failure*/}
}

void transmitSync(uint8* dataout,uint8 len)
{
	uint8_t i;
	
	for(i=0;i<len;i++)
	{
		SPI_Master_Send_Byte(&SPI_Master, dataout[i]);
	}

}


void writeRegister(uint8 reg, uint8* value, uint8 len)
{
	gpio_pin_write_logic(&SPI_SS, GPIO_LOW);
	SPI_Master_Send_Byte(&SPI_Master, W_REGISTER | (REGISTER_MASK & reg));
	transmitSync(value,len);
	gpio_pin_write_logic(&SPI_SS, GPIO_HIGH);
	_delay_ms(500);
}

