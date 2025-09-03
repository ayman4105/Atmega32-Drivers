/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 


#include "application.h"

uint8 Tens = 0;
uint8 Ones = 0;

int main(void)
{
	Std_ReturnType ret = E_NOT_OK;
    application_intialize();
	
	
	if (ret != E_OK)
	{/*Handle failure*/}
	
	if (ret != E_OK)
	{/*Handle failure*/}
    while (1) 
    {
		for(Tens = 0; Tens < 10; Tens++)
		{
			ret = gpio_port_write_logic(PORTC_INDEX,Tens);
			for (Ones = 0; Ones < 10; Ones++)
			{
				ret = gpio_port_write_logic(PORTD_INDEX,Ones);
				_delay_ms(500);
			}
		}
		//if (ret != E_OK)
		//{/*Handle failure*/}
				//
		//if (ret != E_OK)
		//{/*Handle failure*/}
	//
		//
		//
		//if (ret != E_OK)
		//{/*Handle failure*/}
			//
		//if (ret != E_OK)
		//{/*Handle failure*/}
		//
		//
		//
		//if (ret != E_OK)
		//{/*Handle failure*/}
		//
		//if (ret != E_OK)
		//{/*Handle failure*/}
		
    }
}

void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	
	ret = gpio_port_direction_intialize(PORTC_INDEX,0xFF);
	if (ret != E_OK)
	{/*Handle failure*/}
		
	ret = gpio_port_direction_intialize(PORTD_INDEX,0xFF);		 
	if (ret != E_OK)
	{/*Handle failure*/}	
	ret = gpio_port_write_logic(PORTD_INDEX,0); 
	if (ret != E_OK)
	{/*Handle failure*/}
	ret = gpio_port_write_logic(PORTC_INDEX,0);
	if (ret != E_OK)
	{/*Handle failure*/}
}