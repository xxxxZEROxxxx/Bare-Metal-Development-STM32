//
// Created by Arcana on 24/10/26.
//

#include <stdint.h>

#ifndef FLASH_PROGRAMMER_SPI_H
#define FLASH_PROGRAMMER_SPI_H

void spi_init(void);
void spi_transmit(const uint8_t *data, uint32_t length);
uint8_t spi(const uint8_t data);


#endif //FLASH_PROGRAMMER_SPI_H







