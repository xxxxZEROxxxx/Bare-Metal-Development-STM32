//
// Created by Arcana on 13/10/26.
//
#include "timer.h"
#include "../chip_headers/CMSIS/Device/stm32f4xx.h"
#include "../SYSTICK/systick.h"

void breath_light(void) {
    //enable gpio13 clock tree
    RCC->AHB1ENR |= ENR_GPIOA;
    //enable timer2 clock tree
    RCC->APB1ENR |= ENR_TIM2;

    // SET MODER TO AF
    GPIOA->MODER |= MODER_PA0_AF;

    //SET GPIOA 0 TO OUTPUT AF MODE
    GPIOA->AFR[0] |= AFRL_PA0_AF1;

    /** SET THE TIMER PARAMETER **/

    TIM2->PSC = 39;
    TIM2->ARR = 200;

    //output compare mode register
    TIM2->CCMR1 |= 0b01111000;

    //compare enable register
    TIM2->CCER |= 0b0001;

    //output compare register 1; set half here
    TIM2->CCR1 |= 15;

    //turn on UG bit in event generation register
    TIM2->EGR |= 1UL;

    TIM2->CR1 |= 1UL;

    //set pc13 

    volatile short count = 0;

    while (1) {
        while (count < 200) {
            delay(10);
            TIM2->CCR1 = count;
            count++;
        }
        while (count > 0) {
            delay(10);
            TIM2->CCR1 = count;
            count--;
        }
    }
}