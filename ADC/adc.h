//
// Created by Arcana on 22/10/26.
//

#ifndef FLASH_PROGRAMMER_ADC_H
#define FLASH_PROGRAMMER_ADC_H

#define RCC_APB2ENR_ADC1EN      (1UL << 8)
#define CR2_CONT                (1UL << 1)
#define ADON                    (1UL)
#define SWSTART                 (1UL << 30)
#define ADC_SMPR                (0b010 << 3)
#define ADC_SQR_L               (0000 << 20)
#define SQR_FIRST               1
#define STRT                    (1UL << 4)
#define EOC                     (1UL << 1)

void adc_init(void);
float adc_sample(void);

#endif //FLASH_PROGRAMMER_ADC_H
