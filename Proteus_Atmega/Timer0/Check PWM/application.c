/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"

void timer0_compare_handdler(void);
void timer0_ovf_handdler(void);

Timer0_t timer0_config = 
{
	.COMPARE_VALUE = 0x00,
	.PRELOAD_VALUE = 0,
	.PRESCALER_VALUE = TIMER0_SCALER_256,
	.PWM_MODE = FAST_PWM_NON_INVERTING,
	.TIMER_MODE = TIMER0_FAST_PWM,
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
		/* Set duty cycle to 25% (0x40) */
		ret = Timer0_Set_Duty(&timer0_config , 0x40);
		_delay_ms(1000);
		/* Set duty cycle to 50% (0x80) */
		ret = Timer0_Set_Duty(&timer0_config , 0x80);
		_delay_ms(1000);
		/* Set duty cycle to 100% (0xFF) */
		ret = Timer0_Set_Duty(&timer0_config , 0xFF);
		_delay_ms(1000);
	}
}


void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	ret = Timer0_Init(&timer0_config);

	if (ret != E_OK)
	{/*Handle failure*/}
}

