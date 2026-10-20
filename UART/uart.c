//
// Created by Arcana on 17/10/26.
//
#include "uart.h"
#include "../SYSTICK/systick.h"
#include "../chip_headers/CMSIS/Device/stm32f4xx.h"
#include "../GPIO/gpio.h"


/**
 *  setup : PA2 UART2_TX
 *          PA3 UART2_RX
 ***/
volatile uint8_t data[100] = {};
volatile uint16_t data_counter = 0;

void init_uart(void) {
    gpio_init(GPIOA, 2, AF);
    gpio_init(GPIOA, 3, AF);
    gpio_init(GPIOC, 13, OUTPUT);

    // PA2 = USART2_TX (AF7), PA3 = USART2_RX (AF7)
    GPIOA->AFR[0] &= ~((0xFU << 8) | (0xFU << 12));
    GPIOA->AFR[0] |=   (7U    << 8) | (7U    << 12);

    // ENABLE CLOCK ACCESS FOR UART2
    RCC->APB1ENR |= APB1_EN_UART2;

    // CONFIGURE BAUD RATE
    uart_set_baudrate(16000000, 9600);

    // CONFIGURE CR1
    USART2->CR1 |= EN_TE | EN_UART2 | EN_RE;
}


void repeater(void) {
    gpio_init(GPIOA, 0, INPUT);
    //configure a pullup on PA0
    GPIOA -> PUPDR |= (1UL << 0);

    init_uart();
    // configure the intrrupt
        //intrrupt when new data arrive
    USART2->CR1 |= RXNEIE;
        //enable intrrupt for IDLE state
    //USART2->CR1 |= IDLEIE;

    //enable intrrupt in NVIC
    NVIC_EnableIRQ(USART2_IRQn);

    __enable_irq();


    while (1) {

        //Output received data when PA0 is pressed.
        if (gpio_read(GPIOA, 0) == 0) {
            for (uint16_t i = 0; i < data_counter; i++) {
                uart_write(data[i]);
            }
            data_counter = 0;
            // Wait for button release to prevent repeated output.
            while (gpio_read(GPIOA, 0) == 0) {
            }
        }
    }
}


void USART2_IRQHandler(void) {
    if (USART2->SR & RXNE) {
        data[data_counter] = USART2->DR;
        data_counter++;

        if (data_counter == 99) {
            print("Overflow, reset\n");
            data_counter = 0;
        }
    }
    if (USART2->SR & ORE) {
        print("over run, error");
    }
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

void print(const char * data) {
    while (*data != '\0') {
        uart_write(*data);
        data++;
    }
}
