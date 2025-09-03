/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"

	
Timer1_t timer1_config = 
{
	//.TMR1_PRELOAD_VALUE = 49999,
	.COMPARE_VALUE_A = 0x61A8,
	.COMPARE_VALUE_B = 0x61A8,
	.PRESCALER_VALUE = TIMER1_SCALER_64,
	.EDGE = RISING,
	.TIMER_MODE = TIMER1_CTC_OCRA_TOP_MODE,
	.OC1A_CMode = OCR1A_TOGGLE_COMPARE_BIT_MODE ,
	.OC1A_PMode = OCR1A_FAST_PWM_DISCONNECTED ,
	.OC1B_CMode = OCR1B_TOGGLE_COMPARE_BIT_MODE ,
	.OC1B_PMode = OCR1B_FAST_PWM_DISCONNECTED ,
	.NOISE_CANCLER = NOISE_CANCLER_OFF,
	.TIMER1_INTERRUPT = TMR1_INTERRUPT_DISABLE,
	.TMR1_Capture_InterruptHandler = NULL,
	.TMR1_CompareA_InterruptHandler = NULL,
	.TMR1_CompareB_InterruptHandler = NULL,
	.TMR1_OverFlow_InterruptHandler = NULL
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
	ret = Timer1_Init(&timer1_config);
	

	if (ret != E_OK)
	{/*Handle failure*/}
}


