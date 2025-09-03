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

void ADC_Defult_Interrupyt(void);

uint16 adc_res_1 = 0, adc_res_2 = 0, adc_res_3 = 0, adc_res_4 = 0;
uint8  adc_res1_txt[6], adc_res2_txt[6], adc_res3_txt[6], adc_res4_txt[6];
uint8 ADC_REQ = 0;

adc_conf_t adc_1 =
{
	.ADC_InterruptHandler = ADC_Defult_Interrupyt,
	.adc_channel = ADC_CHANNEL_AN0,
	.conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_128,
	.result_format = ADC_RESULT_RIGHT,
	.voltage_reference = AVCC_WITH_EXTERNAL_CAPACITOR
};

chr_lcd_4bits_t lcd_1 =
{
	.lcd_rs.port = PORTC_INDEX,
	.lcd_rs.pin = GPIO_PIN0,
	.lcd_rs.logic = GPIO_LOW,
	.lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
	
	.lcd_en.port = PORTC_INDEX,
	.lcd_en.pin = GPIO_PIN1,
	.lcd_en.logic = GPIO_LOW,
	.lcd_en.direction = GPIO_DIRECTION_OUTPUT,
	
	.lcd_data[0].port = PORTC_INDEX,
	.lcd_data[0].pin = GPIO_PIN2,
	.lcd_data[0].logic = GPIO_LOW,
	.lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
	
	.lcd_data[1].port = PORTC_INDEX,
	.lcd_data[1].pin = GPIO_PIN3,
	.lcd_data[1].logic = GPIO_LOW,
	.lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
	
	.lcd_data[2].port = PORTC_INDEX,
	.lcd_data[2].pin = GPIO_PIN4,
	.lcd_data[2].logic = GPIO_LOW,
	.lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
	
	.lcd_data[3].port = PORTC_INDEX,
	.lcd_data[3].pin = GPIO_PIN5,
	.lcd_data[3].logic = GPIO_LOW,
	.lcd_data[3].direction = GPIO_DIRECTION_OUTPUT
};

int main(void)
{
	Std_ReturnType ret = E_NOT_OK;
	application_intialize();
	
	 ret = lcd_4bits_send_string_pos(&lcd_1, 1, 6, "ADC TEST");
	 _delay_ms(2000);
	 ret = lcd_4bits_send_command(&lcd_1, _LCD_CLEAR);
	 _delay_ms(2);
	 
	 ret = lcd_4bits_send_string_pos(&lcd_1, 1, 1, "POT1 : ");
	 ret = lcd_4bits_send_string_pos(&lcd_1, 2, 1, "POT2 : ");
	 ret = lcd_4bits_send_string_pos(&lcd_1, 3, 1, "POT3 : ");
	 ret = lcd_4bits_send_string_pos(&lcd_1, 4, 1, "POT4 : ");
	 
    while (1) 
    {	
		if(0 == ADC_REQ)
		{
			ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN0);
		}
		else if(1 == ADC_REQ)
		{
			ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN1);
		}
		else if(2 == ADC_REQ)
		{
			ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN2);
		}
		else if(3 == ADC_REQ)
		{
			ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN3);
		}
		else { /* Nothing */ }
		
		
		ret = convert_uint16_to_string(adc_res_1,adc_res1_txt);
		ret = convert_uint16_to_string(adc_res_2,adc_res2_txt);
		ret = convert_uint16_to_string(adc_res_3,adc_res3_txt);
		ret = convert_uint16_to_string(adc_res_4,adc_res4_txt);
		
		ret = lcd_4bits_send_string_pos(&lcd_1, 1, 8,adc_res1_txt);
		ret = lcd_4bits_send_string_pos(&lcd_1, 2, 8,adc_res2_txt);
		ret = lcd_4bits_send_string_pos(&lcd_1, 3, 8,adc_res3_txt);
		ret = lcd_4bits_send_string_pos(&lcd_1, 4, 8,adc_res4_txt);
    }
}


void application_intialize (void)
{
	Std_ReturnType ret = E_OK;
	ret = ADC_Init(&adc_1);
	ret = lcd_4bits_intialize(&lcd_1);
	
	if (ret != E_OK)
	{/*Handle failure*/}
}

void ADC_Defult_Interrupyt(void)
{
	Std_ReturnType ret = E_NOT_OK;
	if(0 == ADC_REQ)
	{
		ret = ADC_GetConversionResult(&adc_1, &adc_res_1);
		ADC_REQ = 1;
	}
	else if(1 == ADC_REQ)
	{
		ret = ADC_GetConversionResult(&adc_1, &adc_res_2);
		ADC_REQ = 2;
	}
	else if(2 == ADC_REQ)
	{
		ret = ADC_GetConversionResult(&adc_1, &adc_res_3);
		ADC_REQ = 3;
	}
	else if(3 == ADC_REQ){
		ret = ADC_GetConversionResult(&adc_1, &adc_res_4);
		ADC_REQ = 0;
	}
	else { /* Nothing */ }
	
}
