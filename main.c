#include "GPIO/gpio.h"
#include <stdio.h>
#include "main.h"
#include "SYSTICK/systick.h"
//#include "stm32f4xx.h"
#include "EXTI/exti.h"
#include "TIM & PWM/timer.h"
#include "UART/uart.h"
#include "ADC/adc.h"
#include "SPI/spi.h"

struct this{
    volatile int a;
    volatile int b;
};
struct this that = {0,0};
#include "main.h" // Ensures correct CMSIS core headers are included

const uint8_t spi_data[] = {
    0xFF, 0x08, 0x04, 0xCB
};

void DWT_Init(void) {
    // 1. Enable the trace and debug block (DEMCR register)
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    // 2. Unlock DWT access (Required ONLY for Cortex-M7/M33 cores like STM32F7, STM32H7)
    // Writing 0xC5ACCE55 unlocks the CoreSight lock mechanism
#if defined(STM32H7) || defined(STM32F7)
    DWT->LAR = 0xC5ACCE55;
#endif

    // 3. Reset the cycle counter register
    DWT->CYCCNT = 0;

    // 4. Enable the cycle counter inside the DWT control register
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}
void fpu_enable(void)
{
    SCB->CPACR |= (0xFUL << 20);  // Enable CP10 and CP11
    __DSB();
    __ISB();
}

volatile int start = 10302;
volatile int end;
volatile int gap;
float decimal;

int main(void) {
    // Enable specific fault handlers (BusFault, UsageFault, MemManage)
    // to prevent escalation to HardFault
    SCB->SHCSR |= (1 << 16) | (1 << 17) | (1 << 18);

    gpio_init(GPIOA, 0, INPUT);
    //configure a pullup on PA0
    GPIOA -> PUPDR |= (1UL << 0);
    spi_init();
    //init_uart();
    //repeater();
    //fpu_enable();
    //adc_init();
    //print("start\n"); // Hardware direct test

    while (1) {
       delay(400);
       spi_transmit(spi_data, sizeof(spi_data));

    }
}




void EXTI0_IRQHandler(void) {
    if (EXTI -> PR & EXTI0) {
        delay(5);
        EXTI -> PR = EXTI0;
    }
    end = DWT->CYCCNT;
    gap = end - start;
}
