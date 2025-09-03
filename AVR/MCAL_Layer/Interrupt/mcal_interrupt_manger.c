/*
 * File   :  mcal_interrupt_manger.c
 * https://www.linkedin.com/in/ayman-abohamed
 * Created: 12/9/2024 11:10:09 PM
 * Author: Ayman_Abohamed
 */ 

#include "mcal_interrupt_manger.h"

/* ============ INTx External On Change Interrupt Start ============ */
	
ISR(INT0_vect)
{
	INT0_ISR(); 
}

ISR(INT1_vect)
{
	INT1_ISR(); 
}

ISR(INT2_vect)
{
	INT2_ISR();  
}
	
/* ============ INTx External Interrupt End ============ */
	
	
/* ============  Internal Interrupt ADC ============ */
	
ISR(ADC_vect)
{
	ADC_ISR();
}


/* ============  EUSART TX INTERNAL INTERRUPT ============ */

ISR(USART_TXC_vect)
{
	EUSART_TX_ISR();
}

/* ============  EUSART RX INTERNAL INTERRUPT ============ */

ISR(USART_RXC_vect)
{
	EUSART_RX_ISR();
}


/*=============== I2C INTERNAL INTERRUPT===============*/
ISR(TWI_vect)
{
	I2C_ISR();
}


/* ============  SPI INTERNAL INTERRUPT ============ */
ISR(SPI_STC_vect)
{
	SPI_ISR();
}

/*=============== TIMER1 INTERNAL INTERRUPT ===============*/
ISR(TIMER0_COMP_vect)
{
	TMR0_Compare_ISR();
}

ISR(TIMER0_OVF_vect)
{
	TMR0_OverFlow_ISR();
}


/*=============== TIMER1 INTERNAL INTERRUPT ===============*/
ISR(TIMER1_CAPT_vect)
{
	TMR1_Capture_ISR();
}

ISR(TIMER1_COMPA_vect)
{
	TMR1_CompareA_ISR();
}

ISR(TIMER1_COMPB_vect)
{
	TMR1_CompareB_ISR();
}

ISR(TIMER1_OVF_vect)
{
	TMR1_OverFlow_ISR();
}