# ADC BusFault Report

## Summary

The firmware enters the default fault handler when the ADC result reaches an
exact zero reading. The original investigation focused on `main()` formatting
the ADC result with:

```c++
snprintf(voltage_buffer, sizeof(voltage_buffer), "%.5f V\n", decimal);
```

The fault was observed while adjusting the potentiometer and appears when the
displayed result reaches approximately `0.0000 V`.

An ADC value of zero is valid and should not directly create an invalid memory
address. The current evidence points more strongly to an ADC-specific
condition or to code that runs after the ADC result becomes zero. The ADC
status flags, conversion mode, data-register handling, and exact faulting PC
must be checked before assigning the fault to `snprintf()`.

## Observed fault behavior

The processor reports a BusFault with these status bits set:

- `PRECISERR`: a precise data bus access fault occurred.
- `BFARVALID`: `SCB->BFAR` contains the address involved in the fault.

The debugger may show `WWDG_IRQHandler`. That name is misleading in this
project. The startup file weakly aliases many handlers, including
`BusFault_Handler`, `ADC_IRQHandler`, and `WWDG_IRQHandler`, to the same
`Default_Handler` address. The displayed symbol does not prove that the window
watchdog caused the fault.

The relevant startup aliases are in:

```text
startup_stm32f401xc.s
```

## Current `main()` call sequence

The current application performs this sequence:

```c++
int main(void)
{
    SCB->SHCSR |= (1 << 16) | (1 << 17) | (1 << 18);
    init_uart();
    fpu_init();
    adc_init();
    print("start\n");

    char voltage_buffer[15] = {};

    while (1) {
        decimal = adc_sample();
        snprintf(voltage_buffer, sizeof(voltage_buffer), "%.5f V\n", decimal);
        print(voltage_buffer);
        delay(40);
    }
}
```

The suspected path is:

```text
main()
  -> adc_sample()
       -> start ADC conversion
       -> wait for EOC
       -> read ADC1->DR
       -> calculate and return float voltage
  -> snprintf(..., "%.5f", decimal)
  -> print(voltage_buffer)
  -> BusFault
```

The ADC peripheral read itself is performed here:

```c++
int adc_value_raw = ADC1->DR;
```

This is a valid ADC1 data-register access. The exact faulting instruction still
needs to be confirmed with the stacked PC. If the PC points into the ADC
register access, ADC status/configuration is the cause. If it points into
`snprintf()` or `print()`, the fault is in the result-handling path.

## Why `snprintf()` can cause this on the target

`snprintf()` with `%f` is expensive on a small bare-metal target. It pulls in
newlib's floating-point formatting code, including internal conversion and
buffer-management routines. These routines use substantially more code,
stack, and runtime support than the ADC calculation itself.

The project is linked with:

```text
--specs=nosys.specs
```

and uses a custom startup and linker setup. That environment does not provide
the normal hosted C runtime. Floating-point formatting can therefore expose
runtime or stack limitations that are not visible when the same code runs on a
desktop computer.

The linker currently reserves:

```ld
_Min_Stack_Size = 0x400;
```

The formatting routine can use enough stack to make this limit relevant. A
precise bus fault occurs when a stack or data access reaches an invalid address;
`BFARVALID` then makes the fault address available in `SCB->BFAR`. However,
zero is valid `%f` input, so this section remains a secondary hypothesis until
the stacked PC confirms it.

## Recommended ADC checks and fixes

### Use single-conversion mode

The current initialization contains:

```c
ADC1->CR2 |= CR2_CONT; // SET CONT TO 0
```

This enables continuous conversion. For one conversion per call, clear the
bit instead:

```c
ADC1->CR2 &= ~CR2_CONT;
```

Also clear the sequence fields before assigning them:

```c
ADC1->SQR1 &= ~(0xFU << 20);
ADC1->SQR3 &= ~0x1FU;
ADC1->SQR3 |= 1U;
```

### Inspect ADC status when the result is zero

Capture the ADC status before reading the data register:

```c
uint32_t adc_status = ADC1->SR;
uint16_t adc_value_raw = (uint16_t)ADC1->DR;
```

Check whether `EOC`, `OVR`, or `AWD` is set. A zero conversion result is
normal; an unexpected `OVR` or analog-watchdog condition indicates an ADC
configuration or status-handling problem.

### Test the zero path without formatting

Temporarily bypass both floating-point formatting and UART output:

```c
uint16_t raw = adc_sample_raw();

if (raw == 0U) {
    while (1) {
    }
}
```

If the debugger stops in this loop without a fault, the ADC read completed and
the fault is caused by code after the ADC read. If it still enters the fault
handler, inspect the ADC access and the stacked PC.

### Avoid floating-point formatting in the final firmware

Do not format floating-point values with `snprintf()` on the MCU. Keep the ADC
conversion as an integer and convert it to millivolts:

```c++
uint16_t adc_sample_raw(void)
{
    ADC1->CR2 |= SWSTART;

    while ((ADC1->SR & EOC) == 0) {
    }

    return (uint16_t)ADC1->DR;
}
```

Then use:

```c++
uint16_t raw = adc_sample_raw();
uint32_t millivolts = ((uint32_t)raw * 3400U) / 4095U;
```

The value can be printed with a small integer-to-decimal function, for example:

```c++
void print_uint32(uint32_t value)
{
    char buffer[11];
    char reversed[11];
    uint32_t i = 0;
    uint32_t j;

    if (value == 0) {
        print("0");
        return;
    }

    while (value != 0) {
        reversed[i++] = (char)('0' + (value % 10U));
        value /= 10U;
    }

    j = 0;
    while (i != 0) {
        buffer[j++] = reversed[--i];
    }
    buffer[j] = '\0';
    print(buffer);
}
```

For a simple voltage report:

```c++
uint16_t raw = adc_sample_raw();
uint32_t millivolts = ((uint32_t)raw * 3400U) / 4095U;

print("ADC: ");
print_uint32(millivolts / 1000U);
print(".");
print_uint32(millivolts % 1000U);
print(" V\n");
```

## Diagnostic information to capture

If the fault needs to be investigated further, record these registers in the
BusFault handler:

```c++
volatile uint32_t fault_cfsr;
volatile uint32_t fault_hfsr;
volatile uint32_t fault_bfar;

void BusFault_Handler(void)
{
    fault_cfsr = SCB->CFSR;
    fault_hfsr = SCB->HFSR;
    fault_bfar = SCB->BFAR;

    while (1) {
    }
}
```

The most useful values are:

- `SCB->CFSR`: identifies the precise BusFault bits.
- `SCB->BFAR`: identifies the accessed address when `BFARVALID` is set.
- The stacked PC: identifies the exact instruction that faulted.

If the stacked PC points inside `snprintf()`, `_svfprintf_r()`, or `_dtoa_r()`,
the floating-point formatting path is confirmed as the faulting operation.

## Conclusion

The updated observation shows that the fault is correlated with an exact ADC
zero result. A zero ADC result is legal, so the report should currently treat
the ADC conversion/status path as the primary suspect and `snprintf()` as a
secondary suspect. The decisive evidence is the stacked PC together with
`SCB->BFAR`: the PC identifies the faulting instruction and `BFAR` identifies
the address that instruction accessed.

Regardless of the final fault location, the firmware should clear continuous
mode for single conversions and use integer millivolt conversion instead of
`snprintf("%f")` on the target.
