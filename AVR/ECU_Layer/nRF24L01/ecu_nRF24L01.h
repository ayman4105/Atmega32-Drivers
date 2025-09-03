/*
 * File   :  hal_nRF24L01.h
 * Author :Ayman_Abohamed
 * https://www.linkedin.com/in/ayman-abohamed
 * Created: 2/28/2025 3:12:12 PM
 */ 




#ifndef HAL_NRF24L01_H_
#define HAL_NRF24L01_H_


/*Section       :         Includes                */
#include <avr/io.h>
#include "mcal_std_types.h"
#include "hal_gpio.h"
#include "Register_Map.h"
#include "hal_spi.h"


/*Section       :         Data type Deceleration                 */



/*Section       :         Macro Deceleration                */

/* ===========================
 * Commands for SPI Communication 
 * =========================== */

/* Read and Write Registers */
#define R_REGISTER				0x00  // Read register command (OR with register address)
#define W_REGISTER				0x20  // Write register command (OR with register address)

/* RX and TX Payload Commands */
#define R_RX_PAYLOAD			0x61  // Read RX payload
#define W_TX_PAYLOAD			0xA0  // Write TX payload
#define FLUSH_TX				0xE1  // Flush TX FIFO
#define FLUSH_RX				0xE2  // Flush RX FIFO
#define REUSE_TX_PL				0xE3  // Reuse last transmitted payload
#define R_RX_PL_WID				0x60  // Read RX payload width
#define W_ACK_PAYLOAD			0xA8  // Write ACK payload (pipe 0-5: 0xA8 - 0xAD)
#define W_TX_PAYLOAD_NO_ACK		0xB0  // Write TX payload without auto ACK

/* Special Commands */
#define ACTIVATE				0x50  // Enable extra features (send 0x73 after this)
#define NOP						0xFF  // No operation (returns STATUS register)

/* =========================== END Commands for SPI Communication =========================== */

#define REGISTER_MASK			0x1F  // Mask to ensure register address is within valid range

#define nrf24_ADDR_LEN			5


#define NRF24_TRANSMISSON_OK	0
#define NRF24_MESSAGE_LOST		1


/*Section       :         Macro Function Deceleration                */
#define nrf24_CONFIG			((1<<EN_CRC)|(0<<CRCO))

/*Section       :         Function Deceleration                */

/* ====================== adjustment functions ====================== */
void nrf24_init();
void nrf24_rx_address(uint8* adr);
void nrf24_tx_address(uint8* adr);
void nrf24_config(uint8 channel, uint8 pay_length);

/* ====================== state check functions ====================== */
uint8 nrf24_dataReady();
uint8 nrf24_isSending();
uint8 nrf24_getStatus();
uint8 nrf24_rxFifoEmpty();

/* ====================== core TX / RX functions ====================== */
void nrf24_send(uint8* value);
void nrf24_getData(uint8* data);


/* ====================== use in dynamic length mode ====================== */
uint8 nrf24_payloadLength();

/* ====================== post transmission analysis ====================== */
uint8 nrf24_lastMessageStatus();
uint8 nrf24_retransmissionCount();

/* ====================== Returns the payload length ====================== */
uint8 nrf24_payload_length();

/* ====================== power management ====================== */
void nrf24_powerUpRx();
void nrf24_powerUpTx();
void nrf24_powerDown();

/* ====================== low level interface ... ====================== */
uint8 spi_transfer(const SPI_Config *Config, uint8 tx);
void nrf24_transmitSync(uint8* dataout,uint8 len);
void nrf24_transferSync(uint8* dataout,uint8* datain,uint8 len);
void nrf24_configRegister(uint8 reg, uint8 value);
void nrf24_readRegister(uint8 reg, uint8* value, uint8 len);
void nrf24_writeRegister(uint8 reg, uint8* value, uint8 len);

#endif /* HAL_NRF24L01_H_ */