/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"

void timer0_compare_handdler(void);
void timer0_ovf_handdler(void);


led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
led_t led2 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};
	
Timer0_t timer0_config = 
{
	.COMPARE_VALUE = 0x7C,
	.PRELOAD_VALUE = 124,
	.PRESCALER_VALUE = TIMER0_SCALER_256,
	.PWM_MODE  = FAST_PWM_DISCONNECTED,
	.COMPARE_MODE = TOGGLE_COMPARE_BIT_MODE,
	.TIMER_MODE = TIMER0_CTC,
	.TIMER0_INTERRUPT = TMR0_INTERRUPT_DISABLE,
	.TMR0_Compare_InterruptHandler = NULL,
	.TMR0_OverFlow_InterruptHandler = NULL

	
}; 




int main(void)
{
	
	Std_ReturnType ret = E_NOT_OK;
	application_intialize();
	
	
	
	while (1)
	{
		
	}
}


void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	ret = Timer0_Init(&timer0_config);
	//ret = led_intialize(&led1);
	//ret = led_intialize(&led2);

	if (ret != E_OK)
	{/*Handle failure*/}
}

void timer0_compare_handdler(void)
{
	
}
void timer0_ovf_handdler(void)
{
	
}

