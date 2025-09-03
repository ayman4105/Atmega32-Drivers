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
#include "hal_timer0.h"
#include "hal_timer1.h"
#include "hal_timer2.h"
#include "hal_pwm.h"
#include "hal_capture.h"
#include "hal_compare.h"

#define Slave_1  0X60

I2C_t i2c;



void I2C_Send_1Byte (uint8 Slave_Add ,uint8 Data)
{
	Std_ReturnType ret = E_NOT_OK;
	ret = I2C_Master_Send_Start(&i2c);
	
	ret = I2C_Master_Send_Slave_Address_With_Write(&i2c,Slave_Add);
	ret = I2C_Master_Write(&i2c,Data);
	
	I2C_Master_Send_Stop(&i2c);
}

int main(void)
{
	
	Std_ReturnType ret = E_NOT_OK;
	
	i2c.TWI_clock = 100000;
	i2c.TWI_interrupt = I2C_INTERRUPT_DISABLE;
	i2c.TWI_mode = TWI_MASTER_MODE;
	i2c.TWI_prescaler = PRESCALLER_BY_1;
	
	I2C_Init(&i2c);
	
	application_intialize();
	
	

    while (1) 
    {	
		I2C_Send_1Byte(Slave_1,'a');
		_delay_ms(1000);
		I2C_Send_1Byte(Slave_1,'c');
		_delay_ms(1000);
    }
}


void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	
	

	if (ret != E_OK)
	{/*Handle failure*/}
}
