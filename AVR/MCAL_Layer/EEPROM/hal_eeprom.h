/*
 * File   :  hal_eeprom.h
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 12/10/2024 6:18:40 PM
 * Author: AhmedShawada
 */ 

/*Section       :         Includes                */
#include <avr/io.h>
#include "mcal_internal_interrupt.h"
#include "mcal_std_types.h"

/*Section       :         Data type Deceleration                 */

/*Section       :         Macro Deceleration                */
#define I				7


/*Section       :         Macro Function Deceleration                */


/*Section       :         Function Deceleration                */
void Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData);
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData);



#ifndef HAL_EEPROM_H_
#define HAL_EEPROM_H_





#endif /* HAL_EEPROM_H_ */