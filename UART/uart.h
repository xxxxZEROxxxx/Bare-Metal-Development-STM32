//
// Created by Arcana on 17/10/26.
//

#ifndef FLASH_PROGRAMMER_UART_H
#define FLASH_PROGRAMMER_UART_H

#include <stdint.h>

#define APB1_EN_UART2 (1UL << 17)
#define EN_TE         (1UL << 3)
#define EN_UART2      (1UL << 13)
#define SR_TXE        (1UL << 7)

void init_uart(void);

static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate);
static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
int __io__putchar(int ch);
void uart_write(int data);

#endif //FLASH_PROGRAMMER_UART_H
