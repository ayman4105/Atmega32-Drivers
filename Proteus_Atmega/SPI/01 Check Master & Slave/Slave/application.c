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

//SPI_Config SPI_Master = 
//{
	//.spi_mode = SPI_MASTER_MODE,
	//.spi_config.SCKFrequency= SPI_MASTER_FOSC_DIV16,
	//.spi_config.ClockPolarity_ClockPhase = SPI_IDLE_LOW_SAMPLE_RAISING,
	//.SPI_InterruptHandler = NULL
//};

SPI_Config SPI_Slave =
{
	.spi_mode = SPI_SLAVE_MODE,
	.spi_config.ClockPolarity_ClockPhase = SPI_IDLE_LOW_SAMPLE_RAISING,
	.spi_config.SPI_Interrupt = SPI_INTERRUPT_DISABLE,
	.SPI_InterruptHandler = NULL
};

//pin_config_t SPI_SS =
//{
	//.port = PORTA_INDEX,
	//.pin = PINA0,
	//.direction = GPIO_DIRECTION_INPUT,
	//.logic = GPIO_HIGH
//};

chr_lcd_4bits_t lcd_1 =
{
	.lcd_rs.port = PORTC_INDEX,
	.lcd_rs.pin = GPIO_PIN0,
	.lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
	.lcd_rs.logic = GPIO_LOW,
	
	.lcd_en.port = PORTC_INDEX,
	.lcd_en.pin = GPIO_PIN1,
	.lcd_en.direction = GPIO_DIRECTION_OUTPUT,
	.lcd_en.logic = GPIO_LOW,
	
	.lcd_data[0].port = PORTC_INDEX,
	.lcd_data[0].pin = GPIO_PIN2,
	.lcd_data[0].logic = GPIO_LOW,
	.lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
	
	.lcd_data[1].port = PORTC_INDEX,
	.lcd_data[1].pin = GPIO_PIN3,
	.lcd_data[1].logic = GPIO_LOW,
	.lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
	
	.lcd_data[2].port = PORTD_INDEX,
	.lcd_data[2].pin = GPIO_PIN4,
	.lcd_data[2].logic = GPIO_LOW,
	.lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
	
	.lcd_data[3].port = PORTC_INDEX,
	.lcd_data[3].pin = GPIO_PIN5,
	.lcd_data[3].logic = GPIO_LOW,
	.lcd_data[3].direction = GPIO_DIRECTION_OUTPUT
};

uint8 counter = ZERO_INIT;
uint8 counter_txt[4];

int main(void)
{
	
	Std_ReturnType ret = E_NOT_OK;
	application_intialize();
	
	ret = lcd_4bits_send_string_pos(&lcd_1,1,1,"Slave Device");
	ret = lcd_4bits_send_string_pos(&lcd_1,2,1,"Receiving Data : ");
	
	//ret = gpio_pin_write_logic(&SPI_SS,GPIO_LOW);

    while (1) 
    {	
		SPI_Slave_Read_Byte(&SPI_Slave,&counter);
		ret = convert_uint8_to_string(counter,counter_txt);
		ret = lcd_4bits_send_string_pos(&lcd_1,1,18,counter_txt);
		
		if (ret != E_OK)
		{/*Handle failure*/}
		
    }
}


void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	//ret = SPI_Init(&SPI_Master);
	ret = SPI_Init(&SPI_Slave);
	ret = lcd_4bits_intialize(&lcd_1);
	//ret = gpio_pin_intialize(&SPI_SS);

	
	
	
	if (ret != E_OK)
	{/*Handle failure*/}
}
