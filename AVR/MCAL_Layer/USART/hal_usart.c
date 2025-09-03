/*
 * File   :  hal_usart.c
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 12/15/2024 2:22:21 AM
 * Author: AhmedShawada
 */ 

#include "hal_usart.h"


#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*EUSART_TxInterruptHandler)(void) = NULL;
#endif
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*EUSART_RxInterruptHandler)(void) = NULL;
static void (*EUSART_FramingErrorHandler)(void) = NULL;
static void (*EUSART_OverrunErrorHandler)(void) = NULL;
#endif


static void EUSART_Baud_Rate_Calculation(const usart_t *_eusart);
static void EUSART_ASYNC_TX_Init(const usart_t *_eusart);
static void EUSART_ASYNC_RX_Init(const usart_t *_eusart);






/**
 * @Summary 
 *    Initializes the EUSART module for asynchronous communication.
 * 
 * @Description 
 *    This function configures the EUSART module by setting the baud rate and initializing the TX and RX channels. 
 *    It enables the EUSART module once all configurations are completed. The module supports both high-speed 
 *    and low-speed configurations.
 * 
 * @Preconditions 
 *    The system clock must be initialized, and the `_eusart` structure must be properly configured.
 * 
 * @param _eusart 
 *    Pointer to a `usart_t` structure containing the configuration parameters for baud rate, TX/RX configuration, 
 *    and interrupt settings.
 * 
 * @return  
 *    Returns `E_OK` if the initialization is successful, otherwise `E_NOT_OK` if the `_eusart` pointer is NULL or 
 *    an error occurs during initialization.
 */
Std_ReturnType EUSART_ASYNC_Init(const usart_t *_eusart)
{
	
	Std_ReturnType ret = E_OK;
	
	if (NULL == _eusart)
	{
		ret = E_NOT_OK;
	} 
	
	else
	{
		
		/* Calculation EUSART Baud Rate */
		//EUSART_Baud_Rate_Calculation(_eusart);
		
		UBRRL=51;
		UBRRH = 0;
	
		/* initialize TX */
		EUSART_ASYNC_TX_Init(_eusart);
		/* initialize RX */
		EUSART_ASYNC_RX_Init(_eusart);
		
		ret = E_OK;
		
	}
	return ret; 
	
}


/**
 * @Summary 
 *    De-initializes the EUSART module.
 * 
 * @Description 
 *    This function disables the EUSART module, effectively stopping any communication.
 *              
 * @Preconditions 
 *    The EUSART module must have been previously initialized.
 * 
 * @param _eusart 
 *    Pointer to a `usart_t` structure. Not used directly but checked for null to ensure validity.
 * 
 * @return  
 *    Returns `E_OK` if the de-initialization is successful, otherwise `E_NOT_OK` if the `_eusart` pointer is NULL.
 */
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == _eusart)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		EUSART_DISABLE_TX();
		EUSART_DISABLE_RX();
		ret = E_OK;
	}
	return ret;
	
}


/**
 * @Summary 
 *    Reads a byte from the EUSART module in blocking mode.
 * 
 * @Description 
 *    This function waits until a byte is received and then stores it in the provided buffer.
 *              
 * @Preconditions 
 *    The EUSART module must be initialized and the RX channel must be enabled.
 * 
 * @param _data 
 *    Pointer to the buffer where the received byte will be stored.
 * 
 * @return  
 *    Returns `E_OK` if a byte is successfully received, otherwise `E_NOT_OK` if `_data` is NULL.
 */
Std_ReturnType EUSART_ASYNC_ReadByteBlocking(uint8 *_data)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == _data)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		/* Wait for data to be received */
		while (!RECIVER_DATA_STATUS());
		
		*_data =  UDR;
		
		ret = E_OK;
		
	}
	return ret;
}



/**
 * @Summary 
 *    Reads a byte from the EUSART module in non-blocking mode.
 * 
 * @Description 
 *    This function checks if a byte has been received and reads it if available. It does not block the execution.
 *              
 * @Preconditions 
 *    The EUSART module must be initialized and the RX channel must be enabled.
 * 
 * @param _data 
 *    Pointer to the buffer where the received byte will be stored.
 * 
 * @return  
 *    Returns `E_OK` if a byte is successfully received, otherwise `E_NOT_OK` if no data is available or `_data` is NULL.
 */
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data)
{
	Std_ReturnType ret = E_OK;
	
	if (NULL == _data)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		if(1 == RECIVER_DATA_STATUS())
		{
			*_data = UDR;
			ret = E_OK;
		}
		
		else
		{
			ret = E_NOT_OK;
		}
	}
	return ret;
}



/**
 * @Summary 
 *    Sends a byte over the EUSART module in blocking mode.
 * 
 * @Description 
 *    This function waits until the transmission buffer is ready, then sends the provided byte.
 *              
 * @Preconditions 
 *    The EUSART module must be initialized, and the TX channel must be enabled.
 * 
 * @param _data 
 *    The byte to be transmitted.
 * 
 * @return  
 *    Always returns `E_OK` as the function will block until the byte is transmitted.
 */
