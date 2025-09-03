/*
 * File   :  hal_nRF24L01.h
 * Author : AhmedShawada
 * https://www.linkedin.com/in/ahmed-shawada/
 * Created: 2/28/2025 3:12:12 PM
 */ 




#ifndef HAL_NRF24L01_H_
#define HAL_NRF24L01_H_


/*Section       :         Includes                */
#include <avr/io.h>
#include "mcal_std_types.h"
#include "hal_gpio.h"
#include "hal_spi.h"

// ?? **????? ????? ?????? nRF24L01**
#define CONFIG       0x00
#define EN_AA        0x01
#define EN_RXADDR    0x02
#define SETUP_AW     0x03
#define SETUP_RETR   0x04
#define RF_CH        0x05
#define RF_SETUP     0x06
#define STATUS       0x07
#define RX_ADDR_P0   0x0A
#define TX_ADDR      0x10
#define RX_PW_P0     0x11
#define FIFO_STATUS  0x17

// ?? **????? SPI**
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define NOP           0xFF

// ?? **???? ??????**
#define PWR_UP   1  // ????? ??????
#define PRIM_RX  0  // ????? ??? ?????????
#define PRIM_TX  0  // ????? ??? ???????
#define TX_DS    5  // ??? ??????? ??????
#define MAX_RT   4  // ??? ????? ???????? ??????
#define RX_DR    6  // ??? ?????? ????????
#define TX_FULL  0  // ???? FIFO ?????
#define REGISTER_MASK  0x1F  

// ?? **????? ??????**
#define CE_PIN   PB2
#define CSN_PIN  PB4
#define MOSI_PIN PB5
#define MISO_PIN PB6
#define SCK_PIN  PB7

// ?? **?????? ?????? ?? CE ? CSN**
#define NRF_CE_HIGH()   (PORTB |= (1 << CE_PIN))
#define NRF_CE_LOW()    (PORTB &= ~(1 << CE_PIN))
#define NRF_CSN_HIGH()  (PORTB |= (1 << CSN_PIN))
#define NRF_CSN_LOW()   (PORTB &= ~(1 << CSN_PIN))

// ?? **????? ??????? ?? SPI ? nRF24L01**
void SPI_init();
uint8_t SPI_Transmit(uint8_t data);
void nRF24_WriteReg(uint8_t reg, uint8_t value);
uint8_t nRF24_ReadReg(uint8_t reg);
void nRF24_Transmit_Process(uint8_t *data, uint8_t length);
uint8_t nRF24_Receive_Process();






#endif /* HAL_NRF24L01_H_ */