/*
 * File   :  ecu_button.h
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/3/2024 5:38:19 AM
*/ 


#ifndef ECU_BUTTON_H_
#define ECU_BUTTON_H_

/*Section       :         Includes                */
#include "GPIO/hal_gpio.h"

/*Section       :         Data type Deceleration                 */

typedef enum {
	BUTTON_PRESSED = 0,
	BUTTON_RELEASED
}button_state_t;

typedef enum {
	BUTTON_ACTIVE_HIGH,
	BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct {
	pin_config_t button_pin;
	button_state_t button_state;
	button_active_t button_connection;
}button_t;

/*Section       :         Macro Deceleration                */



/*Section       :         Macro Function Deceleration                */


/*Section       :         Function Deceleration                */
Std_ReturnType button_intialize (const button_t *btn);
Std_ReturnType button_read_state (const button_t *btn,button_state_t *btn_state);


#endif /* ECU_BUTTON_H_ */