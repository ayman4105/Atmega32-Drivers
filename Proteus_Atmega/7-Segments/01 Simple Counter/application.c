/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 


#include "application.h"

uint8 Number_Value_Common_Anode[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
uint8 Number_Value_Common_Cathod[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
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
			ret = gpio_port_write_logic(PORTC_INDEX,Number_Value_Common_Anode[Tens]);
			for (Ones = 0; Ones < 10; Ones++)
			{
				ret = gpio_port_write_logic(PORTA_INDEX,Number_Value_Common_Cathod[Ones]);
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
		
	ret = gpio_port_direction_intialize(PORTA_INDEX,0xFF);		 
	if (ret != E_OK)
	{/*Handle failure*/}	
	ret = gpio_port_write_logic(PORTA_INDEX,Number_Value_Common_Cathod[0]); 
	if (ret != E_OK)
	{/*Handle failure*/}
	ret = gpio_port_write_logic(PORTC_INDEX,Number_Value_Common_Anode[0]);
	if (ret != E_OK)
	{/*Handle failure*/}
}