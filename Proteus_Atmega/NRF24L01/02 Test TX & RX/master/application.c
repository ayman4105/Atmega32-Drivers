/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"


uint8 temp;
uint8 q = 0;
uint8 data_array[4];
uint8 tx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
uint8 rx_address[5] = {0xD7,0xD7,0xD7,0xD7,0xD7};

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
		
int main(void)
{
	Std_ReturnType ret = E_OK;
	
	application_intialize();
	
	
		
	while(1)
	{
		/* Fill the data buffer */
		data_array[0] = 0x00;
		data_array[1] = 0xAA;
		data_array[2] = 0x55;
		data_array[3] = q++;
		
		/* Automatically goes to TX mode */
		nrf24_send(data_array);
		
		/* Wait for transmission to end */
		while(nrf24_isSending());
		
		/* Make analysis on last transmission attempt */
		temp = nrf24_lastMessageStatus();
		
		if(temp == NRF24_TRANSMISSON_OK)
		{
			led_turn_on(&led1);
		}
		else if(temp == NRF24_MESSAGE_LOST)
		{
			led_turn_off(&led1);
		}
		
		/* Optionally, go back to RX mode ... */
		nrf24_powerUpRx();

		/* Or you might want to power down after TX */
		// nrf24_powerDown();

		/* Wait a little ... */
		_delay_ms(10);
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




