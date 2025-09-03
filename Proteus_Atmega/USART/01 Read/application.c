/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "hal_eeprom.h"
#include "hal_adc.h"


void usart_module_init(void)
{
	usart_t usart_obj;
	Std_ReturnType ret = E_NOT_OK;
	
	
	//usart_obj.baudrate = 19200;
	usart_obj.baudrate_gen_gonfig = BAUDRATE_ASYN_NORMAL_MODE;
	usart_obj.usart_tx_cfg.usart_tx_interrupt_enable = EUSART_INTERRUPT_TX_DISABLE;
	usart_obj.usart_rx_cfg.usart_rx_interrupt_enable = EUSART_INTERRUPT_RX_DISABLE;
	
	usart_obj.EUSART_FramingErrorHandler = NULL;
	usart_obj.EUSART_OverrunErrorHandler = NULL;
	usart_obj.EUSART_RxDefaultInterruptHandler = NULL;
	usart_obj.EUSART_TxDefaultInterruptHandler = NULL;
	
	ret = EUSART_ASYNC_Init(&usart_obj);

	if (ret != E_OK)
	{/*Handle failure*/}
	
}

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};

uint8 RX_USART_REG;

int main(void)
{
	Std_ReturnType ret = E_NOT_OK;
	application_intialize();
	
	usart_module_init();
	
	
	
    while (1) 
    {	
		ret = EUSART_ASYNC_ReadByteNonBlocking(&RX_USART_REG);
		if('a' == RX_USART_REG)
		{
			led_turn_on(&led1);
		}
		else if('b' == RX_USART_REG)
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
	ret = led_intialize(&led1);
	
	
	
	if (ret != E_OK)
	{/*Handle failure*/}
}

