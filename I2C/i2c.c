//
// Created by Arcana on 5/11/26.
//
#include "i2c.h"
#include "../chip_headers/CMSIS/Device/stm32f4xx.h"
#include "../GPIO/gpio.h"

/***
 * use I2C1   --  AF04
 * SCL -- PB6
 * SDA -- PB7
 *
 ****/
void iic_init(void) {
    gpio_init(GPIOB, 6, AF);
    gpio_init(GPIOB, 7, AF);

    /* Open-drain, internal pull-ups, and AF4 on both pins. */
    GPIOB->OTYPER |= (1UL << 6) | (1UL << 7);
    GPIOB->PUPDR |= (0b0101 << 12);

    GPIOB->AFR[0] |= (0b01000100 << 24);

    RCC->APB1ENR |= I2C1EN; /* I2C1 enable bit (bit 22). */
    (void)RCC->APB1ENR;

    I2C1->CR1 = I2C_SWRST;
    I2C1->CR1 &= ~I2C_SWRST; // Release from reset
    I2C1->CR1 = 0;
    I2C1->CR2 = I2C_FREQ;   /* APB1 clock is 16 MHz. */
    I2C1->CCR = I2C_CCR_100K;
    I2C1->TRISE = I2C_TRISE;
    I2C1->CR1 = I2C_EN;
}

static void wait_bus_free(void) {
    while (I2C1->SR2 & IIC_SR2_BUSY) { }
}

static void start(void) {
    I2C1->CR1 |= I2C_START;
    while (!(I2C1->SR1 & IIC_SR1_SB)) { }
}

static void send_address(uint8_t saddr, int read) {
    I2C1->DR = (uint8_t)((saddr << 1) | (read ? 1U : 0U));
    while (!(I2C1->SR1 & IIC_SR1_ADDR)) { }
    (void)I2C1->SR2; /* Clear ADDR by reading SR1 then SR2. */
}

static void write_register_address(uint8_t addr) {
    while (!(I2C1->SR1 & IIC_SR1_TXE)) { }
    I2C1->DR = addr;
    while (!(I2C1->SR1 & IIC_SR1_BTF)) { }
}

void iic_write(uint8_t saddr, uint8_t addr, uint8_t data) {
    iic_burst_write(saddr, addr, &data, 1);
}

uint8_t iic_read(uint8_t saddr, uint8_t addr) {
    uint8_t data = 0;
    iic_burst_read(saddr, addr, &data, 1);
    return data;
}

void iic_burst_write(uint8_t saddr, uint8_t addr, uint8_t *data, int length) {
    wait_bus_free();
    start();
    send_address(saddr, 0);
    write_register_address(addr);

    for (int i = 0; i < length; ++i) {
        while (!(I2C1->SR1 & IIC_SR1_TXE)) { }
        I2C1->DR = data[i];
    }
    while (!(I2C1->SR1 & IIC_SR1_BTF)) { }
    I2C1->CR1 |= I2C_STOP;
}

void iic_burst_read(uint8_t saddr, uint8_t addr, uint8_t *data, int length) {
    // wait bus to be free
    while ((I2C1->SR2 & IIC_SR2_BUSY)){}

    // set start and wait to start
    I2C1->CR1 |= I2C_START;
    while (!(I2C1->SR1 & IIC_SR1_SB)){}

    // send slave address with write - then wait to acknowledge
    I2C1->DR = (uint8_t)(saddr << 1);
    while (!(I2C1->SR1 & IIC_SR1_ADDR)){}
    (void)I2C1->SR2;

    // then send out the register address, then wait for TXE
    I2C1->DR = addr;
    while (!(I2C1->SR1 & IIC_SR1_TXE)){}

    // then issue a restart - wait to start
    I2C1->CR1 |= I2C_START;
    while (!(I2C1->SR1 & IIC_SR1_SB)){}

    I2C1->DR = (uint8_t)((saddr << 1) | 1UL);
    while (!(I2C1->SR1 & IIC_SR1_ADDR)){}
    // line being hold here to decide whether to send NACK or ACK

    if (length == 1) {
        I2C1->CR1 &= ~I2C_EN_ACK;
        (void)I2C1->SR2;
        // release the line, communication continue
        I2C1->CR1 |= I2C_STOP;
        // wait till the rx receive
        while (!(I2C1->SR1 & IIC_SR1_RXNE)){}
        *data = I2C1->DR;
    }
    else if (length == 2) {
        I2C1->CR1 |= I2C_CR1_POS;    // 1. Shift ACK control to the next byte
        I2C1->CR1 &= ~I2C_EN_ACK;    // 2. Program a NACK
        (void)I2C1->SR2;             // 3. Clear ADDR flag -> Bus releases

        while (!(I2C1->SR1 & IIC_SR1_BTF)){} // Wait for both bytes to finish
        I2C1->CR1 |= I2C_STOP;       // Generate STOP

        data[0] = (uint8_t)I2C1->DR; // Read byte 1
        data[1] = (uint8_t)I2C1->DR; // Read byte 2

        I2C1->CR1 &= ~I2C_CR1_POS;   // Clear POS bit for future transfers
    }
    else {
        I2C1->CR1 |= I2C_EN_ACK;
        (void)I2C1->SR2;
        // release the line, communication continue

        if (length - 2) {
            for (int i = 0; i < (length - 2); ++i) {
                while (!(I2C1->SR1 & IIC_SR1_RXNE)) { }
                data[i] = (uint8_t)I2C1->DR;
            }
        }
        while (!(I2C1->SR1 & IIC_SR1_BTF)){}
        I2C1->CR1 &= ~I2C_EN_ACK;
        I2C1->CR1 |= I2C_STOP;
        data[length - 2] = (uint8_t)I2C1->DR;
        data[length - 1] = (uint8_t)I2C1->DR;
    }

    /* Leave ACK enabled for the next transaction. */
    I2C1->CR1 |= I2C_EN_ACK;
}
/*
* else {
        I2C1->CR1 |= I2C_EN_ACK;
        (void)I2C1->SR2;
        // release the line, communication continue

        //// -- start of option 1
        if (length - 2) {
            for (int i = 0; i < (length - 2); ++i) {
                while (!(I2C1->SR1 & IIC_SR1_RXNE)) { }
                data[i] = (uint8_t)I2C1->DR;
            }
        }
        while (!(I2C1->SR1 & IIC_SR1_BTF)){}
        I2C1->CR1 &= ~I2C_EN_ACK;
        I2C1->CR1 |= I2C_STOP;
        data[length - 2] = (uint8_t)I2C1->DR;
        data[length - 1] = (uint8_t)I2C1->DR;
        /// -- end of option 1

        /// -- start of option 2
        for (int i = 0; i < length; i++) {
            if (i == length - 2) {
                while (!(I2C1->SR1 & IIC_SR1_BTF)){}
                I2C1->CR1 &= ~I2C_EN_ACK;
                data[i++] = (uint8_t)I2C1->DR;
                I2C1->CR1 |= I2C_STOP;
                data[i] = (uint8_t)I2C1->DR;
                break;
            }
            while (!(I2C1->SR1 & IIC_SR1_RXNE)) { }
            data[i] = (uint8_t)I2C1->DR;
        }
        /// -- end of option 2
    }
 */