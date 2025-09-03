/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"


int main(void)
{
	Std_ReturnType ret = E_NOT_OK;
	application_intialize();
	
	while (1)
	{
		ret = LDR1_Read();
		
	}
}


void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	
	ret = LDR_Services_Initialize();
	
	
	if (ret != E_OK)
	{/*Handle failure*/}
}
