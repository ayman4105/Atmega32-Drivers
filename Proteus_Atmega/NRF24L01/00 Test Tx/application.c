/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"

nRF24l01_CONFIG_T nrf_config = 
{
	.channel = NRF_CHANNEL_76,       // Set RF channel to 76 (2.476 GHz)
	.payload_size = 32,              // Payload size of 32 bytes
	.address_width = NRF_ADDR_WIDTH_5_BYTES, // 5-byte address width
	.retries = NRF_RETRY_COUNT_5,    // 5 retries
	.retry_delay = NRF_RETRY_DELAY_1000US, // 1000us retry delay
	.data_rate = NRF_DATA_RATE_2MBPS, // 2 Mbps data rate
	.power_level = NRF_POWER_LEVEL_0DBM, // 0 dBm power level
	.auto_ack = ENABLE_AUTO_ACK      // Enable auto acknowledgment
};

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
	
int main(void)
{
	Std_ReturnType ret = E_OK;
	uint8 data[] = "Hello";
	
	
	application_intialize();
	ret = nRF24l01_Set_TX_Mode();
	
	
		
	while(1)
	{
		
		if (nRF24l01_Send_Data(data, sizeof(data)) == E_OK) 
		{
			  led_turn_toggle(&led1);
		} 
		else 
		{
			  // Failed to send data
		}

		// Delay before sending the next message
		_delay_ms(1000);
	}
	
	return 0;
}

void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	ret = nRF24l01_Init(&nrf_config);
	ret = led_intialize(&led1);
	

	if (ret != E_OK)
	{/*Handle failure*/}
}


