/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "hal_eeprom.h"

void INT0_Int_ISR(void);
void program_1(void);
void program_2(void);
void program_3(void);

led_t led_1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
led_t led_2 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};

interrupt_INTx_t INt0_int_obj =
{
	.EXT_InterruptHandler = INT0_Int_ISR,
	.edge = INTERRUPT_RISING_EDGE,
	.source = INTERRUPT_EXTERNAL_INT0,
	.mcu_pin.direction = GPIO_DIRECTION_INPUT,
	.mcu_pin.pin = GPIO_PIN0,
	.mcu_pin.port = PORTB_INDEX,
};

volatile uint8 program_selected = 0;



int main(void)
{
	Std_ReturnType ret = E_NOT_OK;
	
	ret = Data_EEPROM_ReadByte(0x3ff,&program_selected);
	
	
	application_intialize();
	
    while (1) 
    {	
		
		 if(1 == program_selected)
		 {
			 program_1();
		 }
		 
		 else if(2 == program_selected)
		 {
			 program_2();
		 }
		 
		 else if (3 == program_selected)
		 {
			 program_3();
		 }

    }
}


void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	
	ret = led_intialize(&led_1);
	ret = led_intialize(&led_2);
	ret = Interrupt_INTx_Init(&INt0_int_obj);
	
	if (ret != E_OK)
	{/*Handle failure*/}
}


void INT0_Int_ISR(void)
{
	Std_ReturnType ret = E_NOT_OK;
	program_selected ++;
	if(4 == program_selected)
	{
		program_selected = 0;
	}
	else {/*no thing*/}
	
	Data_EEPROM_WriteByte(0x3ff,program_selected);
}


void program_1(void)
{
	led_turn_on(&led_1);
}


void program_2(void)
{
	led_turn_on(&led_2);
}

void program_3(void)
{
	led_turn_on(&led_1);
	_delay_ms(250);
	led_turn_off(&led_1);
	_delay_ms(250);
	led_turn_on(&led_2);
	_delay_ms(250);
	led_turn_off(&led_2);
	_delay_ms(250);
}