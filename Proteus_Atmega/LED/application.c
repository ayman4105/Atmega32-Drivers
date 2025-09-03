/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 


#include "application.h"

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
led_t led2 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};
led_t led3 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN2, .led_status = GPIO_LOW};
led_t led4 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN3, .led_status = GPIO_LOW};
led_t led5 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN4, .led_status = GPIO_LOW};
led_t led6 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN5, .led_status = GPIO_LOW};
led_t led7 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN6, .led_status = GPIO_LOW};
led_t led8 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN7, .led_status = GPIO_LOW};

int main(void)
{
    application_intialize();
	
    while (1) 
    {
		led_turn_on(&led1);
		led_turn_off(&led2);
		led_turn_on(&led3);
		led_turn_off(&led4);
		led_turn_on(&led5);
		led_turn_off(&led6);
		led_turn_on(&led7);
		led_turn_off(&led8);
		
		_delay_ms(250);
		led_turn_off(&led1);
		led_turn_on(&led2);
		led_turn_off(&led3);
		led_turn_on(&led4);
		led_turn_off(&led5);
		led_turn_on(&led6);
		led_turn_off(&led7);
		led_turn_on(&led8);
		
		_delay_ms(250);
    }
}

void application_intialize (void)
{
	Std_ReturnType ret = E_NOT_OK;
	ret = led_intialize(&led1);
	ret = led_intialize(&led2);
	ret = led_intialize(&led3);
	ret = led_intialize(&led4);
	ret = led_intialize(&led5);
	ret = led_intialize(&led6);
	ret = led_intialize(&led7);
	ret = led_intialize(&led8);
}

