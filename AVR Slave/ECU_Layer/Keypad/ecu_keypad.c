/*
 * File   :  ecu_keypad.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/8/2024 1:28:00 AM
 */ 

#include "ecu_keypad.h"

static const uint8 btn_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] = {
																		{'7','8','9','/'},
																		{'4','5','6','*'},
																		{'1','2','3','-'},
																		{'C','0','=','+'}
																	 };

/**
 * @brief Initialize the keypad assigned pins
 * @param _keypad_obj pointer to the keypad configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType keypad_intialize (const keypad_t *_keypad_obj)
{
	Std_ReturnType ret = E_OK;
	
	uint8 Rows_Counter = ZERO_INIT;
	uint8 Column_Counter = ZERO_INIT;
	
	if (NULL == _keypad_obj)
	{
		ret = E_NOT_OK;
	} 
	else
	{
		for (Rows_Counter = ZERO_INIT ;Rows_Counter < ECU_KEYPAD_ROWS ;Rows_Counter++)
		{
			ret = gpio_pin_intialize(&(_keypad_obj->keypad_row_pins[Rows_Counter]));
		}
		
		for (Column_Counter = ZERO_INIT; Column_Counter < ECU_KEYPAD_COLUMNS ;Column_Counter++)
		{
			ret = gpio_pin_intialize(&(_keypad_obj->keypad_columns_pins[Column_Counter]));
		}
	}
	return ret;
}


Std_ReturnType keypad_get_value (const keypad_t *_keypad_obj, uint8 *value)
{
	Std_ReturnType ret = E_OK;
	
	uint8 L_Rows_Counter = ZERO_INIT;
	uint8 L_Columns_Counter = ZERO_INIT;
	uint8 Counter = ZERO_INIT;
	uint8 Logic_Column = ZERO_INIT;
	
	if (NULL == _keypad_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		for(L_Rows_Counter= ZERO_INIT ;L_Rows_Counter < ECU_KEYPAD_ROWS ;L_Rows_Counter++)
		{
			/* Before Active Rows Just Make All Rows Not Active Then Active Row You Need */
			
			for(Counter = ZERO_INIT ;Counter < ECU_KEYPAD_ROWS ;Counter++)
			{
				ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[Counter]),GPIO_LOW);
			}
			
			ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[L_Rows_Counter]),GPIO_HIGH);
			//__delay_ms(10);
			
			/* LOOP Check The Logic In Column If High Or Low */
			
			for(L_Columns_Counter = ZERO_INIT ;L_Columns_Counter < ECU_KEYPAD_ROWS ;L_Columns_Counter++)
			{
				ret = gpio_pin_read_logic(&(_keypad_obj->keypad_columns_pins[L_Columns_Counter]),&Logic_Column);
				if(GPIO_HIGH == Logic_Column)
				{
					*value = btn_values[L_Rows_Counter][L_Columns_Counter];
				}
				
			}
		 }
		
	}
	
	return ret;
}