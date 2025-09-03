/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 


#include "application.h"

keypad_t Keypad = 
{
	.keypad_row_pins[0].port = PORTC_INDEX,
	.keypad_row_pins[0].pin = PINC0,
	.keypad_row_pins[0].direction = GPIO_DIRECTION_OUTPUT,
	.keypad_row_pins[0].logic = GPIO_LOW,
	
	.keypad_row_pins[1].port = PORTC_INDEX,
	.keypad_row_pins[1].pin = GPIO_PIN1,
	.keypad_row_pins[1].logic = GPIO_LOW,
	.keypad_row_pins[1].direction = GPIO_DIRECTION_OUTPUT,
	
	.keypad_row_pins[2].port = PORTC_INDEX,
	.keypad_row_pins[2].pin = GPIO_PIN2,
	.keypad_row_pins[2].logic = GPIO_LOW,
	.keypad_row_pins[2].direction = GPIO_DIRECTION_OUTPUT,
	
	.keypad_row_pins[3].port = PORTC_INDEX,
	.keypad_row_pins[3].pin = GPIO_PIN3,
	.keypad_row_pins[3].logic = GPIO_LOW,
	.keypad_row_pins[3].direction = GPIO_DIRECTION_OUTPUT,
	
	.keypad_columns_pins[0].port = PORTC_INDEX,
	.keypad_columns_pins[0].pin = GPIO_PIN4,
	.keypad_columns_pins[0].logic = GPIO_LOW,
	.keypad_columns_pins[0].direction = GPIO_DIRECTION_INPUT,
	
	.keypad_columns_pins[1].port = PORTC_INDEX,
	.keypad_columns_pins[1].pin = GPIO_PIN5,
	.keypad_columns_pins[1].logic = GPIO_LOW,
	.keypad_columns_pins[1].direction = GPIO_DIRECTION_INPUT,
	
	.keypad_columns_pins[2].port = PORTC_INDEX,
	.keypad_columns_pins[2].pin = GPIO_PIN6,
	.keypad_columns_pins[2].logic = GPIO_LOW,
	.keypad_columns_pins[2].direction = GPIO_DIRECTION_INPUT,
	
	.keypad_columns_pins[3].port = PORTC_INDEX,
	.keypad_columns_pins[3].pin = GPIO_PIN7,
	.keypad_columns_pins[3].logic = GPIO_LOW,
	.keypad_columns_pins[3].direction = GPIO_DIRECTION_INPUT
};

chr_lcd_4bits_t lcd_1 =
{
	.lcd_rs.port = PORTD_INDEX,
	.lcd_rs.pin = GPIO_PIN0,
	.lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
	.lcd_rs.logic = GPIO_LOW,
	
	
	.lcd_en.port = PORTD_INDEX,
	.lcd_en.pin = GPIO_PIN1,
	.lcd_en.direction = GPIO_DIRECTION_OUTPUT,
	.lcd_en.logic = GPIO_LOW,
	
	
	.lcd_data[0].port = PORTD_INDEX,
	.lcd_data[0].pin = GPIO_PIN2,
	.lcd_data[0].logic = GPIO_LOW,
	.lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
	
	.lcd_data[1].port = PORTD_INDEX,
	.lcd_data[1].pin = GPIO_PIN3,
	.lcd_data[1].logic = GPIO_LOW,
	.lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
	
	.lcd_data[2].port = PORTD_INDEX,
	.lcd_data[2].pin = GPIO_PIN4,
	.lcd_data[2].logic = GPIO_LOW,
	.lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
	
	.lcd_data[3].port = PORTD_INDEX,
	.lcd_data[3].pin = GPIO_PIN5,
	.lcd_data[3].logic = GPIO_LOW,
	.lcd_data[3].direction = GPIO_DIRECTION_OUTPUT
	
};

led_t led1 =
{
	.port_name = PORTD_INDEX,
    .pin = GPIO_PIN6, 
	.led_status = GPIO_LOW
};

uint8 keypad_value = ZERO_INIT;
uint8 keypad_value_txt[4];

	

int main(void)
{
	Std_ReturnType ret = E_NOT_OK;
	
	
    application_intialize();
	
	ret = lcd_4bits_send_string_pos(&lcd_1,1,1,"Value: "); 
	
    while (1) 
    {	
		ret = keypad_get_value(&Keypad,&keypad_value);
		
		 if (keypad_value >= '0' && keypad_value <= '9')
		 {
			 ret = convert_uint8_to_string(keypad_value - '0', keypad_value_txt);
		 }
		  
		 else
	     {
			 keypad_value_txt[0] = keypad_value;
			 keypad_value_txt[1] = '\0';
		 }

		 ret = lcd_4bits_send_string_pos(&lcd_1, 1, 8, keypad_value_txt);
		
		
		if('8' == keypad_value)
		{
			led_turn_on(&led1);
		}
		
		else if('9' == keypad_value)
		{
			led_turn_off(&led1);
		}
		
		if (ret != E_OK)
		{/*Handle failure*/}

    }
}

void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	
	ret = keypad_intialize(&Keypad);
	ret = led_intialize(&led1);
	ret = lcd_4bits_intialize(&lcd_1);
	
	if (ret != E_OK)
	{/*Handle failure*/}
}