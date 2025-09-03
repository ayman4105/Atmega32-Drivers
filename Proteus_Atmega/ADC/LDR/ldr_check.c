/*
 * File   :  application.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 4:02:19 AM
*/ 

#include "application.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "hal_eeprom.h"
#include "hal_adc.h"


adc_conf_t adc_1 =
{
	.adc_channel = ADC_CHANNEL_AN0,
	.conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_128,
	.result_format = ADC_RESULT_RIGHT,
	.voltage_reference = AVCC_WITH_EXTERNAL_CAPACITOR
};

adc_conf_t adc_2 =
{
	.adc_channel = ADC_CHANNEL_AN1,
	.conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_128,
	.result_format = ADC_RESULT_RIGHT,
	.voltage_reference = AVCC_WITH_EXTERNAL_CAPACITOR
};

adc_conf_t adc_3 =
{
	.adc_channel = ADC_CHANNEL_AN2,
	.conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_128,
	.result_format = ADC_RESULT_RIGHT,
	.voltage_reference = AVCC_WITH_EXTERNAL_CAPACITOR
};

adc_conf_t adc_4 =
{
	.adc_channel = ADC_CHANNEL_AN3,
	.conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_128,
	.result_format = ADC_RESULT_RIGHT,
	.voltage_reference = AVCC_WITH_EXTERNAL_CAPACITOR
};

uint16 adc_res_1;
uint16 adc_res_2;
uint16 adc_res_3;
uint16 adc_res_4;

int main(void)
{
	Std_ReturnType ret = E_NOT_OK;
	application_intialize();
	
    while (1) 
    {	
		ret = ADC_GetConversion_Blocking(&adc_1,ADC_CHANNEL_AN0,&adc_res_1);
		ret = ADC_GetConversion_Blocking(&adc_2,ADC_CHANNEL_AN1,&adc_res_2);
		ret = ADC_GetConversion_Blocking(&adc_2,ADC_CHANNEL_AN1,&adc_res_2);
		ret = ADC_GetConversion_Blocking(&adc_3,ADC_CHANNEL_AN2,&adc_res_3);
		ret = ADC_GetConversion_Blocking(&adc_4,ADC_CHANNEL_AN3,&adc_res_4);
    }
}


void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	ret = ADC_Init(&adc_1);
	ret = ADC_Init(&adc_2);
	ret = ADC_Init(&adc_3);
	ret = ADC_Init(&adc_4);
	
	if (ret != E_OK)
	{/*Handle failure*/}
}

