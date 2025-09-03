/*
 * File   :  ecu_dc_motor.h
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/4/2024 5:33:49 PM
 */ 


#ifndef ECU_DC_MOTOR_H_
#define ECU_DC_MOTOR_H_

/*Section       :         Includes                */
#include "GPIO/hal_gpio.h"

/*Section       :         Data type Deceleration                 */
typedef struct{
	pin_config_t dc_motor_pin[2];
}dc_motor_t;

/*Section       :         Macro Deceleration                */
#define DC_MOTOR_ON_STATUS  0x01U
#define DC_MOTOR_OFF_STATUS 0x00U

/*Section       :         Macro Function Deceleration                */


/*Section       :         Function Deceleration                */
Std_ReturnType dc_motor_intialize (const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_right (const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_left (const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_stop (const dc_motor_t *_dc_motor);


#endif /* ECU_DC_MOTOR_H_ */