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

void SPI_Interrupt_Handler(void);
volatile uint8 x =0;
SPI_Config SPI_Master = 
{
	.spi_mode = SPI_MASTER_MODE,
	.spi_config.SCKFrequency= SPI_MASTER_FOSC_DIV128,
	.spi_config.ClockPolarity_ClockPhase = SPI_IDLE_LOW_SAMPLE_RAISING,
	.spi_config.SPI_Interrupt = SPI_INTERRUPT_ENABLE,
	.SPI_InterruptHandler = SPI_Interrupt_Handler 
};

//SPI_Config SPI_Slave =
//{
	//.spi_mode = SPI_SLAVE_MODE,
	//.spi_config.SCKFrequency= SPI_MASTER_FOSC_DIV16,
	//.spi_config.ClockPolarity_ClockPhase = SPI_IDLE_LOW_SAMPLE_RAISING,
	//.SPI_InterruptHandler = NULL
//};

pin_config_t SPI_SS =
{
	.port = PORTB_INDEX,
	.pin = GPIO_PIN4,
	.direction = GPIO_DIRECTION_OUTPUT,
	.logic = GPIO_HIGH
};



int main(void)
{
	
	Std_ReturnType ret = E_NOT_OK;
	application_intialize();

    while (1) 
    {	
		// Send character "A" via SPI
		ret = gpio_pin_write_logic(&SPI_SS, GPIO_LOW);
		SPI_Master_Send_Byte(&SPI_Master, 'A');
		ret = gpio_pin_write_logic(&SPI_SS, GPIO_HIGH);
		_delay_ms(500);
		
		// Send character "B" via SPI
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
	ret = gpio_pin_intialize(&SPI_SS);

	
	
	
	if (ret != E_OK)
	{/*Handle failure*/}
}


// Interrupt Handler function for SPI
void SPI_Interrupt_Handler(void)
{
	// When the interrupt occurs, send character "C" via SPI
	SPI_Master_Send_Byte(&SPI_Master, 'C');
	
}