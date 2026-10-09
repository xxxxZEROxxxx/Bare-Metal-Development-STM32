//
// Created by Arcana on 8/10/26.
//
#include "gpio.h"




void gpio_init(GPIO_TypeDef * port, uint32_t number, MODER_TypeDef moder) {
    uint32_t offset = ((uintptr_t)port - (uintptr_t)GPIOA_BASE)/0x400;
    RCC_AHB1ENR |= (1 << offset);

    port->MODER &= ~(0x03 << (number * 2));
    port->MODER |= (moder << (number * 2));
}

void gpio_set(GPIO_TypeDef * port, uint32_t number, bool state) {
    if (state) {
        port->BSRR = (1 << number);
    }
    else {
        port->BSRR = (1 << (number + 16));
    }
}

bool gpio_read(GPIO_TypeDef * port, uint32_t number) {
    return (bool)((port->IDR) >> number & 0x01);
}
