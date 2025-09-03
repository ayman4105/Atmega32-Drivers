/*
 * File   :  mcal_interrupt_manger.h
 * https://www.linkedin.com/in/ayman-abohamed
 * Created: 12/9/2024 11:10:23 PM
 * Author: Ayman_Abohamed
 */ 



#ifndef MCAL_INTERRUPT_MANGER_H_
#define MCAL_INTERRUPT_MANGER_H_

/*Section       :         Includes                */
#include "mcal_interrupt_config.h"


/*Section       :         Function Deceleration                */
void INT0_ISR (void);
void INT1_ISR (void);
void INT2_ISR (void);
void ADC_ISR(void);
void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);
void SPI_ISR(void);
void I2C_ISR(void);
void TMR0_Compare_ISR(void);
void TMR0_OverFlow_ISR(void);
void TMR1_Capture_ISR(void);
void TMR1_CompareA_ISR(void);
void TMR1_CompareB_ISR(void);
void TMR1_OverFlow_ISR(void);


#endif /* MCAL_INTERRUPT_MANGER_H_ */