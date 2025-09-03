/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"

int main(void)
{
	
	application_intialize();
	/*
		Led_FLR > PC3
		Led_FLL > PC2
		Led_BLA > PB3/OC0
		Led_HLR > PD5/OC1A
		Led_HLL > PD4/OC1B
	*/
	
	while(1){
		/*
		LDRS_Automation();
		*/
		/*
		Front_Light_Right_ON();
		_delay_ms(1000);
		Front_Light_Left_ON();
		_delay_ms(1000);
		Front_Light_Right_OFF();
		_delay_ms(1000);
		Front_Light_Left_OFF();
		_delay_ms(1000);
		
		Front_Light_ALL_ON();
		_delay_ms(1000);
		Front_Light_ALL_OFF();
		_delay_ms(1000);
		
		Break_Light_Full();
		_delay_ms(1000);
		Break_Light_Defult();
		_delay_ms(1000);
		
		Hazard_Light_Right_ON();
		_delay_ms(4000);
		Hazard_Light_Left_ON();
		_delay_ms(4000);
		Hazard_Light_Right_OFF();
		_delay_ms(4000);
		Hazard_Light_Left_OFF();
		_delay_ms(4000);
		
		Hazard_Light_ALL_ON();
		_delay_ms(4000);
		Hazard_Light_ALL_OFF();
		_delay_ms(1000);
		Hazard_Light_Emergancy_ON();
		_delay_ms(4000);
		Hazard_Light_Emergancy_OFF();
		_delay_ms(4000);
		*/
	}
	
	return 0;
}

void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	Lighting_Services_Initialize();
	Break_Light_Defult();
	LDR_Services_Initialize();
	if (ret != E_OK)
	{/*Handle failure*/}
}


