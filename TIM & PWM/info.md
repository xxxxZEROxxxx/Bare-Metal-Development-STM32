# TIM and PWM

STM32 timers are hardware counters. They count clock ticks for you, without the
CPU manually looping.

Timers are used for:

- running code every fixed time interval
- generating PWM
- measuring pulse width or signal frequency
- input capture and output compare
- encoder reading

## Timer vs SysTick

`SysTick` is a simple timer inside the ARM Cortex-M core. It is useful for OS
ticks and simple delays.

`TIMx` timers are STM32 peripherals. They are better for PWM, input capture,
output compare, motor control, and precise hardware-driven timing.

## Timer Types

On STM32F401, common timer groups are:

| Type | Example | Main use |
| --- | --- | --- |
| Advanced timer | `TIM1` | PWM with extra motor-control features |
| General-purpose timers | `TIM2`, `TIM3`, `TIM4`, `TIM5` | delays, interrupts, PWM, capture/compare |
| Basic idea only | all `TIMx` | a counter driven by a clock |

General-purpose timers can usually:

- count up, down, or center-aligned
- use a prescaler
- generate update interrupts
- generate PWM
- compare `CNT` against `CCR`
- capture input signal timing

`TIM1` is an advanced timer. It adds features such as:

- complementary PWM outputs
- dead-time insertion
- break input for emergency shutdown
- repetition counter

For normal LED dimming or basic PWM, a general-purpose timer is enough.

## Core Mechanism

The timer receives a timer clock:

```text
TIM clock -> prescaler -> counter CNT
```

The important registers are:

| Register | Meaning |
| --- | --- |
| `PSC` | Prescaler. Slows down the timer clock. |
| `CNT` | Current counter value. |
| `ARR` | Auto-reload value. The counter period limit. |
| `CCR1..CCR4` | Capture/compare value for each channel. Used for PWM duty. |
| `SR` | Status register. Contains flags such as `UIF`. |
| `DIER` | Interrupt/DMA enable register. |
| `CCMRx` | Capture/compare mode register. Selects PWM mode, compare mode, etc. |
| `CCER` | Capture/compare enable register. Enables output channels. |
| `CR1` | Control register. Enables the counter and selects count mode. |
| `EGR` | Event generation register. Can force an update event. |

## Update Event

In up-counting mode, the timer counts like this:

```text
0, 1, 2, 3, ... ARR
```

When `CNT` reaches `ARR`, the timer overflows and creates an **update event**
called `UEV`.

On an update event:

- `CNT` goes back to `0`
- the `UIF` flag is set in `TIMx_SR`
- an interrupt can happen if enabled in `TIMx_DIER`
- a DMA request can happen if enabled

So the basic timer interrupt mechanism is:

```text
clock ticks -> CNT counts -> CNT reaches ARR -> UEV -> UIF flag -> interrupt
```

## Timer Frequency Formula

The update event frequency is:

```text
update frequency = TIM_CLK / ((PSC + 1) * (ARR + 1))
```

Where:

- `TIM_CLK` is the clock feeding the timer
- `PSC` is the prescaler register value
- `ARR` is the auto-reload register value

The `+1` exists because the counter includes zero.

Example:

```text
TIM_CLK = 16 MHz
PSC     = 15999
ARR     = 999

update frequency = 16,000,000 / ((15999 + 1) * (999 + 1))
                 = 16,000,000 / (16,000 * 1,000)
                 = 1 Hz
```

That means one update event every second.

## Timer Clock Note

Timer clock is not always exactly the same as CPU clock.

Usually:

- timers on `APB1` use the APB1 timer clock
- timers on `APB2` use the APB2 timer clock
- if the APB prescaler is not `1`, STM32 timers often receive `2 * APB clock`

So before calculating `PSC` and `ARR`, check the RCC clock tree.

## PWM Mechanism

PWM means **pulse-width modulation**.

PWM creates a square wave where:

- frequency says how often the wave repeats
- duty cycle says how long the output stays high during each cycle

For PWM, the timer still counts from `0` to `ARR`.

The compare register `CCR` decides when the output changes state.

In common PWM mode 1:

```text
output is HIGH while CNT < CCR
output is LOW  while CNT >= CCR
```

Example with `ARR = 9` and `CCR = 3`:

```text
CNT:     0 1 2 3 4 5 6 7 8 9
output:  H H H L L L L L L L
```

The timer then resets to `0` and repeats.

## PWM Frequency

PWM frequency uses the same formula as update frequency:

```text
PWM frequency = TIM_CLK / ((PSC + 1) * (ARR + 1))
```

`ARR` controls the PWM period.

Larger `ARR` means:

- lower PWM frequency
- more duty-cycle resolution

Smaller `ARR` means:

- higher PWM frequency
- less duty-cycle resolution

## PWM Duty Cycle

For PWM mode 1:

```text
duty cycle = CCR / (ARR + 1)
```

Examples with `ARR = 999`:

| Duty | `CCR` value | Meaning |
| --- | --- | --- |
| 0% | `0` | always low |
| 25% | `250` | high for 25% of the period |
| 50% | `500` | high for 50% of the period |
| 75% | `750` | high for 75% of the period |
| 100% | `1000` | always high |

So:

```text
CCR = duty * (ARR + 1)
```

For 50% duty:

```text
CCR = 0.5 * (999 + 1)
CCR = 500
```

## PWM Setup Flow

To output PWM on a pin:

1. Enable the GPIO port clock.
2. Put the GPIO pin into alternate-function mode.
3. Select the correct alternate function number for that timer channel.
4. Enable the timer clock in RCC.
5. Set `PSC` for the timer tick speed.
6. Set `ARR` for the PWM period.
7. Set `CCR` for the duty cycle.
8. Configure the timer channel as PWM mode.
9. Enable the timer output channel in `CCER`.
10. Enable the timer counter in `CR1`.

Mental model:

```text
GPIO pin does not create PWM.
The timer creates PWM.
The GPIO pin only connects the timer output to the outside world.
```
1. the pwm mode is selected in the OCxM bits in the TIMx_CCMRx register
2. The user must enable the corresponding preload register by setting the 
OCxPE bit in the TIMx_CCMRx register, 
3. and eventually the auto-reload preload register
by setting the ARPE bit in the TIMx_CR1 register.
4. OCx output is enabled by the CCxE bit in the TIMx_CCER register.
OCx polarity is software programmable using the CCxP bit in the TIMx_CCER register.
5. e

## Interrupt Setup Flow

To run code periodically from a timer:

1. Enable the timer clock in RCC.
2. Set `PSC`.
3. Set `ARR`.
4. Enable update interrupt in `DIER`.
5. Enable the timer interrupt in NVIC.
6. Enable the counter in `CR1`.
7. In the interrupt handler, check and clear `UIF`.

The handler must clear the flag, otherwise the interrupt will keep firing:

```c
if (TIMx->SR & (1U << 0)) {   // UIF
    TIMx->SR &= ~(1U << 0);   // clear UIF
    // your periodic code here
}
```

## What To Remember

The timer has two important comparisons:

```text
CNT reaches ARR -> period ends -> update event
CNT reaches CCR -> output compare event -> PWM output changes
```

For basic timing:

```text
PSC + ARR decide how often the timer overflows.
```

For PWM:

```text
PSC + ARR decide frequency.
CCR decides duty cycle.
```
