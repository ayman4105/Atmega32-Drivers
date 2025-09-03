/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 


#include "application.h"

dc_motor_t Motor1 =
{
	.dc_motor_pin[0].port = PORTC_INDEX,
	.dc_motor_pin[0].pin = PINC0,
	.dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
	.dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
	
	.dc_motor_pin[1].port = PORTC_INDEX,
	.dc_motor_pin[1].pin = PINC1,
	.dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,
	.dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS 
};

dc_motor_t Motor2 =
{
	.dc_motor_pin[0].port = PORTC_INDEX,
	.dc_motor_pin[0].pin = PINC2,
	.dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
	.dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
	
	.dc_motor_pin[1].port = PORTC_INDEX,
	.dc_motor_pin[1].pin = PINC3,
	.dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,
	.dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS
};

int main(void)
{
	Std_ReturnType ret = E_NOT_OK;
    application_intialize();
	
    while (1) 
    {
		ret = dc_motor_move_right(&Motor1);
		if (ret != E_OK)
		{/*Handle failure*/}
		ret = dc_motor_move_right(&Motor2);		
		if (ret != E_OK)
		{/*Handle failure*/}
		_delay_ms(500);	
		
		ret = dc_motor_move_left(&Motor1);	
		if (ret != E_OK)
		{/*Handle failure*/}
		ret = dc_motor_move_left(&Motor2);	
		if (ret != E_OK)
		{/*Handle failure*/}
		_delay_ms(500);	
		
		ret = dc_motor_stop(&Motor1);
		if (ret != E_OK)
		{/*Handle failure*/}
		ret = dc_motor_stop(&Motor2);
		if (ret != E_OK)
		{/*Handle failure*/}
		_delay_ms(500);	
    }
}

void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	
	ret = dc_motor_intialize(&Motor1);
	if (ret != E_OK)
	{/*Handle failure*/}	 
	ret = dc_motor_intialize(&Motor2);
	if (ret != E_OK)
	{/*Handle failure*/}	 
}