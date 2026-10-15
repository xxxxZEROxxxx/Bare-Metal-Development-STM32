//
// Created by Arcana on 14/10/26.
//
#include "exti.h"
#include "../chip_headers/CMSIS/Device/stm32f4xx.h"
#include "../GPIO/gpio.h"


void exti_init(void) {
    __disable_irq();

    gpio_init(GPIOA, 0, INPUT);
    gpio_init(GPIOC,13,OUTPUT);

    //configure a pullup on PA0
    GPIOA -> PUPDR |= (1UL << 0);

    RCC->APB2ENR |= SYSCFGEN;

    // enable the EXTI0 on PA pin
    SYSCFG -> EXTICR[0] &= ~(0b1111UL << 0);

    // unmask it
    EXTI -> IMR |= (1UL << 0);

    // configure to falling edge trigger
    EXTI -> FTSR |= (1UL << 0);

    // enable irq on NVIC
    NVIC_EnableIRQ(EXTI0_IRQn);

    // dont forget to enable irq back
    __enable_irq();
}
