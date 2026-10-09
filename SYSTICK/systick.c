//
// Created by Arcana on 9/10/26.
//

#include "systick.h"



void delay(int time) {
    /** config under assumption running at 16MHz */
    SYST->CSR |= TICK_CONFIG;
    // set reload value
    SYST->RVR = 16000 - 1;
    // CLEAR THE CURRENT VALUE
    SYST->CVR = 0;

    SYST->CSR |= TICK_ENA;
    for (int i = 0; i < time; i++) {
        while ((SYST->CSR & TICK_FLAG) == 0) {}
    }
    SYST->CSR &= ~TICK_ENA;
}