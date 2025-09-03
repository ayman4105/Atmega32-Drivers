/*
 * File   :  hal_i2c.h
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 12/20/2024 11:11:39 PM
 * Author: AhmedShawada
 */ 


#ifndef HAL_I2C_H_
#define HAL_I2C_H_

/*Section       :         Includes                */
#include <avr/io.h>
#include "mcal_std_types.h"
#include "hal_gpio.h"
#include "mcal_internal_interrupt.h"

/*Section       :         Data type Deceleration                 */
typedef struct
{
#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
	void (* I2C_DefaultInterruptHandle)(void);
#endif
	uint32 TWI_clock;
	uint8 TWI_mode;
	uint8 TWI_prescaler;
	uint8 TWI_master_address;
	uint8 TWI_slave_address;
	uint8 TWI_interrupt;
}I2C_t;


/*Section       :         Macro Deceleration                */
#define START_ACK					0x08    /* START HAS BEEN SENT */
#define REP_START_ACK				0x10    /* REPEATED START */
#define SLAVE_ADD_AND_WR_ACK		0x18    /* MASTER TRANSMIT (SLAVE ADDRESS + WRITE REQUEST) ACK */
#define SLAVE_ADD_AND_RD_ACK		0x40	/* MASTER TRANSMIT (SLAVE ADDRESS + READ REQUEST) ACK */
#define MSTR_WR_BYTE_ACK			0x28    /* MASTER TRANSMIT DATA ACK */
#define MSTR_RD_BYTE_WITH_ACK		0x50    /* MASTER RECEIVED DATA WITH ACK */
#define MSTR_RD_BYTE_WITH_NACK		0x58    /* MASTER RECEIVED DATA WITH NO ACK */
#define SLAVE_ADD_RCVD_RD_REQ		0xA8    /* MEANS THAT SLAVE ADDRESS IS RECEIVED WITH READ REQUEST */
#define SLAVE_ADD_RCVD_WR_REQ		0x60    /* MEANS THAT SLAVE ADDRESS IS RECEIVED WITH WRITE REQUEST */
#define SLAVE_DATA_RECEIVED			0x80    /* MEANS THAT A BYTE IS RECEIVED */
#define SLAVE_BYTE_TRANSMITTED		0xB8    /* MEANS THAT THE WRITTEN BYTE IS TRANSMITTED */
#define TWI_STATUS_MASK				0xF8	/* TWI STATUS MASK */

#define TWI_SLAVE_MODE				0
#define TWI_MASTER_MODE				1

#define PRESCALLER_BY_1				1
#define PRESCALLER_BY_4				4
#define PRESCALLER_BY_16			16
#define PRESCALLER_BY_64			64

#define I2C_INTERRUPT_DISABLE		0
#define I2C_INTERRUPT_ENABLE		1



/*Section       :         Macro Function Deceleration                */
#define TWI_ENABLE_MODULE()				(SET_BIT(TWCR,TWEN))
#define TWI_DISABLE_MODULE()			(CLEAR_BIT(TWCR,TWEN))
		
#define TWI_CLEAR_FLAG()				(SET_BIT(TWCR,TWINT))

#define TWINT_STATUS()					(READ_BIT(TWCR,TWINT))
#define TWWC_STATUS()					(READ_BIT(TWCR,TWWC))

#define TWI_ENABLE_ACK()				(SET_BIT(TWCR,TWEA))
#define TWI_ENABLE_NACK()				(CLEAR_BIT(TWCR,TWEA))

#define TWI_ENABLE_START_CONDITION()	(SET_BIT(TWCR,TWSTA))
#define TWI_DISABLE_START_CONDITION()	(CLEAR_BIT(TWCR,TWSTA))

#define TWI_ENABLE_STOP_CONDITION()		(SET_BIT(TWCR,TWSTO))
#define STOP_STATUS()					(READ_BIT(TWCR,TWSTO))




/*Section       :         Function Deceleration                */
Std_ReturnType I2C_Init(const I2C_t *i2c_obj);
Std_ReturnType I2C_DeInit(const I2C_t *i2c_obj);

Std_ReturnType I2C_Master_Send_Start(const I2C_t *i2c_obj);
Std_ReturnType I2C_Master_Send_Repeated_Start(const I2C_t *i2c_obj);
Std_ReturnType I2C_Master_Send_Stop(const I2C_t *i2c_obj);

Std_ReturnType I2C_Master_Send_Slave_Address_With_Write(const I2C_t *i2c_obj,uint8 i2c_add);
Std_ReturnType I2C_Master_Send_Slave_Address_With_Read(const I2C_t *i2c_obj,uint8 i2c_add);

Std_ReturnType I2C_Master_Write(const I2C_t *i2c_obj, uint8 i2c_data);
Std_ReturnType I2C_Master_Read(const I2C_t *i2c_obj, uint8 *i2c_data);

Std_ReturnType I2C_Slave_Write(const I2C_t *i2c_obj, uint8 i2c_data);
Std_ReturnType I2C_Slave_Read(const I2C_t *i2c_obj,uint8 *i2c_data);




#endif /* HAL_I2C_H_ */