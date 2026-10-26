//
// Created by Arcana on 26/10/26.
//
// Returns temperature in DegC, resolution is 0.01 DegC. Output value of “5123” equals 51.23 DegC.
// t_fine carries fine temperature as global value

#include "bmp280.h"
#include "../SPI/spi.h"
#include "../GPIO/gpio.h"

unsigned short dig_T1;
signed short dig_T2;
signed short dig_T3;
unsigned short dig_P1;
signed short dig_P2;
signed short dig_P3;
signed short dig_P4;
signed short dig_P5;
signed short dig_P6;
signed short dig_P7;
signed short dig_P8;
signed short dig_P9;

/// PB6 as the CS

//////////      DEFINE READ WRITE FOR BMP       ////////////

void bmp_write(uint8_t addr, uint8_t data) {
    gpio_set(GPIOB, 6, 0);
    addr &= ~(0x80);    // clear the MSB to indicate write mode
    spi_transmit(&addr, 1);
    spi_transmit(&data, 1);
}

uint8_t bmp_read(uint8_t addr) {
    gpio_set(GPIOB, 6, 0);
    addr |= (0x80);    // set the MSB to indicate read mode
    spi_transmit(&addr, 1);
    return spi(0xFF);
}

//////////        INIT FUNCTION        ////////////

void bmp_init(void) {
    gpio_init(GPIOB, 6, OUTPUT);
    gpio_set(GPIOB, 6, 0);

    dig_T1 = (uint16_t)bmp_read(0x88) | ((uint16_t)bmp_read(0x89) << 8);
    dig_T2 = (int16_t)((uint16_t)bmp_read(0x8A) | ((uint16_t)bmp_read(0x8B) << 8));
    dig_T3 = (int16_t)((uint16_t)bmp_read(0x8C) | ((uint16_t)bmp_read(0x8D) << 8));

    dig_P1 = (uint16_t)bmp_read(0x8E) | ((uint16_t)bmp_read(0x8F) << 8);
    dig_P2 = (int16_t)((uint16_t)bmp_read(0x90) | ((uint16_t)bmp_read(0x91) << 8));
    dig_P3 = (int16_t)((uint16_t)bmp_read(0x92) | ((uint16_t)bmp_read(0x93) << 8));
    dig_P4 = (int16_t)((uint16_t)bmp_read(0x94) | ((uint16_t)bmp_read(0x95) << 8));
    dig_P5 = (int16_t)((uint16_t)bmp_read(0x96) | ((uint16_t)bmp_read(0x97) << 8));
    dig_P6 = (int16_t)((uint16_t)bmp_read(0x98) | ((uint16_t)bmp_read(0x99) << 8));
    dig_P7 = (int16_t)((uint16_t)bmp_read(0x9A) | ((uint16_t)bmp_read(0x9B) << 8));
    dig_P8 = (int16_t)((uint16_t)bmp_read(0x9C) | ((uint16_t)bmp_read(0x9D) << 8));
    dig_P9 = (int16_t)((uint16_t)bmp_read(0x9E) | ((uint16_t)bmp_read(0x9F) << 8));

    bmp_write(0xF4, BMP_CTRL);
    bmp_write(0xF5, BMP_CONFIG);

    gpio_set(GPIOB, 6, 1);
}

void bmp_get(void) {
    
}




//////////        DATA CONVERSION      ////////////

BMP280_S32_t t_fine = 0;
BMP280_S32_t bmp280_compensate_T_int32(BMP280_S32_t adc_T)
{
    BMP280_S32_t var1, var2, T;
    var1 = ((((adc_T>>3) - ((BMP280_S32_t)dig_T1<<1))) * ((BMP280_S32_t)dig_T2)) >> 11;
    var2 = (((((adc_T>>4) - ((BMP280_S32_t)dig_T1)) * ((adc_T>>4) - ((BMP280_S32_t)dig_T1))) >> 12) *
    ((BMP280_S32_t)dig_T3)) >> 14;
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T;
}
// Returns pressure in Pa as unsigned 32 bit integer. Output value of “96386” equals 96386 Pa = 963.86 hPa
BMP280_U32_t bmp280_compensate_P_int32(BMP280_S32_t adc_P)
{
    BMP280_S32_t var1, var2;
    BMP280_U32_t p;
    var1 = (((BMP280_S32_t)t_fine)>>1) - (BMP280_S32_t)64000;
    var2 = (((var1>>2) * (var1>>2)) >> 11 ) * ((BMP280_S32_t)dig_P6);
    var2 = var2 + ((var1*((BMP280_S32_t)dig_P5))<<1);
    var2 = (var2>>2)+(((BMP280_S32_t)dig_P4)<<16);
    var1 = (((dig_P3 * (((var1>>2) * (var1>>2)) >> 13 )) >> 3) + ((((BMP280_S32_t)dig_P2) * var1)>>1))>>18;
    var1 =((((32768+var1))*((BMP280_S32_t)dig_P1))>>15);
    if (var1 == 0)
    {
        return 0; // avoid exception caused by division by zero
    }
    p = (((BMP280_U32_t)(((BMP280_S32_t)1048576)-adc_P)-(var2>>12)))*3125;
    if (p < 0x80000000)
    {
        p = (p << 1) / ((BMP280_U32_t)var1);
    }
    else
    {
        p = (p / (BMP280_U32_t)var1) * 2;
    }
    var1 = (((BMP280_S32_t)dig_P9) * ((BMP280_S32_t)(((p>>3) * (p>>3))>>13)))>>12;
    var2 = (((BMP280_S32_t)(p>>2)) * ((BMP280_S32_t)dig_P8))>>13;
    p = (BMP280_U32_t)((BMP280_S32_t)p + ((var1 + var2 + dig_P7) >> 4));
    return p;
}
