//
// Created by Arcana on 8/10/26.
//

#ifndef FLASH_PROGRAMMER_GPIO_H
#define FLASH_PROGRAMMER_GPIO_H

#endif //FLASH_PROGRAMMER_GPIO_H

#include "../main.h"

typedef struct {
    __IO MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
    __IO OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
    __IO OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
    __IO PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
    __IO IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
    __IO ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
    __IO BSRR;     /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
    __IO LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
    __IO AFRL;   /*!< GPIO alternate function registers lower, Address offset: 0x20      */
    __IO AFRH;   /*!< GPIO alternate function registers higher,Address offset: 0x24      */
}GPIO_TypeDef;

typedef enum {
    INPUT = 0x00,
    OUTPUT = 0x01,
    AF = 0x02,
    AN = 0x03,
} MODER_TypeDef;

#define GPIOA ((GPIO_TypeDef*) GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef*) GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef*) GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef*) GPIOD_BASE)

#define RCC_AHB1ENR    *((volatile uint32_t *) (RCC_BASE + 0x30UL))

void gpio_init(GPIO_TypeDef * port, uint32_t number, MODER_TypeDef moder);
void gpio_set(GPIO_TypeDef * port, uint32_t number, bool state);
bool gpio_read(GPIO_TypeDef * port, uint32_t number);