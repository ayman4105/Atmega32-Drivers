/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "hal_eeprom.h"

led_t led = {.port_name = PORTC_INDEX ,.pin = GPIO_PIN0 ,.led_status = GPIO_LOW};

int main(void)
{
	Std_ReturnType ret = E_NOT_OK;
	
	uint8 Value = 0;
	uint8 Read_Value;
	
	
	application_intialize();
	
    while (1) 
    {	
		
		 Data_EEPROM_WriteByte(0x23D,Value++);
		_delay_ms(500);
		ret = Data_EEPROM_ReadByte(0x23D,&Read_Value);
		if(10 == Read_Value)
		{
			led_turn_on(&led);
		}
		else
		{
			led_turn_off(&led);
		}

    }
}


void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	
	ret = led_intialize(&led);
	
	if (ret != E_OK)
	{/*Handle failure*/}
}
