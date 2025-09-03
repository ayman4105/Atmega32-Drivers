/*
 * File   :  hal_usart.h
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 12/15/2024 2:22:34 AM
 * Author: AhmedShawada
 */ 


#ifndef HAL_USART_H_
#define HAL_USART_H_


/*Section       :         Includes                */
#include <avr/io.h>
#include "mcal_std_types.h"
#include "hal_gpio.h"
#include "mcal_internal_interrupt.h"

/*Section       :         Macro Deceleration                */

/* EUSART Transmit Interrupt Enable */
#define EUSART_INTERRUPT_TX_ENABLE		              1
#define EUSART_INTERRUPT_TX_DISABLE                   0

/* EUSART 8-Bit Transmit */
#define EUSART_9Bit_TX								  3

/* EUSART Receiver Interrupt Enable */	
#define EUSART_INTERRUPT_RX_ENABLE					  1
#define EUSART_INTERRUPT_RX_DISABLE					  0

/* EUSART 8-Bit Receiver */
#define EUSART_9Bit_RX					              3

/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED				  1
#define EUSART_FRAMING_ERROR_CLEARED				  0

/* EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_DETECTED				  1
#define EUSART_OVERRUN_ERROR_CLEARED				  0


/* EUSART Parity Error */
#define EUSART_PARITY_ERROR_DETECTED				  1
#define EUSART_PARITY_ERROR_CLEARED				      0




/*Section       :         Data type Deceleration                 */
typedef enum
{
	BAUDRATE_ASYN_NORMAL_MODE = 0,
	BAUDRATE_ASYN_DOUPLE_SPEED_MODE,
	BAUDRATE_SYN_MASTER_MODE
}baudrate_gen_t;

typedef struct
{
	uint8 usart_tx_interrupt_enable : 1;
	uint8 usart_tx_9bit_enable : 3;
	uint8 usart_tx_reserved : 4;
}usart_tx_cfg_t;


typedef struct
{
	uint8 usart_rx_interrupt_enable : 1;
	uint8 usart_rx_9bit_enable : 3;
	uint8 usart_rx_reserved : 4;
}usart_rx_cfg_t;



typedef union
{
	struct
	{
		uint8 usart_tx_reserved : 6;
		uint8 usart_ferr : 1;
		uint8 usart_oerr : 1;
	};
	uint8 status;
}usart_error_status_t;


typedef struct
{
	uint32 baudrate;
	baudrate_gen_t baudrate_gen_gonfig;
	usart_tx_cfg_t usart_tx_cfg;
	usart_rx_cfg_t usart_rx_cfg;
	usart_error_status_t error_status;
	
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
	void (*EUSART_TxDefaultInterruptHandler)(void);
#endif
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
	void (*EUSART_RxDefaultInterruptHandler)(void);
	void (*EUSART_FramingErrorHandler)(void);
	void (*EUSART_OverrunErrorHandler)(void);
#endif
}usart_t;


/*Section       :         Macro Function Deceleration                */
#define TX_Output_Configuration()				(SET_BIT(DDRA,DDA1))
#define RX_Input_Configuration()				(CLEAR_BIT(DDRA,DDA0))

#define EUSART_SYNCHRONOUS_MODE_ENABLE()  		(SET_BIT(UCSRC,UMSEL))
#define EUSART_ASYNCHRONOUS_MODE_ENABLE()		(CLEAR_BIT(UCSRC,UMSEL))

#define EUSART_ENABLE_TX()						(SET_BIT(UCSRB,TXEN))
#define EUSART_DISABLE_TX()						(CLEAR_BIT(UCSRB,TXEN))

#define EUSART_ENABLE_RX()						(SET_BIT(UCSRB,RXEN))
#define EUSART_DISABLE_RX()						(CLEAR_BIT(UCSRB,RXEN))

#define EUSART_CONFIG_9BIT()					do{SET_BIT(UCSRC,UCSZ0);SET_BIT(UCSRC,UCSZ1);SET_BIT(UCSRC,UCSZ2);} while(0)

#define TRANSMIT_BUFFER_STATUS()				(READ_BIT(UCSRA,UDRE))
#define RECIVER_DATA_STATUS()					(READ_BIT(UCSRA,RXC))

#define EUSART_UDRE_InterruptEnable()			(SET_BIT(UCSRC,UDRIE))

#define DATA_OVERRUN_STATUS()					(READ_BIT(UCSRA,DOR))
#define FRAME_ERROR_STATUS()					(READ_BIT(UCSRA,FE))
#define PARITY_ERROR_STATUS()					(READ_BIT(UCSRA,UPE))

/*Section       :         Function Deceleration                */
Std_ReturnType EUSART_ASYNC_Init(const usart_t *_eusart);
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart);

Std_ReturnType EUSART_ASYNC_ReadByteBlocking(uint8 *_data);
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data);

void EUSART_ASYNC_WriteByteBlocking(uint8 _data);
Std_ReturnType EUSART_ASYNC_WriteStringBlocking(uint8 *_data, uint16 str_len);
Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking(uint8 _data);
Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking(uint8 *_data, uint16 str_len);




#endif /* HAL_USART_H_ */