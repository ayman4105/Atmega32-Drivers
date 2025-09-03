/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 


#include "application.h"

uint8 hours = 23;
uint8 minutes = 59;
uint8 seconds = 59;
uint8 counter = 0;

int main(void)
{
	Std_ReturnType ret = E_NOT_OK;
    application_intialize();
	
    while (1) 
    {
		/********************** Common Cathode **********************/
		for (counter = 0; counter < 50; counter++)
		{
			ret = gpio_port_write_logic(PORTD_INDEX,0xFE);
			ret = gpio_port_write_logic(PORTC_INDEX,(uint8)hours/10);
			_delay_us(3333);
			ret = gpio_port_write_logic(PORTD_INDEX,0xFD);
			ret = gpio_port_write_logic(PORTC_INDEX,(uint8)hours%10);
			_delay_us(3333);
			ret = gpio_port_write_logic(PORTD_INDEX,0xFB);
			ret = gpio_port_write_logic(PORTC_INDEX,(uint8)minutes/10);
			_delay_us(3333);
			ret = gpio_port_write_logic(PORTD_INDEX,0xF7);
			ret = gpio_port_write_logic(PORTC_INDEX,(uint8)minutes%10);
			_delay_us(3333);
			ret = gpio_port_write_logic(PORTD_INDEX,0xEF);
			ret = gpio_port_write_logic(PORTC_INDEX,(uint8)seconds/10);
			_delay_us(3333);
			ret = gpio_port_write_logic(PORTD_INDEX,0xDF);
			ret = gpio_port_write_logic(PORTC_INDEX,(uint8)seconds%10);
			_delay_us(3333);
		}
		seconds++;
		if(60 == seconds)
		{
			minutes++;
			seconds = 0;
		}
		
		if(60 == minutes)
		{
			hours++;
			minutes = 0;
		}
		
		if(24 == hours)
		{
			hours = 0;
		}
	
		if (ret != E_OK)
		{/*Handle failure*/}
				
	
		
    }
}

void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	
	ret = gpio_port_direction_intialize(PORTC_INDEX,0x0F);
	ret = gpio_port_direction_intialize(PORTD_INDEX,0x3F);
	if (ret != E_OK)
	{/*Handle failure*/}
}