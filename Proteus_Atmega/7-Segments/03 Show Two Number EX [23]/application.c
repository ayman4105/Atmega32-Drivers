/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 


#include "application.h"

uint8 Number = 0;
uint8 New_Number = 0;

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
		New_Number = (((uint8)Number%10) | (((uint8)Number/10) << 4));
		ret = gpio_port_write_logic(PORTC_INDEX,New_Number);
		if (99 == Number)
		{
			Number = 55;
		}
		else{}
		Number++;
		_delay_ms(200);	
	
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
	ret = gpio_port_write_logic(PORTC_INDEX,0);
	if (ret != E_OK)
	{/*Handle failure*/}
}