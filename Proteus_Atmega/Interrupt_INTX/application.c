/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 


#include "application.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"

void INT0_Int_ISR(void);
void INT1_Int_ISR(void);
void INT2_Int_ISR(void);

interrupt_INTx_t INt0_int_obj =
{
	.EXT_InterruptHandler = INT0_Int_ISR,
	.edge = INTERRUPT_RISING_EDGE,
	.source = INTERRUPT_EXTERNAL_INT0,
	.mcu_pin.direction = GPIO_DIRECTION_INPUT,
	.mcu_pin.pin = GPIO_PIN2,
	.mcu_pin.port = PORTD_INDEX
};

interrupt_INTx_t INt1_int_obj =
{
	.EXT_InterruptHandler = INT1_Int_ISR,
	.edge = INTERRUPT_FALLING_EDGE,
	.source = INTERRUPT_EXTERNAL_INT1,
	.mcu_pin.direction = GPIO_DIRECTION_INPUT,
	.mcu_pin.pin = GPIO_PIN3,
	.mcu_pin.port = PORTD_INDEX,
};

interrupt_INTx_t INt2_int_obj =
{
	.EXT_InterruptHandler = INT2_Int_ISR,
	.edge = INTERRUPT_RISING_EDGE,
	.source = INTERRUPT_EXTERNAL_INT2,
	.mcu_pin.direction = GPIO_DIRECTION_INPUT,
	.mcu_pin.pin = GPIO_PIN2,
	.mcu_pin.port = PORTB_INDEX,
};

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
led_t led2 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};
led_t led3 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN2, .led_status = GPIO_LOW};

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
	
	ret = led_intialize(&led1);
	ret = led_intialize(&led2);
	ret = led_intialize(&led3);
	
	ret = Interrupt_INTx_Init(&INt0_int_obj);
	ret = Interrupt_INTx_Init(&INt1_int_obj);
	ret = Interrupt_INTx_Init(&INt2_int_obj);
	
	if (ret != E_OK)
	{/*Handle failure*/}
}




void INT0_Int_ISR(void)
{
	led_turn_on(&led1);
}

void INT1_Int_ISR(void)
{
	led_turn_on(&led2);
}

void INT2_Int_ISR(void)
{
	led_turn_on(&led3);
}