/*
 * File   :  Register_Map.h
 * https://www.linkedin.com/in/ayman-abohamed
 * Author : Ayman_Abohamed
 * Created: 3/14/2025 10:00:42 PM
 */ 

#ifndef REGISTER_MAP_H_
#define REGISTER_MAP_H_

/*Section       :         Includes                */


/*Section       :         Macro Deceleration                */

/* ===========================
 * nRF24L01 Register Map 
 * =========================== */

#define CONFIG				0x00  // Configuration Register
#define EN_AA				0x01  // Enable Auto Acknowledgment
#define EN_RXADDR			0x02  // Enable RX Addresses
#define SETUP_AW			0x03  // Setup Address Width
#define SETUP_RETR			0x04  // Setup Auto Retransmission
#define RF_CH				0x05  // RF Channel
#define RF_SETUP			0x06  // RF Setup Register
#define STATUS				0x07  // Status Register
#define OBSERVE_TX			0x08  // Transmit Observe Register
#define CD					0x09  // Carrier Detect
#define RX_ADDR_P0			0x0A  // Receive Address Data Pipe 1
#define RX_ADDR_P1			0x0B  // Receive Address Data Pipe 1
#define RX_ADDR_P2			0x0C  // Receive Address Data Pipe 2
#define RX_ADDR_P3			0x0D  // Receive Address Data Pipe 3
#define RX_ADDR_P4			0x0E  // Receive Address Data Pipe 4
#define RX_ADDR_P5			0x0F  // Receive Address Data Pipe 5
#define TX_ADDR				0x10  // Transmit Address
#define RX_PW_P0			0x11  // Number of bytes in RX payload in Data Pipe 0
#define RX_PW_P1			0x12  // Number of bytes in RX payload in Data Pipe 1
#define RX_PW_P2			0x13  // Number of bytes in RX payload in Data Pipe 2
#define RX_PW_P3			0x14  // Number of bytes in RX payload in Data Pipe 3
#define RX_PW_P4			0x15  // Number of bytes in RX payload in Data Pipe 4
#define RX_PW_P5			0x16  // Number of bytes in RX payload in Data Pipe 5
#define FIFO_STATUS			0x17  // FIFO Status Register
#define DYNPD				0x1C  // Enable Dynamic Payload Length

/* ===========================
 * Bit Masks for Registers
 * =========================== */

/* CONFIG Register (0x00) */
#define MASK_RX_DR              6  // Mask RX Data Ready interrupt
#define MASK_TX_DS              5  // Mask TX Data Sent interrupt
#define MASK_MAX_RT             4  // Mask Max Retransmit interrupt
#define EN_CRC                  3  // Enable CRC
#define CRCO                    2  // CRC encoding scheme (1: 2 bytes, 0: 1 byte)
#define PWR_UP                  1  // Power Up mode
#define PRIM_RX                 0  // RX/TX mode select (1: RX, 0: TX)

/* EN_AA Register (0x01) - Enable Auto Acknowledgment */
#define ENAA_P5                 5  // Enable Auto-ACK on pipe 5
#define ENAA_P4                 4  // Enable Auto-ACK on pipe 4
#define ENAA_P3                 3  // Enable Auto-ACK on pipe 3
#define ENAA_P2                 2  // Enable Auto-ACK on pipe 2
#define ENAA_P1                 1  // Enable Auto-ACK on pipe 1
#define ENAA_P0                 0  // Enable Auto-ACK on pipe 0

/* EN_RXADDR Register (0x02) - Enable RX Addresses */
#define ERX_P5                 5   // Enable data pipe 5
#define ERX_P4                 4   // Enable data pipe 4
#define ERX_P3                 3   // Enable data pipe 3
#define ERX_P2                 2   // Enable data pipe 2
#define ERX_P1                 1   // Enable data pipe 1
#define ERX_P0                 0   // Enable data pipe 0

/* Setup Address Width (0x03) */ 
#define AW					   0   // 2 bits

/* Setup Auto Retransmission (0x04) */
#define ARD					   4   //4 bits
#define ARC					   0   // 4 bits

/* RF Setup Register (0x06) */
#define PLL_LOCK			   4
#define RF_DR			       3
#define RF_PWR			       1   // 2 bits

/* STATUS Register (0x07) */
#define RX_DR                   6  // RX Data Ready interrupt
#define TX_DS                   5  // TX Data Sent interrupt
#define MAX_RT                  4  // Max Retransmit interrupt
#define RX_P_NO                 1  // Mask for RX_P_NO (bits 3:1 in STATUS register)
#define TX_FULL                 0  // TX FIFO full flag

/* Transmit Observe Register (0x08) */
#define PLOS_CNT			    4 // 4 bits 
#define ARC_CNT				    0 // 4 bits 

/* FIFO_STATUS Register (0x17) */
#define FIFO_TX_REUSE           6  // TX payload reuse enabled
#define FIFO_TX_FULL            5  // TX FIFO full flag
#define FIFO_TX_EMPTY           4  // TX FIFO empty flag
#define FIFO_RX_FULL            1  // RX FIFO full flag
#define FIFO_RX_EMPTY           0  // RX FIFO empty flag

/* DYNPD Register (0x1C) - Enable Dynamic Payload */
#define DPL_P5                  5  // Enable Dynamic Payload Length for pipe 5
#define DPL_P4                  4  // Enable Dynamic Payload Length for pipe 4
#define DPL_P3                  3  // Enable Dynamic Payload Length for pipe 3
#define DPL_P2                  2  // Enable Dynamic Payload Length for pipe 2
#define DPL_P1                  1  // Enable Dynamic Payload Length for pipe 1
#define DPL_P0                  0  // Enable Dynamic Payload Length for pipe 0


#endif /* REGISTER_MAP_H_ */