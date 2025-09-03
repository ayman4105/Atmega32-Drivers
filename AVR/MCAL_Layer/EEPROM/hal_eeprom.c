/*
 * File   :  hal_eeprom.c
 * https://www.linkedin.com/in/ayman-abohamed
 * Created: 12/10/2024 6:18:30 PM
 * Author: Ayman_Abohamed
 */ 

#include "hal_eeprom.h"


/**
 * @Summary Writes a data byte to Data EEPROM
 * @Description This routine writes a data byte to given Data EEPROM location
 * @Preconditions None
 * @param bAdd - Data EEPROM location to which data to be written
 * @param bData - Data to be written to Data EEPROM location
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @Example ret = Data_EEPROM_WriteByte(0x3ff, 0);
 */
void Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData)
{
	uint8 Global_Interrupt_Status = READ_BIT(SREG,I);

	/* Disable global interrupts */
	INTERRUPT_GlobalInterruptDisable();
	
	/* Wait until EEWE becomes zero. */
	while(READ_BIT(EECR, EEWE));
	
	/* Wait until SPMEN in SPMCR becomes zero.*/
	while (READ_BIT(SPMCR,SPMEN));
	
	/* Set up address and data registers */
	EEAR = bAdd;
   	EEDR = bData;
	   
	/* Write logical one to EEMWE */
	SET_BIT(EECR,EEMWE);
	
	/* Start EEPROM write by setting EEWE */
	SET_BIT(EECR,EEWE);	
	
	/* Restore the Interrupt Status */
	if (Global_Interrupt_Status)
    {
		/* Re-enable global interrupts if they were enabled */
		sei();  
	}
}



/**
 * @Summary Reads a data byte from Data EEPROM
 * @Description This routine reads a data byte from given Data EEPROM location
 * @Preconditions None
 * @param bAdd - Data EEPROM location from which data has to be read
 * @param bData - Data byte read from given Data EEPROM location
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @Example ret = Data_EEPROM_ReadByte(0x3ff, &eeprom_read_val);
 */
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData)
{
	Std_ReturnType ret = E_OK; 
	
	if (NULL == bData)
	{
		ret = E_NOT_OK;
	} 
	
	
	else
	{
		/* Wait for completion of previous write */
		while(READ_BIT(EECR, EEWE));
		
		/* Set up address register */
		EEAR = bAdd;
		
		/* Start EEPROM read by writing EERE */
		SET_BIT(EECR,EERE);
		
		/* Return data from data register */
		*bData = EEDR;	
	}
	
	return ret;
}