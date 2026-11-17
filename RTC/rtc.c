//
// Created by Arcana on 16/11/26.
//
#include "../SYSTICK/systick.h"
#include "rtc.h"



TIME_RAW_TypeDef present_time = {
    .YEAR = 26,
    .MONTH = 12,
    .DAY = 31,
    .WEEK = 2,
    .HOUR = 12,
    .MINUTE = 34,
    .SECOND = 4
};

TIME_FIN_TypeDef time_convert(TIME_RAW_TypeDef input) {
    /*
     * only accept 24 hours format
     */
    TIME_FIN_TypeDef result = {0,0};

    result.TR |= ((input.HOUR / 10) << 20) | ((input.HOUR % 10) << 16)
        | ((input.MINUTE / 10) << 12) | ((input.MINUTE % 10) << 8)
        | ((input.SECOND / 10) << 4) | ((input.SECOND % 10) << 0);

    result.DR |= ((input.YEAR / 10) << 20) | ((input.YEAR % 10) << 16)
    | ((input.MONTH / 10) << 12) | ((input.MONTH % 10) << 8)
    | ((input.DAY / 10) << 4) | ((input.DAY % 10) << 0)
    | ((input.WEEK) << 13);

    return result;
}

void rtc_init(void) {
    // enable PWR uint clock
    RCC_APB1ENR_L |= bit(28);
    (void)RCC_APB1ENR_L;  // dummy read, give it a clock cycle to start

    // first set the DBP bit in PWR_CR to enable
    PWR_L->CR |= DBP; // the order matters, refer to P.88 of RM0368

        // set the clock source and enable it in RCC
    RCC_BDCR_L |= RTCSEL | LSEON | RTC_EN;
    while (!(RCC_BDCR_L & LSERDY)){} // wait till LSE stable

    // then unlock RTC internally
    RTC_L->WPR = 0xCA;
    RTC_L->WPR = 0x53;

    // set INIT bit in RTC_ISR to enter init mode, in this mode, the calendar counter is stopped
    RTC_L->ISR |= INIT;
    // pull INITF bit to ensure transistion
    while (!(RTC_L->ISR & INITF)) {}

    // then program the synchronous prescaler in RTC_PRER
    // then asynchronous prescaler bits
        // here we use the default value

    // then set the time format in FMT bit in RTC_CR
    RTC_L->CR &= ~FMT;
    // then load the initial time and data
    TIME_FIN_TypeDef time = time_convert(present_time);
    RTC_L->DR = time.DR;
    RTC_L->TR = time.TR;

    // exit the init mode by clearing INIT bit
    RTC_L->ISR &= ~INIT;
    RTC_L->WPR = 0xFF;            // lock it
    // from here, it starts
}

TIME_RAW_TypeDef rtc_read(void) {
    TIME_RAW_TypeDef t;

    // read TR first: this locks DR until it is read,
    // so time and date always belong together
    uint32_t tr = RTC_L->TR;
    uint32_t dr = RTC_L->DR;

    // RTC_TR: HT[21:20] HU[19:16] MNT[14:12] MNU[11:8] ST[6:4] SU[3:0]
    t.HOUR   = (short)(((tr >> 20) & 0x3) * 10 + ((tr >> 16) & 0xF));
    t.MINUTE = (short)(((tr >> 12) & 0x7) * 10 + ((tr >>  8) & 0xF));
    t.SECOND = (short)(((tr >>  4) & 0x7) * 10 + ((tr >>  0) & 0xF));

    // RTC_DR: YT[23:20] YU[19:16] WDU[15:13] MT[12] MU[11:8] DT[5:4] DU[3:0]
    t.YEAR   = (short)(((dr >> 20) & 0xF) * 10 + ((dr >> 16) & 0xF));
    t.WEEK   = (short)((dr >> 13) & 0x7);
    t.MONTH  = (short)(((dr >> 12) & 0x1) * 10 + ((dr >>  8) & 0xF));
    t.DAY    = (short)(((dr >>  4) & 0x3) * 10 + ((dr >>  0) & 0xF));

    return t;
}

void rtc_calibrate(short stage) {
    /**
     * stage = 0 : proform output calibration part, route to enables the RTC_CALIB output to
     */
    if (!stage) {
        RTC_L->WPR = 0xCA;            // unlock RTC
        RTC_L->WPR = 0x53;

        RTC_L->CR &= ~OSEL_MASK;      // alarm output off, so RTC_CALIB gets the pin
        //RTC_L->CR |=  COSEL;  // select this open one Hz
        RTC_L->CR &= ~COSEL;  // select this open 512 Hz
        RTC_L->CR |= COE;             // PC13 now outputs RTC_CALIB

        RTC_L->WPR = 0xFF;            // lock again
    }
    else {
        // turn off calibration
        RTC_L->WPR = 0xCA;
        RTC_L->WPR = 0x53;
        RTC_L->CR &= ~COE;
        // in our case, we have a positive 265.625 ppm error
        // so CALP = 0, CALM = 265.625 / 0.954 = 279 int
        RTC_L->CALR |= 279;

        RTC_L->WPR = 0xFF;
    }
}

void rtc_test(void) {
    rtc_init();
    rtc_calibrate(1);

    rtc_calibrate(0);

    // while (1) {
    //     delay(1000);
    //     present_time = rtc_read();
    // }
}

