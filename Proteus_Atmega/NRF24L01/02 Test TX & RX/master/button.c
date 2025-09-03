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
	.payload_size = 1,              // Payload size of 32 bytes
	.address_width = NRF_ADDR_WIDTH_5_BYTES, // 5-byte address width
	.retries = NRF_RETRY_COUNT_5,    // 5 retries
	.retry_delay = NRF_RETRY_DELAY_1000US, // 1000us retry delay
	.data_rate = NRF_DATA_RATE_2MBPS, // 2 Mbps data rate
	.power_level = NRF_POWER_LEVEL_0DBM, // 0 dBm power level
	.auto_ack = ENABLE_AUTO_ACK      // Enable auto acknowledgment
};

button_t btn_high = {
	.button_pin.port = PORTC_INDEX,
	.button_pin.pin = GPIO_PIN2,
	.button_pin.logic = GPIO_LOW,
	.button_pin.direction = GPIO_DIRECTION_INPUT,
	.button_connection = BUTTON_ACTIVE_HIGH,
	.button_state = BUTTON_RELEASED
};
	
int main(void)
{
	Std_ReturnType ret = E_OK;
	button_state_t button_state;
	uint8 data;  
	
	
	application_intialize();
	ret = nRF24l01_Set_TX_Mode();
	
	
		
	while(1)
	{
		
		 button_read_state(&btn_high, &button_state);

		 if (button_state == BUTTON_PRESSED)
		 {
			 data = 1;  // Send 1 when button is pressed
		 }
		 else
		 {
			 data = 0;  // Send 0 when button is released
		 }

		 ret = nRF24l01_Send_Data(&data, sizeof(data));
		 _delay_ms(100);  // Small delay to avoid excessive sending
	}
	
	return 0;
}

void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	ret = nRF24l01_Init(&nrf_config);
	ret = button_intialize(&btn_high);
	

	if (ret != E_OK)
	{/*Handle failure*/}
}


