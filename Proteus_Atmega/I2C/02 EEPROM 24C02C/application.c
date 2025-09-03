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
#include "hal_i2c.h"

uint8 Read_1, Read_2;

int main(void)
{
	
	Std_ReturnType ret = E_NOT_OK;
	application_intialize();
	
	Write_EEPROM_24C02C(0xA6,0x00,0x05);
	_delay_ms(10);
	Read_EEPROM_24C02C(0xA6,0x00,&Read_1);

    while (1) 
    {	
		
    }
}


void application_intialize (void)
{
	Std_ReturnType ret = E_OK;

	if (ret != E_OK)
	{/*Handle failure*/}
}
