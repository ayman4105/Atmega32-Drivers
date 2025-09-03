/*
 * File   :  ecu_relay.h
 * https://www.linkedin.com/in/ayman-abohamed
 * Author : Ayman_Abohamed
 * Created: 12/4/2024 5:36:56 AM
*/ 


#ifndef ECU_RELAY_H_
#define ECU_RELAY_H_

/*Section       :         Includes                */
#include "GPIO/hal_gpio.h"

/*Section       :         Data type Deceleration                 */
typedef struct
{
	uint8 relay_port   : 4;
	uint8 relay_pin    : 3;
	uint8 relay_status : 1;
}relay_t;

/*Section       :         Macro Deceleration                */
#define RELAY_ON_STATUS 0x01U
#define RELAY_OFF_STATUS 0x00U

/*Section       :         Macro Function Deceleration                */


/*Section       :         Function Deceleration                */
Std_ReturnType relay_intialize (const relay_t *_relay);
Std_ReturnType relay_turn_on (const relay_t *_relay);
Std_ReturnType relay_turn_off (const relay_t *_relay); 


#endif /* ECU_RELAY_H_ */