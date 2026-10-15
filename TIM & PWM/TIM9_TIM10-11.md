# STM32F401 TIM9–TIM11 General-Purpose Timer Register Reference

> Source: STMicroelectronics RM0368 Rev. 6, Sections 14.4–14.5, “TIM9” and “TIM10/11 registers” (printed pages 398–419). Register headings and order follow the manual. Descriptions are based on the register subsections, not a generic timer template.

This file covers the **general-purpose timers TIM9, TIM10 and TIM11** in RM0368 Chapter 14. TIM9 has two capture/compare channels and a slave-mode controller; TIM10 and TIM11 have one capture/compare channel, and TIM11 additionally has the `TIM11_OR` option register. The exact differences are kept separate below.

## Register navigation

### TIM9

| Offset | Register | Full name | Main job |
|---:|---|---|---|
| `0x00` | [`CR1`](#1441-tim9-control-register-1-timx_cr1) | Control register 1 | Enables the counter and controls basic count behavior. |
| `0x08` | [`SMCR`](#1442-tim9-slave-mode-control-register-timx_smcr) | Slave mode control register | Selects trigger, slave, gated, or encoder-style behavior. |
| `0x0C` | [`DIER`](#1443-tim9-interrupt-enable-register-timx_dier) | Interrupt enable register | Enables update, capture/compare, and trigger interrupts. |
| `0x10` | [`SR`](#1444-tim9-status-register-timx_sr) | Status register | Holds update, capture/compare, trigger, and overcapture flags. |
| `0x14` | [`EGR`](#1445-tim9-event-generation-register-timx_egr) | Event generation register | Lets software force update, capture/compare, or trigger events. |
| `0x18` | [`CCMR1`](#1446-tim9-capturecompare-mode-register-1-timx_ccmr1) | Capture/compare mode register 1 | Configures channel 1 and channel 2 mode. |
| `0x20` | [`CCER`](#1447-tim9-capturecompare-enable-register-timx_ccer) | Capture/compare enable register | Enables channels and selects polarity. |
| `0x24` | [`CNT`](#1448-tim9-counter-timx_cnt) | Counter register | Stores the current timer count value. |
| `0x28` | [`PSC`](#1449-tim9-prescaler-timx_psc) | Prescaler | Divides the timer clock before it reaches `CNT`. |
| `0x2C` | [`ARR`](#14410-tim9-auto-reload-register-timx_arr) | Auto-reload register | Sets the period limit. |
| `0x34` | [`CCR1`](#14411-tim9-capturecompare-register-1-timx_ccr1) | Capture/compare register 1 | Channel 1 compare value or captured input value. |
| `0x38` | [`CCR2`](#14412-tim9-capturecompare-register-2-timx_ccr2) | Capture/compare register 2 | Channel 2 compare value or captured input value. |

### TIM10/TIM11

| Offset | Register | Full name | Main job |
|---:|---|---|---|
| `0x00` | [`CR1`](#1451-tim1011-control-register-1-timx_cr1) | Control register 1 | Enables the counter and controls basic count behavior. |
| `0x0C` | [`DIER`](#1452-tim1011-interrupt-enable-register-timx_dier) | Interrupt enable register | Enables update and capture/compare interrupts. |
| `0x10` | [`SR`](#1453-tim-status-register-timx_sr) | Status register | Holds update, capture/compare, and overcapture flags. |
| `0x14` | [`EGR`](#1454-tim-event-generation-register-timx_egr) | Event generation register | Lets software force update or capture/compare events. |
| `0x18` | [`CCMR1`](#1455-tim1011-capturecompare-mode-register-1-timx_ccmr1) | Capture/compare mode register 1 | Configures channel 1 mode. |
| `0x20` | [`CCER`](#1456-tim1011-capturecompare-enable-register-timx_ccer) | Capture/compare enable register | Enables channel 1 and selects polarity. |
| `0x24` | [`CNT`](#1457-tim1011-counter-timx_cnt) | Counter register | Stores the current timer count value. |
| `0x28` | [`PSC`](#1458-tim1011-prescaler-timx_psc) | Prescaler | Divides the timer clock before it reaches `CNT`. |
| `0x2C` | [`ARR`](#1459-tim1011-auto-reload-register-timx_arr) | Auto-reload register | Sets the period limit. |
| `0x34` | [`CCR1`](#14510-tim1011-capturecompare-register-1-timx_ccr1) | Capture/compare register 1 | Channel 1 compare value or captured input value. |
| `0x50` | [`OR`](#14511-tim11-option-register-1-tim11_or) | Option register | TIM11 input remap options. |

## Register structure

The structure is shown in the `__IO uint32_t` style used by STM32 CMSIS headers. Reserved members preserve the offsets where a timer does not implement a register. Verify the device header for the exact MCU variant before using the structure for memory-mapped access.

<pre><code class="language-c">
typedef struct
{
    __IO uint32_t <a href="#1441-tim9-control-register-1-timx_cr1">CR1</a>;          /*!< TIM9 control register 1,              Address offset: 0x00 */
    uint32_t RESERVED0;         /*!< Reserved address space,               Address offset: 0x04 */
    __IO uint32_t <a href="#1442-tim9-slave-mode-control-register-timx_smcr">SMCR</a>;         /*!< TIM9 slave mode control register,     Address offset: 0x08 */
    __IO uint32_t <a href="#1443-tim9-interrupt-enable-register-timx_dier">DIER</a>;         /*!< TIM9 interrupt enable register,       Address offset: 0x0C */
    __IO uint32_t <a href="#1444-tim9-status-register-timx_sr">SR</a>;           /*!< TIM9 status register,                 Address offset: 0x10 */
    __IO uint32_t <a href="#1445-tim9-event-generation-register-timx_egr">EGR</a>;          /*!< TIM9 event generation register,       Address offset: 0x14 */
    __IO uint32_t <a href="#1446-tim9-capturecompare-mode-register-1-timx_ccmr1">CCMR1</a>;        /*!< TIM9 capture/compare mode register 1, Address offset: 0x18 */
    uint32_t RESERVED1;         /*!< Reserved address space,               Address offset: 0x1C */
    __IO uint32_t <a href="#1447-tim9-capturecompare-enable-register-timx_ccer">CCER</a>;         /*!< TIM9 capture/compare enable register, Address offset: 0x20 */
    __IO uint32_t <a href="#1448-tim9-counter-timx_cnt">CNT</a>;          /*!< TIM9 counter register,                Address offset: 0x24 */
    __IO uint32_t <a href="#1449-tim9-prescaler-timx_psc">PSC</a>;          /*!< TIM9 prescaler,                       Address offset: 0x28 */
    __IO uint32_t <a href="#14410-tim9-auto-reload-register-timx_arr">ARR</a>;          /*!< TIM9 auto-reload register,            Address offset: 0x2C */
    uint32_t RESERVED2;         /*!< Reserved address space,               Address offset: 0x30 */
    __IO uint32_t <a href="#14411-tim9-capturecompare-register-1-timx_ccr1">CCR1</a>;         /*!< TIM9 capture/compare register 1,      Address offset: 0x34 */
    __IO uint32_t <a href="#14412-tim9-capturecompare-register-2-timx_ccr2">CCR2</a>;         /*!< TIM9 capture/compare register 2,      Address offset: 0x38 */
} TIM9_TypeDef;

/* TIM10 and TIM11 share the following one-channel register layout. */
typedef struct
{
    __IO uint32_t <a href="#1451-tim1011-control-register-1-timx_cr1">CR1</a>;          /*!< TIM10/11 control register 1,          Address offset: 0x00 */
    uint32_t RESERVED0;         /*!< Reserved address space,               Address offset: 0x04 */
    uint32_t RESERVED1;         /*!< No SMCR register described here,      Address offset: 0x08 */
    __IO uint32_t <a href="#1452-tim1011-interrupt-enable-register-timx_dier">DIER</a>;         /*!< TIM10/11 interrupt enable register,   Address offset: 0x0C */
    __IO uint32_t <a href="#1453-tim-status-register-timx_sr">SR</a>;           /*!< TIM10/11 status register,             Address offset: 0x10 */
    __IO uint32_t <a href="#1454-tim-event-generation-register-timx_egr">EGR</a>;          /*!< TIM10/11 event generation register,   Address offset: 0x14 */
    __IO uint32_t <a href="#1455-tim1011-capturecompare-mode-register-1-timx_ccmr1">CCMR1</a>;        /*!< TIM10/11 capture/compare mode reg. 1, Address offset: 0x18 */
    uint32_t RESERVED2;         /*!< Reserved address space,               Address offset: 0x1C */
    __IO uint32_t <a href="#1456-tim1011-capturecompare-enable-register-timx_ccer">CCER</a>;         /*!< TIM10/11 capture/compare enable reg., Address offset: 0x20 */
    __IO uint32_t <a href="#1457-tim1011-counter-timx_cnt">CNT</a>;          /*!< TIM10/11 counter register,            Address offset: 0x24 */
    __IO uint32_t <a href="#1458-tim1011-prescaler-timx_psc">PSC</a>;          /*!< TIM10/11 prescaler,                   Address offset: 0x28 */
    __IO uint32_t <a href="#1459-tim1011-auto-reload-register-timx_arr">ARR</a>;          /*!< TIM10/11 auto-reload register,        Address offset: 0x2C */
    uint32_t RESERVED3;         /*!< Reserved address space,               Address offset: 0x30 */
    __IO uint32_t <a href="#14510-tim1011-capturecompare-register-1-timx_ccr1">CCR1</a>;         /*!< TIM10/11 capture/compare register 1,  Address offset: 0x34 */
    uint32_t RESERVED4[6];      /*!< Reserved address space, offsets 0x38 through 0x4C */
    __IO uint32_t <a href="#14511-tim11-option-register-1-tim11_or">OR</a>;           /*!< TIM11 option register 1, only on TIM11; offset 0x50 */
} TIM10_11_TypeDef;

</code></pre>

> **Structure note:** `TIM9_TypeDef` and `TIM10_11_TypeDef` are separate because these timers do not implement identical register sets. The reserved members maintain the RM0368 register offsets in the word-based structure style. `OR` in `TIM10_11_TypeDef` is only meaningful for TIM11; TIM10 has no `TIM11_OR` register.

## Register descriptions

<a id="1441-tim9-control-register-1-timx_cr1"></a>

### 14.4.1 TIM9 control register 1 (TIMx_CR1)

**Address offset:** `0x00`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:10` | **Reserved** |
| `9:8` | **CKD** |
| `7` | **ARPE** |
| `6:4` | **Reserved** |
| `3` | **OPM** |
| `2` | **URS** |
| `1` | **UDIS** |
| `0` | **CEN** |

#### Bit-field descriptions

##### 1. Bits 15:10 — Reserved

Must be kept at reset value.

##### 2. Bits 9:8 — CKD

Clock division
This bit-field indicates the division ratio between the timer clock (CK_INT) frequency and sampling clock used by the digital filters (TIx),
- **`00`:** tDTS = tCK_INT
- **`01`:** tDTS = 2 × tCK_INT
- **`10`:** tDTS = 4 × tCK_INT
- **`11`:** Reserved

##### 3. Bits 7 — ARPE

Auto-reload preload enable
- **`0`:** TIMx_ARR register is not buffered.
- **`1`:** TIMx_ARR register is buffered.

##### 4. Bits 6:4 — Reserved

Must be kept at reset value.

##### 5. Bits 3 — OPM

One-pulse mode
- **`0`:** Counter is not stopped on the update event
- **`1`:** Counter stops counting on the next update event (clearing the CEN bit).

##### 6. Bits 2 — URS

Update request source
This bit is set and cleared by software to select the UEV event sources.
- **`0`:** Any of the following events generates an update interrupt if enabled:
- Counter overflow
- Setting the UG bit
- **`1`:** Only counter overflow generates an update interrupt if enabled.

##### 7. Bits 1 — UDIS

Update disable
This bit is set and cleared by software to enable/disable update event (UEV) generation.
- **`0`:** UEV enabled. An UEV is generated by one of the following events:
- Counter overflow
- Setting the UG bit
Buffered registers are then loaded with their preload values.
- **`1`:** UEV disabled. No UEV is generated, shadow registers keep their value (ARR, PSC,
CCRx). The counter and the prescaler are reinitialized if the UG bit is set.

##### 8. Bits 0 — CEN

Counter enable
- **`0`:** Counter disabled
- **`1`:** Counter enabled
CEN is cleared automatically in one-pulse mode, when an update event occurs.
<a id="1442-tim9-slave-mode-control-register-timx_smcr"></a>

### 14.4.2 TIM9 slave mode control register (TIMx_SMCR)

**Address offset:** `0x08`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:8` | **Reserved** |
| `7` | **MSM** |
| `6:4` | **TS** |
| `3` | **Reserved** |
| `2:0` | **SMS** |

#### Bit-field descriptions

##### 1. Bits 15:8 — Reserved

Must be kept at reset value.

##### 2. Bits 7 — MSM

Master/Slave mode
- **`0`:** No action
- **`1`:** The effect of an event on the trigger input (TRGI) is delayed to allow a perfect
synchronization between the current timer and its slaves (through TRGO). It is useful in order to synchronize several timers on a single external event.

##### 3. Bits 6:4 — TS

Trigger selection
This bit field selects the trigger input to be used to synchronize the counter.
- **`000`:** Internal Trigger 0 (ITR0)
- **`001`:** Internal Trigger 1 (ITR1)
- **`010`:** Internal Trigger 2 (ITR2)
- **`011`:** Internal Trigger 3 (ITR3)
- **`100`:** TI1 Edge Detector (TI1F_ED)
- **`101`:** Filtered Timer Input 1 (TI1FP1)
- **`110`:** Filtered Timer Input 2 (TI2FP2)
- **`111`:** Reserved.
See Table 57 for more details on the meaning of ITRx for each timer.
**Note:** These bits must be changed only when they are not used (e.g. when SMS=’000’) to avoid wrong edge detections at the transition.

##### 4. Bits 3 — Reserved

Must be kept at reset value.

##### 5. Bits 2:0 — SMS

Slave mode selection
When external signals are selected, the active edge of the trigger signal (TRGI) is linked to the polarity selected on the external input (see Input control register and Control register descriptions.
- **`000`:** Slave mode disabled - if CEN = 1 then the prescaler is clocked directly by the internal
clock
- **`001`:** Reserved
- **`010`:** Reserved
- **`011`:** Reserved
- **`100`:** Reset mode - Rising edge of the selected trigger input (TRGI) reinitializes the counter
and generates an update of the registers
- **`101`:** Gated mode - The counter clock is enabled when the trigger input (TRGI) is high. The
counter stops (but is not reset) as soon as the trigger becomes low. Counter starts and stops are both controlled
- **`110`:** Trigger mode - The counter starts on a rising edge of the trigger TRGI (but it is not
reset). Only the start of the counter is controlled
- **`111`:** External clock mode 1 - Rising edges of the selected trigger (TRGI) clock the counter
**Note:** The Gated mode must not be used if TI1F_ED is selected as the trigger input (TS=’100’). Indeed, TI1F_ED outputs 1 pulse for each transition on TI1F, whereas the Gated mode checks the level of the trigger signal.
**Note:** The clock of the slave timer must be enabled prior to receive events from the master timer, and must not be changed on-the-fly while triggers are received from the master timer.
Table 57. TIMx internal trigger connection Slave TIM ITR0 (TS = 000) ITR1 (TS = 001) ITR2 (TS = 010) ITR3 (TS = 011)
TIM9 TIM2_TRGO TIM3_TRGO TIM10_OC TIM11_OC
<a id="1443-tim9-interrupt-enable-register-timx_dier"></a>

### 14.4.3 TIM9 Interrupt enable register (TIMx_DIER)

**Address offset:** `0x0C`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:7` | **Reserved** |
| `6` | **TIE** |
| `5:3` | **Reserved** |
| `2` | **CC2IE** |
| `1` | **CC1IE** |
| `0` | **UIE** |

#### Bit-field descriptions

##### 1. Bits 15:7 — Reserved

Must be kept at reset value.

##### 2. Bits 6 — TIE

Trigger interrupt enable
- **`0`:** Trigger interrupt disabled.
- **`1`:** Trigger interrupt enabled.

##### 3. Bits 5:3 — Reserved

Must be kept at reset value.

##### 4. Bits 2 — CC2IE

Capture/Compare 2 interrupt enable
- **`0`:** CC2 interrupt disabled.
- **`1`:** CC2 interrupt enabled.

##### 5. Bits 1 — CC1IE

Capture/Compare 1 interrupt enable
- **`0`:** CC1 interrupt disabled.
- **`1`:** CC1 interrupt enabled.

##### 6. Bits 0 — UIE

Update interrupt enable
- **`0`:** Update interrupt disabled.
- **`1`:** Update interrupt enabled.
<a id="1444-tim9-status-register-timx_sr"></a>

### 14.4.4 TIM9 status register (TIMx_SR)

**Address offset:** `0x10`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:11` | **Reserved** |
| `10` | **CC2OF** |
| `9` | **CC1OF** |
| `8:7` | **Reserved** |
| `6` | **TIF** |
| `5:3` | **Reserved** |
| `2` | **CC2IF** |
| `1` | **CC1IF** |
| `0` | **UIF** |

#### Bit-field descriptions

##### 1. Bits 15:11 — Reserved

Must be kept at reset value.

##### 2. Bits 10 — CC2OF

Capture/compare 2 overcapture flag
refer to CC1OF description

##### 3. Bits 9 — CC1OF

Capture/Compare 1 overcapture flag
This flag is set by hardware only when the corresponding channel is configured in input capture mode. It is cleared by software by writing it to ‘0’.
- **`0`:** No overcapture has been detected.
- **`1`:** The counter value has been captured in TIMx_CCR1 register while CC1IF flag was
already set

##### 4. Bits 8:7 — Reserved

Must be kept at reset value.

##### 5. Bits 6 — TIF

Trigger interrupt flag
This flag is set by hardware on trigger event (active edge detected on TRGI input when the slave mode controller is enabled in all modes but gated mode. It is set when the counter starts or stops when gated mode is selected. It is cleared by software.
- **`0`:** No trigger event occurred.
- **`1`:** Trigger interrupt pending.

##### 6. Bits 5:3 — Reserved

Must be kept at reset value.

##### 7. Bits 2 — CC2IF

Capture/Compare 2 interrupt flag
refer to CC1IF description

##### 8. Bits 1 — CC1IF

Capture/compare 1 interrupt flag
If channel CC1 is configured as output: This flag is set by hardware when the counter matches the compare value. It is cleared by software.
- **`0`:** No match.
- **`1`:** The content of the counter TIMx_CNT matches the content of the TIMx_CCR1 register.
When the contents of TIMx_CCR1 are greater than the contents of TIMx_ARR, the CC1IF bit goes high on the counter overflow. If channel CC1 is configured as input: This bit is set by hardware on a capture. It is cleared by software or by reading the TIMx_CCR1 register.
- **`0`:** No input capture occurred.
- **`1`:** The counter value has been captured in TIMx_CCR1 register (an edge has been detected
on IC1 which matches the selected polarity).

##### 9. Bits 0 — UIF

Update interrupt flag
This bit is set by hardware on an update event. It is cleared by software.
- **`0`:** No update occurred.
- **`1`:** Update interrupt pending. This bit is set by hardware when the registers are updated:
- At overflow and if UDIS=’0’ in the TIMx_CR1 register.
- When CNT is reinitialized by software using the UG bit in TIMx_EGR register, if URS=’0’ and
UDIS=’0’ in the TIMx_CR1 register.
- When CNT is reinitialized by a trigger event (refer to the synchro control register
description), if URS=’0’ and UDIS=’0’ in the TIMx_CR1 register.
<a id="1445-tim9-event-generation-register-timx_egr"></a>

### 14.4.5 TIM9 event generation register (TIMx_EGR)

**Address offset:** `0x14`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:7` | **Reserved** |
| `6` | **TG** |
| `5:3` | **Reserved** |
| `2` | **CC2G** |
| `1` | **CC1G** |
| `0` | **UG** |

#### Bit-field descriptions

##### 1. Bits 15:7 — Reserved

Must be kept at reset value.

##### 2. Bits 6 — TG

Trigger generation
This bit is set by software in order to generate an event, it is automatically cleared by hardware.
- **`0`:** No action
- **`1`:** The TIF flag is set in the TIMx_SR register. Related interrupt can occur if enabled

##### 3. Bits 5:3 — Reserved

Must be kept at reset value.

##### 4. Bits 2 — CC2G

Capture/compare 2 generation
refer to CC1G description

##### 5. Bits 1 — CC1G

Capture/compare 1 generation
This bit is set by software to generate an event, it is automatically cleared by hardware.
- **`0`:** No action
- **`1`:** A capture/compare event is generated on channel 1:
If channel CC1 is configured as output: the CC1IF flag is set, the corresponding interrupt is sent if enabled. If channel CC1 is configured as input: The current counter value is captured in the TIMx_CCR1 register. The CC1IF flag is set, the corresponding interrupt is sent if enabled. The CC1OF flag is set if the CC1IF flag was already high.

##### 6. Bits 0 — UG

Update generation
This bit can be set by software, it is automatically cleared by hardware.
- **`0`:** No action
- **`1`:** Re-initializes the counter and generates an update of the registers. The prescaler counter
is also cleared and the prescaler ratio is not affected. The counter is cleared.
<a id="1446-tim9-capturecompare-mode-register-1-timx_ccmr1"></a>

### 14.4.6 TIM9 capture/compare mode register 1 (TIMx_CCMR1)

**Address offset:** `0x18`  
**Reset value:** `0x0000`

#### Register layout

**Output compare mode**

| Bit(s) | Field |
|---:|---|
| `14:12` | **OC2M[2:0]** |
| `11` | **OC2PE** |
| `10` | **OC2FE** |
| `9:8` | **CC2S[1:0]** |
| `6:4` | **OC1M** |
| `3` | **OC1PE** |
| `2` | **OC1FE** |
| `1:0` | **CC1S** |

**Input capture mode**

| Bit(s) | Field |
|---:|---|
| `15:12` | **IC2F** |
| `11:10` | **IC2PSC[1:0]** |
| `9:8` | **CC2S** |
| `7:4` | **IC1F** |
| `3:2` | **IC1PSC** |
| `1:0` | **CC1S** |

**Register note:** The channels can be used in input (capture mode) or in output (compare mode). The direction of a channel is defined by configuring the corresponding CCxS bits. All the other bits in this register have different functions in input and output modes. For a given bit, OCxx describes its function when the channel is configured in output mode, ICxx describes its function when the channel is configured in input mode. Take care that the same bit can have different meanings for the input stage and the output stage. Res.          OC2M[2:0]        OC2PE OC2FE                  Res.         OC1M[2:0]        OC1PE OC1FE

#### Bit-field descriptions

##### 1. Bits 14:12 — OC2M[2:0] (Output compare mode)

Output compare 2 mode

##### 2. Bits 11 — OC2PE (Output compare mode)

Output compare 2 preload enable

##### 3. Bits 10 — OC2FE (Output compare mode)

Output compare 2 fast enable

##### 4. Bits 9:8 — CC2S[1:0] (Output compare mode)

Capture/Compare 2 selection
This bitfield defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC2 channel is configured as output
- **`01`:** CC2 channel is configured as input, IC2 is mapped on TI2
- **`10`:** CC2 channel is configured as input, IC2 is mapped on TI1
- **`11`:** CC2 channel is configured as input, IC2 is mapped on TRC. This mode works only if an
internal trigger input is selected through the TS bit (TIMx_SMCR register
**Note:** The CC2S bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).

##### 5. Bits 6:4 — OC1M (Output compare mode)

Output compare 1 mode
These bits define the behavior of the output reference signal OC1REF from which OC1 and OC1N are derived. OC1REF is active high whereas the active levels of OC1 and OC1N depend on the CC1P and CC1NP bits, respectively.
- **`000`:** Frozen - The comparison between the output compare register TIMx_CCR1 and the
counter TIMx_CNT has no effect on the outputs.(this mode is used to generate a timing base).
- **`001`:** Set channel 1 to active level on match. The OC1REF signal is forced high when the
TIMx_CNT counter matches the capture/compare register 1 (TIMx_CCR1).
- **`010`:** Set channel 1 to inactive level on match. The OC1REF signal is forced low when the
TIMx_CNT counter matches the capture/compare register 1 (TIMx_CCR1).
- **`011`:** Toggle - OC1REF toggles when TIMx_CNT=TIMx_CCR1
- **`100`:** Force inactive level - OC1REF is forced low
- **`101`:** Force active level - OC1REF is forced high
- **`110`:** PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1
else it is inactive. In downcounting, channel 1 is inactive (OC1REF=‘0) as long as TIMx_CNT>TIMx_CCR1, else it is active (OC1REF=’1’)
- **`111`:** PWM mode 2 - In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1
else it is active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else it is inactive.
**Note:** In PWM mode 1 or 2, the OCREF level changes only when the result of the comparison changes or when the output compare mode switches from “frozen” mode to “PWM” mode.

##### 6. Bits 3 — OC1PE (Output compare mode)

Output compare 1 preload enable
- **`0`:** Preload register on TIMx_CCR1 disabled. TIMx_CCR1 can be written at anytime, the
new value is taken into account immediately
- **`1`:** Preload register on TIMx_CCR1 enabled. Read/Write operations access the preload
register. TIMx_CCR1 preload value is loaded into the active register at each update event

##### 7. Bits 2 — OC1FE (Output compare mode)

Output compare 1 fast enable
This bit is used to accelerate the effect of an event on the trigger in input on the CC output.
- **`0`:** CC1 behaves normally depending on the counter and CCR1 values even when the
trigger is ON. The minimum delay to activate the CC1 output when an edge occurs on the trigger input is 5 clock cycles
- **`1`:** An active edge on the trigger input acts like a compare match on the CC1 output. Then,
OC is set to the compare level independently of the result of the comparison. Delay to sample the trigger input and to activate CC1 output is reduced to 3 clock cycles. OC1FE acts only if the channel is configured in PWM1 or PWM2 mode.

##### 8. Bits 1:0 — CC1S (Output compare mode)

Capture/Compare 1 selection
This bitfield defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC1 channel is configured as output
- **`01`:** CC1 channel is configured as input, IC1 is mapped on TI1
- **`10`:** CC1 channel is configured as input, IC1 is mapped on TI2
- **`11`:** CC1 channel is configured as input, IC1 is mapped on TRC. This mode works only if an
internal trigger input is selected through the TS bit (TIMx_SMCR register)
**Note:** The CC1S bits are writable only when the channel is OFF (CC1E = 0 in TIMx_CCER).

##### 9. Bits 15:12 — IC2F (Input capture mode)

Input capture 2 filter

##### 10. Bits 11:10 — IC2PSC[1:0] (Input capture mode)

Input capture 2 prescaler

##### 11. Bits 9:8 — CC2S (Input capture mode)

Capture/compare 2 selection
This bitfield defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC2 channel is configured as output
- **`01`:** CC2 channel is configured as input, IC2 is mapped on TI2
- **`10`:** CC2 channel is configured as input, IC2 is mapped on TI1
- **`11`:** CC2 channel is configured as input, IC2 is mapped on TRC. This mode works only if an
internal trigger input is selected through the TS bit (TIMx_SMCR register)
**Note:** The CC2S bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).

##### 12. Bits 7:4 — IC1F (Input capture mode)

Input capture 1 filter
This bitfield defines the frequency used to sample the TI1 input and the length of the digital filter applied to TI1. The digital filter is made of an event counter in which N consecutive events are needed to validate a transition on the output:
- **`0000`:** No filter, sampling is done at fDTS
- **`0001`:** fSAMPLING=fCK_INT, N=2
- **`0010`:** fSAMPLING=fCK_INT, N=4
- **`0011`:** fSAMPLING=fCK_INT, N=8
- **`0100`:** fSAMPLING=fDTS/2, N=6
- **`0101`:** fSAMPLING=fDTS/2, N=8
- **`0110`:** fSAMPLING=fDTS/4, N=6
- **`0111`:** fSAMPLING=fDTS/4, N=8
- **`1000`:** fSAMPLING=fDTS/8, N=6
- **`1001`:** fSAMPLING=fDTS/8, N=8
- **`1010`:** fSAMPLING=fDTS/16, N=5
- **`1011`:** fSAMPLING=fDTS/16, N=6
- **`1100`:** fSAMPLING=fDTS/16, N=8
- **`1101`:** fSAMPLING=fDTS/32, N=5
- **`1110`:** fSAMPLING=fDTS/32, N=6
- **`1111`:** fSAMPLING=fDTS/32, N=8

##### 13. Bits 3:2 — IC1PSC (Input capture mode)

Input capture 1 prescaler
This bitfield defines the ratio of the prescaler acting on the CC1 input (IC1). The prescaler is reset as soon as CC1E=’0’ (TIMx_CCER register).
- **`00`:** no prescaler, capture is done each time an edge is detected on the capture input
- **`01`:** capture is done once every 2 events
- **`10`:** capture is done once every 4 events
- **`11`:** capture is done once every 8 events

##### 14. Bits 1:0 — CC1S (Input capture mode)

Capture/Compare 1 selection
This bitfield defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC1 channel is configured as output
- **`01`:** CC1 channel is configured as input, IC1 is mapped on TI1
- **`10`:** CC1 channel is configured as input, IC1 is mapped on TI2
- **`11`:** CC1 channel is configured as input, IC1 is mapped on TRC. This mode is working only if
an internal trigger input is selected through TS bit (TIMx_SMCR register)
**Note:** The CC1S bits are writable only when the channel is OFF (CC1E = 0 in TIMx_CCER).
<a id="1447-tim9-capturecompare-enable-register-timx_ccer"></a>

### 14.4.7 TIM9 capture/compare enable register (TIMx_CCER)

**Address offset:** `0x20`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:8` | **Reserved** |
| `7` | **CC2NP** |
| `6` | **Reserved** |
| `5` | **CC2P** |
| `4` | **CC2E** |
| `3` | **CC1NP** |
| `2` | **Reserved** |
| `1` | **CC1P** |
| `0` | **CC1E** |

#### Bit-field descriptions

##### 1. Bits 15:8 — Reserved

Must be kept at reset value.

##### 2. Bits 7 — CC2NP

Capture/Compare 2 output Polarity
refer to CC1NP description

##### 3. Bits 6 — Reserved

Must be kept at reset value.

##### 4. Bits 5 — CC2P

Capture/Compare 2 output Polarity
refer to CC1P description

##### 5. Bits 4 — CC2E

Capture/Compare 2 output enable
refer to CC1E description

##### 6. Bits 3 — CC1NP

Capture/Compare 1 complementary output Polarity
CC1 channel configured as output: CC1NP must be kept cleared CC1 channel configured as input: CC1NP is used in conjunction with CC1P to define TI1FP1/TI2FP1 polarity (refer to CC1P description).

##### 7. Bits 2 — Reserved

Must be kept at reset value.

##### 8. Bits 1 — CC1P

Capture/Compare 1 output Polarity.
CC1 channel configured as output:
- **`0`:** OC1 active high.
- **`1`:** OC1 active low.
CC1 channel configured as input: CC1NP/CC1P bits select TI1FP1 and TI2FP1 polarity for trigger or capture operations.
- **`00`:** noninverted/rising edge
Circuit is sensitive to TIxFP1 rising edge (capture, trigger in reset, external clock or trigger mode), TIxFP1 is not inverted (trigger in gated mode, encoder mode).
- **`01`:** inverted/falling edge
Circuit is sensitive to TIxFP1 falling edge (capture, trigger in reset, external clock or trigger mode), TIxFP1 is inverted (trigger in gated mode, encoder mode).
- **`10`:** reserved, do not use this configuration.
**Note:** 11: noninverted/both edges Circuit is sensitive to both TIxFP1 rising and falling edges (capture, trigger in reset, external clock or trigger mode), TIxFP1 is not inverted (trigger in gated mode). This configuration must not be used for encoder mode.

##### 9. Bits 0 — CC1E

Capture/Compare 1 output enable.
CC1 channel configured as output:
- **`0`:** Off - OC1 is not active.
- **`1`:** On - OC1 signal is output on the corresponding output pin.
CC1 channel configured as input: This bit determines if a capture of the counter value can actually be done into the input capture/compare register 1 (TIMx_CCR1) or not.
- **`0`:** Capture disabled.
- **`1`:** Capture enabled.
Table 58. Output control bit for standard OCx channels CCxE bit OCx output state
0 Output disabled (OCx=’0’, OCx_EN=’0’) 1 OCx=OCxREF + Polarity, OCx_EN=’1’
**Note:** The states of the external I/O pins connected to the standard OCx channels depend on the state of the OCx channel and on the GPIO registers.
<a id="1448-tim9-counter-timx_cnt"></a>

### 14.4.8 TIM9 counter (TIMx_CNT)

**Address offset:** `0x24`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:0` | **CNT[15:0]** |

#### Bit-field descriptions

##### 1. Bits 15:0 — CNT[15:0]

Counter value
<a id="1449-tim9-prescaler-timx_psc"></a>

### 14.4.9 TIM9 prescaler (TIMx_PSC)

**Address offset:** `0x28`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:0` | **PSC[15:0]** |

#### Bit-field descriptions

##### 1. Bits 15:0 — PSC[15:0]

Prescaler value
The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1). PSC contains the value to be loaded in the active prescaler register at each update event (including when the counter is cleared through UG bit of TIMx_EGR register or through trigger controller when configured in “reset mode”).
<a id="14410-tim9-auto-reload-register-timx_arr"></a>

### 14.4.10 TIM9 auto-reload register (TIMx_ARR)

**Address offset:** `0x2C`  
**Reset value:** `0xFFFF`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:0` | **ARR[15:0]** |

#### Bit-field descriptions

##### 1. Bits 15:0 — ARR[15:0]

Auto-reload value
ARR is the value to be loaded into the actual auto-reload register. Refer to the Section 14.3.1: Time-base unit for more details about ARR update and behavior. The counter is blocked while the auto-reload value is null.
<a id="14411-tim9-capturecompare-register-1-timx_ccr1"></a>

### 14.4.11 TIM9 capture/compare register 1 (TIMx_CCR1)

**Address offset:** `0x34`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:0` | **CCR1[15:0]** |

#### Bit-field descriptions

##### 1. Bits 15:0 — CCR1[15:0]

Capture/Compare 1 value
If channel CC1 is configured as output: CCR1 is the value to be loaded into the actual capture/compare 1 register (preload value). It is loaded permanently if the preload feature is not selected in the TIMx_CCMR1 register (OC1PE bit). Else the preload value is copied into the active capture/compare 1 register when an update event occurs. The active capture/compare register contains the value to be compared to the TIMx_CNT counter and signaled on the OC1 output. If channel CC1is configured as input: CCR1 is the counter value transferred by the last input capture 1 event (IC1). The TIMx_CCR1 register is read-only and cannot be programmed.
<a id="14412-tim9-capturecompare-register-2-timx_ccr2"></a>

### 14.4.12 TIM9 capture/compare register 2 (TIMx_CCR2)

**Address offset:** `0x38`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:0` | **CCR2[15:0]** |

#### Bit-field descriptions

##### 1. Bits 15:0 — CCR2[15:0]

Capture/Compare 2 value
If channel CC2 is configured as output: CCR2 is the value to be loaded into the actual capture/compare 2 register (preload value). It is loaded permanently if the preload feature is not selected in the TIMx_CCMR2 register (OC2PE bit). Else the preload value is copied into the active capture/compare 2 register when an update event occurs. The active capture/compare register contains the value to be compared to the TIMx_CNT counter and signalled on the OC2 output. If channel CC2 is configured as input: CCR2 is the counter value transferred by the last input capture 2 event (IC2). The TIMx_CCR2 register is read-only and cannot be programmed.
<a id="1451-tim1011-control-register-1-timx_cr1"></a>

### 14.5.1 TIM10/11 control register 1 (TIMx_CR1)

**Address offset:** `0x00`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:10` | **Reserved** |
| `9:8` | **CKD** |
| `7` | **ARPE** |
| `6:4` | **Reserved** |
| `3` | **OPM** |
| `2` | **URS** |
| `1` | **UDIS** |
| `0` | **CEN** |

#### Bit-field descriptions

##### 1. Bits 15:10 — Reserved

Must be kept at reset value.

##### 2. Bits 9:8 — CKD

Clock division
This bit-field indicates the division ratio between the timer clock (CK_INT) frequency and sampling clock used by the digital filters (TIx),
- **`00`:** tDTS = tCK_INT
- **`01`:** tDTS = 2 × tCK_INT
- **`10`:** tDTS = 4 × tCK_INT
- **`11`:** Reserved

##### 3. Bits 7 — ARPE

Auto-reload preload enable
- **`0`:** TIMx_ARR register is not buffered
- **`1`:** TIMx_ARR register is buffered

##### 4. Bits 6:4 — Reserved

Must be kept at reset value.

##### 5. Bits 3 — OPM

One-pulse mode
- **`0`:** Counter is not stopped on the update event
- **`1`:** Counter stops counting on the next update event (clearing the CEN bit).

##### 6. Bits 2 — URS

Update request source
This bit is set and cleared by software to select the update interrupt (UEV) sources.
- **`0`:** Any of the following events generate an UEV if enabled:
- Counter overflow
- Setting the UG bit
- **`1`:** Only counter overflow generates an UEV if enabled.

##### 7. Bits 1 — UDIS

Update disable
This bit is set and cleared by software to enable/disable update interrupt (UEV) event generation.
- **`0`:** UEV enabled. An UEV is generated by one of the following events:
- Counter overflow
- Setting the UG bit.
Buffered registers are then loaded with their preload values.
- **`1`:** UEV disabled. No UEV is generated, shadow registers keep their value (ARR, PSC,
CCRx). The counter and the prescaler are reinitialized if the UG bit is set.

##### 8. Bits 0 — CEN

Counter enable
- **`0`:** Counter disabled
- **`1`:** Counter enabled
<a id="1452-tim1011-interrupt-enable-register-timx_dier"></a>

### 14.5.2 TIM10/11 Interrupt enable register (TIMx_DIER)

**Address offset:** `0x0C`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:2` | **Reserved** |
| `1` | **CC1IE** |
| `0` | **UIE** |

#### Bit-field descriptions

##### 1. Bits 15:2 — Reserved

Must be kept at reset value.

##### 2. Bits 1 — CC1IE

Capture/Compare 1 interrupt enable
- **`0`:** CC1 interrupt disabled
- **`1`:** CC1 interrupt enabled

##### 3. Bits 0 — UIE

Update interrupt enable
- **`0`:** Update interrupt disabled
- **`1`:** Update interrupt enabled
<a id="1453-tim-status-register-timx_sr"></a>

### 14.5.3 TIM status register (TIMx_SR)

**Address offset:** `0x10`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:10` | **Reserved** |
| `9` | **CC1OF** |
| `8:2` | **Reserved** |
| `1` | **CC1IF** |
| `0` | **UIF** |

#### Bit-field descriptions

##### 1. Bits 15:10 — Reserved

Must be kept at reset value.

##### 2. Bits 9 — CC1OF

Capture/Compare 1 overcapture flag
This flag is set by hardware only when the corresponding channel is configured in input capture mode. It is cleared by software by writing it to ‘0’.
- **`0`:** No overcapture has been detected.
- **`1`:** The counter value has been captured in TIMx_CCR1 register while CC1IF flag was
already set

##### 3. Bits 8:2 — Reserved

Must be kept at reset value.

##### 4. Bits 1 — CC1IF

Capture/compare 1 interrupt flag
If channel CC1 is configured as output: This flag is set by hardware when the counter matches the compare value. It is cleared by software.
- **`0`:** No match.
- **`1`:** The content of the counter TIMx_CNT matches the content of the TIMx_CCR1 register.
When the contents of TIMx_CCR1 are greater than the contents of TIMx_ARR, the CC1IF bit goes high on the counter overflow. If channel CC1 is configured as input: This bit is set by hardware on a capture. It is cleared by software or by reading the TIMx_CCR1 register.
- **`0`:** No input capture occurred.
- **`1`:** The counter value has been captured in TIMx_CCR1 register (an edge has been detected
on IC1 which matches the selected polarity).

##### 5. Bits 0 — UIF

Update interrupt flag
This bit is set by hardware on an update event. It is cleared by software.
- **`0`:** No update occurred.
- **`1`:** Update interrupt pending. This bit is set by hardware when the registers are updated:
- At overflow and if UDIS=’0’ in the TIMx_CR1 register.
- When CNT is reinitialized by software using the UG bit in TIMx_EGR register, if
URS=’0’ and UDIS=’0’ in the TIMx_CR1 register.
<a id="1454-tim-event-generation-register-timx_egr"></a>

### 14.5.4 TIM event generation register (TIMx_EGR)

**Address offset:** `0x14`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:2` | **Reserved** |
| `1` | **CC1G** |
| `0` | **UG** |

#### Bit-field descriptions

##### 1. Bits 15:2 — Reserved

Must be kept at reset value.

##### 2. Bits 1 — CC1G

Capture/compare 1 generation
This bit is set by software in order to generate an event, it is automatically cleared by hardware.
- **`0`:** No action
- **`1`:** A capture/compare event is generated on channel 1:
If channel CC1 is configured as output: CC1IF flag is set, Corresponding interrupt or is sent if enabled. If channel CC1 is configured as input: The current value of the counter is captured in TIMx_CCR1 register. The CC1IF flag is set, the corresponding interrupt is sent if enabled. The CC1OF flag is set if the CC1IF flag was already high.

##### 3. Bits 0 — UG

Update generation
This bit can be set by software, it is automatically cleared by hardware.
- **`0`:** No action
- **`1`:** Re-initialize the counter and generates an update of the registers. Note that the prescaler
counter is cleared too (anyway the prescaler ratio is not affected). The counter is cleared.
<a id="1455-tim1011-capturecompare-mode-register-1-timx_ccmr1"></a>

### 14.5.5 TIM10/11 capture/compare mode register 1 (TIMx_CCMR1)

**Address offset:** `0x18`  
**Reset value:** `0x0000`

#### Register layout

**Output compare mode**

| Bit(s) | Field |
|---:|---|
| `15:7` | **Reserved** |
| `6:4` | **OC1M** |
| `3` | **OC1PE** |
| `2` | **OC1FE** |
| `1:0` | **CC1S** |

**Input capture mode**

| Bit(s) | Field |
|---:|---|
| `15:8` | **Reserved** |
| `7:4` | **IC1F** |
| `3:2` | **IC1PSC** |
| `1:0` | **CC1S** |

**Register note:** The channels can be used in input (capture mode) or in output (compare mode). The direction of a channel is defined by configuring the corresponding CCxS bits. All the other bits of this register have a different function in input and in output mode. For a given bit, OCxx describes its function when the channel is configured in output, ICxx describes its function when the channel is configured in input. So take care that the same bit can have a different meaning for the input stage and for the output stage.

#### Bit-field descriptions

##### 1. Bits 15:7 — Reserved (Output compare mode)

Must be kept at reset value.

##### 2. Bits 6:4 — OC1M (Output compare mode)

Output compare 1 mode
These bits define the behavior of the output reference signal OC1REF from which OC1 is derived. OC1REF is active high whereas OC1 active level depends on CC1P bit.
- **`000`:** Frozen. The comparison between the output compare register TIMx_CCR1 and the
counter TIMx_CNT has no effect on the outputs.
- **`001`:** Set channel 1 to active level on match. OC1REF signal is forced high when the counter
TIMx_CNT matches the capture/compare register 1 (TIMx_CCR1).
- **`010`:** Set channel 1 to inactive level on match. OC1REF signal is forced low when the
counter TIMx_CNT matches the capture/compare register 1 (TIMx_CCR1).
- **`011`:** Toggle - OC1REF toggles when TIMx_CNT = TIMx_CCR1.
- **`100`:** Force inactive level - OC1REF is forced low.
- **`101`:** Force active level - OC1REF is forced high.
- **`110`:** PWM mode 1 - Channel 1 is active as long as TIMx_CNT < TIMx_CCR1 else inactive.
- **`111`:** PWM mode 2 - Channel 1 is inactive as long as TIMx_CNT < TIMx_CCR1 else active.
**Note:** In PWM mode 1 or 2, the OCREF level changes when the result of the comparison changes or when the output compare mode switches from frozen to PWM mode.

##### 3. Bits 3 — OC1PE (Output compare mode)

Output compare 1 preload enable
- **`0`:** Preload register on TIMx_CCR1 disabled. TIMx_CCR1 can be written at anytime, the
new value is taken in account immediately.
- **`1`:** Preload register on TIMx_CCR1 enabled. Read/Write operations access the preload
register. TIMx_CCR1 preload value is loaded in the active register at each update event.

##### 4. Bits 2 — OC1FE (Output compare mode)

Output compare 1 fast enable
This bit is used to accelerate the effect of an event on the trigger in input on the CC output.
- **`0`:** CC1 behaves normally depending on counter and CCR1 values even when the trigger is
ON. The minimum delay to activate CC1 output when an edge occurs on the trigger input is 5 clock cycles.
- **`1`:** An active edge on the trigger input acts like a compare match on CC1 output. OC is then
set to the compare level independently of the result of the comparison. Delay to sample the trigger input and to activate CC1 output is reduced to 3 clock cycles. OC1FE acts only if the channel is configured in PWM1 or PWM2 mode.

##### 5. Bits 1:0 — CC1S (Output compare mode)

Capture/Compare 1 selection
This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC1 channel is configured as output.
- **`01`:** CC1 channel is configured as input, IC1 is mapped on TI1.
- **`10`:** 
- **`11`:** 
**Note:** CC1S bits are writable only when the channel is OFF (CC1E = 0 in TIMx_CCER).

##### 6. Bits 15:8 — Reserved (Input capture mode)

Must be kept at reset value.

##### 7. Bits 7:4 — IC1F (Input capture mode)

Input capture 1 filter
This bit-field defines the frequency used to sample TI1 input and the length of the digital filter applied to TI1. The digital filter is made of an event counter in which N consecutive events are needed to validate a transition on the output:
- **`0000`:** No filter, sampling is done at fDTS
- **`0001`:** fSAMPLING=fCK_INT, N=2
- **`0010`:** fSAMPLING=fCK_INT, N=4
- **`0011`:** fSAMPLING=fCK_INT, N=8
- **`0100`:** fSAMPLING=fDTS/2, N=6
- **`0101`:** fSAMPLING=fDTS/2, N=8
- **`0110`:** fSAMPLING=fDTS/4, N=6
- **`0111`:** fSAMPLING=fDTS/4, N=8
- **`1000`:** fSAMPLING=fDTS/8, N=6
- **`1001`:** fSAMPLING=fDTS/8, N=8
- **`1010`:** fSAMPLING=fDTS/16, N=5
- **`1011`:** fSAMPLING=fDTS/16, N=6
- **`1100`:** fSAMPLING=fDTS/16, N=8
- **`1101`:** fSAMPLING=fDTS/32, N=5
- **`1110`:** fSAMPLING=fDTS/32, N=6
- **`1111`:** fSAMPLING=fDTS/32, N=8

##### 8. Bits 3:2 — IC1PSC (Input capture mode)

Input capture 1 prescaler
This bit-field defines the ratio of the prescaler acting on CC1 input (IC1). The prescaler is reset as soon as CC1E=’0’ (TIMx_CCER register).
- **`00`:** no prescaler, capture is done each time an edge is detected on the capture input
- **`01`:** capture is done once every 2 events
- **`10`:** capture is done once every 4 events
- **`11`:** capture is done once every 8 events

##### 9. Bits 1:0 — CC1S (Input capture mode)

Capture/Compare 1 selection
This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC1 channel is configured as output
- **`01`:** CC1 channel is configured as input, IC1 is mapped on TI1
- **`10`:** Reserved
- **`11`:** Reserved
**Note:** CC1S bits are writable only when the channel is OFF (CC1E = 0 in TIMx_CCER).
<a id="1456-tim1011-capturecompare-enable-register-timx_ccer"></a>

### 14.5.6 TIM10/11 capture/compare enable register (TIMx_CCER)

**Address offset:** `0x20`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:4` | **Reserved** |
| `3` | **CC1NP** |
| `2` | **Reserved** |
| `1` | **CC1P** |
| `0` | **CC1E** |

#### Bit-field descriptions

##### 1. Bits 15:4 — Reserved

Must be kept at reset value.

##### 2. Bits 3 — CC1NP

Capture/Compare 1 complementary output Polarity.
CC1 channel configured as output: CC1NP must be kept cleared. CC1 channel configured as input: CC1NP bit is used in conjunction with CC1P to define TI1FP1 polarity (refer to CC1P description).

##### 3. Bits 2 — Reserved

Must be kept at reset value.

##### 4. Bits 1 — CC1P

Capture/Compare 1 output Polarity.
CC1 channel configured as output:
- **`0`:** OC1 active high
- **`1`:** OC1 active low
CC1 channel configured as input: The CC1P bit selects TI1FP1 and TI2FP1 polarity for trigger or capture operations.
- **`00`:** noninverted/rising edge
Circuit is sensitive to TI1FP1 rising edge (capture mode), TI1FP1 is not inverted.
- **`01`:** inverted/falling edge
Circuit is sensitive to TI1FP1 falling edge (capture mode), TI1FP1 is inverted.
- **`10`:** reserved, do not use this configuration.
- **`11`:** noninverted/both edges
Circuit is sensitive to both TI1FP1 rising and falling edges (capture mode), TI1FP1 is not inverted.

##### 5. Bits 0 — CC1E

Capture/Compare 1 output enable.
CC1 channel configured as output:
- **`0`:** Off - OC1 is not active
- **`1`:** On - OC1 signal is output on the corresponding output pin
CC1 channel configured as input: This bit determines if a capture of the counter value can actually be done into the input capture/compare register 1 (TIMx_CCR1) or not.
- **`0`:** Capture disabled
- **`1`:** Capture enabled
Table 60. Output control bit for standard OCx channels CCxE bit OCx output state 0 Output Disabled (OCx=’0’, OCx_EN=’0’) 1 OCx=OCxREF + Polarity, OCx_EN=’1’
**Note:** The state of the external I/O pins connected to the standard OCx channels depends on the OCx channel state and the GPIO registers.
<a id="1457-tim1011-counter-timx_cnt"></a>

### 14.5.7 TIM10/11 counter (TIMx_CNT)

**Address offset:** `0x24`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:0` | **CNT[15:0]** |

#### Bit-field descriptions

##### 1. Bits 15:0 — CNT[15:0]

Counter value
<a id="1458-tim1011-prescaler-timx_psc"></a>

### 14.5.8 TIM10/11 prescaler (TIMx_PSC)

**Address offset:** `0x28`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:0` | **PSC[15:0]** |

#### Bit-field descriptions

##### 1. Bits 15:0 — PSC[15:0]

Prescaler value
The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1). PSC contains the value to be loaded in the active prescaler register at each update event (including when the counter is cleared through UG bit of TIMx_EGR register or through trigger controller when configured in “reset mode”).
<a id="1459-tim1011-auto-reload-register-timx_arr"></a>

### 14.5.9 TIM10/11 auto-reload register (TIMx_ARR)

**Address offset:** `0x2C`  
**Reset value:** `0xFFFF`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:0` | **ARR[15:0]** |

#### Bit-field descriptions

##### 1. Bits 15:0 — ARR[15:0]

Auto-reload value
ARR is the value to be loaded in the actual auto-reload register. Refer to Section 14.3.1: Time-base unit for more details about ARR update and behavior. The counter is blocked while the auto-reload value is null.
<a id="14510-tim1011-capturecompare-register-1-timx_ccr1"></a>

### 14.5.10 TIM10/11 capture/compare register 1 (TIMx_CCR1)

**Address offset:** `0x34`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:0` | **CCR1[15:0]** |

#### Bit-field descriptions

##### 1. Bits 15:0 — CCR1[15:0]

Capture/Compare 1 value
If channel CC1 is configured as output: CCR1 is the value to be loaded in the actual capture/compare 1 register (preload value). It is loaded permanently if the preload feature is not selected in the TIMx_CCMR1 register (bit OC1PE). Else the preload value is copied in the active capture/compare 1 register when an update event occurs. The active capture/compare register contains the value to be compared to the counter TIMx_CNT and signaled on OC1 output.
If channel CC1is configured as input: CCR1 is the counter value transferred by the last input capture 1 event (IC1). The TIMx_CCR1 register is read-only and cannot be programmed.
<a id="14511-tim11-option-register-1-tim11_or"></a>

### 14.5.11 TIM11 option register 1 (TIM11_OR)

**Address offset:** `0x50`  
**Reset value:** `0x0x0000`

> **Source note:** RM0368 Rev. 6 prints the TIM11_OR reset value as `0x0x0000`; this value is retained verbatim from the manual.

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:2` | **Reserved** |
| `1:0` | **TI1_RMP[1:0]** |

#### Bit-field descriptions

##### 1. Bits 15:2 — Reserved

Must be kept at reset value.

##### 2. Bits 1:0 — TI1_RMP[1:0]

TIM11 Input 1 remapping capability
Set and cleared by software. 00,01,11: TIM11 Channel1 is connected to the GPIO (refer to the Alternate function mapping table in the datasheets).
- **`10`:** HSE_RTC clock (HSE divided by programmable prescaler) is connected to the
TIM11_CH1 input for measurement purposes.

## Reference notes

- Register offsets are shown as in RM0368.
- Register-layout tables use separate Markdown cells for bit ranges and field names.
- Reserved bits should be kept at the values specified by the reference manual.
