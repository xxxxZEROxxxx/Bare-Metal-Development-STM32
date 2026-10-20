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
#define EN_RE         (1UL << 2)

#define RXNEIE        (1UL << 5)
#define IDLEIE        (1UL << 4)

#define RXNE          (1UL << 5) //REVEIVE NOT EMPTY
#define IDLE          (1UL << 4) // IDLE STATE
#define ORE           (1UL << 3) //OVER RUN

void init_uart(void);

static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate);
static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
void uart_write(int data);
void print(const char * data);
void repeater(void);
#endif //FLASH_PROGRAMMER_UART_H
