//
// Created by Arcana on 26/10/26.
//
// Returns temperature in DegC, resolution is 0.01 DegC. Output value of “5123” equals 51.23 DegC.
// t_fine carries fine temperature as global value

#include "bmp280.h"
#include "../SPI/spi.h"
#include "../GPIO/gpio.h"
#include "../SYSTICK/systick.h"

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

static void bmp_select(void) {
    gpio_set(GPIOB, 6, 0);
}

static void bmp_deselect(void) {
    gpio_set(GPIOB, 6, 1);
}

static void bmp_read_burst(uint8_t addr, uint8_t *data, uint8_t length) {
    bmp_select();
    addr |= 0x80;
    spi_transmit(&addr, 1);
    for (uint8_t i = 0; i < length; ++i) {
        data[i] = spi(0xFF);
    }
    bmp_deselect();
}

void bmp_write(uint8_t addr, uint8_t data) {
    bmp_select();
    addr &= ~(0x80);    // clear the MSB to indicate write mode
    spi_transmit(&addr, 1);
    spi_transmit(&data, 1);
    bmp_deselect();
}

uint8_t bmp_read(uint8_t addr) {
    uint8_t data;
    bmp_select();
    addr |= (0x80);    // set the MSB to indicate read mode
    spi_transmit(&addr, 1);
    data = spi(0xFF);
    bmp_deselect();
    return data;
}


//////////        INIT FUNCTION        ////////////

void bmp_init(void) {
    gpio_init(GPIOB, 6, OUTPUT);
    bmp_deselect();
    delay(5);
    bmp_read(0xD0);

    uint8_t calib[24];
    bmp_read_burst(0x88, calib, sizeof(calib));
    dig_T1 = (uint16_t)calib[0] | ((uint16_t)calib[1] << 8);
    dig_T2 = (int16_t)((uint16_t)calib[2] | ((uint16_t)calib[3] << 8));
    dig_T3 = (int16_t)((uint16_t)calib[4] | ((uint16_t)calib[5] << 8));
    dig_P1 = (uint16_t)calib[6] | ((uint16_t)calib[7] << 8);
    dig_P2 = (int16_t)((uint16_t)calib[8] | ((uint16_t)calib[9] << 8));
    dig_P3 = (int16_t)((uint16_t)calib[10] | ((uint16_t)calib[11] << 8));
    dig_P4 = (int16_t)((uint16_t)calib[12] | ((uint16_t)calib[13] << 8));
    dig_P5 = (int16_t)((uint16_t)calib[14] | ((uint16_t)calib[15] << 8));
    dig_P6 = (int16_t)((uint16_t)calib[16] | ((uint16_t)calib[17] << 8));
    dig_P7 = (int16_t)((uint16_t)calib[18] | ((uint16_t)calib[19] << 8));
    dig_P8 = (int16_t)((uint16_t)calib[20] | ((uint16_t)calib[21] << 8));
    dig_P9 = (int16_t)((uint16_t)calib[22] | ((uint16_t)calib[23] << 8));

    // Config must be written while the sensor is in sleep mode.
    bmp_write(0xF5, BMP_CONFIG);
    bmp_write(0xF4, BMP_CTRL);
}

int32_t bmp_get(BMP_ReadType e) {
    uint8_t raw_p[3];
    bmp_read_burst(0xF7, raw_p, 3);

    BMP280_S32_t adc_P = ((BMP280_S32_t)raw_p[0] << 12) |
                         ((BMP280_S32_t)raw_p[1] << 4) | (raw_p[2] >> 4);

    uint8_t raw_t[3];
    bmp_read_burst(0xFA, raw_p, 3);
    BMP280_S32_t adc_T = ((BMP280_S32_t)raw_t[0] << 12) |
                         ((BMP280_S32_t)raw_t[1] << 4) | (raw_t[2] >> 4);

    BMP280_S32_t temperature = bmp280_compensate_T_int32(adc_T);

    if (e == Pressure) {
        return (int32_t)bmp280_compensate_P_int32(adc_P);
    }
    return (int32_t)temperature;
}

//////////        APPLICATION FUNCTION        ///////////

static void uart_print_uint(uint32_t value) {
    char digits[10];
    unsigned int count = 0;

    do {
        digits[count++] = (char)('0' + (value % 10U));
        value /= 10U;
    } while (value != 0U);

    while (count > 0U) {
        uart_write(digits[--count]);
    }
}

void bmp_print(void) {
    int32_t temperature = bmp_get(Temperature);
    uint32_t pressure = (uint32_t)bmp_get(Pressure);

    // Temperature is in hundredths of a degree Celsius.
    print("Temperature: ");
    if (temperature < 0) {
        uart_write('-');
        temperature = -temperature;
    }
    uart_print_uint((uint32_t)temperature / 100U);
    uart_write('.');
    uint32_t fraction = (uint32_t)temperature % 100U;
    if (fraction < 10U) {
        uart_write('0');
    }
    uart_print_uint(fraction);
    print(" C, Pressure: ");
    uart_print_uint(pressure);
    print(" Pa\r\n");
    // UART2 is configured for 9600 baud; allow about 40 ms for this line.
    // Combined with this wait, output is approximately every 250 ms.
    delay(140);
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
