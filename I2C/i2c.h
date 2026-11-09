//
// Created by Arcana on 5/11/26.
//
#include <stdint.h>
#ifndef FLASH_PROGRAMMER_I2C_H
#define FLASH_PROGRAMMER_I2C_H

#define  I2C1EN          (1UL << 21) // enable on RCC

#define  I2C_SWRST       (1UL << 15) // SOFTWARE RESET
#define  I2C_EN_ACK      (1UL << 10) // ENABLE ACK
#define  I2C_START       (1UL << 8) // USED IN GENERATE START IN CR1
#define  I2C_STOP        (1UL << 9) // USED TO GENERATE STOP IN CR1
#define  I2C_EN          (1UL) // USED IN CR1 TO ENABLE I2C PERIPHERAL
#define  I2C_POS         (1UL << 11) // in CR1 POS to control the byte to ack or nack

#define  I2C_FREQ        16 // IN CR2, USED TO SET THE PERIPHERAL CLOCK FREQUENCY

// BELOW IS FOR SR
#define  IIC_SR1_AF      (1UL << 10) // SET WHEN NO ACK IS RETURNED
#define  IIC_SR1_ARLO    (1UL << 9) // SET WHEN ARBITRATION LOST
#define  IIC_SR1_TXE     (1UL << 7) // SET WHEN DATA REGISTER EMPTY, READY TO GET ANOTHER BYTE
#define  IIC_SR1_RXNE    (1UL << 6) // SET WHEN RX RECEIVED A BYTE
#define  IIC_SR1_STOPF   (1UL << 4) // SET WHEN STOP DETECTED
#define  IIC_SR1_BTF     (1UL << 2) // BYTE TRANSFER FINISHED
#define  IIC_SR1_ADDR    (1UL << 1) // SET WHEN SLAVE ACKED THE MESSAGE
#define  IIC_SR1_SB      (1UL) // SET WHEN START CONDITION IS SET

#define  IIC_SR2_BUSY    (1UL << 1) // COMMUNICATION ONGOING ON THE BUS

#define  I2C_CCR_100K    80 // CLOCK CONTROL REGISTER

#define  I2C_TRISE       17 // TRIG RISE


void iic_init(void);

void iic_write(uint8_t saddr, uint8_t addr, uint8_t data);

uint8_t iic_read(uint8_t saddr, uint8_t addr);

void iic_burst_write(uint8_t saddr, uint8_t addr, uint8_t * data, int length);

void iic_burst_read(uint8_t saddr, uint8_t addr, uint8_t * data, int length);


#endif //FLASH_PROGRAMMER_I2C_H
