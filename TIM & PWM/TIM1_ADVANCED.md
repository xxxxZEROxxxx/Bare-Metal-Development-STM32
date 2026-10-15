# STM32F401 TIM1 Advanced-Control Timer Register Reference

> Source: STMicroelectronics RM0368 Rev. 6, Section 12.4, “TIM1 registers” (printed pages 288–313). Register headings and order follow the manual. Descriptions are based on the register subsections, not a generic timer template.

This file documents the **advanced-control timer TIM1**. It follows RM0368 Section 12.4 (printed pages 288–313), including the register-specific fields for complementary PWM outputs, break/dead-time control, repetition counting, and DMA burst transfers.

## Register navigation

| Offset | Register | Full name | Main job |
|---:|---|---|---|
| `0x00` | [`CR1`](#1241-tim1-control-register-1-timx_cr1) | Control register 1 | Enables the counter and controls count direction/mode. |
| `0x04` | [`CR2`](#1242-tim1-control-register-2-timx_cr2) | Control register 2 | Controls output idle states, master trigger, and capture/compare preload behavior. |
| `0x08` | [`SMCR`](#1243-tim1-slave-mode-control-register-timx_smcr) | Slave mode control register | Selects trigger, external clock, encoder, gated, or slave modes. |
| `0x0C` | [`DIER`](#1244-tim1-dmainterrupt-enable-register-timx_dier) | DMA/interrupt enable register | Enables update, capture/compare, commutation, trigger, break, and DMA requests. |
| `0x10` | [`SR`](#1245-tim1-status-register-timx_sr) | Status register | Holds event flags such as `UIF`, `CCxIF`, `COMIF`, `TIF`, and `BIF`. |
| `0x14` | [`EGR`](#1246-tim1-event-generation-register-timx_egr) | Event generation register | Lets software force update, capture/compare, commutation, trigger, or break events. |
| `0x18` | [`CCMR1`](#1247-tim1-capturecompare-mode-register-1-timx_ccmr1) | Capture/compare mode register 1 | Configures channel 1 and channel 2 mode. |
| `0x1C` | [`CCMR2`](#1248-tim1-capturecompare-mode-register-2-timx_ccmr2) | Capture/compare mode register 2 | Configures channel 3 and channel 4 mode. |
| `0x20` | [`CCER`](#1249-tim1-capturecompare-enable-register-timx_ccer) | Capture/compare enable register | Enables normal/complementary outputs and selects polarity. |
| `0x24` | [`CNT`](#12410-tim1-counter-timx_cnt) | Counter register | Stores the current timer count value. |
| `0x28` | [`PSC`](#12411-tim1-prescaler-timx_psc) | Prescaler | Divides the timer clock before it reaches `CNT`. |
| `0x2C` | [`ARR`](#12412-tim1-auto-reload-register-timx_arr) | Auto-reload register | Sets the period limit. |
| `0x30` | [`RCR`](#12413-tim1-repetition-counter-register-timx_rcr) | Repetition counter register | Delays update events by a number of counter cycles. |
| `0x34` | [`CCR1`](#12414-tim1-capturecompare-register-1-timx_ccr1) | Capture/compare register 1 | Channel 1 compare value or captured input value. |
| `0x38` | [`CCR2`](#12415-tim1-capturecompare-register-2-timx_ccr2) | Capture/compare register 2 | Channel 2 compare value or captured input value. |
| `0x3C` | [`CCR3`](#12416-tim1-capturecompare-register-3-timx_ccr3) | Capture/compare register 3 | Channel 3 compare value or captured input value. |
| `0x40` | [`CCR4`](#12417-tim1-capturecompare-register-4-timx_ccr4) | Capture/compare register 4 | Channel 4 compare value or captured input value. |
| `0x44` | [`BDTR`](#12418-tim1-break-and-dead-time-register-timx_bdtr) | Break and dead-time register | Controls output safety, dead time, break input, and main output enable. |
| `0x48` | [`DCR`](#12419-tim1-dma-control-register-timx_dcr) | DMA control register | Configures timer DMA burst base address and burst length. |
| `0x4C` | [`DMAR`](#12420-tim1-dma-address-for-full-transfer-timx_dmar) | DMA address register | Access window used by timer DMA burst transfers. |

## Register structure

The structure is shown in the `__IO uint32_t` style used by STM32 CMSIS headers. Reserved members preserve the offsets where a timer does not implement a register. Verify the device header for the exact MCU variant before using the structure for memory-mapped access.

<pre><code class="language-c">
typedef struct
{
    __IO uint32_t <a href="#1241-tim1-control-register-1-timx_cr1">CR1</a>;          /*!< TIM1 control register 1,              Address offset: 0x00 */
    __IO uint32_t <a href="#1242-tim1-control-register-2-timx_cr2">CR2</a>;          /*!< TIM1 control register 2,              Address offset: 0x04 */
    __IO uint32_t <a href="#1243-tim1-slave-mode-control-register-timx_smcr">SMCR</a>;         /*!< TIM1 slave mode control register,     Address offset: 0x08 */
    __IO uint32_t <a href="#1244-tim1-dmainterrupt-enable-register-timx_dier">DIER</a>;         /*!< TIM1 DMA/interrupt enable register,   Address offset: 0x0C */
    __IO uint32_t <a href="#1245-tim1-status-register-timx_sr">SR</a>;           /*!< TIM1 status register,                 Address offset: 0x10 */
    __IO uint32_t <a href="#1246-tim1-event-generation-register-timx_egr">EGR</a>;          /*!< TIM1 event generation register,       Address offset: 0x14 */
    __IO uint32_t <a href="#1247-tim1-capturecompare-mode-register-1-timx_ccmr1">CCMR1</a>;        /*!< TIM1 capture/compare mode register 1, Address offset: 0x18 */
    __IO uint32_t <a href="#1248-tim1-capturecompare-mode-register-2-timx_ccmr2">CCMR2</a>;        /*!< TIM1 capture/compare mode register 2, Address offset: 0x1C */
    __IO uint32_t <a href="#1249-tim1-capturecompare-enable-register-timx_ccer">CCER</a>;         /*!< TIM1 capture/compare enable register, Address offset: 0x20 */
    __IO uint32_t <a href="#12410-tim1-counter-timx_cnt">CNT</a>;          /*!< TIM1 counter register,                Address offset: 0x24 */
    __IO uint32_t <a href="#12411-tim1-prescaler-timx_psc">PSC</a>;          /*!< TIM1 prescaler,                       Address offset: 0x28 */
    __IO uint32_t <a href="#12412-tim1-auto-reload-register-timx_arr">ARR</a>;          /*!< TIM1 auto-reload register,            Address offset: 0x2C */
    __IO uint32_t <a href="#12413-tim1-repetition-counter-register-timx_rcr">RCR</a>;          /*!< TIM1 repetition counter register,     Address offset: 0x30 */
    __IO uint32_t <a href="#12414-tim1-capturecompare-register-1-timx_ccr1">CCR1</a>;         /*!< TIM1 capture/compare register 1,       Address offset: 0x34 */
    __IO uint32_t <a href="#12415-tim1-capturecompare-register-2-timx_ccr2">CCR2</a>;         /*!< TIM1 capture/compare register 2,       Address offset: 0x38 */
    __IO uint32_t <a href="#12416-tim1-capturecompare-register-3-timx_ccr3">CCR3</a>;         /*!< TIM1 capture/compare register 3,       Address offset: 0x3C */
    __IO uint32_t <a href="#12417-tim1-capturecompare-register-4-timx_ccr4">CCR4</a>;         /*!< TIM1 capture/compare register 4,       Address offset: 0x40 */
    __IO uint32_t <a href="#12418-tim1-break-and-dead-time-register-timx_bdtr">BDTR</a>;         /*!< TIM1 break and dead-time register,     Address offset: 0x44 */
    __IO uint32_t <a href="#12419-tim1-dma-control-register-timx_dcr">DCR</a>;          /*!< TIM1 DMA control register,             Address offset: 0x48 */
    __IO uint32_t <a href="#12420-tim1-dma-address-for-full-transfer-timx_dmar">DMAR</a>;         /*!< TIM1 DMA address for full transfer,    Address offset: 0x4C */
} TIM1_TypeDef;
</code></pre>

## Register descriptions

<a id="1241-tim1-control-register-1-timx_cr1"></a>

### 12.4.1 TIM1 control register 1 (TIMx_CR1)

**Address offset:** `0x00`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:10` | **Reserved** |
| `9:8` | **CKD[1:0]** |
| `7` | **ARPE** |
| `6:5` | **CMS[1:0]** |
| `4` | **DIR** |
| `3` | **OPM** |
| `2` | **URS** |
| `1` | **UDIS** |
| `0` | **CEN** |

#### Bit-field descriptions

##### 1. Bits 15:10 — Reserved

Must be kept at reset value.

##### 2. Bits 9:8 — CKD[1:0]

Clock division
This bit-field indicates the division ratio between the timer clock (CK_INT) frequency and the dead-time and sampling clock (tDTS)used by the dead-time generators and the digital filters (ETR, TIx),
- **`00`:** tDTS=tCK_INT
- **`01`:** tDTS=2*tCK_INT
- **`10`:** tDTS=4*tCK_INT
- **`11`:** Reserved, do not program this value

##### 3. Bits 7 — ARPE

Auto-reload preload enable
- **`0`:** TIMx_ARR register is not buffered
- **`1`:** TIMx_ARR register is buffered

##### 4. Bits 6:5 — CMS[1:0]

Center-aligned mode selection
- **`00`:** Edge-aligned mode. The counter counts up or down depending on the direction bit
(DIR).
- **`01`:** Center-aligned mode 1. The counter counts up and down alternatively. Output compare
interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set only when the counter is counting down.
- **`10`:** Center-aligned mode 2. The counter counts up and down alternatively. Output compare
interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set only when the counter is counting up.
- **`11`:** Center-aligned mode 3. The counter counts up and down alternatively. Output compare
interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set both when the counter is counting up or down.
**Note:** It is not allowed to switch from edge-aligned mode to center-aligned mode as long as the counter is enabled (CEN=1)

##### 5. Bits 4 — DIR

Direction
- **`0`:** Counter used as upcounter
- **`1`:** Counter used as downcounter
**Note:** This bit is read only when the timer is configured in Center-aligned mode or Encoder mode.

##### 6. Bits 3 — OPM

One pulse mode
- **`0`:** Counter is not stopped at update event
- **`1`:** Counter stops counting at the next update event (clearing the bit CEN)

##### 7. Bits 2 — URS

Update request source
This bit is set and cleared by software to select the UEV event sources.
- **`0`:** Any of the following events generate an update interrupt or DMA request if enabled.
These events can be:
- Counter overflow/underflow
- Setting the UG bit
- Update generation through the slave mode controller
- **`1`:** Only counter overflow/underflow generates an update interrupt or DMA request if
enabled.

##### 8. Bits 1 — UDIS

Update disable
This bit is set and cleared by software to enable/disable UEV event generation.
- **`0`:** UEV enabled. The Update (UEV) event is generated by one of the following events:
- Counter overflow/underflow
- Setting the UG bit
- Update generation through the slave mode controller
Buffered registers are then loaded with their preload values.
- **`1`:** UEV disabled. The Update event is not generated, shadow registers keep their value
(ARR, PSC, CCRx). However the counter and the prescaler are reinitialized if the UG bit is set or if a hardware reset is received from the slave mode controller.

##### 9. Bits 0 — CEN

Counter enable
- **`0`:** Counter disabled
- **`1`:** Counter enabled
**Note:** External clock, gated mode and encoder mode can work only if the CEN bit has been previously set by software. However trigger mode can set the CEN bit automatically by hardware.
<a id="1242-tim1-control-register-2-timx_cr2"></a>

### 12.4.2 TIM1 control register 2 (TIMx_CR2)

**Address offset:** `0x04`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15` | **Reserved** |
| `14` | **OIS4** |
| `13` | **OIS3N** |
| `12` | **OIS3** |
| `11` | **OIS2N** |
| `10` | **OIS2** |
| `9` | **OIS1N** |
| `8` | **OIS1** |
| `7` | **TI1S** |
| `6:4` | **MMS[2:0]** |
| `3` | **CCDS** |
| `2` | **CCUS** |
| `1` | **Reserved** |
| `0` | **CCPC** |

#### Bit-field descriptions

##### 1. Bits 15 — Reserved

Must be kept at reset value.

##### 2. Bits 14 — OIS4

Output Idle state 4 (OC4 output)
refer to OIS1 bit

##### 3. Bits 13 — OIS3N

Output Idle state 3 (OC3N output)
refer to OIS1N bit

##### 4. Bits 12 — OIS3

Output Idle state 3 (OC3 output)
refer to OIS1 bit

##### 5. Bits 11 — OIS2N

Output Idle state 2 (OC2N output)
refer to OIS1N bit

##### 6. Bits 10 — OIS2

Output Idle state 2 (OC2 output)
refer to OIS1 bit

##### 7. Bits 9 — OIS1N

Output Idle state 1 (OC1N output)
- **`0`:** OC1N=0 after a dead-time when MOE=0
- **`1`:** OC1N=1 after a dead-time when MOE=0
**Note:** This bit can not be modified as long as LOCK level 1, 2 or 3 has been programmed (LOCK bits in TIMx_BDTR register).

##### 8. Bits 8 — OIS1

Output Idle state 1 (OC1 output)
- **`0`:** OC1=0 (after a dead-time if OC1N is implemented) when MOE=0
- **`1`:** OC1=1 (after a dead-time if OC1N is implemented) when MOE=0
**Note:** This bit can not be modified as long as LOCK level 1, 2 or 3 has been programmed (LOCK bits in TIMx_BDTR register).

##### 9. Bits 7 — TI1S

TI1 selection
- **`0`:** The TIMx_CH1 pin is connected to TI1 input
- **`1`:** The TIMx_CH1, CH2 and CH3 pins are connected to the TI1 input (XOR combination)

##### 10. Bits 6:4 — MMS[2:0]

Master mode selection
These bits allow to select the information to be sent in master mode to slave timers for synchronization (TRGO). The combination is as follows:
- **`000`:** Reset - the UG bit from the TIMx_EGR register is used as trigger output (TRGO). If the
reset is generated by the trigger input (slave mode controller configured in reset mode) then the signal on TRGO is delayed compared to the actual reset.
- **`001`:** Enable - the Counter Enable signal CNT_EN is used as trigger output (TRGO). It is
useful to start several timers at the same time or to control a window in which a slave timer is enable. The Counter Enable signal is generated by a logic OR between CEN control bit and the trigger input when configured in gated mode. When the Counter Enable signal is controlled by the trigger input, there is a delay on TRGO, except if the master/slave mode is selected (see the MSM bit description in TIMx_SMCR register).
- **`010`:** Update - The update event is selected as trigger output (TRGO). For instance a master
timer can then be used as a prescaler for a slave timer.
- **`011`:** Compare Pulse - The trigger output send a positive pulse when the CC1IF flag is to be
set (even if it was already high), as soon as a capture or a compare match occurred. (TRGO).
- **`100`:** Compare - OC1REF signal is used as trigger output (TRGO)
- **`101`:** Compare - OC2REF signal is used as trigger output (TRGO)
- **`110`:** Compare - OC3REF signal is used as trigger output (TRGO)
- **`111`:** Compare - OC4REF signal is used as trigger output (TRGO)
**Note:** The clock of the slave timer and ADC must be enabled prior to receiving events from the master timer, and must not be changed on-the-fly while triggers are received from the master timer.

##### 11. Bits 3 — CCDS

Capture/compare DMA selection
- **`0`:** CCx DMA request sent when CCx event occurs
- **`1`:** CCx DMA requests sent when update event occurs

##### 12. Bits 2 — CCUS

Capture/compare control update selection
- **`0`:** When capture/compare control bits are preloaded (CCPC=1), they are updated by setting
the COMG bit only
- **`1`:** When capture/compare control bits are preloaded (CCPC=1), they are updated by setting
the COMG bit or when an rising edge occurs on TRGI
**Note:** This bit acts only on channels that have a complementary output.

##### 13. Bits 1 — Reserved

Must be kept at reset value.

##### 14. Bits 0 — CCPC

Capture/compare preloaded control
- **`0`:** CCxE, CCxNE and OCxM bits are not preloaded
- **`1`:** CCxE, CCxNE and OCxM bits are preloaded, after having been written, they are updated
only when a commutation event (COM) occurs (COMG bit set or rising edge detected on TRGI, depending on the CCUS bit).
**Note:** This bit acts only on channels that have a complementary output.
<a id="1243-tim1-slave-mode-control-register-timx_smcr"></a>

### 12.4.3 TIM1 slave mode control register (TIMx_SMCR)

**Address offset:** `0x08`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15` | **ETP** |
| `14` | **ECE** |
| `13:12` | **ETPS[1:0]** |
| `11:8` | **ETF[3:0]** |
| `7` | **MSM** |
| `6:4` | **TS[2:0]** |
| `3` | **Reserved** |
| `2:0` | **SMS** |

#### Bit-field descriptions

##### 1. Bits 15 — ETP

External trigger polarity
This bit selects whether ETR or ETR is used for trigger operations
- **`0`:** ETR is non-inverted, active at high level or rising edge.
- **`1`:** ETR is inverted, active at low level or falling edge.

##### 2. Bits 14 — ECE

External clock enable
This bit enables External clock mode 2.
- **`0`:** External clock mode 2 disabled
- **`1`:** External clock mode 2 enabled. The counter is clocked by any active edge on the ETRF
signal.
**Note:** 1: Setting the ECE bit has the same effect as selecting external clock mode 1 with TRGI connected to ETRF (SMS=111 and TS=111). 2: It is possible to simultaneously use external clock mode 2 with the following slave modes: reset mode, gated mode and trigger mode. Nevertheless, TRGI must not be connected to ETRF in this case (TS bits must not be 111). 3: If external clock mode 1 and external clock mode 2 are enabled at the same time, the external clock input is ETRF.

##### 3. Bits 13:12 — ETPS[1:0]

External trigger prescaler
External trigger signal ETRP frequency must be at most 1/4 of TIMxCLK frequency. A prescaler can be enabled to reduce ETRP frequency. It is useful when inputting fast external clocks.
- **`00`:** Prescaler OFF
- **`01`:** ETRP frequency divided by 2
- **`10`:** ETRP frequency divided by 4
- **`11`:** ETRP frequency divided by 8

##### 4. Bits 11:8 — ETF[3:0]

External trigger filter
This bit-field then defines the frequency used to sample ETRP signal and the length of the digital filter applied to ETRP. The digital filter is made of an event counter in which N consecutive events are needed to validate a transition on the output:
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

##### 5. Bits 7 — MSM

Master/slave mode
- **`0`:** No action
- **`1`:** The effect of an event on the trigger input (TRGI) is delayed to allow a perfect
synchronization between the current timer and its slaves (through TRGO). It is useful if we want to synchronize several timers on a single external event.

##### 6. Bits 6:4 — TS[2:0]

Trigger selection
This bit-field selects the trigger input to be used to synchronize the counter.
- **`000`:** Internal Trigger 0 (ITR0)
- **`001`:** Internal Trigger 1 (ITR1)
- **`010`:** Internal Trigger 2 (ITR2)
- **`011`:** Internal Trigger 3 (ITR3)
- **`100`:** TI1 Edge Detector (TI1F_ED)
- **`101`:** Filtered Timer Input 1 (TI1FP1)
- **`110`:** Filtered Timer Input 2 (TI2FP2)
- **`111`:** External Trigger input (ETRF)
See Table 50 for more details on ITRx meaning for each Timer.
**Note:** These bits must be changed only when they are not used (e.g. when SMS=000) to avoid wrong edge detections at the transition.

##### 7. Bits 3 — Reserved

Must be kept at reset value.

##### 8. Bits 2:0 — SMS

Slave mode selection
When external signals are selected the active edge of the trigger signal (TRGI) is linked to the polarity selected on the external input (see Input Control register and Control register description.
- **`000`:** Slave mode disabled - if CEN = ‘1’ then the prescaler is clocked directly by the internal
clock.
- **`001`:** Encoder mode 1 - Counter counts up/down on TI1FP1 edge depending on TI2FP2
level.
- **`010`:** Encoder mode 2 - Counter counts up/down on TI2FP2 edge depending on TI1FP1
level.
- **`011`:** Encoder mode 3 - Counter counts up/down on both TI1FP1 and TI2FP2 edges
depending on the level of the other input.
- **`100`:** Reset mode - Rising edge of the selected trigger input (TRGI) reinitializes the counter
and generates an update of the registers.
- **`101`:** Gated mode - The counter clock is enabled when the trigger input (TRGI) is high. The
counter stops (but is not reset) as soon as the trigger becomes low. Both start and stop of the counter are controlled.
- **`110`:** Trigger mode - The counter starts at a rising edge of the trigger TRGI (but it is not
reset). Only the start of the counter is controlled.
- **`111`:** External Clock mode 1 - Rising edges of the selected trigger (TRGI) clock the counter.
**Note:** The gated mode must not be used if TI1F_ED is selected as the trigger input (TS=’100’). Indeed, TI1F_ED outputs 1 pulse for each transition on TI1F, whereas the gated mode checks the level of the trigger signal. The clock of the slave timer must be enabled prior to receiving events from the master timer, and must not be changed on-the-fly while triggers are received from the master timer.
Table 50. TIMx Internal trigger connection Slave TIM ITR0 (TS = 000) ITR1 (TS = 001) ITR2 (TS = 010) ITR3 (TS = 011)
TIM1 TIM5_TRGO TIM2_TRGO TIM3_TRGO TIM4_TRGO
<a id="1244-tim1-dmainterrupt-enable-register-timx_dier"></a>

### 12.4.4 TIM1 DMA/interrupt enable register (TIMx_DIER)

**Address offset:** `0x0C`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15` | **Reserved** |
| `14` | **TDE** |
| `13` | **COMDE** |
| `12` | **CC4DE** |
| `11` | **CC3DE** |
| `10` | **CC2DE** |
| `9` | **CC1DE** |
| `8` | **UDE** |
| `7` | **BIE** |
| `6` | **TIE** |
| `5` | **COMIE** |
| `4` | **CC4IE** |
| `3` | **CC3IE** |
| `2` | **CC2IE** |
| `1` | **CC1IE** |
| `0` | **UIE** |

#### Bit-field descriptions

##### 1. Bits 15 — Reserved

Must be kept at reset value.

##### 2. Bits 14 — TDE

Trigger DMA request enable
- **`0`:** Trigger DMA request disabled
- **`1`:** Trigger DMA request enabled

##### 3. Bits 13 — COMDE

COM DMA request enable
- **`0`:** COM DMA request disabled
- **`1`:** COM DMA request enabled

##### 4. Bits 12 — CC4DE

Capture/Compare 4 DMA request enable
- **`0`:** CC4 DMA request disabled
- **`1`:** CC4 DMA request enabled

##### 5. Bits 11 — CC3DE

Capture/Compare 3 DMA request enable
- **`0`:** CC3 DMA request disabled
- **`1`:** CC3 DMA request enabled

##### 6. Bits 10 — CC2DE

Capture/Compare 2 DMA request enable
- **`0`:** CC2 DMA request disabled
- **`1`:** CC2 DMA request enabled

##### 7. Bits 9 — CC1DE

Capture/Compare 1 DMA request enable
- **`0`:** CC1 DMA request disabled
- **`1`:** CC1 DMA request enabled

##### 8. Bits 8 — UDE

Update DMA request enable
- **`0`:** Update DMA request disabled
- **`1`:** Update DMA request enabled

##### 9. Bits 7 — BIE

Break interrupt enable
- **`0`:** Break interrupt disabled
- **`1`:** Break interrupt enabled

##### 10. Bits 6 — TIE

Trigger interrupt enable
- **`0`:** Trigger interrupt disabled
- **`1`:** Trigger interrupt enabled

##### 11. Bits 5 — COMIE

COM interrupt enable
- **`0`:** COM interrupt disabled
- **`1`:** COM interrupt enabled

##### 12. Bits 4 — CC4IE

Capture/Compare 4 interrupt enable
- **`0`:** CC4 interrupt disabled
- **`1`:** CC4 interrupt enabled

##### 13. Bits 3 — CC3IE

Capture/Compare 3 interrupt enable
- **`0`:** CC3 interrupt disabled
- **`1`:** CC3 interrupt enabled

##### 14. Bits 2 — CC2IE

Capture/Compare 2 interrupt enable
- **`0`:** CC2 interrupt disabled
- **`1`:** CC2 interrupt enabled

##### 15. Bits 1 — CC1IE

Capture/Compare 1 interrupt enable
- **`0`:** CC1 interrupt disabled
- **`1`:** CC1 interrupt enabled

##### 16. Bits 0 — UIE

Update interrupt enable
- **`0`:** Update interrupt disabled
- **`1`:** Update interrupt enabled
<a id="1245-tim1-status-register-timx_sr"></a>

### 12.4.5 TIM1 status register (TIMx_SR)

**Address offset:** `0x10`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:13` | **Reserved** |
| `12` | **CC4OF** |
| `11` | **CC3OF** |
| `10` | **CC2OF** |
| `9` | **CC1OF** |
| `8` | **Reserved** |
| `7` | **BIF** |
| `6` | **TIF** |
| `5` | **COMIF** |
| `4` | **CC4IF** |
| `3` | **CC3IF** |
| `2` | **CC2IF** |
| `1` | **CC1IF** |
| `0` | **UIF** |

#### Bit-field descriptions

##### 1. Bits 15:13 — Reserved

Must be kept at reset value.

##### 2. Bits 12 — CC4OF

Capture/Compare 4 overcapture flag
refer to CC1OF description

##### 3. Bits 11 — CC3OF

Capture/Compare 3 overcapture flag
refer to CC1OF description

##### 4. Bits 10 — CC2OF

Capture/Compare 2 overcapture flag
refer to CC1OF description

##### 5. Bits 9 — CC1OF

Capture/Compare 1 overcapture flag
This flag is set by hardware only when the corresponding channel is configured in input capture mode. It is cleared by software by writing it to ‘0’.
- **`0`:** No overcapture has been detected.
- **`1`:** The counter value has been captured in TIMx_CCR1 register while CC1IF flag was
already set

##### 6. Bits 8 — Reserved

Must be kept at reset value.

##### 7. Bits 7 — BIF

Break interrupt flag
This flag is set by hardware as soon as the break input goes active. It can be cleared by software if the break input is not active.
- **`0`:** No break event occurred.
- **`1`:** An active level has been detected on the break input.

##### 8. Bits 6 — TIF

Trigger interrupt flag
This flag is set by hardware on trigger event (active edge detected on TRGI input when the slave mode controller is enabled in all modes but gated mode. It is set when the counter starts or stops when gated mode is selected.It is cleared by software.
- **`0`:** No trigger event occurred.
- **`1`:** Trigger interrupt pending.

##### 9. Bits 5 — COMIF

COM interrupt flag
This flag is set by hardware on COM event (when Capture/compare Control bits - CCxE, CCxNE, OCxM - have been updated). It is cleared by software.
- **`0`:** No COM event occurred.
- **`1`:** COM interrupt pending.

##### 10. Bits 4 — CC4IF

Capture/Compare 4 interrupt flag
refer to CC1IF description

##### 11. Bits 3 — CC3IF

Capture/Compare 3 interrupt flag
refer to CC1IF description

##### 12. Bits 2 — CC2IF

Capture/Compare 2 interrupt flag
refer to CC1IF description

##### 13. Bits 1 — CC1IF

Capture/Compare 1 interrupt flag
If channel CC1 is configured as output: This flag is set by hardware when the counter matches the compare value, with some exception in center-aligned mode (refer to the CMS bits in the TIMx_CR1 register description). It is cleared by software.
- **`0`:** No match.
- **`1`:** The content of the counter TIMx_CNT matches the content of the TIMx_CCR1 register.
When the contents of TIMx_CCR1 are greater than the contents of TIMx_ARR, the CC1IF bit goes high on the counter overflow (in upcounting and up/down-counting modes) or underflow (in downcounting mode) If channel CC1 is configured as input: This bit is set by hardware on a capture. It is cleared by software or by reading the TIMx_CCR1 register.
- **`0`:** No input capture occurred
- **`1`:** The counter value has been captured in TIMx_CCR1 register (An edge has been
detected on IC1 which matches the selected polarity)

##### 14. Bits 0 — UIF

Update interrupt flag
This bit is set by hardware on an update event. It is cleared by software.
- **`0`:** No update occurred.
- **`1`:** Update interrupt pending. This bit is set by hardware when the registers are updated:
- At overflow or underflow regarding the repetition counter value (update if repetition counter
= 0) and if the UDIS=0 in the TIMx_CR1 register.
- When CNT is reinitialized by software using the UG bit in TIMx_EGR register, if URS=0 and
UDIS=0 in the TIMx_CR1 register.
- When CNT is reinitialized by a trigger event (refer to Section 12.4.3: TIM1 slave mode
control register (TIMx_SMCR)), if URS=0 and UDIS=0 in the TIMx_CR1 register.
<a id="1246-tim1-event-generation-register-timx_egr"></a>

### 12.4.6 TIM1 event generation register (TIMx_EGR)

**Address offset:** `0x14`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:8` | **Reserved** |
| `7` | **BG** |
| `6` | **TG** |
| `5` | **COMG** |
| `4` | **CC4G** |
| `3` | **CC3G** |
| `2` | **CC2G** |
| `1` | **CC1G** |
| `0` | **UG** |

#### Bit-field descriptions

##### 1. Bits 15:8 — Reserved

Must be kept at reset value.

##### 2. Bits 7 — BG

Break generation
This bit is set by software in order to generate an event, it is automatically cleared by hardware.
- **`0`:** No action
- **`1`:** A break event is generated. MOE bit is cleared and BIF flag is set. Related interrupt or
DMA transfer can occur if enabled.

##### 3. Bits 6 — TG

Trigger generation
This bit is set by software in order to generate an event, it is automatically cleared by hardware.
- **`0`:** No action
- **`1`:** The TIF flag is set in TIMx_SR register. Related interrupt or DMA transfer can occur if
enabled.

##### 4. Bits 5 — COMG

Capture/Compare control update generation
This bit can be set by software, it is automatically cleared by hardware
- **`0`:** No action
- **`1`:** When CCPC bit is set, it allows to update CCxE, CCxNE and OCxM bits
**Note:** This bit acts only on channels having a complementary output.

##### 5. Bits 4 — CC4G

Capture/Compare 4 generation
refer to CC1G description

##### 6. Bits 3 — CC3G

Capture/Compare 3 generation
refer to CC1G description

##### 7. Bits 2 — CC2G

Capture/Compare 2 generation
refer to CC1G description

##### 8. Bits 1 — CC1G

Capture/Compare 1 generation
This bit is set by software in order to generate an event, it is automatically cleared by hardware.
- **`0`:** No action
- **`1`:** A capture/compare event is generated on channel 1:
If channel CC1 is configured as output: CC1IF flag is set, Corresponding interrupt or DMA request is sent if enabled. If channel CC1 is configured as input: The current value of the counter is captured in TIMx_CCR1 register. The CC1IF flag is set, the corresponding interrupt or DMA request is sent if enabled. The CC1OF flag is set if the CC1IF flag was already high.

##### 9. Bits 0 — UG

Update generation
This bit can be set by software, it is automatically cleared by hardware.
- **`0`:** No action
- **`1`:** Reinitialize the counter and generates an update of the registers. Note that the prescaler
counter is cleared too (anyway the prescaler ratio is not affected). The counter is cleared if the center-aligned mode is selected or if DIR=0 (upcounting), else it takes the auto-reload value (TIMx_ARR) if DIR=1 (downcounting).
<a id="1247-tim1-capturecompare-mode-register-1-timx_ccmr1"></a>

### 12.4.7 TIM1 capture/compare mode register 1 (TIMx_CCMR1)

**Address offset:** `0x18`  
**Reset value:** `0x0000`

#### Register layout

**Output compare mode**

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

**Input capture mode**

| Bit(s) | Field |
|---:|---|
| `15:12` | **IC2F** |
| `11:10` | **IC2PSC[1:0]** |
| `9:8` | **CC2S** |
| `7:4` | **IC1F[3:0]** |
| `3:2` | **IC1PSC** |
| `1:0` | **CC1S** |

**Register note:** The channels can be used in input (capture mode) or in output (compare mode). The direction of a channel is defined by configuring the corresponding CCxS bits. All the other bits of this register have a different function in input and in output mode. For a given bit, OCxx describes its function when the channel is configured in output, ICxx describes its function when the channel is configured in input. So the user must take care that the same bit can have a different meaning for the input stage and for the output stage. OC2                           OC2     OC2                   OC1                           OC1    OC1 CE                            PE      FE      CC2S[1:0]     CE                            PE      FE     CC1S[1:0]

#### Bit-field descriptions

##### 1. Bits 15 — OC2CE (Output compare mode)

Output compare 2 clear enable

##### 2. Bits 14:12 — OC2M[2:0] (Output compare mode)

Output compare 2 mode

##### 3. Bits 11 — OC2PE (Output compare mode)

Output compare 2 preload enable

##### 4. Bits 10 — OC2FE (Output compare mode)

Output compare 2 fast enable

##### 5. Bits 9:8 — CC2S[1:0] (Output compare mode)

Capture/Compare 2 selection
This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC2 channel is configured as output
- **`01`:** CC2 channel is configured as input, IC2 is mapped on TI2
- **`10`:** CC2 channel is configured as input, IC2 is mapped on TI1
- **`11`:** CC2 channel is configured as input, IC2 is mapped on TRC. This mode is working only if
an internal trigger input is selected through the TS bit (TIMx_SMCR register)
**Note:** CC2S bits are writable only when the channel is OFF (CC2E = ‘0’ in TIMx_CCER).

##### 6. Bits 7 — OC1CE (Output compare mode)

Output compare 1 clear enable
OC1CE: Output compare 1 Clear Enable
- **`0`:** OC1Ref is not affected by the ETRF Input
- **`1`:** OC1Ref is cleared as soon as a High level is detected on ETRF input

##### 7. Bits 6:4 — OC1M (Output compare mode)

Output compare 1 mode
These bits define the behavior of the output reference signal OC1REF from which OC1 and OC1N are derived. OC1REF is active high whereas OC1 and OC1N active level depends on CC1P and CC1NP bits.
- **`000`:** Frozen - The comparison between the output compare register TIMx_CCR1 and the
counter TIMx_CNT has no effect on the outputs.(this mode is used to generate a timing base).
- **`001`:** Set channel 1 to active level on match. OC1REF signal is forced high when the counter
TIMx_CNT matches the capture/compare register 1 (TIMx_CCR1).
- **`010`:** Set channel 1 to inactive level on match. OC1REF signal is forced low when the
counter TIMx_CNT matches the capture/compare register 1 (TIMx_CCR1).
- **`011`:** Toggle - OC1REF toggles when TIMx_CNT=TIMx_CCR1.
- **`100`:** Force inactive level - OC1REF is forced low.
- **`101`:** Force active level - OC1REF is forced high.
- **`110`:** PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1
else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0’) as long as TIMx_CNT>TIMx_CCR1 else active (OC1REF=’1’).
- **`111`:** PWM mode 2 - In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1
else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else inactive.
**Note:** 1: These bits can not be modified as long as LOCK level 3 has been programmed (LOCK bits in TIMx_BDTR register) and CC1S=’00’ (the channel is configured in output). 2: In PWM mode 1 or 2, the OCREF level changes only when the result of the comparison changes or when the output compare mode switches from “frozen” mode to “PWM” mode. 3: On channels having a complementary output, this bit field is preloaded. If the CCPC bit is set in the TIMx_CR2 register then the OC1M active bits take the new value from the preloaded bits only when a COM event is generated.

##### 8. Bits 3 — OC1PE (Output compare mode)

Output compare 1 preload enable
- **`0`:** Preload register on TIMx_CCR1 disabled. TIMx_CCR1 can be written at anytime, the
new value is taken in account immediately.
- **`1`:** Preload register on TIMx_CCR1 enabled. Read/Write operations access the preload
register. TIMx_CCR1 preload value is loaded in the active register at each update event.
**Note:** These bits can not be modified as long as LOCK level 3 has been programmed (LOCK bits in TIMx_BDTR register) and CC1S=’00’ (the channel is configured in output).

##### 9. Bits 2 — OC1FE (Output compare mode)

Output compare 1 fast enable
This bit is used to accelerate the effect of an event on the trigger in input on the CC output.
- **`0`:** CC1 behaves normally depending on counter and CCR1 values even when the trigger is
ON. The minimum delay to activate CC1 output when an edge occurs on the trigger input is 5 clock cycles.
- **`1`:** An active edge on the trigger input acts like a compare match on CC1 output. Then, OC is
set to the compare level independently from the result of the comparison. Delay to sample the trigger input and to activate CC1 output is reduced to 3 clock cycles. OCFE acts only if the channel is configured in PWM1 or PWM2 mode.

##### 10. Bits 1:0 — CC1S (Output compare mode)

Capture/Compare 1 selection
This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC1 channel is configured as output
- **`01`:** CC1 channel is configured as input, IC1 is mapped on TI1
- **`10`:** CC1 channel is configured as input, IC1 is mapped on TI2
- **`11`:** CC1 channel is configured as input, IC1 is mapped on TRC. This mode is working only if
an internal trigger input is selected through TS bit (TIMx_SMCR register)
**Note:** CC1S bits are writable only when the channel is OFF (CC1E = ‘0’ in TIMx_CCER).

##### 11. Bits 15:12 — IC2F (Input capture mode)

Input capture 2 filter

##### 12. Bits 11:10 — IC2PSC[1:0] (Input capture mode)

Input capture 2 prescaler

##### 13. Bits 9:8 — CC2S (Input capture mode)

Capture/Compare 2 selection
This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC2 channel is configured as output
- **`01`:** CC2 channel is configured as input, IC2 is mapped on TI2
- **`10`:** CC2 channel is configured as input, IC2 is mapped on TI1
- **`11`:** CC2 channel is configured as input, IC2 is mapped on TRC. This mode is working only if an
internal trigger input is selected through TS bit (TIMx_SMCR register)
**Note:** CC2S bits are writable only when the channel is OFF (CC2E = ‘0’ in TIMx_CCER).

##### 14. Bits 7:4 — IC1F[3:0] (Input capture mode)

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

##### 15. Bits 3:2 — IC1PSC (Input capture mode)

Input capture 1 prescaler
This bit-field defines the ratio of the prescaler acting on CC1 input (IC1). The prescaler is reset as soon as CC1E=’0’ (TIMx_CCER register).
- **`00`:** no prescaler, capture is done each time an edge is detected on the capture input
- **`01`:** capture is done once every 2 events
- **`10`:** capture is done once every 4 events
- **`11`:** capture is done once every 8 events

##### 16. Bits 1:0 — CC1S (Input capture mode)

Capture/Compare 1 Selection
This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC1 channel is configured as output
- **`01`:** CC1 channel is configured as input, IC1 is mapped on TI1
- **`10`:** CC1 channel is configured as input, IC1 is mapped on TI2
- **`11`:** CC1 channel is configured as input, IC1 is mapped on TRC. This mode is working only if an
internal trigger input is selected through TS bit (TIMx_SMCR register)
**Note:** CC1S bits are writable only when the channel is OFF (CC1E = ‘0’ in TIMx_CCER).
<a id="1248-tim1-capturecompare-mode-register-2-timx_ccmr2"></a>

### 12.4.8 TIM1 capture/compare mode register 2 (TIMx_CCMR2)

**Address offset:** `0x1C`  
**Reset value:** `0x0000`

#### Register layout

**Output compare mode**

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

**Input capture mode**

| Bit(s) | Field |
|---:|---|
| `15:12` | **IC4F** |
| `11:10` | **IC4PSC** |
| `9:8` | **CC4S** |
| `7:4` | **IC3F** |
| `3:2` | **IC3PSC** |
| `1:0` | **CC3S** |

**Register note:** Refer to the above CCMR1 register description. OC4                             OC4    OC4                   OC3                           OC3    OC3 CE                              PE     FE       CC4S[1:0]    CE.                           PE      FE     CC3S[1:0]

#### Bit-field descriptions

##### 1. Bits 15 — OC4CE (Output compare mode)

Output compare 4 clear enable

##### 2. Bits 14:12 — OC4M (Output compare mode)

Output compare 4 mode

##### 3. Bits 11 — OC4PE (Output compare mode)

Output compare 4 preload enable

##### 4. Bits 10 — OC4FE (Output compare mode)

Output compare 4 fast enable

##### 5. Bits 9:8 — CC4S (Output compare mode)

Capture/Compare 4 selection
This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC4 channel is configured as output
- **`01`:** CC4 channel is configured as input, IC4 is mapped on TI4
- **`10`:** CC4 channel is configured as input, IC4 is mapped on TI3
- **`11`:** CC4 channel is configured as input, IC4 is mapped on TRC. This mode is working only if
an internal trigger input is selected through TS bit (TIMx_SMCR register)
**Note:** CC4S bits are writable only when the channel is OFF (CC4E = ‘0’ in TIMx_CCER).

##### 6. Bits 7 — OC3CE (Output compare mode)

Output compare 3 clear enable

##### 7. Bits 6:4 — OC3M (Output compare mode)

Output compare 3 mode

##### 8. Bits 3 — OC3PE (Output compare mode)

Output compare 3 preload enable

##### 9. Bits 2 — OC3FE (Output compare mode)

Output compare 3 fast enable

##### 10. Bits 1:0 — CC3S (Output compare mode)

Capture/Compare 3 selection
This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC3 channel is configured as output
- **`01`:** CC3 channel is configured as input, IC3 is mapped on TI3
- **`10`:** CC3 channel is configured as input, IC3 is mapped on TI4
- **`11`:** CC3 channel is configured as input, IC3 is mapped on TRC. This mode is working only if
an internal trigger input is selected through TS bit (TIMx_SMCR register)
**Note:** CC3S bits are writable only when the channel is OFF (CC3E = ‘0’ in TIMx_CCER).

##### 11. Bits 15:12 — IC4F (Input capture mode)

Input capture 4 filter

##### 12. Bits 11:10 — IC4PSC (Input capture mode)

Input capture 4 prescaler

##### 13. Bits 9:8 — CC4S (Input capture mode)

Capture/Compare 4 selection
This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC4 channel is configured as output
- **`01`:** CC4 channel is configured as input, IC4 is mapped on TI4
- **`10`:** CC4 channel is configured as input, IC4 is mapped on TI3
- **`11`:** CC4 channel is configured as input, IC4 is mapped on TRC. This mode is working only if
an internal trigger input is selected through TS bit (TIMx_SMCR register)
**Note:** CC4S bits are writable only when the channel is OFF (CC4E = ‘0’ in TIMx_CCER).

##### 14. Bits 7:4 — IC3F (Input capture mode)

Input capture 3 filter

##### 15. Bits 3:2 — IC3PSC (Input capture mode)

Input capture 3 prescaler

##### 16. Bits 1:0 — CC3S (Input capture mode)

Capture/compare 3 selection
This bit-field defines the direction of the channel (input/output) as well as the used input.
- **`00`:** CC3 channel is configured as output
- **`01`:** CC3 channel is configured as input, IC3 is mapped on TI3
- **`10`:** CC3 channel is configured as input, IC3 is mapped on TI4
- **`11`:** CC3 channel is configured as input, IC3 is mapped on TRC. This mode is working only if
an internal trigger input is selected through TS bit (TIMx_SMCR register)
**Note:** CC3S bits are writable only when the channel is OFF (CC3E = ‘0’ in TIMx_CCER).
<a id="1249-tim1-capturecompare-enable-register-timx_ccer"></a>

### 12.4.9 TIM1 capture/compare enable register (TIMx_CCER)

**Address offset:** `0x20`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15` | **CC4NP** |
| `14` | **Reserved** |
| `13` | **CC4P** |
| `12` | **CC4E** |
| `11` | **CC3NP** |
| `10` | **CC3NE** |
| `9` | **CC3P** |
| `8` | **CC3E** |
| `7` | **CC2NP** |
| `6` | **CC2NE** |
| `5` | **CC2P** |
| `4` | **CC2E** |
| `3` | **CC1NP** |
| `2` | **CC1NE** |
| `1` | **CC1P** |
| `0` | **CC1E** |

#### Bit-field descriptions

##### 1. Bits 15 — CC4NP

Capture/Compare 4 complementary output polarity
refer to CC1NP description

##### 2. Bits 14 — Reserved

Must be kept at reset value.

##### 3. Bits 13 — CC4P

Capture/Compare 4 output polarity
refer to CC1P description

##### 4. Bits 12 — CC4E

Capture/Compare 4 output enable
refer to CC1E description

##### 5. Bits 11 — CC3NP

Capture/Compare 3 complementary output polarity
refer to CC1NP description

##### 6. Bits 10 — CC3NE

Capture/Compare 3 complementary output enable
refer to CC1NE description

##### 7. Bits 9 — CC3P

Capture/Compare 3 output polarity
refer to CC1P description

##### 8. Bits 8 — CC3E

Capture/Compare 3 output enable
refer to CC1E description

##### 9. Bits 7 — CC2NP

Capture/Compare 2 complementary output polarity
refer to CC1NP description

##### 10. Bits 6 — CC2NE

Capture/Compare 2 complementary output enable
refer to CC1NE description

##### 11. Bits 5 — CC2P

Capture/Compare 2 output polarity
refer to CC1P description

##### 12. Bits 4 — CC2E

Capture/Compare 2 output enable
refer to CC1E description

##### 13. Bits 3 — CC1NP

Capture/Compare 1 complementary output polarity
CC1 channel configured as output:
- **`0`:** OC1N active high.
- **`1`:** OC1N active low.
CC1 channel configured as input: This bit is used in conjunction with CC1P to define the polarity of TI1FP1 and TI2FP1. Refer to CC1P description.
**Note:** On channels having a complementary output, this bit is preloaded. If the CCPC bit is set in the TIMx_CR2 register then the CC1NP active bit takes the new value from the preloaded bit only when a Commutation event is generated.
**Note:** This bit is not writable as soon as LOCK level 2 or 3 has been programmed (LOCK bits in TIMx_BDTR register) and CC1S=”00” (the channel is configured in output).

##### 14. Bits 2 — CC1NE

Capture/Compare 1 complementary output enable
- **`0`:** Off - OC1N is not active. OC1N level is then function of MOE, OSSI, OSSR, OIS1, OIS1N
and CC1E bits.
- **`1`:** On - OC1N signal is output on the corresponding output pin depending on MOE, OSSI,
OSSR, OIS1, OIS1N and CC1E bits.
**Note:** On channels having a complementary output, this bit is preloaded. If the CCPC bit is set in the TIMx_CR2 register then the CC1NE active bit takes the new value from the preloaded bit only when a Commutation event is generated.

##### 15. Bits 1 — CC1P

Capture/Compare 1 output polarity
CC1 channel configured as output:
- **`0`:** OC1 active high
- **`1`:** OC1 active low
CC1 channel configured as input: CC1NP/CC1P bits select the active polarity of TI1FP1 and TI2FP1 for trigger or capture operations.
- **`00`:** non-inverted/rising edge
The circuit is sensitive to TIxFP1 rising edge (capture or trigger operations in reset, external clock or trigger mode), TIxFP1 is not inverted (trigger operation in gated mode or encoder mode).
- **`01`:** inverted/falling edge
The circuit is sensitive to TIxFP1 falling edge (capture or trigger operations in reset, external clock or trigger mode), TIxFP1 is inverted (trigger operation in gated mode or encoder mode).
- **`10`:** reserved, do not use this configuration.
- **`11`:** non-inverted/both edges
The circuit is sensitive to both TIxFP1 rising and falling edges (capture or trigger operations in reset, external clock or trigger mode), TIxFP1 is not inverted (trigger operation in gated mode). This configuration must not be used in encoder mode.
**Note:** On channels having a complementary output, this bit is preloaded. If the CCPC bit is set in the TIMx_CR2 register then the CC1P active bit takes the new value from the preloaded bit only when a Commutation event is generated.
**Note:** This bit is not writable as soon as LOCK level 2 or 3 has been programmed (LOCK bits in TIMx_BDTR register).

##### 16. Bits 0 — CC1E

Capture/Compare 1 output enable
CC1 channel configured as output:
- **`0`:** Off - OC1 is not active. OC1 level is then function of MOE, OSSI, OSSR, OIS1, OIS1N
and CC1NE bits.
- **`1`:** On - OC1 signal is output on the corresponding output pin depending on MOE, OSSI,
OSSR, OIS1, OIS1N and CC1NE bits. CC1 channel configured as input: This bit determines if a capture of the counter value can actually be done into the input capture/compare register 1 (TIMx_CCR1) or not.
- **`0`:** Capture disabled.
- **`1`:** Capture enabled.
**Note:** On channels having a complementary output, this bit is preloaded. If the CCPC bit is set in the TIMx_CR2 register then the CC1E active bit takes the new value from the preloaded bit only when a Commutation event is generated.
Table 51. Output control bits for complementary OCx and OCxN channels with break feature Control bits Output states(1)
MOE OSSI OSSR CCxE CCxNE OCx output state OCxN output state bit bit bit bit bit
Output Disabled (not driven by Output Disabled (not driven by the 0 0 0 the timer), OCx=0, OCx_EN=0 timer), OCxN=0, OCxN_EN=0 Output Disabled (not driven by OCxREF + Polarity OCxN=OCxREF 0 0 1 the timer), OCx=0, OCx_EN=0 xor CCxNP, OCxN_EN=1 OCxREF + Polarity Output Disabled (not driven by the 0 1 0 OCx=OCxREF xor CCxP, timer) OCx_EN=1 OCxN=0, OCxN_EN=0 Complementary to OCREF (not OCREF + Polarity + dead-time 0 1 1 OCREF) + Polarity + dead-time OCx_EN=1 OCxN_EN=1
1 X Output Disabled (not driven by Output Disabled (not driven by the 1 0 0 the timer) timer) OCx=CCxP, OCx_EN=0 OCxN=CCxNP, OCxN_EN=0 Off-State (output enabled with OCxREF + Polarity 1 0 1 inactive state) OCxN=OCxREF xor CCxNP, OCx=CCxP, OCx_EN=1 OCxN_EN=1 OCxREF + Polarity Off-State (output enabled with 1 1 0 OCx=OCxREF xor CCxP, inactive state) OCx_EN=1 OCxN=CCxNP, OCxN_EN=1 Complementary to OCREF (not OCREF + Polarity + dead-time 1 1 1 OCREF) + Polarity + dead-time OCx_EN=1 OCxN_EN=1 0 X X Output disabled (not driven by the timer anymore). The output state is 0 0 defined by the GPIO controller and can be High, Low or Hi-Z.
0 1 Off-State (output enabled with inactive state) 0 X Asynchronously: OCx=CCxP, OCx_EN=1, OCxN=CCxNP, 1 1 0 OCxN_EN=1 Then if the clock is present: OCx=OISx and OCxN=OISxN after a 1 1 dead-time, assuming that OISx and OISxN do not correspond to OCX and OCxN both in active state 1. When both outputs of a channel are not used (CCxE = CCxNE = 0), the OISx, OISxN, CCxP and CCxNP bits must be kept cleared.
**Note:** The state of the external I/O pins connected to the complementary OCx and OCxN channels depends on the OCx and OCxN channel state and the GPIO registers.
<a id="12410-tim1-counter-timx_cnt"></a>

### 12.4.10 TIM1 counter (TIMx_CNT)

**Address offset:** `0x24`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:0` | **CNT[15:0]** |

#### Bit-field descriptions

##### 1. Bits 15:0 — CNT[15:0]

Counter value
<a id="12411-tim1-prescaler-timx_psc"></a>

### 12.4.11 TIM1 prescaler (TIMx_PSC)

**Address offset:** `0x28`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:0` | **PSC[15:0]** |

#### Bit-field descriptions

##### 1. Bits 15:0 — PSC[15:0]

Prescaler value
The counter clock frequency (CK_CNT) is equal to fCK_PSC / (PSC[15:0] + 1). PSC contains the value to be loaded in the active prescaler register at each update event (including when the counter is cleared through UG bit of TIMx_EGR register or through trigger controller when configured in “reset mode”).
<a id="12412-tim1-auto-reload-register-timx_arr"></a>

### 12.4.12 TIM1 auto-reload register (TIMx_ARR)

**Address offset:** `0x2C`  
**Reset value:** `0xFFFF`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:0` | **ARR[15:0]** |

#### Bit-field descriptions

##### 1. Bits 15:0 — ARR[15:0]

Auto-reload value
ARR is the value to be loaded in the actual auto-reload register. Refer to Section 12.3.1: Time-base unit for more details about ARR update and behavior. The counter is blocked while the auto-reload value is null.
<a id="12413-tim1-repetition-counter-register-timx_rcr"></a>

### 12.4.13 TIM1 repetition counter register (TIMx_RCR)

**Address offset:** `0x30`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:8` | **Reserved** |
| `7:0` | **REP[7:0]** |

#### Bit-field descriptions

##### 1. Bits 15:8 — Reserved

Must be kept at reset value.

##### 2. Bits 7:0 — REP[7:0]

Repetition counter value
These bits allow the user to set-up the update rate of the compare registers (i.e. periodic transfers from preload to active registers) when preload registers are enable, as well as the update interrupt generation rate, if this interrupt is enable. Each time the REP_CNT related downcounter reaches zero, an update event is generated and it restarts counting from REP value. As REP_CNT is reloaded with REP value only at the repetition update event U_RC, any write to the TIMx_RCR register is not taken in account until the next repetition update event. It means in PWM mode (REP+1) corresponds to:
- the number of PWM periods in edge-aligned mode
- the number of half PWM period in center-aligned mode.
<a id="12414-tim1-capturecompare-register-1-timx_ccr1"></a>

### 12.4.14 TIM1 capture/compare register 1 (TIMx_CCR1)

**Address offset:** `0x34`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:0` | **CCR1[15:0]** |

#### Bit-field descriptions

##### 1. Bits 15:0 — CCR1[15:0]

Capture/Compare 1 value
If channel CC1 is configured as output: CCR1 is the value to be loaded in the actual capture/compare 1 register (preload value). It is loaded permanently if the preload feature is not selected in the TIMx_CCMR1 register (bit OC1PE). Else the preload value is copied in the active capture/compare 1 register when an update event occurs. The active capture/compare register contains the value to be compared to the counter TIMx_CNT and signaled on OC1 output. If channel CC1 is configured as input: CCR1 is the counter value transferred by the last input capture 1 event (IC1). The TIMx_CCR1 register is read-only and cannot be programmed.
<a id="12415-tim1-capturecompare-register-2-timx_ccr2"></a>

### 12.4.15 TIM1 capture/compare register 2 (TIMx_CCR2)

**Address offset:** `0x38`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:0` | **CCR2[15:0]** |

#### Bit-field descriptions

##### 1. Bits 15:0 — CCR2[15:0]

Capture/Compare 2 value
If channel CC2 is configured as output: CCR2 is the value to be loaded in the actual capture/compare 2 register (preload value). It is loaded permanently if the preload feature is not selected in the TIMx_CCMR2 register (bit OC2PE). Else the preload value is copied in the active capture/compare 2 register when an update event occurs. The active capture/compare register contains the value to be compared to the counter TIMx_CNT and signalled on OC2 output. If channel CC2 is configured as input: CCR2 is the counter value transferred by the last input capture 2 event (IC2). The TIMx_CCR2 register is read-only and cannot be programmed.
<a id="12416-tim1-capturecompare-register-3-timx_ccr3"></a>

### 12.4.16 TIM1 capture/compare register 3 (TIMx_CCR3)

**Address offset:** `0x3C`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:0` | **CCR3[15:0]** |

#### Bit-field descriptions

##### 1. Bits 15:0 — CCR3[15:0]

Capture/Compare value
If channel CC3 is configured as output: CCR3 is the value to be loaded in the actual capture/compare 3 register (preload value). It is loaded permanently if the preload feature is not selected in the TIMx_CCMR3 register (bit OC3PE). Else the preload value is copied in the active capture/compare 3 register when an update event occurs. The active capture/compare register contains the value to be compared to the counter TIMx_CNT and signalled on OC3 output. If channel CC3 is configured as input: CCR3 is the counter value transferred by the last input capture 3 event (IC3). The TIMx_CCR3 register is read-only and cannot be programmed.
<a id="12417-tim1-capturecompare-register-4-timx_ccr4"></a>

### 12.4.17 TIM1 capture/compare register 4 (TIMx_CCR4)

**Address offset:** `0x40`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:0` | **CCR4[15:0]** |

#### Bit-field descriptions

##### 1. Bits 15:0 — CCR4[15:0]

Capture/Compare value
If channel CC4 is configured as output: CCR4 is the value to be loaded in the actual capture/compare 4 register (preload value). It is loaded permanently if the preload feature is not selected in the TIMx_CCMR4 register (bit OC4PE). Else the preload value is copied in the active capture/compare 4 register when an update event occurs. The active capture/compare register contains the value to be compared to the counter TIMx_CNT and signalled on OC4 output. If channel CC4 is configured as input: CCR4 is the counter value transferred by the last input capture 4 event (IC4). The TIMx_CCR3 register is read-only and cannot be programmed.
<a id="12418-tim1-break-and-dead-time-register-timx_bdtr"></a>

### 12.4.18 TIM1 break and dead-time register (TIMx_BDTR)

**Address offset:** `0x44`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15` | **MOE** |
| `14` | **AOE** |
| `13` | **BKP** |
| `12` | **BKE** |
| `11` | **OSSR** |
| `10` | **OSSI** |
| `9:8` | **LOCK[1:0]** |
| `7:0` | **DTG[7:0]** |

#### Bit-field descriptions

##### 1. Bits 15 — MOE

Main output enable
This bit is cleared asynchronously by hardware as soon as the break input is active. It is set by software or automatically depending on the AOE bit. It is acting only on the channels which are configured in output.
- **`0`:** OC and OCN outputs are disabled or forced to idle state.
- **`1`:** OC and OCN outputs are enabled if their respective enable bits are set (CCxE, CCxNE in
TIMx_CCER register). See OC/OCN enable description for more details (Section 12.4.9: TIM1 capture/compare enable register (TIMx_CCER)).

##### 2. Bits 14 — AOE

Automatic output enable
- **`0`:** MOE can be set only by software
- **`1`:** MOE can be set by software or automatically at the next update event (if the break input is
not be active)
**Note:** This bit can not be modified as long as LOCK level 1 has been programmed (LOCK bits in TIMx_BDTR register).

##### 3. Bits 13 — BKP

Break polarity
- **`0`:** Break input BRK is active low
- **`1`:** Break input BRK is active high
**Note:** This bit can not be modified as long as LOCK level 1 has been programmed (LOCK bits in TIMx_BDTR register).
**Note:** Any write operation to this bit takes a delay of 1 APB clock cycle to become effective.

##### 4. Bits 12 — BKE

Break enable
- **`0`:** Break inputs (BRK and CSS clock failure event) disabled
1; Break inputs (BRK and CSS clock failure event) enabled
**Note:** This bit cannot be modified when LOCK level 1 has been programmed (LOCK bits in TIMx_BDTR register).
**Note:** Any write operation to this bit takes a delay of 1 APB clock cycle to become effective.

##### 5. Bits 11 — OSSR

Off-state selection for Run mode
This bit is used when MOE=1 on channels having a complementary output which are configured as outputs. OSSR is not implemented if no complementary output is implemented in the timer. See OC/OCN enable description for more details (Section 12.4.9: TIM1 capture/compare enable register (TIMx_CCER)).
- **`0`:** When inactive, OC/OCN outputs are disabled (OC/OCN enable output signal=0).
- **`1`:** When inactive, OC/OCN outputs are enabled with their inactive level as soon as CCxE=1
or CCxNE=1. Then, OC/OCN enable output signal=1
**Note:** This bit can not be modified as soon as the LOCK level 2 has been programmed (LOCK bits in TIMx_BDTR register).

##### 6. Bits 10 — OSSI

Off-state selection for Idle mode
This bit is used when MOE=0 on channels configured as outputs. See OC/OCN enable description for more details (Section 12.4.9: TIM1 capture/compare enable register (TIMx_CCER)).
- **`0`:** When inactive, OC/OCN outputs are disabled (OC/OCN enable output signal=0).
- **`1`:** When inactive, OC/OCN outputs are forced first with their idle level as soon as CCxE=1 or
CCxNE=1. OC/OCN enable output signal=1)
**Note:** This bit can not be modified as soon as the LOCK level 2 has been programmed (LOCK bits in TIMx_BDTR register).

##### 7. Bits 9:8 — LOCK[1:0]

Lock configuration
These bits offer a write protection against software errors.
- **`00`:** LOCK OFF - No bit is write protected.
- **`01`:** LOCK Level 1 = DTG bits in TIMx_BDTR register, OISx and OISxN bits in TIMx_CR2
register and BKE/BKP/AOE bits in TIMx_BDTR register can no longer be written.
- **`10`:** LOCK Level 2 = LOCK Level 1 + CC Polarity bits (CCxP/CCxNP bits in TIMx_CCER
register, as long as the related channel is configured in output through the CCxS bits) as well as OSSR and OSSI bits can no longer be written.
- **`11`:** LOCK Level 3 = LOCK Level 2 + CC Control bits (OCxM and OCxPE bits in
TIMx_CCMRx registers, as long as the related channel is configured in output through the CCxS bits) can no longer be written.
**Note:** The LOCK bits can be written only once after the reset. Once the TIMx_BDTR register has been written, their content is frozen until the next reset.

##### 8. Bits 7:0 — DTG[7:0]

Dead-time generator setup
This bit-field defines the duration of the dead-time inserted between the complementary outputs. DT correspond to this duration. DTG[7:5]=0xx => DT=DTG[7:0]x tdtg with tdtg=tDTS. DTG[7:5]=10x => DT=(64+DTG[5:0])xtdtg with Tdtg=2xtDTS. DTG[7:5]=110 => DT=(32+DTG[4:0])xtdtg with Tdtg=8xtDTS. DTG[7:5]=111 => DT=(32+DTG[4:0])xtdtg with Tdtg=16xtDTS. Example if TDTS=125ns (8MHz), dead-time possible values are: 0 to 15875 ns by 125 ns steps, 16 us to 31750 ns by 250 ns steps, 32 us to 63us by 1 us steps, 64 us to 126 us by 2 us steps
**Note:** This bit-field can not be modified as long as LOCK level 1, 2 or 3 has been programmed (LOCK bits in TIMx_BDTR register).
<a id="12419-tim1-dma-control-register-timx_dcr"></a>

### 12.4.19 TIM1 DMA control register (TIMx_DCR)

**Address offset:** `0x48`  
**Reset value:** `0x0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `15:13` | **Reserved** |
| `12:8` | **DBL[4:0]** |
| `7:5` | **Reserved** |
| `4:0` | **DBA[4:0]** |

#### Bit-field descriptions

##### 1. Bits 15:13 — Reserved

Must be kept at reset value.

##### 2. Bits 12:8 — DBL[4:0]

DMA burst length
This 5-bit vector defines the number of DMA transfers (the timer detects a burst transfer when a read or a write access to the TIMx_DMAR register address is performed). the TIMx_DMAR address) 00000: 1 transfer 00001: 2 transfers 00010: 3 transfers ... 10001: 18 transfers

##### 3. Bits 7:5 — Reserved

Must be kept at reset value.

##### 4. Bits 4:0 — DBA[4:0]

DMA base address
This 5-bits vector defines the base-address for DMA transfers (when read/write access are done through the TIMx_DMAR address). DBA is defined as an offset starting from the address of the TIMx_CR1 register. Example: 00000: TIMx_CR1, 00001: TIMx_CR2, 00010: TIMx_SMCR, ... Example: Let us consider the following transfer: DBL = 7 transfers and DBA = TIMx_CR1. In this case the transfer is done to/from 7 registers starting from the TIMx_CR1 address.
<a id="12420-tim1-dma-address-for-full-transfer-timx_dmar"></a>

### 12.4.20 TIM1 DMA address for full transfer (TIMx_DMAR)

**Address offset:** `0x4C`  
**Reset value:** `0x0000 0000`

#### Register layout

| Bit(s) | Field(s) |
|---:|---|
| `31:0` | **DMAB[31:0]** |

#### Bit-field descriptions

##### 1. Bits 31:0 — DMAB[31:0]

DMA register for burst accesses
A read or write operation to the DMAR register accesses the register located at the address (TIMx_CR1 address) + (DBA + DMA index) x 4 where TIMx_CR1 address is the address of the control register 1, DBA is the DMA base address configured in TIMx_DCR register, DMA index is automatically controlled by the DMA transfer, and ranges from 0 to DBL (DBL configured in TIMx_DCR).
Example of how to use the DMA burst feature In this example the timer DMA burst feature is used to update the contents of the CCRx registers (x = 2, 3, 4) with the DMA transferring half words into the CCRx registers. This is done in the following steps: 1. Configure the corresponding DMA channel as follows:
- DMA channel peripheral address is the DMAR register address
- DMA channel memory address is the address of the buffer in the RAM containing
the data to be transferred by DMA into CCRx registers.
- Number of data to transfer = 3 (See note below).
- Circular mode disabled.
2. Configure the DCR register by configuring the DBA and DBL bit fields as follows: DBL = 3 transfers, DBA = 0xE. 3. Enable the TIMx update DMA request (set the UDE bit in the DIER register). 4. Enable TIMx 5. Enable the DMA channel
**Note:** This example is for the case where every CCRx register to be updated once. If every CCRx register is to be updated twice for example, the number of data to transfer should be 6. Let's take the example of a buffer in the RAM containing data1, data2, data3, data4, data5 and data6. The data is transferred to the CCRx registers as follows: on the first update DMA request, data1 is transferred to CCR2, data2 is transferred to CCR3, data3 is transferred to CCR4 and on the second update DMA request, data4 is transferred to CCR2, data5 is transferred to CCR3 and data6 is transferred to CCR4.

## Reference notes

- Register offsets are shown as in RM0368.
- Register-layout tables use separate Markdown cells for bit ranges and field names.
- Reserved bits should be kept at the values specified by the reference manual.
