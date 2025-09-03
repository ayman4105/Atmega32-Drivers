/*
 * File   :  application.c
 * https://www.linkedin.com/in/ayman-abohamed
 * Author : Ayman_Abohamed
 * Created: 12/3/2024 4:02:19 AM
*/ 


#include "application.h"



chr_lcd_4bits_t lcd_1 =
{
	.lcd_rs.port = PORTC_INDEX,
	.lcd_rs.pin = GPIO_PIN0,
	.lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
	.lcd_rs.logic = GPIO_LOW,
	
	.lcd_en.port = PORTC_INDEX,
	.lcd_en.pin = GPIO_PIN1,
	.lcd_en.direction = GPIO_DIRECTION_OUTPUT,
	.lcd_en.logic = GPIO_LOW,
	
	.lcd_data[0].port = PORTC_INDEX,
	.lcd_data[0].pin = GPIO_PIN2,
	.lcd_data[0].logic = GPIO_LOW,
	.lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
	
	.lcd_data[1].port = PORTC_INDEX,
	.lcd_data[1].pin = GPIO_PIN3,
	.lcd_data[1].logic = GPIO_LOW,
	.lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
	
	.lcd_data[2].port = PORTC_INDEX,
	.lcd_data[2].pin = GPIO_PIN4,
	.lcd_data[2].logic = GPIO_LOW,
	.lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
	
	.lcd_data[3].port = PORTC_INDEX,
	.lcd_data[3].pin = GPIO_PIN5,
	.lcd_data[3].logic = GPIO_LOW,
	.lcd_data[3].direction = GPIO_DIRECTION_OUTPUT
};

uint8 lcd_counter = ZERO_INIT;
uint8 lcd_counter_txt[4];

int main(void)
{
	Std_ReturnType ret = E_NOT_OK;
    application_intialize();
	
	ret = lcd_4bits_send_string_pos(&lcd_1,1,1,(uint8*)"Counter: ");
	
    while (1) 
    {	
		ret = convert_uint8_to_string(lcd_counter,lcd_counter_txt);
		ret = lcd_4bits_send_string_pos(&lcd_1,1,10,lcd_counter_txt);
		
		if (ret != E_OK)
		{/*Handle failure*/}
		
		lcd_counter++;
		
		_delay_ms(500);
		
		
    }
}

void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	
	ret = lcd_4bits_intialize(&lcd_1);
	
	if (ret != E_OK)
	{/*Handle failure*/}
}