void EUSART_ASYNC_WriteByteBlocking(uint8 _data)
{
	while (!TRANSMIT_BUFFER_STATUS());
	
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
	EUSART_TX_InterruptEnable();
#endif

	UDR = _data;
}


/**
 * @Summary 
 *    Sends a string over the EUSART module in blocking mode.
 * 
 * @Description 
 *    This function transmits a string of specified length over the EUSART module by sending each character one by one.
 *              
 * @Preconditions 
 *    The EUSART module must be initialized, and the TX channel must be enabled.
 * 
 * @param _data 
 *    Pointer to the string to be transmitted.
 * 
 * @param str_len 
 *    The length of the string to be transmitted.
 * 
 * @return  
 *    Returns `E_OK` if the string is successfully transmitted, otherwise `E_NOT_OK` if `_data` is NULL.
 */
Std_ReturnType EUSART_ASYNC_WriteStringBlocking(uint8 *_data, uint16 str_len)
{
	Std_ReturnType ret = E_OK;
	uint16 Index_Counter = ZERO_INIT;
	
	if (NULL == _data)
	{
		ret = E_NOT_OK;
	}
	
	else
	{	
		for(Index_Counter = ZERO_INIT; Index_Counter < str_len; Index_Counter++)
		{
			EUSART_ASYNC_WriteByteBlocking(_data[Index_Counter]);
		}
		ret = E_OK;
			
		//while( _data[Index_Counter] != ZERO_INIT )
		//{
			//ret = EUSART_ASYNC_WriteByteBlocking(_data[Index_Counter]);
			//Index_Counter++;
		//}			
	}
	return ret;
}



/**
 * @Summary 
 *    Sends a byte over the EUSART module in non-blocking mode.
 * 
 * @Description 
 *    This function sends a byte if the transmission buffer is ready. It does not block execution and will return 
 *    immediately if the transmission buffer is not ready.
 *              
 * @Preconditions 
 *    The EUSART module must be initialized, and the TX channel must be enabled.
 * 
 * @param _data 
 *    The byte to be transmitted.
 * 
 * @return  
 *    Returns `E_OK` if the byte is successfully transmitted, otherwise `E_NOT_OK` if the transmission buffer is not ready.
 */
Std_ReturnType EUSART_ASYNC_WriteByteNonBlocking(uint8 _data)
{
	Std_ReturnType ret = E_NOT_OK;
	
	if(1 == TRANSMIT_BUFFER_STATUS())
	{
		
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
		EUSART_TX_InterruptEnable();
#endif
		
		UDR = _data;
		ret = E_OK;
	}
	
	else
	{
		ret = E_NOT_OK;
	}
	return ret;
}



/**
 * @Summary 
 *    Sends a string over the EUSART module in non-blocking mode.
 * 
 * @Description 
 *    This function transmits a string by sending each character in non-blocking mode. It iterates through the string 
 *    and sends each byte if the transmission buffer is ready.
 *              
 * @Preconditions 
 *    The EUSART module must be initialized, and the TX channel must be enabled.
 * 
 * @param _data 
 *    Pointer to the string to be transmitted.
 * 
 * @param str_len 
 *    The length of the string to be transmitted.
 * 
 * @return  
 *    Returns `E_OK` if the string is successfully transmitted, otherwise `E_NOT_OK` if `_data` is NULL or the transmission fails.
 */
Std_ReturnType EUSART_ASYNC_WriteStringNonBlocking(uint8 *_data, uint16 str_len)
{
	
	Std_ReturnType ret = E_OK;
	uint16 Index_Counter = ZERO_INIT;
	
	if (NULL == _data)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		for(Index_Counter = ZERO_INIT; Index_Counter < str_len; Index_Counter++)
		{	
			ret = EUSART_ASYNC_WriteByteNonBlocking(_data[Index_Counter]);
			_delay_ms(2);
		}
		ret = E_OK;	
	}
	return ret;
}





/**
 * @Summary 
 *    Calculates the baud rate for the EUSART module.
 * 
 * @Description 
 *    This function calculates the baud rate for different modes (high/low speed, 8-bit/16-bit) based on the 
 *    system clock and baud rate settings in the `_eusart` structure.
 *              
 * @Preconditions 
 *    The `_eusart` structure must be properly initialized with the desired baud rate and configuration settings.
 * 
 * @param _eusart 
 *    Pointer to a `usart_t` structure containing the baud rate configuration parameters.
 * 
 * @return  
 *    None.
 */
