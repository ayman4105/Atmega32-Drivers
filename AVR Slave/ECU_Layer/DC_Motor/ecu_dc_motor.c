/*
 * File   :  ecu_dc_motor.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/4/2024 5:33:31 PM
 */ 

#include "ecu_dc_motor.h"


/**
 * @brief Initialize the assigned pins to be OUTPUT and turn the motor OFF or ON.
 * @param _dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_intialize (const dc_motor_t *_dc_motor)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == _dc_motor)
	{
		ret = E_NOT_OK;
	} 
	
	else
	{
		ret = gpio_pin_intialize(&(_dc_motor->dc_motor_pin[0]));
		if (ret != E_OK)
		{/*Handle failure*/}
		ret = gpio_pin_intialize(&(_dc_motor->dc_motor_pin[1]));
		if (ret != E_OK)
		{/*Handle failure*/}
	}
	return ret;
}

/**
 * @brief Move the motor to the right direction
 * @param _dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_right (const dc_motor_t *_dc_motor)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == _dc_motor)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]) , GPIO_HIGH);
		if (ret != E_OK)
		{/*Handle failure*/}
		ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]) , GPIO_LOW);
		if (ret != E_OK)
		{/*Handle failure*/}
	}
	return ret;
}

/**
 * @brief Move the motor to the left direction
 * @param _dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_left (const dc_motor_t *_dc_motor)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == _dc_motor)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]) , GPIO_LOW);
		if (ret != E_OK)
		{/*Handle failure*/}
		ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]) , GPIO_HIGH);
		if (ret != E_OK)
		{/*Handle failure*/}
	}
	return ret;
}


/**
 * @brief stop the motor movement
 * @param _dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_stop (const dc_motor_t *_dc_motor)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == _dc_motor)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]) , GPIO_LOW);
		if (ret != E_OK)
		{/*Handle failure*/}
		ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]) , GPIO_LOW);
		if (ret != E_OK)
		{/*Handle failure*/}
	}
	return ret;
}