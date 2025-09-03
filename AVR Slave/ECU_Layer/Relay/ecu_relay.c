/*
 * File   :  ecu_relay.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/4/2024 5:36:19 AM
*/ 
 #include "ecu_relay.h"
 
 /**
 * @brief Initialize the assigned pin to be OUTPUT and turn the relay OFF or ON.
 * @param _relay pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
 Std_ReturnType relay_intialize (const relay_t *_relay)
 {
	 Std_ReturnType ret = E_OK;
	 
	 if (NULL == _relay)
	 {
		 ret = E_NOT_OK;
	 } 
	 
	 else
	 {
		 pin_config_t pin_obj = 
		 {
			 .pin = _relay->relay_pin,
			 .port = _relay->relay_port,
			 .logic = _relay->relay_status,
			 .direction = GPIO_DIRECTION_OUTPUT
		 };
		 
		 ret = gpio_pin_intialize(&pin_obj);
		 if (ret != E_OK)
		 {/*Handle failure*/}
	 }
	 return ret;
 }
 
 
 /**
 * @brief Turn the relay on
 * @param _relay pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
 Std_ReturnType relay_turn_on (const relay_t *_relay)
 {
	 Std_ReturnType ret = E_OK;
	 
	 if (NULL == _relay)
	 {
		 ret = E_NOT_OK;
	 }
	 
	 else
	 {
		 pin_config_t pin_obj =
		 {
			 .pin = _relay->relay_pin,
			 .port = _relay->relay_port,
			 .logic = _relay->relay_status,
			 .direction = GPIO_DIRECTION_OUTPUT
		 };
		 
		 ret = gpio_pin_write_logic(&pin_obj,GPIO_HIGH);
		 if (ret != E_OK)
		 {/*Handle failure*/}
	 }
	 return ret; 
 }
 
 
 /**
 * @brief Turn the relay off
 * @param _relay pointer to the relay module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
 Std_ReturnType relay_turn_off (const relay_t *_relay)
 {
	 Std_ReturnType ret = E_OK;
	 
	 if (NULL == _relay)
	 {
		 ret = E_NOT_OK;
	 }
	 
	 else
	 {
		 pin_config_t pin_obj =
		 {
			 .pin = _relay->relay_pin,
			 .port = _relay->relay_port,
			 .logic = _relay->relay_status,
			 .direction = GPIO_DIRECTION_OUTPUT
		 };
		 
		 ret = gpio_pin_write_logic(&pin_obj,GPIO_LOW);
		 if (ret != E_OK)
		 {/*Handle failure*/}
	 }
	 return ret;
 }