static void EUSART_Baud_Rate_Calculation(const usart_t *_eusart)
{
	float Baud_Rate_Temp = 0;
	
	switch(_eusart->baudrate_gen_gonfig)
	{
		case BAUDRATE_ASYN_NORMAL_MODE :
		CLEAR_BIT(UCSRA,U2X);
		EUSART_ASYNCHRONOUS_MODE_ENABLE();
		Baud_Rate_Temp = ((F_CPU / (float)_eusart->baudrate) / 16) - 1;
		break;
		
		case BAUDRATE_ASYN_DOUPLE_SPEED_MODE :
		SET_BIT(UCSRA,U2X);
		EUSART_ASYNCHRONOUS_MODE_ENABLE();
		Baud_Rate_Temp = ((F_CPU / (float)_eusart->baudrate) / 8) - 1;
		break;
		
		
		case BAUDRATE_SYN_MASTER_MODE :
		EUSART_SYNCHRONOUS_MODE_ENABLE();
		Baud_Rate_Temp = ((F_CPU / (float)_eusart->baudrate) / 2) - 1;
		break;
		
		default : ;
	}
	
	UBRRL  = (uint8)((uint32)Baud_Rate_Temp );
	UBRRH = (uint8)(((uint32)Baud_Rate_Temp) >> 8 );
	
}


/**
 * @Summary 
 *    Initializes the TX (transmit) part of the EUSART module.
 * 
 * @Description 
 *    This function configures the EUSART transmitter, enabling it for asynchronous transmission, 
 *    and setting up any necessary interrupts and 9-bit transmission modes.
 *              
 * @Preconditions 
 *    The EUSART module must be initialized, and the TX settings in the `_eusart` structure must be correctly configured.
 * 
 * @param _eusart 
 *    Pointer to a `usart_t` structure containing the TX configuration settings.
 * 
 * @return  
 *    None.
 */
static void EUSART_ASYNC_TX_Init(const usart_t *_eusart)
{
		/* Enable EUSART Transmit */
		EUSART_ENABLE_TX();
		EUSART_TxInterruptHandler = _eusart->EUSART_TxDefaultInterruptHandler;
		
		/* EUSART Transmit Interrupt Configuration */
		if(EUSART_INTERRUPT_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable)
		{	
				
			/* Interrupt Configurations */
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
			EUSART_TX_InterruptEnable();
			INTERRUPT_GlobalInterruptEnable();
#endif	
		}
		else if(EUSART_INTERRUPT_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable)
		{
			EUSART_TX_InterruptDisable();
		}
		else{ /* NOThing */ }

	
	
		/* EUSART  9-Bit Transmit Configuration */
		if(EUSART_9Bit_TX == _eusart->usart_tx_cfg.usart_tx_9bit_enable)
		{
			EUSART_CONFIG_9BIT();
		}
		else{ /* NOThing */ }
	

	
}



/**
 * @Summary 
 *    Initializes the RX (receive) part of the EUSART module.
 * 
 * @Description 
 *    This function configures the EUSART receiver, enabling it for asynchronous reception, and 
 *    setting up any necessary interrupts and 9-bit reception modes.
 *              
 * @Preconditions 
 *    The EUSART module must be initialized, and the RX settings in the `_eusart` structure must be correctly configured.
 * 
 * @param _eusart 
 *    Pointer to a `usart_t` structure containing the RX configuration settings.
 * 
 * @return  
 *    None.
 */
static void EUSART_ASYNC_RX_Init(const usart_t *_eusart)
{
	
		/* Enable EUSART Receiver */
		EUSART_ENABLE_RX();
		EUSART_RxInterruptHandler  = _eusart->EUSART_RxDefaultInterruptHandler;
		EUSART_FramingErrorHandler = _eusart->EUSART_FramingErrorHandler;
		EUSART_OverrunErrorHandler = _eusart->EUSART_OverrunErrorHandler;
	
		/* EUSART Receiver Interrupt Configuration */
		if(EUSART_INTERRUPT_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable)
		{			
			/* Interrupt Configurations */
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
			EUSART_RX_InterruptEnable();
			INTERRUPT_GlobalInterruptEnable();
#endif
		}
		
		else if(EUSART_INTERRUPT_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable)
		{
			EUSART_RX_InterruptDisable();
		}
		else{ /* NOThing */ }
	
	
	
		/* EUSART  9-Bit Receiver Configuration */
		if(EUSART_9Bit_RX == _eusart->usart_rx_cfg.usart_rx_9bit_enable)
		{
			EUSART_CONFIG_9BIT();
		}
		else{ /* NOThing */ }
	
	
}


void EUSART_TX_ISR(void)
{
	EUSART_TX_InterruptDisable();
	if(EUSART_TxInterruptHandler)
	{
		EUSART_TxInterruptHandler();
	}
	else{ /* NOThing */ }
}

void EUSART_RX_ISR(void)
{
	
	if(EUSART_RxInterruptHandler)
	{
		EUSART_RxInterruptHandler();
	}
	else{ /* NOThing */ }
	
	if(EUSART_FramingErrorHandler)
	{
		EUSART_FramingErrorHandler();
	}
	else{ /* NOThing */ }
	
	if(EUSART_OverrunErrorHandler)
	{
		EUSART_OverrunErrorHandler();
	}
	else{ /* NOThing */ }
	
}