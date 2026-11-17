//
// Created by Arcana on 16/11/26.
//

#ifndef FLASH_PROGRAMMER_RTC_H
#define FLASH_PROGRAMMER_RTC_H
#include <stdint.h>

#define bit(x)      (1UL << x)

#define DBP         bit(8)
#define INIT        bit(7)
#define INITF       bit(6)
#define FMT         bit(6)
#define RSF         bit(5)      // RTC_ISR: shadow registers synchronised


#define RCC_APB1ENR_L (*(volatile uint32_t *)0x40023840)


#define RCC_BDCR_L  (*(volatile uint32_t *)(0x40023870))
#define LSERDY      bit(1)
#define LSEON       bit(0)
#define RTCSEL      bit(8) // select LSE as RTC clock
#define RTC_EN      bit(15) // enable RTC

#define COE         bit(23)
#define OSEL_MASK   (3UL << 21)
#define COSEL       bit(19)

void rtc_calib_out(int one_hz);
void rtc_calib_out_off(void);

// time structure
typedef struct {
    short YEAR;
    short MONTH;
    short DAY;
    short WEEK;
    short HOUR;
    short MINUTE;
    short SECOND;
}TIME_RAW_TypeDef;

typedef struct {
    uint32_t TR; // time
    uint32_t DR; // date
}TIME_FIN_TypeDef;

void rtc_init(void);
void rtc_test(void);
TIME_FIN_TypeDef time_convert(TIME_RAW_TypeDef);
TIME_RAW_TypeDef rtc_read(void);
void rtc_calibrate(short stage);





typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CSR;
}PWR_TypeDef_L;
#define PWR_BASE_L 0x40007000
#define PWR_L ((PWR_TypeDef_L*) PWR_BASE_L)

// structure of RTC

typedef struct
{
  volatile uint32_t TR;      /*!< RTC time register,                                        Address offset: 0x00 */
  volatile uint32_t DR;      /*!< RTC date register,                                        Address offset: 0x04 */
  volatile uint32_t CR;      /*!< RTC control register,                                     Address offset: 0x08 */
  volatile uint32_t ISR;     /*!< RTC initialization and status register,                   Address offset: 0x0C */
  volatile uint32_t PRER;    /*!< RTC prescaler register,                                   Address offset: 0x10 */
  volatile uint32_t WUTR;    /*!< RTC wakeup timer register,                                Address offset: 0x14 */
  volatile uint32_t CALIBR;  /*!< RTC calibration register,                                 Address offset: 0x18 */
  volatile uint32_t ALRMAR;  /*!< RTC alarm A register,                                     Address offset: 0x1C */
  volatile uint32_t ALRMBR;  /*!< RTC alarm B register,                                     Address offset: 0x20 */
  volatile uint32_t WPR;     /*!< RTC write protection register,                            Address offset: 0x24 */
  volatile uint32_t SSR;     /*!< RTC sub second register,                                  Address offset: 0x28 */
  volatile uint32_t SHIFTR;  /*!< RTC shift control register,                               Address offset: 0x2C */
  volatile uint32_t TSTR;    /*!< RTC time stamp time register,                             Address offset: 0x30 */
  volatile uint32_t TSDR;    /*!< RTC time stamp date register,                             Address offset: 0x34 */
  volatile uint32_t TSSSR;   /*!< RTC time-stamp sub second register,                       Address offset: 0x38 */
  volatile uint32_t CALR;    /*!< RTC calibration register,                                 Address offset: 0x3C */
  volatile uint32_t TAFCR;   /*!< RTC tamper and alternate function configuration register, Address offset: 0x40 */
  volatile uint32_t ALRMASSR;/*!< RTC alarm A sub second register,                          Address offset: 0x44 */
  volatile uint32_t ALRMBSSR;/*!< RTC alarm B sub second register,                          Address offset: 0x48 */
  uint32_t RESERVED7;    /*!< Reserved, 0x4C                                                                 */
  volatile uint32_t BKP0R;   /*!< RTC backup register 1,                                    Address offset: 0x50 */
  volatile uint32_t BKP1R;   /*!< RTC backup register 1,                                    Address offset: 0x54 */
  volatile uint32_t BKP2R;   /*!< RTC backup register 2,                                    Address offset: 0x58 */
  volatile uint32_t BKP3R;   /*!< RTC backup register 3,                                    Address offset: 0x5C */
  volatile uint32_t BKP4R;   /*!< RTC backup register 4,                                    Address offset: 0x60 */
  volatile uint32_t BKP5R;   /*!< RTC backup register 5,                                    Address offset: 0x64 */
  volatile uint32_t BKP6R;   /*!< RTC backup register 6,                                    Address offset: 0x68 */
  volatile uint32_t BKP7R;   /*!< RTC backup register 7,                                    Address offset: 0x6C */
  volatile uint32_t BKP8R;   /*!< RTC backup register 8,                                    Address offset: 0x70 */
  volatile uint32_t BKP9R;   /*!< RTC backup register 9,                                    Address offset: 0x74 */
  volatile uint32_t BKP10R;  /*!< RTC backup register 10,                                   Address offset: 0x78 */
  volatile uint32_t BKP11R;  /*!< RTC backup register 11,                                   Address offset: 0x7C */
  volatile uint32_t BKP12R;  /*!< RTC backup register 12,                                   Address offset: 0x80 */
  volatile uint32_t BKP13R;  /*!< RTC backup register 13,                                   Address offset: 0x84 */
  volatile uint32_t BKP14R;  /*!< RTC backup register 14,                                   Address offset: 0x88 */
  volatile uint32_t BKP15R;  /*!< RTC backup register 15,                                   Address offset: 0x8C */
  volatile uint32_t BKP16R;  /*!< RTC backup register 16,                                   Address offset: 0x90 */
  volatile uint32_t BKP17R;  /*!< RTC backup register 17,                                   Address offset: 0x94 */
  volatile uint32_t BKP18R;  /*!< RTC backup register 18,                                   Address offset: 0x98 */
  volatile uint32_t BKP19R;  /*!< RTC backup register 19,                                   Address offset: 0x9C */
} RTC_TypeDef_LT;
#define RTC_BASE_L 0x40002800
#define RTC_L ((RTC_TypeDef_LT*) RTC_BASE_L)


#endif //FLASH_PROGRAMMER_RTC_H