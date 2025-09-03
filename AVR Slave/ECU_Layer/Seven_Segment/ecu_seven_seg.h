/*
 * File   :  ecu_seven_seg.h
 * https://www.linkedin.com/in/ahmed-shawada/
 * Author : AhmedShawada
 * Created: 12/4/2024 8:40:12 PM
 */ 


#ifndef ECU_SEVEN_SEG_H_
#define ECU_SEVEN_SEG_H_

/*Section       :         Includes                */
#include "GPIO/hal_gpio.h"

/*Section       :         Data type Deceleration                 */
typedef enum{
	SEGMENT_COMMON_ANODE = 0,
	SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct{
	pin_config_t segment_pins[4];
	segment_type_t segment_type;
}segment_t;

typedef struct{
	pin_config_t enable_pins;
}segment_enable_t;


/*Section       :         Macro Deceleration                */
#define SEGMENT_DECODER_PIN0		0
#define SEGMENT_DECODER_PIN1		1
#define SEGMENT_DECODER_PIN2		2
#define SEGMENT_DECODER_PIN3		3

/*Section       :         Macro Function Deceleration                */


/*Section       :         Function Deceleration                */
Std_ReturnType seven_segment_intialize(const segment_t *seg);
Std_ReturnType seven_segment_enable_intialize(const segment_enable_t *seg_enable);
Std_ReturnType seven_segment_write_number(const segment_t *seg ,uint8 number);
Std_ReturnType seven_segment_enable_on(const segment_enable_t *seg_enable);
Std_ReturnType seven_segment_enable_off(const segment_enable_t *seg_enable);


#endif /* ECU_SEVEN_SEG_H_ */