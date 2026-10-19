//
// Created by Arcana on 17/10/26.
//
#include "uart.h"

#include "../chip_headers/CMSIS/Device/stm32f4xx.h"
#include "../GPIO/gpio.h"


/**
 *  setup : PA2 UART2_TX
 *          PA3 UART2_RX
 ***/
void init_uart(void) {
    gpio_init(GPIOA, 2, AF);
    gpio_init(GPIOA, 3, AF);

    // ENABLE CLOCK ACCESS FOR UART2
    RCC->APB1ENR |= APB1_EN_UART2;

    // CONFIGURE BAUD RATE
    uart_set_baudrate(16000000, 9600);

    // CONFIGURE CR1
    USART2->CR1 |= EN_TE | EN_UART2;
}


static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate)
{
    return ((periph_clk + (baudrate / 2U)) / baudrate);
}

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate)
{
    USART2->BRR = compute_uart_bd(periph_clk, baudrate);
}

void uart_write(int data) {
    while (!(USART2->SR & SR_TXE)){};
    USART2->DR = (data & 0xFF);
}

int __io_putchar(int ch)
{
    uart_write(ch);
    return ch;
}

int _write(int file, char *ptr, int len)
{
    int i;
    for (i = 0; i < len; i++) {
        uart_write(ptr[i]);
    }
    return len;
}
