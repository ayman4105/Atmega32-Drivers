/*
 * File   :  hal_i2c.c
 * https://www.linkedin.com/in/ayman-abohamed
 * Created: 12/20/2024 11:11:26 PM
 * Author: Ayman_Abohamed
 */ 

#include "hal_i2c.h" 

/***************************Helper_Function***************************/
static inline void I2C_Master_Mode_Prescalar_Configurations(const I2C_t *i2c_obj);
static inline void I2C_Master_Mode_Clock_Configurations(const I2C_t *i2c_obj);
static void I2C_Interrupt_Init (const I2C_t *i2c_obj);

/******* Pointer to function to hold the call-backs for I2C *******/
#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*I2C_DefaultInterruptHandle)(void) = NULL;
#endif



Std_ReturnType I2C_Init(const I2C_t *i2c_obj)
{
	Std_ReturnType ret = E_OK;
	
	if(NULL == i2c_obj)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		/* Disable I2C Module */
		TWI_DISABLE_MODULE();
		
		/* I2C Mode Select */
		if (TWI_MASTER_MODE == i2c_obj->TWI_mode)
		{
			I2C_Master_Mode_Prescalar_Configurations(i2c_obj);
			I2C_Master_Mode_Clock_Configurations(i2c_obj);
			if(i2c_obj->TWI_master_address != 0)
			{
				/*Set the required address in the 7 MSB of TWAR*/
				TWAR = ((i2c_obj->TWI_master_address) & 0xFE);
			}
			else { /* Nothing */ }
		}
		
		else if (TWI_SLAVE_MODE  == i2c_obj->TWI_mode)
		{
			TWAR = ((i2c_obj->TWI_slave_address) & 0xFE);
		}
		else { /* Nothing */ }
		
		/* Interrupt Configurations */
		if(I2C_INTERRUPT_ENABLE == i2c_obj->TWI_interrupt)
		{
			I2C_Interrupt_Init(i2c_obj);
		}
		else{ /* Nothing */ }
		
		/*Enable Acknowledge bit*/
		TWI_ENABLE_ACK();
		
		/* Enable I2C Module */
		TWI_ENABLE_MODULE();
		
		ret = E_OK;
	}
	
	return ret;
}



Std_ReturnType I2C_DeInit(const I2C_t *i2c_obj)
{
	Std_ReturnType ret = E_OK;
	
	if(NULL == i2c_obj)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		/* Disable I2C Module */
		TWI_DISABLE_MODULE();
			
		/* Disable Interrupt */
#if I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
		I2C_InterruptDisable();
#endif
		ret = E_OK;
	}
	
	return ret;
}



Std_ReturnType I2C_Master_Send_Start(const I2C_t *i2c_obj)
{
	Std_ReturnType ret = E_OK;
	
	if(NULL == i2c_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		TWI_DISABLE_START_CONDITION();
		TWI_CLEAR_FLAG();
		TWI_ENABLE_START_CONDITION();
		while(!TWINT_STATUS());
		
		
		/*Check the operation status (Bit Masking) */
		if((TWSR & TWI_STATUS_MASK) != START_ACK )
		{
			ret = E_NOT_OK;
		}
		else{ /* Nothing */ }
	}
	return ret;
}

Std_ReturnType I2C_Master_Send_Repeated_Start(const I2C_t *i2c_obj)
{
	Std_ReturnType ret = E_OK;
	
	if(NULL == i2c_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		TWI_CLEAR_FLAG();
		TWI_ENABLE_START_CONDITION();
		while(!TWINT_STATUS());
		
		
		/*Check the operation status (Bit Masking) */
		if((TWSR & TWI_STATUS_MASK) != REP_START_ACK )
		{
			ret = E_NOT_OK;
		}
		else{ /* Nothing */ }
	}
	return ret;
}



Std_ReturnType I2C_Master_Send_Stop(const I2C_t *i2c_obj)
{
	Std_ReturnType ret = E_OK;
	
	if(NULL == i2c_obj)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		TWI_CLEAR_FLAG();
		TWI_ENABLE_STOP_CONDITION();
		while(STOP_STATUS());
		
		ret = E_OK;
	}
	
	return ret; 
}


Std_ReturnType I2C_Master_Send_Slave_Address_With_Write(const I2C_t *i2c_obj,uint8 i2c_add)
{
	Std_ReturnType ret = E_OK;
	
	if(NULL == i2c_obj)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		/*send the 7bit slave address to the bus*/
		TWDR = i2c_add;
		/*Clear the start condition bit*/
		TWI_DISABLE_START_CONDITION();
		/*Clear the interrupt flag to start the previous operation*/
		TWI_CLEAR_FLAG();
		/*wait until the operation finishes and the flag is raised*/
		while(!TWINT_STATUS());
		/*Check the operation status (Bit Masking) */
		if((TWSR & TWI_STATUS_MASK) != SLAVE_ADD_AND_WR_ACK)
		{
			ret = E_NOT_OK;
		}
		else{ /* Nothing */ }	
	}
	return ret;
}

