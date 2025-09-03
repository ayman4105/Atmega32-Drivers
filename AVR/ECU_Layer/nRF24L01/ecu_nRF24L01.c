/*
 * File   :  hal_nRF24L01.c
 * Author : Ayman_Abohamed
 * https://www.linkedin.com/in/ayman-abohamed
 * Created: 2/28/2025 3:12:12 PM
 */ 

#include "ecu_nRF24L01.h"
/* ================  SPI Configuration ================ */
static SPI_Config SPI_CONFIG =
{
	/* SPI in Master mode (correct) */
	.spi_mode = SPI_MASTER_MODE,
	/* SPI Clock = 8 MHz (best choice) */
	.spi_config.SCKFrequency = SPI_MASTER_FOSC_DIV2,
	/* Mode 0 (correct for nRF24L01) */
	.spi_config.ClockPolarity_ClockPhase = SPI_IDLE_LOW_SAMPLE_RAISING,
	/* Disable SPI Interrupt (OK for polling) */
	.spi_config.SPI_Interrupt = SPI_INTERRUPT_DISABLE,
	/* No interrupt handler needed */
	.SPI_InterruptHandler = NULL
};

/* ================  CE Configuration ================ */
static pin_config_t CE_PIN =
{
	.port = PORTB_INDEX,
	.pin = GPIO_PIN1,
	.direction = GPIO_DIRECTION_OUTPUT,
	/* Start in Standby Mode */
	.logic = GPIO_LOW
};

/* ================  CSN Configuration ================ */
static pin_config_t CSN_PIN =
{
	.port = PORTB_INDEX,
	.pin = GPIO_PIN4,
	.direction = GPIO_DIRECTION_OUTPUT,
	/* CSN should be HIGH by default */
	.logic = GPIO_HIGH
};/* ================ variables ================ */
static uint8 payload_len;/* ================ Helper Function to set CE pin LOW ================ */
static inline void nRF24l01_CE_LOW(void);
/* ================ Helper Function to set CE pin HIGH ================ */
static inline void nRF24l01_CE_HIGH(void);
/* ================ Helper Function to set CSN pin LOW (Start SPI) ================ */
static inline void nRF24l01_CSN_LOW(void);
/* ================ Helper Function to set CSN pin HIGH (End SPI) ================ */
static inline void nRF24l01_CSN_HIGH(void);
	
void nrf24_init()
{
	SPI_Init(&SPI_CONFIG);
	gpio_pin_direction_intialize(&CE_PIN);
	gpio_pin_direction_intialize(&CSN_PIN);
	nRF24l01_CE_LOW();
	nRF24l01_CSN_HIGH();
}

void nrf24_config(uint8 channel, uint8 pay_length)
{
	/* Use static payload length ... */
	payload_len = pay_length;

	// Set RF channel
	nrf24_configRegister(RF_CH,channel);

	// Set length of incoming payload
	nrf24_configRegister(RX_PW_P0, payload_len); // Auto-ACK pipe ... Data payload pipe
	nrf24_configRegister(RX_PW_P1, 0x00); // Data payload pipe
	nrf24_configRegister(RX_PW_P2, 0x00); // Pipe not used
	nrf24_configRegister(RX_PW_P3, 0x00); // Pipe not used
	nrf24_configRegister(RX_PW_P4, 0x00); // Pipe not used
	nrf24_configRegister(RX_PW_P5, 0x00); // Pipe not used

	// 1 Mbps, TX gain: 0dbm
	nrf24_configRegister(RF_SETUP, (0<<RF_DR)|((0x03)<<RF_PWR));

	// CRC enable, 1 byte CRC length
	nrf24_configRegister(CONFIG,nrf24_CONFIG);

	// Auto Acknowledgment
	nrf24_configRegister(EN_AA,(1<<ENAA_P0)|(1<<ENAA_P1)|(0<<ENAA_P2)|(0<<ENAA_P3)|(0<<ENAA_P4)|(0<<ENAA_P5));

	// Enable RX addresses
	nrf24_configRegister(EN_RXADDR,(1<<ERX_P0)|(1<<ERX_P1)|(0<<ERX_P2)|(0<<ERX_P3)|(0<<ERX_P4)|(0<<ERX_P5));

	// Auto retransmit delay: 1000 us and Up to 15 retransmit trials
	nrf24_configRegister(SETUP_RETR,(0x04<<ARD)|(0x0F<<ARC));

	// Dynamic length configurations: No dynamic length
	nrf24_configRegister(DYNPD,(0<<DPL_P0)|(0<<DPL_P1)|(0<<DPL_P2)|(0<<DPL_P3)|(0<<DPL_P4)|(0<<DPL_P5));

	// Start listening
	nrf24_powerUpRx();
}
	
