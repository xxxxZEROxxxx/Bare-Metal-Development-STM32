//
// Created by Arcana on 13/10/26.
//

#ifndef FLASH_PROGRAMMER_TIMER_H
#define FLASH_PROGRAMMER_TIMER_H

#define ENR_GPIOA (1UL << 0)
#define MODER_PA0_AF (0b10 << 0)
#define AFRL_PA0_AF1 (1UL << 0)
#define ENR_TIM2 (1UL << 0)

void breath_light(void);


#endif //FLASH_PROGRAMMER_TIMER_H
