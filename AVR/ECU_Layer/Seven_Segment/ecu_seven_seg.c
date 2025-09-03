/*
 * File   :  ecu_seven_seg.c
 * https://www.linkedin.com/in/ayman-abohamed
 * Author : Ayman_Abohamed
 * Created: 12/4/2024 8:40:12 PM
 */ 


#include "ecu_seven_seg.h"


/**
 * This Interface to make the needed GPIO and segment initialization
 * @param seg pointer to the segment configurations 
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType seven_segment_intialize(const segment_t *seg)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == seg)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		ret = gpio_pin_intialize(&(seg->segment_pins[SEGMENT_DECODER_PIN0]));
		ret = gpio_pin_intialize(&(seg->segment_pins[SEGMENT_DECODER_PIN1]));
		ret = gpio_pin_intialize(&(seg->segment_pins[SEGMENT_DECODER_PIN2]));
		ret = gpio_pin_intialize(&(seg->segment_pins[SEGMENT_DECODER_PIN3]));
	}
	return ret;
}


/**
 * This Interface to make the needed GPIO and segment enable initialization
 * @param seg_enable pointer to the segment configurations 
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType seven_segment_enable_intialize(const segment_enable_t *seg_enable)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == seg_enable)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		ret = gpio_pin_intialize(&(seg_enable->enable_pins));
	}
	return ret;
}



/**
 * Write a number to the segment 0 ~ 9
 * @param seg pointer to the segment configurations 
 * @param number the needed number to show
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType seven_segment_write_number(const segment_t *seg ,uint8 number)
{
	Std_ReturnType ret = E_OK;
	
	if ((NULL == seg) && (number > 9))
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_DECODER_PIN0]), number & 0x01);
		ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_DECODER_PIN1]), (number >> 1) & 0x01);
		ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_DECODER_PIN2]), (number >> 2) & 0x01);
		ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_DECODER_PIN3]), (number >> 3) & 0x01);
	}
	return ret;
}


/**
 * @brief Turn segment enable on
 * @param seg_enable : pointer to the segment_enable_t module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType seven_segment_enable_on(const segment_enable_t *seg_enable)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == seg_enable)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		pin_config_t pin_obj =
		{
			.port = seg_enable->enable_pins.port,
			.pin = seg_enable->enable_pins.pin,
			.direction = GPIO_DIRECTION_OUTPUT,
			.logic = seg_enable->enable_pins.logic
		};
		
		ret = gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
		if (ret != E_OK)
		{/*Handle failure*/}
	}
	return ret;
	
}


/**
 * @brief Turn segment enable off
 * @param seg_enable : pointer to the segment_enable_t module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
Std_ReturnType seven_segment_enable_off(const segment_enable_t *seg_enable)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == seg_enable)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		pin_config_t pin_obj =
		{
			.port = seg_enable->enable_pins.port,
			.pin = seg_enable->enable_pins.pin,
			.direction = GPIO_DIRECTION_OUTPUT,
			.logic = seg_enable->enable_pins.logic
		};
		
		ret = gpio_pin_write_logic(&pin_obj, GPIO_LOW);
		if (ret != E_OK)
		{/*Handle failure*/}
	}
	return ret;
}