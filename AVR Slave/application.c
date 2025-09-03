/*
 * File   :  application.c
 * https://www.linkedin.com/in/ayman-abohamed
 * Author : Ayman_Abohamed
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"

#define RX_ADDRESS "NODE1"

uint8 rx_address[5] = RX_ADDRESS;
uint8 rx_payload[32];

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
		
int main(void)
{
	Std_ReturnType ret = E_OK;
	
	application_intialize();
	
	
		
	while(1)
	{
		
		if(nrf24_dataReady())
		{
			nrf24_getData(rx_payload);
			// Process received data (e.g., print it via UART)
			led_turn_on(&led1);
		}
		_delay_ms(500);
	
		
	}
	
	return 0;
}

void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	
	ret = led_intialize(&led1);
	nrf24_init();
	nrf24_config(2, 32); // Channel 2, 32-byte payload
	nrf24_rx_address(rx_address);
	nrf24_powerUpRx();
	
	
	if (ret != E_OK)
	{/*Handle failure*/}
}




