//
// Created by Arcana on 10/11/26.
//
/**
 * This example will configure a timer triggered 1KHz sample rate ADC,
 * which will use DMA to write ADC result into memory
 * this use PA1 as input example, PA1 connected to ADC_IN1 channel 1
 *  -- DMA 2 stream 0 channel 0
 *
 * then, when the 1000 numbers is arrived, CPU process the memory, then when
 * processing is done, it will call DMA on another channel to send out these
 * 1000 numbers to UART -- DMA 1 stream 6 channel 4
 */

#include "dma_adc.h"
#include "../SYSTICK/systick.h"
#include "../chip_headers/CMSIS/Device/stm32f4xx.h"
#include "../GPIO/gpio.h"
#include "../UART/uart.h"

uint16_t ADC_data[1000] = {};
void dma_adc_timer_init(void) {
    // ------- RCC ENABLE

    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    gpio_init(GPIOA, 1, AN);

    // ------------------------TIM CONFIGURE--------------------------------
    TIM2->PSC = 15;
    TIM2->ARR = 999; // the setup required to generate 1kHz under 16Mhz input

    TIM2->CR2 |= (0b010 << 4); // *-A0 select which event will trigger the output trigger output (TRGO)
    TIM2->EGR |= 1UL; // *-A1  set the UG bit here, so when the first time the timer load up, it will use the new value of ARR PSC

    // ------------------------ADC CONFIGURE--------------------------------
    /**  use single conversion mode, set CONT to 0 in CR2
     *  triggered by Timer 2 TRGO event
     *  then set the order and channel in the SQRx
     *  default 12bit resolution
     *  SAMPLE TIME 28 CYCLES : SMPRx -> 010
     */
    ADC1->CR2 &= ~CR2_CONT; // SET CONT TO 0
    ADC1->CR2 |= (0b0110 << 24); // trigger select for regular group to Timer 2 TRGO event
    ADC1->CR2 |= DDS;
    ADC1->CR2 |= DMA;
    ADC1->CR2 |= bit(28); // set EXTEN so ADC will trigger on the rising edge of TRGO line

    ADC1->SMPR2 |= ADC_SMPR; //SET SAMPLE TIME
    ADC1->SQR1 &= ~ADC_SQR_L; // SET TOTAL CONVERSION NUMBER TO 1
    ADC1->SQR3 |= SQR_FIRST; // SET THE FIRST CONVERSION TO CHANNEL 1

    ADC1->CR2 |= ADON; // TURN ON ADC

    // ------------------------IRQ CONFIGURE------------------------------
    __disable_irq();
    NVIC_EnableIRQ(DMA2_Stream0_IRQn);
    __enable_irq();

    // ------------------------DMA CONFIGURE------------------------------
    DMA2_Stream0->CR &= ~DMA2_EN;
    while (DMA2_Stream0->CR & DMA2_EN){}

    DMA2_Stream0->CR &= ~(0b111 << 25); //CHSEL select channel to 0 for ADC
    DMA2_Stream0->CR |= (0b0101 << 11); //M,PSIZE set the memory, peripheral data size to 16bit

    //DMA2_Stream0->CR |= bit(5); //PFETRL let peripheral be the flow controller ! dont set this because we gonna need DMA to count the samples and decides when the buffer is full using NDTR
    DMA2_Stream0->CR |= bit(10); //MINC allow memory increment by set MSIZE
    DMA2_Stream0->CR |= bit(8);  //CIRC enable circular mode, so it will reload after it
    DMA2_Stream0->CR |= bit(4); //TCIE enable interrupt when transfer is done

    DMA2_Stream0->NDTR = 1000; // *-A3
    DMA2_Stream0->PAR = (uint32_t)(&(ADC1->DR));
    DMA2_Stream0->M0AR = (uint32_t)(&ADC_data);

    DMA2_Stream0->CR |= DMA2_EN;

    // ------------------------UART CONFIGURE------------------------------
    init_dma_uart();
    // ------------------------DMA FOR UART CONFIGURE------------------------------
    DMA1_Stream6->CR &= ~DMA1_EN;
    while (DMA1_Stream6->CR & DMA1_EN){}

    DMA1_Stream6->CR &= ~(0b100 << 25); //CHSEL select channel to 4 for UART
    DMA1_Stream6->CR &= ~(0b1111 << 11); //M,PSIZE set the memory, peripheral data size to 8 bit
    DMA1_Stream6->CR |= bit(10);  // let memory pointer increment
    DMA1_Stream6->CR |= bit(6); // DIR configure memory direction
    DMA1_Stream6->CR |= bit(4); // enabled compelete intrrupt
    DMA1_Stream6->NDTR = 2000;  // set number of 8 bits to transfer in one batch
    DMA1_Stream6->PAR = (uint32_t)(&(USART2->DR));
    DMA1_Stream6->M0AR = (uint32_t)(&ADC_data);

    // here dont use DMA2_Stream0->CR |= DMA2_EN; because it will trriger DMA right away
}
static void ADC_convert(uint16_t * raw) {
    for (uint16_t i = 0; i < 1000; i++) {
        raw[i] = (raw[i]*3400)/4096;
        // return like 2450 means 2.45V
    }
}

void dma_adc_timer_start(void) {
    TIM2->CR1 |= 1UL; // start timer to trigger all of them
    init_uart();

}

void DMA2_Stream0_IRQHandler(void) {
    if (DMA2->LISR & DMA2_SR_TCIF0) {
        DMA2->LIFCR = DMA2_SR_TCIF0; // write one to clear
        ADC_convert(ADC_data);
        DMA2_Stream0->CR |= DMA2_EN;
    }
}
void DMA1_Stream6_IRQHandler(void) {
    if (1) {

    }
}
//4096 from 0-3.4