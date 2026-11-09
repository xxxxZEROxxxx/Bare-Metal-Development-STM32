# MPU6500 portable high-performance SPI driver

`mpu6500.c` is a register-level, allocation-free MPU-6500 driver. Its core has no STM32/CMSIS dependency: port it by supplying three callbacks in `MPU6500_Bus` (`transfer`, `chip_select`, and optionally `delay_ms`). Each callback works in task, interrupt, or bare-metal polling contexts as long as the underlying SPI bus is serialized by the application. Compile without `MPU6500_ENABLE_STM32F401_TEST=1` to omit the STM32 demonstration adapter completely.

The driver has a fixed-cost fast path: one 14-byte SPI burst produces coherent acceleration, temperature, and gyro data. The enabled FIFO uses the same 14-byte record, avoiding individual register transactions and preserving sample timing. Floating-point conversion occurs only after the burst; raw data is also available for fixed-point applications.

## Included features

- MPU-6500 reset sequence required by the datasheet for SPI, `WHO_AM_I` validation, PLL clock selection, and configurable accelerometer/gyro full scales.
- Configurable digital low-pass filters and sample divider (the standard setup uses the valid 1 kHz internal rate divided to **20 Hz**).
- Coherent direct reads and physical units: acceleration in `g`, gyro in `deg/s`, and temperature in `°C` (`raw / 333.87 + 21`).
- FIFO enable/reset/count/read, overflow recovery, raw-data/FIFO-overflow/motion interrupt setup, gyro offset read/write and stationary gyro calibration.
- Sleep and per-axis standby control, plus low-power wake-on-motion (`MPU6500_EnableWakeOnMotion`).
- Generic `MPU6500_ReadRegisters` / `MPU6500_WriteRegisters` access for every MPU6500 register. The MPU6500 acting as an I2C master is intentionally not wrapped, as requested; do not enable `I2C_MST_EN` when SPI is used.

The DMP is not loaded or enabled: it needs a separately licensed/board-specific firmware image. The public register access APIs still permit an application that owns such firmware to load it.

## STM32F401CCU6 quick start

The included demo assumes the existing project wiring:

| Signal | STM32F401 pin |
| --- | --- |
| SPI1 SCK / MISO / MOSI | PB3 / PB4 / PB5 |
| MPU6500 CS | PB6 |
| UART2 TX | PA2 |

`main.c` already calls:

```c
MPU6500_Test();
```

It initializes SPI/UART and continuously writes temperature, X/Y/Z acceleration, and X/Y/Z gyro to UART2 at 20 Hz. It intentionally does not return. Remove the call if another application owns the peripherals. SPI is already configured by this project for mode 3, which the MPU6500 supports. Connect MPU `INT` to an MCU interrupt-capable GPIO only if you use interrupt-driven sampling; the demo polls the FIFO.

## General-MCU integration

```c
static uint8_t xfer(void *user, uint8_t tx) { return board_spi_exchange(tx); }
static void cs(void *user, bool asserted) { board_mpu_cs(!asserted); }
static void wait(void *user, uint32_t ms) { board_delay_ms(ms); }

MPU6500_Device imu;
MPU6500_Bus bus = { xfer, cs, wait, NULL };
if (MPU6500_Init(&imu, &bus) == MPU6500_OK) {
    MPU6500_Sample sample;
    if (MPU6500_FIFOReadSample(&imu, &sample) == MPU6500_OK) {
        /* sample.accel_g[], sample.gyro_dps[], sample.temperature_c */
    }
}
```

Call `MPU6500_FIFOReadSample()` at least once per FIFO-depth interval (1024 / 14 / 20, about 3.6 seconds). For freshest data when the consumer falls behind, drain all complete frames and retain the last one. If it returns `MPU6500_E_OVERFLOW`, the driver has reset and re-enabled the FIFO; continue reading on the next period.

## Motion wake and calibration

Keep the board still and call `MPU6500_CalibrateGyro(&imu, 200, &bias)` after normal initialization to write averaged gyro offsets. To enter accelerometer-only motion wake, call `MPU6500_EnableWakeOnMotion(&imu, threshold_mg, odr_code)`; use an MCU GPIO interrupt and inspect `MPU6500_GetInterruptStatus()`. `threshold_mg` is the MPU6500 wake-threshold register value and `odr_code` is the MPU6500 `LP_ACCEL_ODR` encoding from the datasheet. Call `MPU6500_DisableWakeOnMotion()` before resuming normal FIFO streaming, then reconfigure/enable FIFO.

See `mpu6500.h` for all APIs and the supplied MPU-6500 datasheet and register map in this directory for electrical limits, exact interrupt polarity/latch behavior, self-test procedure, and low-power ODR codes.
