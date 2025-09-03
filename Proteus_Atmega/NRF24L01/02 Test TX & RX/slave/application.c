/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"


uint8 temp;
uint8 q = 0;
uint8 data_array_rx[4];
uint8 tx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
uint8 rx_address[5] = {0xD7,0xD7,0xD7,0xD7,0xD7};

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
		
int main(void)
{
	Std_ReturnType ret = E_OK;
	
	application_intialize();
	
	
		
	while(1)
	{
		
		if(nrf24_dataReady())
		{
			nrf24_getData(data_array_rx);
			led_turn_on(&led1);
			_delay_ms(1000);
		}
		
	}
	
	return 0;
}

void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	
	ret = led_intialize(&led1);
	nrf24_init();
	/* Channel #2 , payload length: 4 */
	nrf24_config(2,4);
	nrf24_tx_address(tx_address);
	nrf24_rx_address(rx_address);
	
	if (ret != E_OK)
	{/*Handle failure*/}
}




