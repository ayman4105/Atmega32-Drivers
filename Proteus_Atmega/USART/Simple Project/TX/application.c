/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "hal_eeprom.h"
#include "hal_usart.h"
#include "hal_spi.h"


led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
led_t led2 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};

void EUSART_TxDefaultInterruptHandler(void);
void EUSART_RxDefaultInterruptHandler(void);

uint8 RX_USART_REG;




void usart_module_interrupt_init(void)
{
	usart_t usart_obj;
	Std_ReturnType ret = E_NOT_OK;
	
	
	//usart_obj.baudrate = 9600;
	usart_obj.baudrate_gen_gonfig = BAUDRATE_ASYN_NORMAL_MODE;
	usart_obj.usart_tx_cfg.usart_tx_interrupt_enable = EUSART_INTERRUPT_TX_ENABLE;
	usart_obj.usart_rx_cfg.usart_rx_interrupt_enable = EUSART_INTERRUPT_RX_ENABLE;
	
	usart_obj.EUSART_FramingErrorHandler = NULL;
	usart_obj.EUSART_OverrunErrorHandler = NULL;
	usart_obj.EUSART_RxDefaultInterruptHandler = EUSART_RxDefaultInterruptHandler;
	usart_obj.EUSART_TxDefaultInterruptHandler = NULL;
	
	ret = EUSART_ASYNC_Init(&usart_obj);
}



int main(void)
{
	Std_ReturnType ret = E_NOT_OK;
	application_intialize();
	usart_module_interrupt_init();
	
	EUSART_ASYNC_WriteByteBlocking('a');

	
	
    while (1) 
    {	
		
		
		if (ret != E_OK)
		{/*Handle failure*/}
		
    }
}


void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	ret = led_intialize(&led1);
	ret = led_intialize(&led2);

	
	
	
	if (ret != E_OK)
	{/*Handle failure*/}
}

void EUSART_TxDefaultInterruptHandler(void)
{
	Std_ReturnType ret = E_NOT_OK;
	
	
}

void EUSART_RxDefaultInterruptHandler(void)
{
	Std_ReturnType ret = E_NOT_OK;
	EUSART_ASYNC_ReadByteNonBlocking(&RX_USART_REG);
	
	if('c' == RX_USART_REG)
	{
		led_turn_on(&led1);
		EUSART_ASYNC_WriteByteBlocking('b');
	}
	
	if('d' == RX_USART_REG)
	{
		led_turn_off(&led1);
		EUSART_ASYNC_WriteByteBlocking('a');
	}
}