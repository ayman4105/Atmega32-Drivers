/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 


#include "application.h"

segment_t segment =
{
	.segment_pins[0].port = PORTC_INDEX,
	.segment_pins[0].pin = PINC0,
	.segment_pins[0].logic = GPIO_LOW,
	.segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
	
	.segment_pins[1].port = PORTC_INDEX,
	.segment_pins[1].pin = PINC1,
	.segment_pins[1].logic = GPIO_LOW,
	.segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
	
	.segment_pins[2].port = PORTC_INDEX,
	.segment_pins[2].pin = PINC2,
	.segment_pins[2].logic = GPIO_LOW,
	.segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
	
	.segment_pins[3].port = PORTC_INDEX,
	.segment_pins[3].pin = PINC3,
	.segment_pins[3].logic = GPIO_LOW,
	.segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
	
	.segment_type = SEGMENT_COMMON_ANODE
};

segment_enable_t enable1 =
{
	.enable_pins.port = PORTD_INDEX,
	.enable_pins.pin = PIND0,
	.enable_pins.direction = GPIO_DIRECTION_OUTPUT,
	.enable_pins.logic = GPIO_LOW
};

segment_enable_t enable2 =
{
	.enable_pins.port = PORTD_INDEX,
	.enable_pins.pin = PIND1,
	.enable_pins.direction = GPIO_DIRECTION_OUTPUT,
	.enable_pins.logic = GPIO_LOW
};

uint8 Number = 23;
uint8 counter = 0;

int main(void)
{
	Std_ReturnType ret = E_NOT_OK;
    application_intialize();
	
    while (1) 
    {	
		for (counter = 0; counter <= 50; counter++)
		{
			ret = seven_segment_write_number(&segment,(uint8)(Number/10));
			ret = seven_segment_enable_on(&enable1);
			
			_delay_ms(10);
			
			ret = seven_segment_enable_off(&enable1);
			
			ret = seven_segment_write_number(&segment,(uint8)(Number%10));
			ret = seven_segment_enable_on(&enable2);
			
			_delay_ms(10);
			
			ret = seven_segment_enable_off(&enable2);
		}
		Number++;
		
		if (ret != E_OK)
		{/*Handle failure*/}
    }
}

void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	
	ret = seven_segment_intialize(&segment);
	ret = seven_segment_enable_intialize(&enable1);
	ret = seven_segment_enable_intialize(&enable2);
	if (ret != E_OK)
	{/*Handle failure*/}
}