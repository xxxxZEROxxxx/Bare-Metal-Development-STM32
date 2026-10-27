//
// Created by Arcana on 24/10/26.
//
#include "spi.h"
#include "../SYSTICK/systick.h"
#include "../chip_headers/CMSIS/Device/stm32f4xx.h"
#include "../GPIO/gpio.h"
/**
 * SET UP - GPIO - AF05
 * SPI1_SCK  - PB3
 * SPI1_MISO - PB4
 * SPI1_MOSI - BP5
 *
 */
// define status register position
#define SR_BSY (1UL << 7)
#define SR_TXE (1UL << 1)
#define SR_RXNE (1UL << 0)

#define SPI_EN (1UL << 6)
#define SPI_MSTR (1UL << 2)
#define SPI_SSI (1UL << 8)
#define SPI_SSM (1UL << 9)

void spi_init(void) {
    // set up gpio with clock enable
    gpio_init(GPIOB, 3, AF);
    gpio_init(GPIOB, 4, AF);
    gpio_init(GPIOB, 5, AF);
    // Select AF5 for PB3, PB4, and PB5.
    GPIOB->AFR[0] &= ~(
        (0xFUL << 12) |
        (0xFUL << 16) |
        (0xFUL << 20)
    );
    GPIOB->AFR[0] |=
        (5UL << 12) |
        (5UL << 16) |
        (5UL << 20);

    //enable clock on SPI 1
    RCC->APB2ENR |= (1UL << 12);

    //SET THE BAUD RATE, TREE ON SPI IS 16M , HERE DEVIDED BY 16 TO GET 1M
    SPI1->CR1 = 0;
    SPI1->CR1 |= (0b011UL << 3);

    // SET MODE TO MASTER
    SPI1->CR1 |= SPI_MSTR;

    //SET CLOCK POLARITY ADN PHASE
    SPI1->CR1 |= (0b10UL << 0); // SPI mode 3 (BMP280 supports modes 0 and 3).

    // Use software NSS management and keep the internal NSS signal high.
    // Without this, a floating/low hardware NSS input can set MODF and
    // disable SPI1 while it is configured as a master.
    SPI1->CR1 |= SPI_SSM | SPI_SSI;

    // ENABLE SPI
    SPI1->CR1 |= SPI_EN;
}

uint8_t spi(const uint8_t data) {
    while ((SPI1->SR & SR_TXE) == 0) {
    }
    SPI1->DR = data;

    //Here because its full duplex, every byte send will result in a byte received
    //even if this byte is meaningless, you still have to read it to prevent over run flag
    while ((SPI1->SR & SR_RXNE) == 0) {
    }
    return (SPI1->DR);
}

void spi_transmit(const uint8_t *data, uint32_t length) {
    for (uint32_t i = 0; i < length; i++) {
        spi(data[i]);
    }
    while (SPI1->SR & SR_BSY) {
    }
}





