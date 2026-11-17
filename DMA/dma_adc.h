//
// Created by Arcana on 10/11/26.
//

#ifndef FLASH_PROGRAMMER_DMA_ADC_H
#define FLASH_PROGRAMMER_DMA_ADC_H


#define bit(x)                  (1UL << x)
#define RCC_APB2ENR_ADC1EN      (1UL << 8)
#define RCC_AHB1ENR_DMA2EN      (1UL << 22)
#define RCC_APB1ENR_TIM2EN      (1UL << 0)
#define CR2_CONT                (1UL << 1)
#define ADON                    (1UL)
#define SWSTART                 (1UL << 30)
#define ADC_SMPR                (0b010 << 3)
#define ADC_SQR_L               (0b1111 << 20)
#define SQR_FIRST               1
#define STRT                    (1UL << 4)
#define EOC                     (1UL << 1)
#define DDS                     (1UL << 9)// enable DMA when new data is ready in CR2
#define DMA                     (1UL << 8)// enable DMA in CR2

#define DMA1_EN                 bit(1)
#define DMA2_EN                 bit(1)






#define DMA2_SR_TCIF0           bit(5)
void dma_adc_timer_init(void);
void dma_adc_timer_start(void);


#endif //FLASH_PROGRAMMER_DMA_ADC_H
