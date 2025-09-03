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

uint8 Slave_Ack;

I2C_t i2c =
{
	.TWI_clock = 400000,
	.TWI_interrupt = I2C_INTERRUPT_DISABLE,
	.TWI_mode = TWI_MASTER_MODE,
	.TWI_prescaler = PRESCALER_1
};



int main(void)
{
	
	Std_ReturnType ret = E_NOT_OK;
	application_intialize();

    while (1) 
    {	
		I2C_Master_Send_Start(&i2c);
		_delay_ms(1000);
		I2C_Master_Write_Blocking(&i2c,0x30,&Slave_Ack);
		_delay_ms(1000);
		I2C_Master_Send_Stop(&i2c);
		_delay_ms(1000);
		
		if (ret != E_OK)
		{/*Handle failure*/}
    }
}


void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	I2C_Init(&i2c);

	if (ret != E_OK)
	{/*Handle failure*/}
}