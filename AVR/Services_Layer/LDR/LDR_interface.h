/*
 * LDR_interface.h
 * https://www.linkedin.com/in/ayman-abohamed
 * Created: 1/27/2025 6:39:19 PM
 *  Author: Ayman_Abohamed
 */ 


#ifndef LDR_INTERFACE_H_
#define LDR_INTERFACE_H_

/*Section       :         Includes                */
#include "hal_adc.h"
#include "lighting_interface.h"


/*Section       :         Data type Deceleration                 */


/*Section       :         Macro Deceleration                */
//#define LIGHT_REFRANCE  450


/*Section       :         Macro Function Deceleration                */


/*Section       :         Function Deceleration                */
Std_ReturnType LDR_Services_Initialize(void);
Std_ReturnType LDR1_Read(void);
Std_ReturnType LDR2_Read(void);
Std_ReturnType LDR3_Read(void);
Std_ReturnType LDR4_Read(void);
Std_ReturnType LDRS_Automation (void);
Std_ReturnType Dynamic_Threshold_Write(uint16 New_Dynamic_Threshold);


#endif /* LDR_INTERFACE_H_ */