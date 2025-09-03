/*
 * File   :  ecu_keypad.c
 * https://www.linkedin.com/in/ayman-abohamed
 * Author : Ayman_Abohamed
 * Created: 12/8/2024 1:28:10 AM
 */ 


#ifndef ECU_KEYPAD_H_
#define ECU_KEYPAD_H_

/*Section       :         Includes                */
#include "GPIO/hal_gpio.h"


/*Section       :         Macro Deceleration                */
#define ECU_KEYPAD_ROWS  4
#define ECU_KEYPAD_COLUMNS  4


/*Section       :         Data type Deceleration                 */
typedef struct
{
	pin_config_t keypad_row_pins[ECU_KEYPAD_ROWS];
	pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;


/*Section       :         Macro Function Deceleration                */


/*Section       :         Function Deceleration                */
Std_ReturnType keypad_intialize (const keypad_t *_keypad_obj);
Std_ReturnType keypad_get_value (const keypad_t *_keypad_obj, uint8 *value);


#endif /* ECU_KEYPAD_H_ */