Std_ReturnType I2C_Master_Send_Slave_Address_With_Read(const I2C_t *i2c_obj,uint8 i2c_add)
{
	Std_ReturnType ret = E_OK;
	
	if(NULL == i2c_obj)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		/*send the 7bit slave address to the bus*/
		TWDR = i2c_add;
		/*Clear the start condition bit*/
		TWI_DISABLE_START_CONDITION();
		/*Clear the interrupt flag to start the previous operation*/
		TWI_CLEAR_FLAG();
		/*wait until the operation finishes and the flag is raised*/
		while(!TWINT_STATUS());
		/*Check the operation status (Bit Masking) */
		if((TWSR & TWI_STATUS_MASK) != SLAVE_ADD_AND_RD_ACK)
		{
			ret = E_NOT_OK;
		}
		else{ /* Nothing */ }
	}
	return ret;
}


Std_ReturnType I2C_Master_Write(const I2C_t *i2c_obj, uint8 i2c_data)
{
	Std_ReturnType ret = E_OK;
	
	if(NULL == i2c_obj)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		/* Write Data to the Data register */
		TWDR = i2c_data;	
		/* Clear  Interrupt Flag bit -> TWINT */
		TWI_CLEAR_FLAG();
		/* Wait The transmission to be completed and the flag is raised */
		while(!TWINT_STATUS());
		/*Check the operation status (Bit Masking) */
		if((TWSR & TWI_STATUS_MASK) != MSTR_WR_BYTE_ACK)
		{
			ret = E_NOT_OK;
		}
		else{ /* Nothing */ }
	}
	return ret;
}


Std_ReturnType I2C_Master_Read(const I2C_t *i2c_obj,uint8 *i2c_data)
{
	Std_ReturnType ret = E_OK;
	
	if((NULL == i2c_obj) || (NULL == i2c_data))
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		/* Clear  Interrupt Flag bit -> TWINT */
		TWI_CLEAR_FLAG();
		/* Wait for complete byte received */
		while(!TWINT_STATUS());
	
		/*Check the operation status (Bit Masking) */
		if((TWSR & TWI_STATUS_MASK) != MSTR_RD_BYTE_WITH_ACK)
		{
			ret = E_NOT_OK;
		}
		else
		{ 
			/*Read the received data*/
			*i2c_data = TWDR;
		}
	}
	return ret;
}



Std_ReturnType I2C_Slave_Write(const I2C_t *i2c_obj, uint8 i2c_data)
{
	Std_ReturnType ret = E_OK;
	
	if(NULL == i2c_obj)
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		/* Write Data to the Data register */
		TWDR = i2c_data;
		/* Clear  Interrupt Flag bit -> TWINT */
		TWI_CLEAR_FLAG();
		/* Wait The transmission to be completed and the flag is raised */
		while(!TWINT_STATUS());
		/*Check the operation status (Bit Masking) */
		if((TWSR & TWI_STATUS_MASK) != SLAVE_BYTE_TRANSMITTED)
		{
			ret = E_NOT_OK;
		}
		else{ /* Nothing */ }
	}
	return ret;
}



Std_ReturnType I2C_Slave_Read(const I2C_t *i2c_obj,uint8 *i2c_data)
{
	Std_ReturnType ret = E_OK;
	
	if((NULL == i2c_obj) || (NULL == i2c_data))
	{
		ret = E_NOT_OK;
	}
	
	else
	{
		/* Clear  Interrupt Flag bit -> TWINT */
		TWI_CLEAR_FLAG();
		/* Wait for complete byte received */
		while(!TWINT_STATUS());
		
		/* Copy The data registers to buffer variable */
		*i2c_data = TWDR;
		/*Check the operation status (Bit Masking) */
		if((TWSR & TWI_STATUS_MASK) != SLAVE_ADD_RCVD_WR_REQ)
		{
			ret = E_NOT_OK;
		}
		else
		{
			/*Read the received data*/
			*i2c_data = TWDR;
		}
	}
	return ret;
}





static inline void I2C_Master_Mode_Prescalar_Configurations(const I2C_t *i2c_obj)
{
	switch(i2c_obj->TWI_prescaler)
	{
		case PRESCALLER_BY_1 :
		CLEAR_BIT(TWSR,TWPS0);
		CLEAR_BIT(TWSR,TWPS1);
		break;
		
		case PRESCALLER_BY_4 :
		SET_BIT(TWSR,TWPS0);
		CLEAR_BIT(TWSR,TWPS1);
		break;
		
		case PRESCALLER_BY_16 :
		CLEAR_BIT(TWSR,TWPS0);
		SET_BIT(TWSR,TWPS1);
		break;
		
		case PRESCALLER_BY_64 :
		SET_BIT(TWSR,TWPS0);
		SET_BIT(TWSR,TWPS1);
		break;
	}
}


static inline void I2C_Master_Mode_Clock_Configurations(const I2C_t *i2c_obj)
{
	// SCL Frequency = CPU Clock Frequency / (16 * (2^TWPS) * (4 + TWBR))
	
	TWBR = (uint8) ( ( (F_CPU / (i2c_obj->TWI_clock) ) - 16) / ( 2 * (i2c_obj->TWI_prescaler) ) );
	 
}



static void I2C_Interrupt_Init (const I2C_t *i2c_obj)
{
#if I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
	I2C_DefaultInterruptHandle = i2c_obj->I2C_DefaultInterruptHandle;
	I2C_InterruptEnable();
	I2C_InterruptFlagClear();
	INTERRUPT_GlobalInterruptEnable();
#endif
}






void I2C_ISR(void)
{
	
#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
	I2C_InterruptFlagClear();
	
	if(I2C_DefaultInterruptHandle)
	{
		I2C_DefaultInterruptHandle();
	}
	
#endif
}