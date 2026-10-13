# STM32F401 TIM2–TIM5 Register Reference

> Based on STMicroelectronics RM0368 Rev. 6, Section 13.4, “TIM2 to TIM5 registers” (printed pages 353–373). Register order and field descriptions follow the reference manual.

## Register navigation

Use this table as the main map for the timer register block. The register names
match the `TIM_TypeDef` member names below.

| Offset | Register | Full name | Main job |
|---:|---|---|---|
| `0x00` | [`CR1`](#1341-timx-control-register-1-timx_cr1) | Control register 1 | Enables the counter and controls basic count behavior. |
| `0x04` | [`CR2`](#1342-timx-control-register-2-timx_cr2) | Control register 2 | Controls master trigger and secondary timer behavior. |
| `0x08` | [`SMCR`](#1343-timx-slave-mode-control-register-timx_smcr) | Slave mode control register | Selects trigger, external clock, encoder, gated, or slave modes. |
| `0x0C` | [`DIER`](#1344-timx-dmainterrupt-enable-register-timx_dier) | DMA/interrupt enable register | Enables update, capture/compare, trigger, and DMA requests. |
| `0x10` | [`SR`](#1345-timx-status-register-timx_sr) | Status register | Holds event flags such as `UIF` and `CCxIF`. |
| `0x14` | [`EGR`](#1346-timx-event-generation-register-timx_egr) | Event generation register | Lets software force events such as update or capture/compare events. |
| `0x18` | [`CCMR1`](#1347-timx-capturecompare-mode-register-1-timx_ccmr1) | Capture/compare mode register 1 | Configures channel 1 and channel 2 mode. |
| `0x1C` | [`CCMR2`](#1348-timx-capturecompare-mode-register-2-timx_ccmr2) | Capture/compare mode register 2 | Configures channel 3 and channel 4 mode. |
| `0x20` | [`CCER`](#1349-timx-capturecompare-enable-register-timx_ccer) | Capture/compare enable register | Enables channels and selects output/input polarity. |
| `0x24` | [`CNT`](#13410-timx-counter-timx_cnt) | Counter register | Stores the current timer count value. |
| `0x28` | [`PSC`](#13411-timx-prescaler-timx_psc) | Prescaler | Divides the timer clock before it reaches `CNT`. |
| `0x2C` | [`ARR`](#13412-timx-auto-reload-register-timx_arr) | Auto-reload register | Sets the period limit; update happens when `CNT` reaches this. |
| `0x30` | [`RCR`](#timx-repetition-counter-register-timx_rcr) | Repetition counter register | Advanced-timer feature; not a TIM2-TIM5 register in RM0368 section 13.4. |
| `0x34` | [`CCR1`](#13413-timx-capturecompare-register-1-timx_ccr1) | Capture/compare register 1 | Channel 1 compare value or captured input value. |
| `0x38` | [`CCR2`](#13414-timx-capturecompare-register-2-timx_ccr2) | Capture/compare register 2 | Channel 2 compare value or captured input value. |
| `0x3C` | [`CCR3`](#13415-timx-capturecompare-register-3-timx_ccr3) | Capture/compare register 3 | Channel 3 compare value or captured input value. |
| `0x40` | [`CCR4`](#13416-timx-capturecompare-register-4-timx_ccr4) | Capture/compare register 4 | Channel 4 compare value or captured input value. |
| `0x44` | [`BDTR`](#timx-break-and-dead-time-register-timx_bdtr) | Break and dead-time register | Advanced-timer feature; not a TIM2-TIM5 register in RM0368 section 13.4. |
| `0x48` | [`DCR`](#13417-timx-dma-control-register-timx_dcr) | DMA control register | Configures timer DMA burst base address and burst length. |
| `0x4C` | [`DMAR`](#13418-timx-dma-address-for-full-transfer-timx_dmar) | DMA address register | Access window used by timer DMA burst transfers. |
| `0x50` | [`OR`](#13419-tim2-option-register-tim2_or) | Option register | Timer-specific remap options. See both `TIM2_OR` and `TIM5_OR`. |

## `TIM_TypeDef` structure

The structure below is kept in the order and with the member offsets you supplied:

<pre><code class="language-c++">
typedef struct
{
    __IO uint32_t <a href="#1341-timx-control-register-1-timx_cr1">CR1</a>;         /*!< TIM control register 1,              Address offset: 0x00 */
    __IO uint32_t <a href="#1342-timx-control-register-2-timx_cr2">CR2</a>;         /*!< TIM control register 2,              Address offset: 0x04 */
    __IO uint32_t <a href="#1343-timx-slave-mode-control-register-timx_smcr">SMCR</a>;        /*!< TIM slave mode control register,     Address offset: 0x08 */
    __IO uint32_t <a href="#1344-timx-dmainterrupt-enable-register-timx_dier">DIER</a>;        /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
    __IO uint32_t <a href="#1345-timx-status-register-timx_sr">SR</a>;          /*!< TIM status register,                 Address offset: 0x10 */
    __IO uint32_t <a href="#1346-timx-event-generation-register-timx_egr">EGR</a>;         /*!< TIM event generation register,       Address offset: 0x14 */
    __IO uint32_t <a href="#1347-timx-capturecompare-mode-register-1-timx_ccmr1">CCMR1</a>;       /*!< TIM capture/compare mode register 1, Address offset: 0x18 */
    __IO uint32_t <a href="#1348-timx-capturecompare-mode-register-2-timx_ccmr2">CCMR2</a>;       /*!< TIM capture/compare mode register 2, Address offset: 0x1C */
    __IO uint32_t <a href="#1349-timx-capturecompare-enable-register-timx_ccer">CCER</a>;        /*!< TIM capture/compare enable register, Address offset: 0x20 */
    __IO uint32_t <a href="#13410-timx-counter-timx_cnt">CNT</a>;         /*!< TIM counter register,                Address offset: 0x24 */
    __IO uint32_t <a href="#13411-timx-prescaler-timx_psc">PSC</a>;         /*!< TIM prescaler,                       Address offset: 0x28 */
    __IO uint32_t <a href="#13412-timx-auto-reload-register-timx_arr">ARR</a>;         /*!< TIM auto-reload register,            Address offset: 0x2C */
    __IO uint32_t <a href="#timx-repetition-counter-register-timx_rcr">RCR</a>;         /*!< TIM repetition counter register,     Address offset: 0x30 */
    __IO uint32_t <a href="#13413-timx-capturecompare-register-1-timx_ccr1">CCR1</a>;        /*!< TIM capture/compare register 1,      Address offset: 0x34 */
    __IO uint32_t <a href="#13414-timx-capturecompare-register-2-timx_ccr2">CCR2</a>;        /*!< TIM capture/compare register 2,      Address offset: 0x38 */
    __IO uint32_t <a href="#13415-timx-capturecompare-register-3-timx_ccr3">CCR3</a>;        /*!< TIM capture/compare register 3,      Address offset: 0x3C */
    __IO uint32_t <a href="#13416-timx-capturecompare-register-4-timx_ccr4">CCR4</a>;        /*!< TIM capture/compare register 4,      Address offset: 0x40 */
    __IO uint32_t <a href="#timx-break-and-dead-time-register-timx_bdtr">BDTR</a>;        /*!< TIM break and dead-time register,    Address offset: 0x44 */
    __IO uint32_t <a href="#13417-timx-dma-control-register-timx_dcr">DCR</a>;         /*!< TIM DMA control register,            Address offset: 0x48 */
    __IO uint32_t <a href="#13418-timx-dma-address-for-full-transfer-timx_dmar">DMAR</a>;        /*!< TIM DMA address for full transfer,   Address offset: 0x4C */
    __IO uint32_t <a href="#13419-tim2-option-register-tim2_or">OR</a>;          /*!< TIM option register,                 Address offset: 0x50 */
} TIM_TypeDef;
</code></pre>

> **Compatibility note:** The structure above is preserved exactly as requested. In RM0368 Section 13.4 for TIM2–TIM5, the registers named `RCR` and `BDTR` are not documented as TIM2–TIM5 registers; offsets `0x30` and `0x44` are therefore not confirmed by that section as `RCR` and `BDTR`. Verify these two members against the exact MCU header and reference manual before using this structure for memory-mapped access.

## How to read each register

- The register sections below are presented in RM0368 order.
- The field-map tables use **Bit(s)** and **Field** columns so each bit range has a clear cell boundary.
- `Reserved` fields and access restrictions are retained where described in the reference manual.
- TIM2 and TIM5 support 32-bit counter/capture-compare values; TIM3 and TIM4 use 16-bit counters/capture-compare values as described in RM0368.

<a id="1341-timx-control-register-1-timx_cr1"></a>

## 13.4.1 TIMx control register 1 (TIMx_CR1)

**Address offset:** `0x00`  
**Reset value:** `0x0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `15:10` | **Reserved** |
| `9:8` | **CKD** |
| `7` | **ARPE** |
| `6:5` | **CMS** |
| `4` | **DIR** |
| `3` | **OPM** |
| `2` | **URS** |
| `1` | **UDIS** |
| `0` | **CEN** |

### Bit-field descriptions — Register fields

#### 1. Bits 15:10 — Reserved

Must be kept at reset value.

#### 2. Bits 9:8 — CKD

Clock division This bit-field indicates the division ratio between the timer clock (CK_INT) frequency and sampling clock used by the digital filters (ETR, TIx),
- **`00`:** tDTS = tCK_INT
- **`01`:** tDTS = 2 × tCK_INT
- **`10`:** tDTS = 4 × tCK_INT
- **`11`:** Reserved

#### 3. Bits 7 — ARPE

Auto-reload preload enable
- **`0`:** TIMx_ARR register is not buffered
- **`1`:** TIMx_ARR register is buffered

#### 4. Bits 6:5 — CMS

Center-aligned mode selection
- **`00`:** Edge-aligned mode. The counter counts up or down depending on the direction bit (DIR).
- **`01`:** Center-aligned mode 1. The counter counts up and down alternatively. Output compare interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set only when the counter is counting down.
- **`10`:** Center-aligned mode 2. The counter counts up and down alternatively. Output compare interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set only when the counter is counting up.
- **`11`:** Center-aligned mode 3. The counter counts up and down alternatively. Output compare interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set both when the counter is counting up or down.
> **Note:** It is not allowed to switch from edge-aligned mode to center-aligned mode as long as the counter is enabled (CEN=1)

#### 5. Bits 4 — DIR

Direction
- **`0`:** Counter used as upcounter
- **`1`:** Counter used as downcounter
> **Note:** This bit is read only when the timer is configured in Center-aligned mode or Encoder mode.

#### 6. Bits 3 — OPM

One-pulse mode
- **`0`:** Counter is not stopped at update event
- **`1`:** Counter stops counting at the next update event (clearing the bit CEN)

#### 7. Bits 2 — URS

Update request source This bit is set and cleared by software to select the UEV event sources.
- **`0`:** Any of the following events generate an update interrupt or DMA request if enabled. These events can be:
- Counter overflow/underflow
- Setting the UG bit
- Update generation through the slave mode controller
- **`1`:** Only counter overflow/underflow generates an update interrupt or DMA request if enabled.

#### 8. Bits 1 — UDIS

Update disable This bit is set and cleared by software to enable/disable UEV event generation.
- **`0`:** UEV enabled. The Update (UEV) event is generated by one of the following events:
- Counter overflow/underflow
- Setting the UG bit
- Update generation through the slave mode controller Buffered registers are then loaded with their preload values.
- **`1`:** UEV disabled. The Update event is not generated, shadow registers keep their value (ARR, PSC, CCRx). However the counter and the prescaler are reinitialized if the UG bit is set or if a hardware reset is received from the slave mode controller.

#### 9. Bits 0 — CEN

Counter enable
- **`0`:** Counter disabled
- **`1`:** Counter enabled
> **Note:** External clock, gated mode and encoder mode can work only if the CEN bit has been previously set by software. However trigger mode can set the CEN bit automatically by hardware. CEN is cleared automatically in one-pulse mode, when an update event occurs.

<a id="1342-timx-control-register-2-timx_cr2"></a>

## 13.4.2 TIMx control register 2 (TIMx_CR2)

**Address offset:** `0x04`  
**Reset value:** `0x0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `15:8` | **Reserved** |
| `7` | **TI1S** |
| `6:4` | **MMS[2:0]** |
| `3` | **CCDS** |
| `2:0` | **Reserved** |

### Bit-field descriptions — Register fields

#### 1. Bits 15:8 — Reserved

Must be kept at reset value.

#### 2. Bits 7 — TI1S

TI1 selection
- **`0`:** The TIMx_CH1 pin is connected to TI1 input
- **`1`:** The TIMx_CH1, CH2 and CH3 pins are connected to the TI1 input (XOR combination)

#### 3. Bits 6:4 — MMS[2:0]

Master mode selection These bits can be used to select the information to be sent in master mode to slave timers for synchronization (TRGO). The combination is as follows:
- **`000`:** Reset - the UG bit from the TIMx_EGR register is used as trigger output (TRGO). If the reset is generated by the trigger input (slave mode controller configured in reset mode) then the signal on TRGO is delayed compared to the actual reset.
- **`001`:** Enable - the Counter enable signal, CNT_EN, is used as trigger output (TRGO). It is useful to start several timers at the same time or to control a window in which a slave timer is enabled. The Counter Enable signal is generated by a logic OR between CEN control bit and the trigger input when configured in gated mode. When the Counter Enable signal is controlled by the trigger input, there is a delay on TRGO, except if the master/slave mode is selected (see the MSM bit description in TIMx_SMCR register).
- **`010`:** Update - The update event is selected as trigger output (TRGO). For instance a master timer can then be used as a prescaler for a slave timer.
- **`011`:** Compare Pulse - The trigger output send a positive pulse when the CC1IF flag is to be set (even if it was already high), as soon as a capture or a compare match occurred. (TRGO)
- **`100`:** Compare - OC1REF signal is used as trigger output (TRGO)
- **`101`:** Compare - OC2REF signal is used as trigger output (TRGO)
- **`110`:** Compare - OC3REF signal is used as trigger output (TRGO)
- **`111`:** Compare - OC4REF signal is used as trigger output (TRGO)
> **Note:** The clock of the slave timer and ADC must be enabled prior to receiving events from the master timer, and must not be changed on-the-fly while triggers are received from the master timer.

#### 4. Bits 3 — CCDS

Capture/compare DMA selection
- **`0`:** CCx DMA request sent when CCx event occurs
- **`1`:** CCx DMA requests sent when update event occurs

#### 5. Bits 2:0 — Reserved

Must be kept at reset value.

<a id="1343-timx-slave-mode-control-register-timx_smcr"></a>

## 13.4.3 TIMx slave mode control register (TIMx_SMCR)

**Address offset:** `0x08`  
**Reset value:** `0x0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `15` | **ETP** |
| `14` | **ECE** |
| `13:12` | **ETPS** |
| `11:8` | **ETF[3:0]** |
| `7` | **MSM** |
| `6:4` | **TS** |
| `3` | **Reserved** |
| `2:0` | **SMS** |

### Bit-field descriptions — Register fields

#### 1. Bits 15 — ETP

External trigger polarity This bit selects whether ETR or ETR is used for trigger operations
- **`0`:** ETR is noninverted, active at high level or rising edge
- **`1`:** ETR is inverted, active at low level or falling edge

#### 2. Bits 14 — ECE

External clock enable This bit enables External clock mode 2.
- **`0`:** External clock mode 2 disabled
- **`1`:** External clock mode 2 enabled. The counter is clocked by any active edge on the ETRF signal.
- **`1`:** Setting the ECE bit has the same effect as selecting external clock mode 1 with TRGI connected to ETRF (SMS=111 and TS=111).
- **`2`:** It is possible to simultaneously use external clock mode 2 with the following slave modes: reset mode, gated mode and trigger mode. Nevertheless, TRGI must not be connected to ETRF in this case (TS bits must not be 111).
- **`3`:** If external clock mode 1 and external clock mode 2 are enabled at the same time, the external clock input is ETRF.

#### 3. Bits 13:12 — ETPS

External trigger prescaler External trigger signal ETRP frequency must be at most 1/4 of CK_INT frequency. A prescaler can be enabled to reduce ETRP frequency. It is useful when inputting fast external clocks.
- **`00`:** Prescaler OFF
- **`01`:** ETRP frequency divided by 2
- **`10`:** ETRP frequency divided by 4
- **`11`:** ETRP frequency divided by 8

#### 4. Bits 11:8 — ETF[3:0]

External trigger filter This bit-field then defines the frequency used to sample ETRP signal and the length of the digital filter applied to ETRP. The digital filter is made of an event counter in which N consecutive events are needed to validate a transition on the output:
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

#### 5. Bits 7 — MSM

Master/Slave mode
- **`0`:** No action
- **`1`:** The effect of an event on the trigger input (TRGI) is delayed to allow a perfect synchronization between the current timer and its slaves (through TRGO). It is useful if we want to synchronize several timers on a single external event.

#### 6. Bits 6:4 — TS

Trigger selection This bit-field selects the trigger input to be used to synchronize the counter.
- **`000`:** Internal Trigger 0 (ITR0).
- **`001`:** Internal Trigger 1 (ITR1).
- **`010`:** Internal Trigger 2 (ITR2).
- **`011`:** Internal Trigger 3 (ITR3).
- **`100`:** TI1 Edge Detector (TI1F_ED)
- **`101`:** Filtered Timer Input 1 (TI1FP1)
- **`110`:** Filtered Timer Input 2 (TI2FP2)
- **`111`:** External Trigger input (ETRF) See Table 54: TIMx internal trigger connection on page 358 for more details on ITRx meaning for each Timer.
> **Note:** These bits must be changed only when they are not used (e.g. when SMS=000) to avoid wrong edge detections at the transition.

#### 7. Bits 3 — Reserved

Must be kept at reset value.

#### 8. Bits 2:0 — SMS

Slave mode selection When external signals are selected the active edge of the trigger signal (TRGI) is linked to the polarity selected on the external input (see Input Control register and Control register description.
- **`000`:** Slave mode disabled - if CEN = ‘1 then the prescaler is clocked directly by the internal clock.
- **`001`:** Encoder mode 1 - Counter counts up/down on TI1FP1 edge depending on TI2FP2 level.
- **`010`:** Encoder mode 2 - Counter counts up/down on TI2FP2 edge depending on TI1FP1 level.
- **`011`:** Encoder mode 3 - Counter counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input.
- **`100`:** Reset mode - Rising edge of the selected trigger input (TRGI) reinitializes the counter and generates an update of the registers.
- **`101`:** Gated mode - The counter clock is enabled when the trigger input (TRGI) is high. The counter stops (but is not reset) as soon as the trigger becomes low. Both start and stop of the counter are controlled.
- **`110`:** Trigger mode - The counter starts at a rising edge of the trigger TRGI (but it is not reset). Only the start of the counter is controlled.
- **`111`:** External Clock mode 1 - Rising edges of the selected trigger (TRGI) clock the counter.
> **Note:** The gated mode must not be used if TI1F_ED is selected as the trigger input (TS=100). Indeed, TI1F_ED outputs 1 pulse for each transition on TI1F, whereas the gated mode checks the level of the trigger signal. The clock of the slave timer must be enabled prior to receiving events from the master timer, and must not be changed on-the-fly while triggers are received from the master timer. Table 54. TIMx internal trigger connection Slave TIM           ITR0 (TS = 000)         ITR1 (TS = 001)        ITR2 (TS = 010)      ITR3 (TS = 011) TIM2           TIM1_TRGO                 Reserved             TIM3_TRGO               TIM4_TRGO TIM3           TIM1_TRGO               TIM2_TRGO              TIM5_TRGO               TIM4_TRGO TIM4           TIM1_TRGO               TIM2_TRGO              TIM3_TRGO                 Reserved TIM5           TIM2_TRGO               TIM3_TRGO              TIM4_TRGO                 Reserved

<a id="1344-timx-dmainterrupt-enable-register-timx_dier"></a>

## 13.4.4 TIMx DMA/Interrupt enable register (TIMx_DIER)

**Address offset:** `0x0C`  
**Reset value:** `0x0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `15` | **Reserved** |
| `14` | **TDE** |
| `13` | **Reserved** |
| `12` | **CC4DE** |
| `11` | **CC3DE** |
| `10` | **CC2DE** |
| `9` | **CC1DE** |
| `8` | **UDE** |
| `7` | **Reserved** |
| `6` | **TIE** |
| `5` | **Reserved** |
| `4` | **CC4IE** |
| `3` | **CC3IE** |
| `2` | **CC2IE** |
| `1` | **CC1IE** |
| `0` | **UIE** |

### Bit-field descriptions — Register fields

#### 1. Bits 15 — Reserved

Must be kept at reset value.

#### 2. Bits 14 — TDE

Trigger DMA request enable
- **`0`:** Trigger DMA request disabled.
- **`1`:** Trigger DMA request enabled.

#### 3. Bits 13 — Reserved

Always read as 0.

#### 4. Bits 12 — CC4DE

Capture/Compare 4 DMA request enable
- **`0`:** CC4 DMA request disabled.
- **`1`:** CC4 DMA request enabled.

#### 5. Bits 11 — CC3DE

Capture/Compare 3 DMA request enable
- **`0`:** CC3 DMA request disabled.
- **`1`:** CC3 DMA request enabled.

#### 6. Bits 10 — CC2DE

Capture/Compare 2 DMA request enable
- **`0`:** CC2 DMA request disabled.
- **`1`:** CC2 DMA request enabled.

#### 7. Bits 9 — CC1DE

Capture/Compare 1 DMA request enable
- **`0`:** CC1 DMA request disabled.
- **`1`:** CC1 DMA request enabled.

#### 8. Bits 8 — UDE

Update DMA request enable
- **`0`:** Update DMA request disabled.
- **`1`:** Update DMA request enabled.

#### 9. Bits 7 — Reserved

Must be kept at reset value.

#### 10. Bits 6 — TIE

Trigger interrupt enable
- **`0`:** Trigger interrupt disabled.
- **`1`:** Trigger interrupt enabled.

#### 11. Bits 5 — Reserved

Must be kept at reset value.

#### 12. Bits 4 — CC4IE

Capture/Compare 4 interrupt enable
- **`0`:** CC4 interrupt disabled.
- **`1`:** CC4 interrupt enabled.

#### 13. Bits 3 — CC3IE

Capture/Compare 3 interrupt enable
- **`0`:** CC3 interrupt disabled.
- **`1`:** CC3 interrupt enabled.

#### 14. Bits 2 — CC2IE

Capture/Compare 2 interrupt enable
- **`0`:** CC2 interrupt disabled
- **`1`:** CC2 interrupt enabled

#### 15. Bits 1 — CC1IE

Capture/Compare 1 interrupt enable
- **`0`:** CC1 interrupt disabled
- **`1`:** CC1 interrupt enabled

#### 16. Bits 0 — UIE

Update interrupt enable
- **`0`:** Update interrupt disabled
- **`1`:** Update interrupt enabled

<a id="1345-timx-status-register-timx_sr"></a>

## 13.4.5 TIMx status register (TIMx_SR)

**Address offset:** `0x10`  
**Reset value:** `0x0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `15:13` | **Reserved** |
| `12` | **CC4OF** |
| `11` | **CC3OF** |
| `10` | **CC2OF** |
| `9` | **CC1OF** |
| `8:7` | **Reserved** |
| `6` | **TIF** |
| `5` | **Reserved** |
| `4` | **CC4IF** |
| `3` | **CC3IF** |
| `2` | **CC2IF** |
| `1` | **CC1IF** |
| `0` | **UIF** |

### Bit-field descriptions — Register fields

#### 1. Bits 15:13 — Reserved

Must be kept at reset value.

#### 2. Bits 12 — CC4OF

Capture/Compare 4 overcapture flag refer to CC1OF description

#### 3. Bits 11 — CC3OF

Capture/Compare 3 overcapture flag refer to CC1OF description

#### 4. Bits 10 — CC2OF

Capture/compare 2 overcapture flag refer to CC1OF description

#### 5. Bits 9 — CC1OF

Capture/Compare 1 overcapture flag This flag is set by hardware only when the corresponding channel is configured in input capture mode. It is cleared by software by writing it to ‘0.
- **`0`:** No overcapture has been detected
- **`1`:** The counter value has been captured in TIMx_CCR1 register while CC1IF flag was already set

#### 6. Bits 8:7 — Reserved

Must be kept at reset value.

#### 7. Bits 6 — TIF

Trigger interrupt flag This flag is set by hardware on trigger event (active edge detected on TRGI input when the slave mode controller is enabled in all modes but gated mode. It is set when the counter starts or stops when gated mode is selected. It is cleared by software.
- **`0`:** No trigger event occurred
- **`1`:** Trigger interrupt pending

#### 8. Bits 5 — Reserved

Must be kept at reset value.

#### 9. Bits 4 — CC4IF

Capture/Compare 4 interrupt flag refer to CC1IF description

#### 10. Bits 3 — CC3IF

Capture/Compare 3 interrupt flag refer to CC1IF description

#### 11. Bits 2 — CC2IF

Capture/Compare 2 interrupt flag refer to CC1IF description

#### 12. Bits 1 — CC1IF

Capture/compare 1 interrupt flag If channel CC1 is configured as output: This flag is set by hardware when the counter matches the compare value, with some exception in center-aligned mode (refer to the CMS bits in the TIMx_CR1 register description). It is cleared by software.
- **`0`:** No match
- **`1`:** The content of the counter TIMx_CNT matches the content of the TIMx_CCR1 register. When the contents of TIMx_CCR1 are greater than the contents of TIMx_ARR, the CC1IF bit goes high on the counter overflow (in upcounting and up/down-counting modes) or underflow (in downcounting mode) If channel CC1 is configured as input: This bit is set by hardware on a capture. It is cleared by software or by reading the TIMx_CCR1 register.
- **`0`:** No input capture occurred
- **`1`:** The counter value has been captured in TIMx_CCR1 register (An edge has been detected on IC1 which matches the selected polarity)

#### 13. Bits 0 — UIF

Update interrupt flag. This bit is set by hardware on an update event. It is cleared by software.
- **`0`:** No update occurred.
- **`1`:** Update interrupt pending. This bit is set by hardware when the registers are updated:
  - At overflow or underflow (for TIM2 to TIM5) and if UDIS=0 in the TIMx_CR1 register.
  - When CNT is reinitialized by software using the UG bit in TIMx_EGR register, if URS=0 and UDIS=0 in the TIMx_CR1 register.
  - When CNT is reinitialized by a trigger event (refer to the slave mode control register description), if URS=0 and UDIS=0 in the TIMx_CR1 register.

<a id="1346-timx-event-generation-register-timx_egr"></a>

## 13.4.6 TIMx event generation register (TIMx_EGR)

**Address offset:** `0x14`  
**Reset value:** `0x0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `15:7` | **Reserved** |
| `6` | **TG** |
| `5` | **Reserved** |
| `4` | **CC4G** |
| `3` | **CC3G** |
| `2` | **CC2G** |
| `1` | **CC1G** |
| `0` | **UG** |

### Bit-field descriptions — Register fields

#### 1. Bits 15:7 — Reserved

Must be kept at reset value.

#### 2. Bits 6 — TG

Trigger generation This bit is set by software in order to generate an event, it is automatically cleared by hardware.
- **`0`:** No action
- **`1`:** The TIF flag is set in TIMx_SR register. Related interrupt or DMA transfer can occur if enabled.

#### 3. Bits 5 — Reserved

Must be kept at reset value.

#### 4. Bits 4 — CC4G

Capture/compare 4 generation refer to CC1G description

#### 5. Bits 3 — CC3G

Capture/compare 3 generation refer to CC1G description

#### 6. Bits 2 — CC2G

Capture/compare 2 generation refer to CC1G description

#### 7. Bits 1 — CC1G

Capture/compare 1 generation This bit is set by software in order to generate an event, it is automatically cleared by hardware.
- **`0`:** No action
- **`1`:** A capture/compare event is generated on channel 1: If channel CC1 is configured as output: CC1IF flag is set, Corresponding interrupt or DMA request is sent if enabled. If channel CC1 is configured as input: The current value of the counter is captured in TIMx_CCR1 register. The CC1IF flag is set, the corresponding interrupt or DMA request is sent if enabled. The CC1OF flag is set if the CC1IF flag was already high.

#### 8. Bits 0 — UG

Update generation This bit can be set by software, it is automatically cleared by hardware.
- **`0`:** No action
- **`1`:** Re-initialize the counter and generates an update of the registers. Note that the prescaler counter is cleared too (anyway the prescaler ratio is not affected). The counter is cleared if the center-aligned mode is selected or if DIR=0 (upcounting), else it takes the auto-reload value (TIMx_ARR) if DIR=1 (downcounting).

<a id="1347-timx-capturecompare-mode-register-1-timx_ccmr1"></a>

## 13.4.7 TIMx capture/compare mode register 1 (TIMx_CCMR1)

**Address offset:** `0x18`  
**Reset value:** `0x0000`

### Output compare configuration (CCxS = 00)

| Bit(s) | Field |
|---:|---|
| `15` | **OC2CE** |
| `14:12` | **OC2M[2:0]** |
| `11` | **OC2PE** |
| `10` | **OC2FE** |
| `9:8` | **CC2S[1:0]** |
| `7` | **OC1CE** |
| `6:4` | **OC1M** |
| `3` | **OC1PE** |
| `2` | **OC1FE** |
| `1:0` | **CC1S** |

### Bit-field descriptions — Output compare configuration (CCxS = 00)

#### 1. Bits 15 — OC2CE

Output compare 2 clear enable

#### 2. Bits 14:12 — OC2M[2:0]

Output compare 2 mode

#### 3. Bits 11 — OC2PE

Output compare 2 preload enable

#### 4. Bits 10 — OC2FE

Output compare 2 fast enable

#### 5. Bits 9:8 — CC2S[1:0]

Capture/Compare 2 selection This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC2 channel is configured as output
- **`01`:** CC2 channel is configured as input, IC2 is mapped on TI2
- **`10`:** CC2 channel is configured as input, IC2 is mapped on TI1
- **`11`:** CC2 channel is configured as input, IC2 is mapped on TRC. This mode is working only if an internal trigger input is selected through the TS bit (TIMx_SMCR register)
> **Note:** CC2S bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).

#### 6. Bits 7 — OC1CE

Output compare 1 clear enable OC1CE: Output compare 1 Clear Enable
- **`0`:** OC1Ref is not affected by the ETRF input
- **`1`:** OC1Ref is cleared as soon as a High level is detected on ETRF input

#### 7. Bits 6:4 — OC1M

Output compare 1 mode These bits define the behavior of the output reference signal OC1REF from which OC1 and OC1N are derived. OC1REF is active high whereas OC1 and OC1N active level depends on CC1P and CC1NP bits.
- **`000`:** Frozen - The comparison between the output compare register TIMx_CCR1 and the counter TIMx_CNT has no effect on the outputs.(this mode is used to generate a timing base).
- **`001`:** Set channel 1 to active level on match. OC1REF signal is forced high when the counter TIMx_CNT matches the capture/compare register 1 (TIMx_CCR1).
- **`010`:** Set channel 1 to inactive level on match. OC1REF signal is forced low when the counter TIMx_CNT matches the capture/compare register 1 (TIMx_CCR1).
- **`011`:** Toggle - OC1REF toggles when TIMx_CNT=TIMx_CCR1.
- **`100`:** Force inactive level - OC1REF is forced low.
- **`101`:** Force active level - OC1REF is forced high.
- **`110`:** PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0) as long as TIMx_CNT>TIMx_CCR1 else active (OC1REF=1).
- **`111`:** PWM mode 2 - In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1 else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else inactive.
> **Note:** In PWM mode 1 or 2, the OCREF level changes only when the result of the comparison changes or when the output compare mode switches from “frozen” mode to “PWM” mode.

#### 8. Bits 3 — OC1PE

Output compare 1 preload enable
- **`0`:** Preload register on TIMx_CCR1 disabled. TIMx_CCR1 can be written at anytime, the new value is taken in account immediately.
- **`1`:** Preload register on TIMx_CCR1 enabled. Read/Write operations access the preload register. TIMx_CCR1 preload value is loaded in the active register at each update event.
> **Note:** These bits can not be modified as long as LOCK level 3 has been programmed (LOCK bits in TIMx_BDTR register) and CC1S=00 (the channel is configured in output).

#### 9. Bits 2 — OC1FE

Output compare 1 fast enable This bit is used to accelerate the effect of an event on the trigger in input on the CC output.
- **`0`:** CC1 behaves normally depending on counter and CCR1 values even when the trigger is ON. The minimum delay to activate CC1 output when an edge occurs on the trigger input is 5 clock cycles.
- **`1`:** An active edge on the trigger input acts like a compare match on CC1 output. Then, OC is set to the compare level independently from the result of the comparison. Delay to sample the trigger input and to activate CC1 output is reduced to 3 clock cycles. OCFE acts only if the channel is configured in PWM1 or PWM2 mode.

#### 10. Bits 1:0 — CC1S

Capture/Compare 1 selection This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC1 channel is configured as output.
- **`01`:** CC1 channel is configured as input, IC1 is mapped on TI1.
- **`10`:** CC1 channel is configured as input, IC1 is mapped on TI2.
- **`11`:** CC1 channel is configured as input, IC1 is mapped on TRC. This mode is working only if an internal trigger input is selected through TS bit (TIMx_SMCR register)
> **Note:** CC1S bits are writable only when the channel is OFF (CC1E = 0 in TIMx_CCER). Input capture mode

### Input capture configuration (CCxS ≠ 00)

| Bit(s) | Field |
|---:|---|
| `15:12` | **IC2F** |
| `11:10` | **IC2PSC[1:0]** |
| `9:8` | **CC2S** |
| `7:4` | **IC1F** |
| `3:2` | **IC1PSC** |
| `1:0` | **CC1S** |

### Bit-field descriptions — Input capture configuration (CCxS ≠ 00)

#### 1. Bits 15:12 — IC2F

Input capture 2 filter

#### 2. Bits 11:10 — IC2PSC[1:0]

Input capture 2 prescaler

#### 3. Bits 9:8 — CC2S

Capture/compare 2 selection This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC2 channel is configured as output.
- **`01`:** CC2 channel is configured as input, IC2 is mapped on TI2.
- **`10`:** CC2 channel is configured as input, IC2 is mapped on TI1.
- **`11`:** CC2 channel is configured as input, IC2 is mapped on TRC. This mode is working only if an internal trigger input is selected through TS bit (TIMx_SMCR register)
> **Note:** CC2S bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).

#### 4. Bits 7:4 — IC1F

Input capture 1 filter This bit-field defines the frequency used to sample TI1 input and the length of the digital filter applied to TI1. The digital filter is made of an event counter in which N consecutive events are needed to validate a transition on the output:
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

#### 5. Bits 3:2 — IC1PSC

Input capture 1 prescaler This bit-field defines the ratio of the prescaler acting on CC1 input (IC1). The prescaler is reset as soon as CC1E=0 (TIMx_CCER register).
- **`00`:** no prescaler, capture is done each time an edge is detected on the capture input
- **`01`:** capture is done once every 2 events
- **`10`:** capture is done once every 4 events
- **`11`:** capture is done once every 8 events

#### 6. Bits 1:0 — CC1S

Capture/Compare 1 selection This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC1 channel is configured as output
- **`01`:** CC1 channel is configured as input, IC1 is mapped on TI1
- **`10`:** CC1 channel is configured as input, IC1 is mapped on TI2
- **`11`:** CC1 channel is configured as input, IC1 is mapped on TRC. This mode is working only if an internal trigger input is selected through TS bit (TIMx_SMCR register)
> **Note:** CC1S bits are writable only when the channel is OFF (CC1E = 0 in TIMx_CCER).

<a id="1348-timx-capturecompare-mode-register-2-timx_ccmr2"></a>

## 13.4.8 TIMx capture/compare mode register 2 (TIMx_CCMR2)

**Address offset:** `0x1C`  
**Reset value:** `0x0000`

### Output compare configuration (CCxS = 00)

| Bit(s) | Field |
|---:|---|
| `15` | **OC4CE** |
| `14:12` | **OC4M** |
| `11` | **OC4PE** |
| `10` | **OC4FE** |
| `9:8` | **CC4S** |
| `7` | **OC3CE** |
| `6:4` | **OC3M** |
| `3` | **OC3PE** |
| `2` | **OC3FE** |
| `1:0` | **CC3S** |

### Bit-field descriptions — Output compare configuration (CCxS = 00)

#### 1. Bits 15 — OC4CE

Output compare 4 clear enable

#### 2. Bits 14:12 — OC4M

Output compare 4 mode

#### 3. Bits 11 — OC4PE

Output compare 4 preload enable

#### 4. Bits 10 — OC4FE

Output compare 4 fast enable

#### 5. Bits 9:8 — CC4S

Capture/Compare 4 selection This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC4 channel is configured as output
- **`01`:** CC4 channel is configured as input, IC4 is mapped on TI4
- **`10`:** CC4 channel is configured as input, IC4 is mapped on TI3
- **`11`:** CC4 channel is configured as input, IC4 is mapped on TRC. This mode is working only if an internal trigger input is selected through TS bit (TIMx_SMCR register)
> **Note:** CC4S bits are writable only when the channel is OFF (CC4E = 0 in TIMx_CCER).

#### 6. Bits 7 — OC3CE

Output compare 3 clear enable

#### 7. Bits 6:4 — OC3M

Output compare 3 mode

#### 8. Bits 3 — OC3PE

Output compare 3 preload enable

#### 9. Bits 2 — OC3FE

Output compare 3 fast enable

#### 10. Bits 1:0 — CC3S

Capture/Compare 3 selection This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC3 channel is configured as output
- **`01`:** CC3 channel is configured as input, IC3 is mapped on TI3
- **`10`:** CC3 channel is configured as input, IC3 is mapped on TI4
- **`11`:** CC3 channel is configured as input, IC3 is mapped on TRC. This mode is working only if an internal trigger input is selected through TS bit (TIMx_SMCR register)
> **Note:** CC3S bits are writable only when the channel is OFF (CC3E = 0 in TIMx_CCER). Input capture mode

### Input capture configuration (CCxS ≠ 00)

| Bit(s) | Field |
|---:|---|
| `15:12` | **IC4F** |
| `11:10` | **IC4PSC** |
| `9:8` | **CC4S** |
| `7:4` | **IC3F** |
| `3:2` | **IC3PSC** |
| `1:0` | **CC3S** |

### Bit-field descriptions — Input capture configuration (CCxS ≠ 00)

#### 1. Bits 15:12 — IC4F

Input capture 4 filter

#### 2. Bits 11:10 — IC4PSC

Input capture 4 prescaler

#### 3. Bits 9:8 — CC4S

Capture/Compare 4 selection This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC4 channel is configured as output
- **`01`:** CC4 channel is configured as input, IC4 is mapped on TI4
- **`10`:** CC4 channel is configured as input, IC4 is mapped on TI3
- **`11`:** CC4 channel is configured as input, IC4 is mapped on TRC. This mode is working only if an internal trigger input is selected through TS bit (TIMx_SMCR register)
> **Note:** CC4S bits are writable only when the channel is OFF (CC4E = 0 in TIMx_CCER).

#### 4. Bits 7:4 — IC3F

Input capture 3 filter

#### 5. Bits 3:2 — IC3PSC

Input capture 3 prescaler

#### 6. Bits 1:0 — CC3S

Capture/Compare 3 selection This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC3 channel is configured as output
- **`01`:** CC3 channel is configured as input, IC3 is mapped on TI3
- **`10`:** CC3 channel is configured as input, IC3 is mapped on TI4
- **`11`:** CC3 channel is configured as input, IC3 is mapped on TRC. This mode is working only if an internal trigger input is selected through TS bit (TIMx_SMCR register)
> **Note:** CC3S bits are writable only when the channel is OFF (CC3E = 0 in TIMx_CCER).

<a id="1349-timx-capturecompare-enable-register-timx_ccer"></a>

## 13.4.9 TIMx capture/compare enable register (TIMx_CCER)

**Address offset:** `0x20`  
**Reset value:** `0x0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `15` | **CC4NP** |
| `14` | **Reserved** |
| `13` | **CC4P** |
| `12` | **CC4E** |
| `11` | **CC3NP** |
| `10` | **Reserved** |
| `9` | **CC3P** |
| `8` | **CC3E** |
| `7` | **CC2NP** |
| `6` | **Reserved** |
| `5` | **CC2P** |
| `4` | **CC2E** |
| `3` | **CC1NP** |
| `2` | **Reserved** |
| `1` | **CC1P** |
| `0` | **CC1E** |

### Bit-field descriptions — Register fields

#### 1. Bits 15 — CC4NP

Capture/Compare 4 output Polarity. Refer to CC1NP description

#### 2. Bits 14 — Reserved

Must be kept at reset value.

#### 3. Bits 13 — CC4P

Capture/Compare 4 output Polarity. refer to CC1P description

#### 4. Bits 12 — CC4E

Capture/Compare 4 output enable. refer to CC1E description

#### 5. Bits 11 — CC3NP

Capture/Compare 3 output Polarity. refer to CC1NP description

#### 6. Bits 10 — Reserved

Must be kept at reset value.

#### 7. Bits 9 — CC3P

Capture/Compare 3 output Polarity. refer to CC1P description

#### 8. Bits 8 — CC3E

Capture/Compare 3 output enable. refer to CC1E description

#### 9. Bits 7 — CC2NP

Capture/Compare 2 output Polarity. refer to CC1NP description

#### 10. Bits 6 — Reserved

Must be kept at reset value.

#### 11. Bits 5 — CC2P

Capture/Compare 2 output Polarity. refer to CC1P description

#### 12. Bits 4 — CC2E

Capture/Compare 2 output enable. refer to CC1E description

#### 13. Bits 3 — CC1NP

Capture/Compare 1 output Polarity. CC1 channel configured as output: CC1NP must be kept cleared in this case. CC1 channel configured as input: This bit is used in conjunction with CC1P to define TI1FP1/TI2FP1 polarity. refer to CC1P description.

#### 14. Bits 2 — Reserved

Must be kept at reset value.

#### 15. Bits 1 — CC1P

Capture/Compare 1 output Polarity. CC1 channel configured as output:
- **`0`:** OC1 active high
- **`1`:** OC1 active low CC1 channel configured as input: CC1NP/CC1P bits select TI1FP1 and TI2FP1 polarity for trigger or capture operations.
- **`00`:** noninverted/rising edge Circuit is sensitive to TIxFP1 rising edge (capture, trigger in reset, external clock or trigger mode), TIxFP1 is not inverted (trigger in gated mode, encoder mode).
- **`01`:** inverted/falling edge Circuit is sensitive to TIxFP1 falling edge (capture, trigger in reset, external clock or trigger mode), TIxFP1 is inverted (trigger in gated mode, encoder mode).
- **`10`:** reserved, do not use this configuration.
- **`11`:** noninverted/both edges Circuit is sensitive to both TIxFP1 rising and falling edges (capture, trigger in reset, external clock or trigger mode), TIxFP1 is not inverted (trigger in gated mode). This configuration must not be used for encoder mode.

#### 16. Bits 0 — CC1E

Capture/Compare 1 output enable. CC1 channel configured as output:
- **`0`:** Off - OC1 is not active
- **`1`:** On - OC1 signal is output on the corresponding output pin CC1 channel configured as input: This bit determines if a capture of the counter value can actually be done into the input capture/compare register 1 (TIMx_CCR1) or not.
- **`0`:** Capture disabled
- **`1`:** Capture enabled Table 55. Output control bit for standard OCx channels CCxE bit          OCx output state 0              Output Disabled (OCx=0, OCx_EN=0) 1              OCx=OCxREF + Polarity, OCx_EN=1
> **Note:** The state of the external IO pins connected to the standard OCx channels depends on the OCx channel state and the GPIO registers.

<a id="13410-timx-counter-timx_cnt"></a>

## 13.4.10 TIMx counter (TIMx_CNT)

**Address offset:** `0x24`  
**Reset value:** `0x0000 0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `31:16` | **CNT[31:16]** |
| `15:0` | **CNT[15:0]** |

### Bit-field descriptions — Register fields

#### 1. Bits 31:16 — CNT[31:16]

High counter value (on TIM2 and TIM5).

#### 2. Bits 15:0 — CNT[15:0]

Counter value

<a id="13411-timx-prescaler-timx_psc"></a>

## 13.4.11 TIMx prescaler (TIMx_PSC)

**Address offset:** `0x28`  
**Reset value:** `0x0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `15:0` | **PSC[15:0]** |

### Bit-field descriptions — Register fields

#### 1. Bits 15:0 — PSC[15:0]

Prescaler value The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1). PSC contains the value to be loaded in the active prescaler register at each update event (including when the counter is cleared through UG bit of TIMx_EGR register or through trigger controller when configured in “reset mode”).

<a id="13412-timx-auto-reload-register-timx_arr"></a>

## 13.4.12 TIMx auto-reload register (TIMx_ARR)

**Address offset:** `0x2C`  
**Reset value:** `0xFFFF FFFF`

### Register layout

| Bit(s) | Field |
|---:|---|
| `15:0` | **ARR[15:0]** |

### Bit-field descriptions — Register fields

#### 1. Bits 15:0 — ARR[15:0]

Auto-reload value ARR is the value to be loaded in the actual auto-reload register. Refer to the Section 13.3.1: Time-base unit for more details about ARR update and behavior. The counter is blocked while the auto-reload value is null.

<a id="timx-repetition-counter-register-timx_rcr"></a>

## TIMx repetition counter register (TIMx_RCR)

**Address offset in supplied struct:** `0x30`

`RCR` means **repetition counter register**.

For STM32 advanced timers, the repetition counter can delay when update events
are generated. Instead of producing an update event every time `CNT` reaches
`ARR`, the timer can wait for multiple counter cycles.

Basic idea:

```text
CNT reaches ARR -> repetition counter changes
repetition counter expires -> real update event
```

This is useful for advanced PWM and motor-control timing, where you may want the
PWM counter to repeat several times before loading new buffered values.

> **TIM2-TIM5 note:** RM0368 section 13.4 documents TIM2 to TIM5 registers and
> does not list `RCR` as a TIM2-TIM5 register. Treat offset `0x30` as reserved
> for TIM2-TIM5 unless the exact device header/manual says otherwise.

<a id="13413-timx-capturecompare-register-1-timx_ccr1"></a>

## 13.4.13 TIMx capture/compare register 1 (TIMx_CCR1)

**Address offset:** `0x34`  
**Reset value:** `0x0000 0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `31:16` | **CCR1[31:16]** |
| `15:0` | **CCR1[15:0]** |

### Bit-field descriptions — Register fields

#### 1. Bits 31:16 — CCR1[31:16]

High Capture/Compare 1 value (on TIM2 and TIM5).

#### 2. Bits 15:0 — CCR1[15:0]

Low Capture/Compare 1 value If channel CC1 is configured as output: CCR1 is the value to be loaded in the actual capture/compare 1 register (preload value). It is loaded permanently if the preload feature is not selected in the TIMx_CCMR1 register (bit OC1PE). Else the preload value is copied in the active capture/compare 1 register when an update event occurs. The active capture/compare register contains the value to be compared to the counter TIMx_CNT and signaled on OC1 output. If channel CC1is configured as input: CCR1 is the counter value transferred by the last input capture 1 event (IC1). The TIMx_CCR1 register is read-only and cannot be programmed.

<a id="13414-timx-capturecompare-register-2-timx_ccr2"></a>

## 13.4.14 TIMx capture/compare register 2 (TIMx_CCR2)

**Address offset:** `0x38`  
**Reset value:** `0x0000 0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `31:16` | **CCR2[31:16]** |
| `15:0` | **CCR2[15:0]** |

### Bit-field descriptions — Register fields

#### 1. Bits 31:16 — CCR2[31:16]

High Capture/Compare 2 value (on TIM2 and TIM5).

#### 2. Bits 15:0 — CCR2[15:0]

Low Capture/Compare 2 value If channel CC2 is configured as output: CCR2 is the value to be loaded in the actual capture/compare 2 register (preload value). It is loaded permanently if the preload feature is not selected in the TIMx_CCMR register (bit OC2PE). Else the preload value is copied in the active capture/compare 2 register when an update event occurs. The active capture/compare register contains the value to be compared to the counter TIMx_CNT and signalled on OC2 output. If channel CC2 is configured as input: CCR2 is the counter value transferred by the last input capture 2 event (IC2). The TIMx_CCR2 register is read-only and cannot be programmed.

<a id="13415-timx-capturecompare-register-3-timx_ccr3"></a>

## 13.4.15 TIMx capture/compare register 3 (TIMx_CCR3)

**Address offset:** `0x3C`  
**Reset value:** `0x0000 0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `31:16` | **CCR3[31:16]** |
| `15:0` | **CCR3[15:0]** |

### Bit-field descriptions — Register fields

#### 1. Bits 31:16 — CCR3[31:16]

High Capture/Compare 3 value (on TIM2 and TIM5).

#### 2. Bits 15:0 — CCR3[15:0]

Low Capture/Compare value If channel CC3 is configured as output: CCR3 is the value to be loaded in the actual capture/compare 3 register (preload value). It is loaded permanently if the preload feature is not selected in the TIMx_CCMR register (bit OC3PE). Else the preload value is copied in the active capture/compare 3 register when an update event occurs. The active capture/compare register contains the value to be compared to the counter TIMx_CNT and signaled on OC3 output. If channel CC3 is configured as input: CCR3 is the counter value transferred by the last input capture 3 event (IC3). The TIMx_CCR3 register is read-only and cannot be programmed.

<a id="13416-timx-capturecompare-register-4-timx_ccr4"></a>

## 13.4.16 TIMx capture/compare register 4 (TIMx_CCR4)

**Address offset:** `0x40`  
**Reset value:** `0x0000 0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `31:16` | **CCR4[31:16]** |
| `15:0` | **CCR4[15:0]** |

### Bit-field descriptions — Register fields

#### 1. Bits 31:16 — CCR4[31:16]

High Capture/Compare 4 value (on TIM2 and TIM5).

#### 2. Bits 15:0 — CCR4[15:0]

Low Capture/Compare value 1. if CC4 channel is configured as output (CC4S bits): CCR4 is the value to be loaded in the actual capture/compare 4 register (preload value). It is loaded permanently if the preload feature is not selected in the TIMx_CCMR register (bit OC4PE). Else the preload value is copied in the active capture/compare 4 register when an update event occurs. The active capture/compare register contains the value to be compared to the counter TIMx_CNT and signalled on OC4 output. 2. if CC4 channel is configured as input (CC4S bits in TIMx_CCMR4 register): CCR4 is the counter value transferred by the last input capture 4 event (IC4). The TIMx_CCR4 register is read-only and cannot be programmed.

<a id="timx-break-and-dead-time-register-timx_bdtr"></a>

## TIMx break and dead-time register (TIMx_BDTR)

**Address offset in supplied struct:** `0x44`

`BDTR` means **break and dead-time register**.

This is mainly an advanced-timer register. It is used for power electronics and
motor-control PWM where outputs must be protected.

Important mechanism:

- **Dead time** inserts a short delay between complementary PWM outputs, so both
  sides of a half-bridge are not on at the same time.
- **Break input** can force PWM outputs into a safe state when a fault happens.
- **Main output enable** controls whether advanced-timer outputs are allowed to
  drive the pins.

For ordinary LED PWM or simple timing, you usually do not need `BDTR`.

> **TIM2-TIM5 note:** RM0368 section 13.4 documents TIM2 to TIM5 registers and
> does not list `BDTR` as a TIM2-TIM5 register. Treat offset `0x44` as reserved
> for TIM2-TIM5 unless the exact device header/manual says otherwise.

<a id="13417-timx-dma-control-register-timx_dcr"></a>

## 13.4.17 TIMx DMA control register (TIMx_DCR)

**Address offset:** `0x48`  
**Reset value:** `0x0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `15:13` | **Reserved** |
| `12:8` | **DBL[4:0]** |
| `7:5` | **Reserved** |
| `4:0` | **DBA[4:0]** |

### Bit-field descriptions — Register fields

#### 1. Bits 15:13 — Reserved

Must be kept at reset value.

#### 2. Bits 12:8 — DBL[4:0]

DMA burst length This 5-bit vector defines the number of DMA transfers (the timer recognizes a burst transfer when a read or a write access is done to the TIMx_DMAR address). 00000: 1 transfer, 00001: 2 transfers, 00010: 3 transfers, ... 10001: 18 transfers.

#### 3. Bits 7:5 — Reserved

Must be kept at reset value.

#### 4. Bits 4:0 — DBA[4:0]

DMA base address This 5-bit vector defines the base-address for DMA transfers (when read/write access are done through the TIMx_DMAR address). DBA is defined as an offset starting from the address of the TIMx_CR1 register. Example: 00000: TIMx_CR1, 00001: TIMx_CR2, 00010: TIMx_SMCR, ... Example: Let us consider the following transfer: DBL = 7 transfers & DBA = TIMx_CR1. In this case the transfer is done to/from 7 registers starting from the TIMx_CR1 address.

<a id="13418-timx-dma-address-for-full-transfer-timx_dmar"></a>

## 13.4.18 TIMx DMA address for full transfer (TIMx_DMAR)

**Address offset:** `0x4C`  
**Reset value:** `0x0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `15:0` | **DMAB[15:0]** |

### Bit-field descriptions — Register fields

#### 1. Bits 15:0 — DMAB[15:0]

DMA register for burst accesses A read or write operation to the DMAR register accesses the register located at the address (TIMx_CR1 address) + (DBA + DMA index) x 4 where TIMx_CR1 address is the address of the control register 1, DBA is the DMA base address configured in TIMx_DCR register, DMA index is automatically controlled by the DMA transfer, and ranges from 0 to DBL (DBL configured in TIMx_DCR). Example of how to use the DMA burst feature In this example the timer DMA burst feature is used to update the contents of the CCRx registers (x = 2, 3, 4) with the DMA transferring half words into the CCRx registers. This is done in the following steps: 1.        Configure the corresponding DMA channel as follows:
- DMA channel peripheral address is the DMAR register address
- DMA channel memory address is the address of the buffer in the RAM containing the data to be transferred by DMA into CCRx registers.
- Number of data to transfer = 3 (See note below).
- Circular mode disabled. 2.        Configure the DCR register by configuring the DBA and DBL bit fields as follows: DBL = 3 transfers, DBA = 0xE. 3.        Enable the TIMx update DMA request (set the UDE bit in the DIER register). 4.        Enable TIMx 5.        Enable the DMA channel
> **Note:** This example is for the case where every CCRx register to be updated once. If every CCRx register is to be updated twice for example, the number of data to transfer should be 6. Let's take the example of a buffer in the RAM containing data1, data2, data3, data4, data5 and data6. The data is transferred to the CCRx registers as follows: on the first update DMA request, data1 is transferred to CCR2, data2 is transferred to CCR3, data3 is transferred to CCR4 and on the second update DMA request, data4 is transferred to CCR2, data5 is transferred to CCR3 and data6 is transferred to CCR4.

<a id="13419-tim2-option-register-tim2_or"></a>

## 13.4.19 TIM2 option register (TIM2_OR)

**Address offset:** `0x50`  
**Reset value:** `0x0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `15:12` | **Reserved** |
| `11:10` | **ITR1_RMP** |
| `9:0` | **Reserved** |

### Bit-field descriptions — Register fields

#### 1. Bits 15:12 — Reserved

Must be kept at reset value.

#### 2. Bits 11:10 — ITR1_RMP

Internal trigger 1 remap Set and cleared by software.
- **`00`:** Reserved
- **`01`:** PTP trigger output is connected to TIM2_ITR1
- **`10`:** OTG FS SOF is connected to the TIM2_ITR1 input
- **`11`:** OTG HS SOF is connected to the TIM2_ITR1 input

#### 3. Bits 9:0 — Reserved

Must be kept at reset value.

<a id="13420-tim5-option-register-tim5_or"></a>

## 13.4.20 TIM5 option register (TIM5_OR)

**Address offset:** `0x50`  
**Reset value:** `0x0000`

### Register layout

| Bit(s) | Field |
|---:|---|
| `15:8` | **Reserved** |
| `7:6` | **TI4_RMP** |
| `5:0` | **Reserved** |

### Bit-field descriptions — Register fields

#### 1. Bits 15:8 — Reserved

Must be kept at reset value.

#### 2. Bits 7:6 — TI4_RMP

Timer Input 4 remap Set and cleared by software.
- **`00`:** TIM5 Channel4 is connected to the GPIO: Refer to the Alternate function mapping table in the datasheets.
- **`01`:** the LSI internal clock is connected to the TIM5_CH4 input for calibration purposes
- **`10`:** the LSE internal clock is connected to the TIM5_CH4 input for calibration purposes
- **`11`:** the RTC wake-up interrupt is connected to TIM5_CH4 input for calibration purposes. Wake-up interrupt should be enabled.

#### 3. Bits 5:0 — Reserved

Must be kept at reset value.

## Source and scope

- **Source:** RM0368 Rev. 6, *STM32F401xB/C and STM32F401xD/E advanced Arm-based 32-bit MCUs*, Section **13.4 TIM2 to TIM5 registers**, printed pages **353–373**.
- This README documents subsections **13.4.1–13.4.20** in the same order as RM0368. The following register-map table (13.4.21) is not reproduced.
- The bit-field wording and encodings are drawn from the supplied manual extraction. Consult the official reference manual for the complete device context before using the details in production firmware.
