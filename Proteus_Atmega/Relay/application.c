/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 


#include "application.h"

relay_t Relay_1 = 
{
	.relay_port = PORTC_INDEX,
	.relay_pin = PINC0,
	.relay_status = RELAY_OFF_STATUS,
};

relay_t Relay_2 =
{
	.relay_port = PORTC_INDEX,
	.relay_pin = PINC1,
	.relay_status = RELAY_OFF_STATUS,
};

int main(void)
{
	Std_ReturnType ret = E_NOT_OK;
    application_intialize();
	
    while (1) 
    {
		ret = relay_turn_on(&Relay_1);
		if (ret != E_OK)
		{/*Handle failure*/}
		ret = relay_turn_off(&Relay_2);
		if (ret != E_OK)
		{/*Handle failure*/}
			
		_delay_ms(5000);
		
		ret = relay_turn_on(&Relay_2);
		if (ret != E_OK)
		{/*Handle failure*/}
		ret = relay_turn_off(&Relay_1);
		if (ret != E_OK)
		{/*Handle failure*/}
			
		_delay_ms(5000);
    }
}

void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	
	ret = relay_intialize(&Relay_1);
	 if (ret != E_OK)
	 {
		 /*Handle failure to initialize*/
	 }
		 
	ret = relay_intialize(&Relay_2);
	if (ret != E_OK)
	{
		/*Handle failure to initialize*/
	}	 
}