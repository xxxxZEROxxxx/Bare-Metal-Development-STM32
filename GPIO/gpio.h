//
// Created by Arcana on 8/10/26.
//

#ifndef FLASH_PROGRAMMER_GPIO_H
#define FLASH_PROGRAMMER_GPIO_H

#include "../main.h"
#include "../chip_headers/CMSIS/Device/stm32f4xx.h"

typedef enum {
    INPUT = 0x00,
    OUTPUT = 0x01,
    AF = 0x02,
    AN = 0x03,
} MODER_TypeDef;


#define RCC_AHB1ENR    *((volatile uint32_t *) (RCC_BASE + 0x30UL))

void gpio_init(GPIO_TypeDef * port, uint32_t number, MODER_TypeDef moder);
void gpio_set(GPIO_TypeDef * port, uint32_t number, bool state);
bool gpio_read(GPIO_TypeDef * port, uint32_t number);
void gpio_toggle(GPIO_TypeDef * port, uint32_t number);
#endif //FLASH_PROGRAMMER_GPIO_H