void nrf24_rx_address(uint8* adr)
{
	nRF24l01_CE_LOW();
	nrf24_writeRegister(RX_ADDR_P1,adr,nrf24_ADDR_LEN);
	nRF24l01_CE_HIGH();
}	


uint8 nrf24_payload_length()
{
	return payload_len;
}
	
void nrf24_tx_address(uint8* adr)
{
	/* RX_ADDR_P0 must be set to the sending address for auto ack to work. */
	nrf24_writeRegister(RX_ADDR_P0,adr,nrf24_ADDR_LEN);
	nrf24_writeRegister(TX_ADDR,adr,nrf24_ADDR_LEN);
}

/* Checks if data is available for reading */
/* Returns 1 if data is ready ... */
uint8 nrf24_dataReady()
{
	// See note in getData() function - just checking RX_DR isn't good enough
	uint8_t status = nrf24_getStatus();

	// We can short circuit on RX_DR, but if it's not set, we still need
	// to check the FIFO for any pending packets
	if ( status & (1 << RX_DR) )
	{
		return 1;
	}

	return !nrf24_rxFifoEmpty();;
}

/* Checks if receive FIFO is empty or not */
uint8 nrf24_rxFifoEmpty()
{
	uint8 fifoStatus;

	nrf24_readRegister(FIFO_STATUS,&fifoStatus,1);
	
	return (fifoStatus & (1 << FIFO_RX_EMPTY));
}

/* Returns the length of data waiting in the RX fifo */
uint8 nrf24_payloadLength()
{
	uint8 status;
	nRF24l01_CSN_LOW();
	spi_transfer(&SPI_CONFIG,R_RX_PL_WID);
	status = spi_transfer(&SPI_CONFIG,0x00);
	nRF24l01_CSN_HIGH();
	return status;
}

/* Reads payload bytes into data array */
void nrf24_getData(uint8* data)
{
	/* Pull down chip select */
	nRF24l01_CSN_LOW();

	/* Send cmd to read rx payload */
	spi_transfer(&SPI_CONFIG,R_RX_PAYLOAD);
	
	/* Read payload */
	nrf24_transferSync(data,data,payload_len);
	
	/* Pull up chip select */
	nRF24l01_CSN_HIGH();

	/* Reset status register */
	nrf24_configRegister(STATUS,(1<<RX_DR));
}

/* Returns the number of retransmissions occurred for the last message */
uint8 nrf24_retransmissionCount()
{
	uint8 rv;
	nrf24_readRegister(OBSERVE_TX,&rv,1);
	rv = rv & 0x0F;
	return rv;
}

// Sends a data package to the default address. Be sure to send the correct
// amount of bytes as configured as payload on the receiver.
void nrf24_send(uint8* value)
{
	/* Go to Standby-I first */
	nRF24l01_CE_LOW();
	
	/* Set to transmitter mode , Power up if needed */
	nrf24_powerUpTx();

	/* Do we really need to flush TX fifo each time ? */
	#if 1
	/* Pull down chip select */
	nRF24l01_CSN_LOW();

	/* Write cmd to flush transmit FIFO */
	spi_transfer(&SPI_CONFIG,FLUSH_TX);

	/* Pull up chip select */
	nRF24l01_CSN_HIGH();
	#endif

	/* Pull down chip select */
	nRF24l01_CSN_LOW();

	/* Write cmd to write payload */
	spi_transfer(&SPI_CONFIG,W_TX_PAYLOAD);

	/* Write payload */
	nrf24_transmitSync(value,payload_len);

	/* Pull up chip select */
	nRF24l01_CSN_HIGH();

	/* Start the transmission */
	nRF24l01_CE_HIGH();
}	


uint8 nrf24_isSending()
{
	uint8 status;

	/* read the current status */
	status = nrf24_getStatus();
	
	/* if sending successful (TX_DS) or max retries exceeded (MAX_RT). */
	if((status & ((1 << TX_DS)  | (1 << MAX_RT))))
	{
		return 0; /* false */
	}

	return 1; /* true */

}

