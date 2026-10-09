//
// Created by Arcana on 9/10/26.
//

#ifndef FLASH_PROGRAMMER_SYSTICK_H
#define FLASH_PROGRAMMER_SYSTICK_H

#include "../main.h"

#define TICK_ENA    (1UL)
#define TICK_CONFIG    (0b100UL) // disable interrupt, enable internal clock
#define TICK_FLAG       (1UL << 16) // count flag



typedef struct {
    __IO CSR;
    __IO RVR;
    __IO CVR;
    __IO CALIB;
}SysTick_type;

#define SYST  ((volatile SysTick_type *) SYS_TICK_BASE)

void delay(int time);

#endif //FLASH_PROGRAMMER_SYSTICK_H
