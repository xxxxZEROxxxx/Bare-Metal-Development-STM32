//
// Created by Arcana on 26/10/26.
//

#ifndef FLASH_PROGRAMMER_BMP280_H
#define FLASH_PROGRAMMER_BMP280_H

#include <stdint.h>
#define BMP280_S32_t signed int
#define BMP280_U32_t unsigned int

///       [7:5]        [4:2]        [1:0]
///     temperature   pressure      mode
///
///     temp and pressure   size in xlsb    |   mode
///   000 : skipped                         |   00 : sleep
///   001 : x1                16bit         |   01, 10 : forced mode
///   010 : x2                17bit         |   11 : normal mode
///   011 : x4                18bit
///   100 : x8                19bit
///   101,110,111 : x16       20bit
#define BMP_CTRL 0b00100111 // 1 x temp, 1 x pressure
///         [7:5]         [4:2]      [1]     [0]
///      time_interval    filter     N     SPI3_EN
///
///   time : (ms)
///    000 : 0.5
///    001 : 62.5
///    010 : 125
///    011 : 250
///    100 : 500
///    101 : 1000
///    110 : 2000
///    111 : 4000
#define BMP_CONFIG 0b01100000

// status register 0xF3 : measuring
#define BMP_MEASURE  (1UL << 3)

// status register 0xF3 : im_update
#define BMP_UPDATE  (1UL << 0)



typedef enum {
    Temperature = 0,
    Pressure = 1,
}BMP_ReadType;





// Temperature is returned in 0.01 degC; pressure is returned in Pa.
int32_t bmp_get(BMP_ReadType);
BMP280_S32_t bmp280_compensate_T_int32(BMP280_S32_t adc_T);
BMP280_U32_t bmp280_compensate_P_int32(BMP280_S32_t adc_P);
void bmp_write(uint8_t addr, uint8_t data);
uint8_t bmp_read(uint8_t addr);
void bmp_init(void);


#endif //FLASH_PROGRAMMER_BMP280_H
