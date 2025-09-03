/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"

uint8 received_data;

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
	
nRF24l01_CONFIG_T nrf_config = 
{
	.channel = NRF_CHANNEL_76,       // Set RF channel to 76 (2.476 GHz)
	.payload_size = 1,              // Payload size of 32 bytes
	.address_width = NRF_ADDR_WIDTH_5_BYTES, // 5-byte address width
	.retries = NRF_RETRY_COUNT_5,    // 5 retries
	.retry_delay = NRF_RETRY_DELAY_1000US, // 1000us retry delay
	.data_rate = NRF_DATA_RATE_2MBPS, // 2 Mbps data rate
	.power_level = NRF_POWER_LEVEL_0DBM, // 0 dBm power level
	.auto_ack = ENABLE_AUTO_ACK      // Enable auto acknowledgment
};

int main(void)
{
	Std_ReturnType ret = E_OK;
	
	
	
	application_intialize();
	ret = nRF24l01_Set_RX_Mode();
		
	while (1)
	{
		          
		if (NRF24_DataAvailable())
		{
			ret = nrf24l01_receive_data(&received_data, sizeof(received_data));

			if (ret == E_OK)
			{
				if (received_data == 1)
				{
					led_turn_on(&led1);    
				}
				else
				{
					led_turn_off(&led1);   
				}
			}
		}
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