uint8 nrf24_getStatus()
{
	uint8_t rv;
	nRF24l01_CSN_LOW();
	rv = spi_transfer(&SPI_CONFIG,NOP);
	nRF24l01_CSN_HIGH();
	return rv;
}

uint8 nrf24_lastMessageStatus()
{
	uint8 rv;

	rv = nrf24_getStatus();

	/* Transmission went OK */
	if((rv & ((1 << TX_DS))))
	{
		return NRF24_TRANSMISSON_OK;
	}
	/* Maximum retransmission count is reached */
	/* Last message probably went missing ... */
	else if((rv & ((1 << MAX_RT))))
	{
		return NRF24_MESSAGE_LOST;
	}
	/* Probably still sending ... */
	else
	{
		return 0xFF;
	}
}


void nrf24_powerUpRx()
{
	nRF24l01_CSN_LOW();
	spi_transfer(&SPI_CONFIG,FLUSH_RX);
	nRF24l01_CSN_HIGH();

	nrf24_configRegister(STATUS,(1<<RX_DR)|(1<<TX_DS)|(1<<MAX_RT));

	nRF24l01_CE_LOW();
	nrf24_configRegister(CONFIG,nrf24_CONFIG|((1<<PWR_UP)|(1<<PRIM_RX)));
	nRF24l01_CE_HIGH();
}

void nrf24_powerUpTx()
{
	nrf24_configRegister(STATUS,(1<<RX_DR)|(1<<TX_DS)|(1<<MAX_RT));

	nrf24_configRegister(CONFIG,nrf24_CONFIG|((1<<PWR_UP)|(0<<PRIM_RX)));
}

void nrf24_powerDown()
{
	nRF24l01_CE_LOW();
	nrf24_configRegister(CONFIG,nrf24_CONFIG);
}

uint8 spi_transfer(const SPI_Config *Config, uint8 tx)
{
	SPDR = tx;    
	while(!(SPSR & (1<<SPIF)));          
	return SPDR;        
}	


/* send and receive multiple bytes over SPI */
void nrf24_transferSync(uint8* dataout, uint8* datain, uint8 len)
{
	uint8 i;

	for(i=0; i<len; i++)
	{
		datain[i] = spi_transfer(&SPI_CONFIG, dataout[i]);
	}

}

/* send multiple bytes over SPI */
void nrf24_transmitSync(uint8* dataout,uint8 len)
{
	uint8_t i;
	
	for(i=0;i<len;i++)
	{
		spi_transfer(&SPI_CONFIG, dataout[i]);
	}

}

/* Clocks only one byte into the given nrf24 register */
void nrf24_configRegister(uint8 reg, uint8 value)
{
	nRF24l01_CSN_LOW();
	spi_transfer(&SPI_CONFIG, W_REGISTER | (REGISTER_MASK & reg));
	spi_transfer(&SPI_CONFIG, value);
	nRF24l01_CSN_HIGH();
}

/* Read single register from nrf24 */
void nrf24_readRegister(uint8 reg, uint8* value, uint8 len)
{
	nRF24l01_CSN_LOW();
	spi_transfer(&SPI_CONFIG, R_REGISTER | (REGISTER_MASK & reg));
	nrf24_transferSync(value,value,len);
	nRF24l01_CSN_HIGH();
}


/* Write to a single register of nrf24 */
void nrf24_writeRegister(uint8 reg, uint8* value, uint8 len)
{
	nRF24l01_CSN_LOW();
	spi_transfer(&SPI_CONFIG, W_REGISTER | (REGISTER_MASK & reg));
	nrf24_transmitSync(value,len);
	nRF24l01_CSN_HIGH();
}






static inline void nRF24l01_CE_LOW(void)
{
	gpio_pin_write_logic(&CE_PIN,GPIO_LOW);
}


static inline void nRF24l01_CE_HIGH(void)
{
	gpio_pin_write_logic(&CE_PIN,GPIO_HIGH);
}

static inline void nRF24l01_CSN_LOW(void)
{
	gpio_pin_write_logic(&CSN_PIN,GPIO_LOW);
}

static inline void nRF24l01_CSN_HIGH(void)
{
	gpio_pin_write_logic(&CSN_PIN,GPIO_HIGH);
}

