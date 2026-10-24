/** Created by Arcana on 22/10/26.
 * this use PA1 as a input example, PA1 connected to ADC_IN1 channel 1
 *
 *
 */
#include "adc.h"
#include "../SYSTICK/systick.h"
#include "../chip_headers/CMSIS/Device/stm32f4xx.h"
#include "../GPIO/gpio.h"

void adc_init(void) {
    // ENABLE CLOCK TREE / GPIOA IN AHB1, ADC IN APB2
    // GPIO WILL BE ENABLED LATER IN FUNCTION CALL
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // GPIO ENABLE AND SET TO ANALOGE
    gpio_init(GPIOA, 1, AN);

    // ADC CONFIGURE
    /**  use single conversion mode, set CONT to 0 in CR2
     *  then set the order and channel in the SQRx
     *  default 12bit resolution
     *  SAMPLE TIME 28 CYCLES : SMPRx -> 010
     */
    ADC1->CR2 &= ~CR2_CONT; // SET CONT TO 0
    ADC1->SMPR2 |= ADC_SMPR; //SET SAMPLE TIME
    ADC1->SQR1 &= ~(ADC_SQR_L); // SET TOTAL CONVERSION NUMBER TO 1
    ADC1->SQR3 |= SQR_FIRST; // SET THE FIRST CONVERSION TO CHANNEL 1

    ADC1->CR2 |= ADON; // TURN ON ADC
}

float adc_sample(void) {
    // 3.4V ave
    ADC1->CR2 |= SWSTART;
    while (!(ADC1->SR & EOC)) {
        // pull for EOC to be set
    }
    int adc_value_raw = ADC1->DR;
    float voltage = (3.4/4096) * adc_value_raw;
    return voltage;
}


