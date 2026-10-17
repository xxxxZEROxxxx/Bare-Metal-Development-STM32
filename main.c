#include "GPIO/gpio.h"
#include <stdio.h>
#include "main.h"
#include "SYSTICK/systick.h"
//#include "stm32f4xx.h"
#include "EXTI/exti.h"
#include "TIM & PWM/timer.h"
#include "UART/uart.h"

struct this{
    volatile int a;
    volatile int b;
};
struct this that = {0,0};
#include "main.h" // Ensures correct CMSIS core headers are included

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

volatile int start;
volatile int end;
volatile int gap;

int main(void) {
    init_uart();
    while (1) {
        delay(1000);
        printf("P");
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

