/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "hal_eeprom.h"
#include "hal_usart.h"
#include "hal_spi.h"

SPI_Config SPI_Master = 
{
	.spi_mode = SPI_MASTER_MODE,
	.spi_config.SCKFrequency= SPI_MASTER_FOSC_DIV64,
	.spi_config.ClockPolarity_ClockPhase = SPI_IDLE_LOW_SAMPLE_RAISING,
	.spi_config.SPI_Interrupt = SPI_INTERRUPT_DISABLE,
	.SPI_InterruptHandler = NULL
};

//SPI_Config SPI_Slave =
//{
	//.spi_mode = SPI_SLAVE_MODE,
	//.spi_config.ClockPolarity_ClockPhase = SPI_IDLE_LOW_SAMPLE_RAISING,
	//.SPI_InterruptHandler = NULL
//};

pin_config_t SPI_SS =
{
	.port = PORTC_INDEX,
	.pin = GPIO_PIN0,
	.direction = GPIO_DIRECTION_OUTPUT,
	.logic = GPIO_HIGH
};



int main(void)
{
	
	Std_ReturnType ret = E_NOT_OK;
	application_intialize();
	

	while (1)
	{
        ret = gpio_pin_write_logic(&SPI_SS, GPIO_LOW);
        SPI_Master_Send_Byte(&SPI_Master, 'A');
        ret = gpio_pin_write_logic(&SPI_SS, GPIO_HIGH);
        _delay_ms(500);
		
		ret = gpio_pin_write_logic(&SPI_SS, GPIO_LOW);
		SPI_Master_Send_Byte(&SPI_Master, 'B');
		ret = gpio_pin_write_logic(&SPI_SS, GPIO_HIGH);
		_delay_ms(500);
		
	}
}


void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	ret = SPI_Init(&SPI_Master);
	//ret = SPI_Init(&SPI_Slave);
	//ret = lcd_4bits_intialize(&lcd_1);
	ret = gpio_pin_intialize(&SPI_SS);

	
	
	
	if (ret != E_OK)
	{/*Handle failure*/}
}
