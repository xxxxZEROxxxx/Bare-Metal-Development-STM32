# STM32F401 RTC — Study Notes (17 Nov 2026)

Board: **STM32F401CCU6** (Black Pill) · Manual: **RM0368** (RTC = chapter 17) · Pins: datasheet **DS9716**

## Contents

| # | Section | What it's about |
|---|---|---|
| 1 | [Big picture](#big-picture) | Clock chain from crystal to calendar, one diagram |
| 2 | [Clocks: LSE vs LSI, prescalers](#clocks) | Which clock to use, `ck_apre` / `ck_spre` formulas |
| 3 | [Protection & backup domain ⚠️](#protection) | DBP, RCC_BDCR, WPR, init mode — **why writes silently fail** |
| 4 | [Calendar registers & BCD](#calendar) | TR / DR bit layout, tens/units split |
| 5 | [Shadow registers & reading time](#shadow) | Why reads go through copies, read order, RSF |
| 6 | [Calibration ⚠️](#calibration) | Smooth vs coarse, ppm maths, CALM is 9 bits, my 265 ppm case |
| 7 | [PC13 / RTC_AF1 outputs](#pc13) | RTC_CALIB 512 Hz / 1 Hz, RTC_ALARM, pin limits |
| 8 | [Tamper detection](#tamper) | Why backup regs are wiped, edge vs level mode |
| 9 | [Timestamp](#timestamp) | Hardware time capture on a pin edge, use cases |
| 10 | [Procedures (step by step)](#procedures) | **Bullet-point setup sequences** for every feature |
| 11 | [Code](#code) | Final `rtc.h` / `rtc.c`, ready to copy |
| 12 | [C language notes](#c-notes) | Struct register maps, `volatile`, `/` `%` `//`, bit-field widths |
| 13 | [Troubleshooting checklist](#troubleshooting) | "My RTC write does nothing" — what to check |
| 14 | [Register bit reference](#bits) | Every bit used today, in one table |

---

<a id="big-picture"></a>
## 1. Big picture

```
LSE 32.768 kHz ─┐
LSI ~32 kHz  ───┼─► RTCSEL ─► RTCCLK ─► [Smooth cal: RTC_CALR]
HSE / RTCPRE ───┘                              │
                                               ▼
                              [Async ÷ (PREDIV_A+1)] ─► ck_apre (256 Hz) ─► 512 Hz tap → RTC_CALIB
                                               │                            ─► SSR sub-second counter
                                               ▼
                              [Coarse cal: RTC_CALIBR]
                                               │
                                               ▼
                              [Sync ÷ (PREDIV_S+1)] ─► ck_spre (1 Hz) ─► calendar (TR/DR) ─► 1 Hz tap → RTC_CALIB
                                                                        └► alarms, wake-up timer
```

- The RTC, LSE, RCC_BDCR and backup registers all live in the **backup domain**: a power domain that keeps running on VBAT (coin cell) when main power is off and **survives resets**.
- Everything the RTC shows on a pin goes out through **PC13 (RTC_AF1)**.

---

<a id="clocks"></a>
## 2. Clocks: LSE vs LSI, prescalers

### LSE vs LSI

| | **LSE** (external crystal) | **LSI** (internal RC) |
|---|---|---|
| Frequency | 32.768 kHz exact | ~32 kHz, varies |
| Accuracy | ~±20 ppm (seconds/month) | several % (minutes/day) |
| Runs on VBAT | ✅ | ❌ |
| Use for | **The RTC** | Watchdog (IWDG), rough timing |

> Rule: **LSE for keeping time.** The Black Pill has the crystal on board.

### The two prescaler outputs

$$f_{ck\_apre} = \frac{f_{RTCCLK}}{PREDIV\_A + 1} \qquad f_{ck\_spre} = \frac{f_{RTCCLK}}{(PREDIV\_S + 1)(PREDIV\_A + 1)}$$

| Clock | Name meaning | Default | Drives |
|---|---|---|---|
| `ck_apre` | **a**synchronous **pre**scaler out | 32768 / 128 = **256 Hz** | SSR sub-second counter (1 tick ≈ 3.9 ms), 512 Hz output |
| `ck_spre` | **s**ynchronous **pre**scaler out | 256 / 256 = **1 Hz** | Calendar seconds, wake-up timer |

- PREDIV_A: 7 bits (÷1…÷128). PREDIV_S: 15 bits. Defaults: **A = 127, S = 255**.
- SSR counts down from PREDIV_S to 0; at 0 it reloads and the seconds counter increments.
- **Splitting the divide:** keep (A+1)(S+1) = f_RTCCLK so ck_spre = 1 Hz.
  - Large PREDIV_A → lower power (ST recommends this).
  - Large PREDIV_S → finer sub-second resolution.
- Example, 1 MHz RTCCLK: A = 124 (÷125), S = 7999 (÷8000) → 8 kHz / 1 Hz.

---

<a id="protection"></a>
## 3. Protection & backup domain ⚠️

> **The key lesson today:** a write to a protected RTC/backup register **does not fault and sets no error flag — it is silently ignored.** Always read back to verify.

### Three locks, all must be open

| Lock | What it protects | How to open | Notes |
|---|---|---|---|
| **PWR clock** (`RCC_APB1ENR.PWREN`, bit 28) | PWR registers | Set bit 28 | Without it, the DBP write itself is ignored |
| **DBP** (`PWR_CR` bit 8) | **RCC_BDCR**, all RTC registers, backup registers, `PWR_CSR.BRE` | Set DBP, then **dummy read PWR_CR** | 0 = locked (reset state), 1 = writable |
| **RTC_WPR key** | All RTC registers **except** ISR[13:8], TAFCR, BKPxR | Write `0xCA` then `0x53` | Any wrong value re-locks (use `0xFF`) |
| **Init mode** (`ISR.INIT`, wait `INITF`) | TR, DR, PRER | Set INIT, wait for INITF = 1 | Calendar is stopped while in init mode |

### RCC_BDCR — the part I got confused about

- **RCC_BDCR = RCC *Backup Domain Control* Register** at `0x40023870` (RCC `0x40023800` + `0x70`).
- It is a **real control register**, not backup memory. It turns the LSE on and gives the RTC its clock.
- It sits in the backup domain *on purpose*: its settings survive reset, so the RTC doesn't stop when you press reset.
- RM0368 DBP description literally lists it first: *"the RCC_BDCR register, the RTC registers (including the backup registers) … are protected against parasitic write access."*
  - **"Parasitic write" = accidental write** (bug, stray pointer, power glitch), not another device interfering.
- ⇒ **DBP must be set before writing RCC_BDCR.** My first version set LSEON before DBP → write ignored → LSE never started → hang on `while(!LSERDY)`.

| RCC_BDCR bit | Name | Meaning |
|---|---|---|
| 0 | LSEON | LSE oscillator on |
| 1 | LSERDY | (read-only) LSE stable |
| 9:8 | RTCSEL | 00 none · **01 LSE** · 10 LSI · 11 HSE/RTCPRE |
| 15 | RTCEN | RTC clock enable |
| 16 | BDRST | Backup domain reset (wipes RTC + backup regs + LSEON) |

- **RTCSEL is write-once.** To change it later you must pulse BDRST (set, then clear).

### Backup registers vs backup domain

- **Backup domain** = power domain (LSE, RTC, RCC_BDCR bits, backup regs, PC13 logic).
- **Backup registers** = `RTC_BKP0R…BKP19R`, data storage at `0x40002850`+: **20 × 32 bit = 80 bytes**. Survive reset and VBAT; **wiped by a tamper event**.

---

<a id="calendar"></a>
## 4. Calendar registers & BCD

Values are stored in **BCD**: tens and units in separate bit fields.

| Register | Fields (bits) |
|---|---|
| **RTC_TR** | PM[22] · HT[21:20] · HU[19:16] · MNT[14:12] · MNU[11:8] · ST[6:4] · SU[3:0] |
| **RTC_DR** | YT[23:20] · YU[19:16] · WDU[15:13] · MT[12] · MU[11:8] · DT[5:4] · DU[3:0] |

- Split a number: **tens = `v / 10`**, **units = `v % 10`** (12 → 1 and 2).
- Weekday WDU: **1 = Monday … 7 = Sunday**, 0 is forbidden. The hardware does **not** check it is correct — it just keeps counting from what you wrote. (31 Dec 2026 = Thursday = 4.)
- Year is 2 digits (26 = 2026).
- FMT (RTC_CR bit 6): 0 = 24 h, 1 = AM/PM (then PM bit 22 matters).

Check values: 12:34:04 → `TR = 0x00123404`; 2026-12-31 Thu → `DR = 0x00269231`.

---

<a id="shadow"></a>
## 5. Shadow registers & reading time

- The real counters run on RTCCLK (32 kHz); the CPU reads over APB (tens of MHz). Different, unsynchronised clocks → reading the live counter could catch it mid-change (e.g. 12:59:59 → 12:00:59).
- So the CPU reads **shadow copies**: **RTC_SSR, RTC_TR, RTC_DR**, updated every 2 RTCCLK cycles. After each copy the **RSF** flag (ISR bit 5) is set.
- **Coherency lock:** reading SSR or TR **freezes DR** until DR is read. ⇒ Always read **SSR → TR → DR**, otherwise time and date can mismatch at midnight.
- **After waking from Stop/Standby** the shadows are stale: clear RSF and wait for it to be set again before reading.
- APB1 clock must be **≥ 7 × RTCCLK** when using shadows.
- `BYPSHAD = 1` (RTC_CR bit 5) reads the counters directly — then you must read twice and compare yourself.

---

<a id="calibration"></a>
## 6. Calibration ⚠️

Both methods are **digital**: they don't tune the crystal, they **remove or add clock pulses** so the *average* rate is right.

- 1 ppm ≈ 2.6 s/month. A typical crystal is ±20 ppm ≈ ±52 s/month.

### Smooth vs coarse

| | **Smooth (RTC_CALR)** ✅ use this | Coarse (RTC_CALIBR) |
|---|---|---|
| Acts on | RTCCLK (before prescalers) | ck_apre |
| Range | **−487 to +488 ppm** | −63 to +126 ppm |
| Step | **0.954 ppm** | ~2 ppm (−) / ~4 ppm (+) |
| Change while running | ✅ (wait RECALPF = 0) | ❌ init mode only |
| Spread | Evenly over 32 s window | Bursts in first 2×DC min of 64 min |

> ⚠️ **Never enable both.** Use smooth.

### How smooth calibration works

- Window = 2²⁰ RTCCLK cycles = **32 s** (CALW16 → 16 s, CALW8 → 8 s: faster but coarser).
- **CALM[8:0]** = number of pulses **removed** per window → each = 1/2²⁰ = **0.954 ppm** (slows down).
- **CALP = 1** inserts **512** extra pulses per window = **+488.5 ppm** (speeds up).
- Net correction ≈ **(512 × CALP − CALM) × 0.954 ppm**.

$$f_{CAL} = f_{RTCCLK} \times \left[1 + \frac{CALP \times 512 - CALM}{2^{20} + CALM - CALP \times 512}\right]$$

> **CALM[8:0] is 9 bits, not 8.** `[high:low]` includes both ends → width = 8 − 0 + 1 = **9 bits → 0…511**. So 279 = `0x117` = `1 0001 0111` fits. Mask = `0x1FF`.

### Calculating the setting

$$\text{error (ppm)} = \frac{f_{measured} - f_{nominal}}{f_{nominal}} \times 10^6 \qquad \text{pulses} = \frac{|\text{error}|}{0.954}$$

| Clock is… | error | CALP | CALM |
|---|---|---|---|
| **Fast** (f > 512 Hz) | positive | 0 | pulses |
| **Slow** (f < 512 Hz) | negative | 1 | 512 − pulses |

- Example fast: 512.0098 Hz → +19.1 ppm → CALP 0, CALM 20.
- Example slow by 10 ppm → CALP 1, CALM 512 − 10.5 ≈ 502.

### My case: 265.625 ppm

- Coarse **can't** reach it (max +126 / −63). Smooth can.
- Pulses = 265.625 / 0.954 ≈ 278.5 → **279**.
  - Fast → `CALP = 0, CALM = 279`. Slow → `CALP = 1, CALM = 233`.
- ⚠️ 265 ppm ≈ **23 s/day** — unusually large for a crystal. Suspect the **measurement** first (scope/multimeter frequency readouts are not ppm-accurate; gate too short). Sanity check: set RTC to PC time, compare after 24 h.

### Measuring tips

- Measure the **512 Hz** output (more precise than 1 Hz in the same time).
- **Gate ≥ 32 s** (one full calibration window) — single periods show jitter from masked pulses.
- Your instrument must be **more accurate than the error** you measure.

---

<a id="pc13"></a>
## 7. PC13 / RTC_AF1 outputs

- **RTC_AF1 = PC13**, the RTC's own pin. Not set through GPIO AFR (AF0–15) — the RTC **takes over the pin directly** when you enable a function (COE, OSEL, TAMP1E, TSE). Leave GPIOC alone.
- F401CCU6 (UFQFPN48): PC13 = **pin 2**. No PI8 on this package, so no RTC_AF2 — everything shares PC13.
- Where to find it: **datasheet DS9716 → pin definitions table → "Additional functions"** column (it's *not* in the AF table). Also RM0368 §17.3 "RTC and alternate function", or click PC13 in CubeMX.

| Function | Direction | Enabled by |
|---|---|---|
| **RTC_OUT → RTC_CALIB** (512 Hz / 1 Hz) | out | `COE = 1`, `COSEL` = 0 (512 Hz) / 1 (1 Hz), `OSEL = 00` |
| **RTC_OUT → RTC_ALARM** (Alarm A/B/wake-up) | out | `OSEL` ≠ 00 (has priority over CALIB) · `POL` polarity · `ALARMOUTTYPE` OD/PP |
| RTC_TAMP1 | in | `TAMP1E` |
| RTC_TS | in | `TSE` |

- **Output has priority** over the inputs on the pin.
- **PC13 is weak:** sinks ~3 mA, can't source, ~2 MHz max. Wire LEDs **active-low**: `3V3 → resistor → LED → PC13` (≤ 3 mA; 1 kΩ ≈ 1.3 mA).
- Black Pill: onboard LED is on PC13 (active-low) → `COSEL = 1` makes it **blink at 1 Hz**: a free check that LSE + RTC run.
- 512 Hz needs PREDIV_A = 127; exact 1 Hz needs the defaults (A = 127, S = 255).

---

<a id="tamper"></a>
## 8. Tamper detection

**What:** watch a pin; on an event the hardware **instantly erases all backup registers** (80 bytes), even with the CPU off and only VBAT present.

**Why erase?** Backup registers hold data that survives power loss — keys, session tokens, credentials, "trusted" flags. An attacker who opens the box could read them. Example: a switch under the lid → lid opened → secrets wiped before anyone can probe the board.

- The hardware doesn't know which registers are secret → it wipes **all** (fast, no gaps).
- Even with no secrets it's useful: `TAMPTS = 1` **timestamps** the event, and wiped registers tell firmware "someone opened me".
- ⇒ Don't store things you want to keep (settings) in backup registers if tamper is on — use flash.

### Detection modes (RTC_TAFCR)

| Mode | Setting | Trigger (`TAMP1TRG`) |
|---|---|---|
| **Edge** | `TAMPFLT = 00` | 0 = rising edge · 1 = falling edge |
| **Level + filter** | `TAMPFLT` = 01/10/11 → 2/4/8 consecutive samples | 0 = staying low · 1 = staying high |

- Level mode extras: `TAMPFREQ[2:0]` sample rate (000 = 1 Hz … 011 = 8 Hz … 111 = 128 Hz), `TAMPPRCH[1:0]` precharge 1/2/4/8 cycles (internal pull-up pulsed only while sampling → low power), `TAMPPUDIS = 1` if you use an external pull-up.
- Level + filter rejects noise/bounce → **preferred for a mechanical switch**.

**On a tamper event:** TAMP1F (ISR bit 13) set → backup regs erased → interrupt (if TAMPIE, via **EXTI line 21**, IRQ `TAMP_STAMP`) → wake from Stop/Standby → timestamp saved (if TAMPTS).

---

<a id="timestamp"></a>
## 9. Timestamp

**What:** an edge on **RTC_TS (PC13)** makes the hardware copy the current time **instantly**, independent of what the CPU is doing (asleep, busy, ISR latency). Accuracy ≈ 1 ck_apre tick (≈ 4 ms at defaults).

| Register | Holds |
|---|---|
| RTC_TSTR | hh:mm:ss |
| RTC_TSDR | date, month, weekday — **no year** (read year from RTC_DR) |
| RTC_TSSSR | sub-seconds |

- Flags: **TSF** (bit 11) set on capture; **TSOVF** (bit 12) if another event comes before TSF is cleared — registers keep the **first** event.
- Interrupt: `TSIE` → EXTI line 21 → `TAMP_STAMP_IRQHandler`; can wake from Stop/Standby.
- ⚠️ Clear TSF **before** changing `TSE` / `TSEDGE` — changing them can cause a false event.

**Use cases**
- **Low-power event logger** (door reed switch → PC13): MCU sleeps in Stop, RTC captures the time, wakes MCU, ISR logs it, back to sleep.
- **Tamper forensics** (TAMPTS): when the case was opened.
- **Power-fail log**: supply-supervisor output → RTC_TS.
- **Interval measurement** (anemometer, rain gauge): subtract two timestamps, no ISR jitter.
- **Shock capture**: accelerometer INT → RTC_TS.

---

<a id="procedures"></a>
## 10. Procedures (step by step)

### A. RTC initialisation (LSE, 24 h)

1. **PWR clock on:** `RCC_APB1ENR |= bit 28 (PWREN)`; dummy read `RCC_APB1ENR`.
2. **Unlock backup domain:** `PWR_CR |= bit 8 (DBP)`; **dummy read `PWR_CR`** (required by RM).
3. **Already running?** If `RCC_BDCR.RTCEN (bit 15)` and `RTC_ISR.INITS (bit 4)` are both 1 → RTC kept time on VBAT → **stop here** (don't overwrite the time).
4. *(Optional)* If `RCC_BDCR.RTCSEL` ≠ 00 and ≠ 01 (wrong source locked in): set then clear `BDRST (bit 16)`. ⚠️ Wipes RTC + backup regs.
5. **Start LSE:** `RCC_BDCR |= LSEON (bit 0)`; wait for `LSERDY (bit 1)` (can take ~1–2 s; use a timeout).
6. **Select LSE:** `RCC_BDCR.RTCSEL[9:8] = 01`.
7. **Enable RTC clock:** `RCC_BDCR |= RTCEN (bit 15)`.
8. **Unlock RTC:** `RTC_WPR = 0xCA`, then `RTC_WPR = 0x53`.
9. **Enter init mode:** `RTC_ISR |= INIT (bit 7)`; wait for `INITF (bit 6)`.
10. **Prescalers** (only if not default): write `PREDIV_S` (PRER[14:0]) first, then `PREDIV_A` (PRER[22:16]) — two separate writes.
11. **Format:** `RTC_CR &= ~FMT (bit 6)` → 24 h.
12. **Load time/date:** write `RTC_TR`, `RTC_DR` (BCD).
13. **Exit init mode:** `RTC_ISR &= ~INIT` → calendar starts.
14. **Re-lock:** `RTC_WPR = 0xFF`.
15. **Verify:** read `RTC_TR` twice ~1 s apart; SU (bits 3:0) increments.

### B. Reading the time

1. *(After Stop/Standby only)* unlock WPR, clear `RSF`, re-lock, wait for `RSF = 1`.
2. Read `RTC_SSR` (optional) → `RTC_TR` → `RTC_DR` — **in this order**.
3. Decode BCD: value = tens × 10 + units.

### C. Calibration output on PC13

1. RTC initialised (A done; DBP set).
2. Unlock WPR (`0xCA`, `0x53`).
3. `OSEL[22:21] = 00` (alarm output off).
4. `COSEL (bit 19)`: 0 = 512 Hz, 1 = 1 Hz.
5. `COE (bit 23) = 1` → PC13 outputs RTC_CALIB. No GPIO config, no init mode.
6. Re-lock WPR.

### D. Smooth calibration

1. Output 512 Hz (procedure C, `COSEL = 0`), with `RTC_CALR = 0`.
2. Measure with gate ≥ 32 s → compute error (ppm) and pulses = |error| / 0.954.
3. Choose: fast → `CALP = 0, CALM = pulses`; slow → `CALP = 1, CALM = 512 − pulses`.
4. Unlock WPR.
5. Wait until `RTC_ISR.RECALPF (bit 16) = 0`.
6. Write `RTC_CALR = (CALP << 15) | CALM` (CALW8/CALW16 = 0 → 32 s window).
7. Re-lock WPR. Calendar keeps running.
8. Re-measure (≥ 32 s gate) → should read 512.000 Hz. Long-term check: compare with PC time after 24 h.
9. CALR is in the backup domain → survives reset; only redo after a backup-domain reset.

### E. Tamper detection (lid switch on PC13)

Wiring: switch between **PC13 and GND**, **closed when lid closed** (pin held low). Lid opens → switch opens → precharge pull-up pulls pin high → tamper.

1. RTC initialised (A done; DBP set). TAFCR is **not** WPR-protected, but needs DBP.
2. `TAMP1E (bit 0) = 0` while configuring.
3. Configure `RTC_TAFCR`:
   - `TAMPFLT[12:11] = 01` → level mode, 2 consecutive samples.
   - `TAMP1TRG (bit 1) = 1` → **high** level = tamper.
   - `TAMPFREQ[10:8] = 011` → sample at 8 Hz.
   - `TAMPPRCH[14:13] = 00`, `TAMPPUDIS (bit 15) = 0` → internal precharge pull-up.
   - `TAMPTS (bit 7) = 1` → also timestamp the event.
   - `TAMPIE (bit 2) = 1` → interrupt.
4. Clear stale flags: `RTC_ISR = ~(TAMP1F | TSF | INIT)`.
5. EXTI line 21: `EXTI_IMR |= bit 21`, `EXTI_RTSR |= bit 21`.
6. NVIC: enable IRQ 2 (`TAMP_STAMP`) → `NVIC_ISER0 |= bit 2`.
7. `TAMP1E = 1` → armed. (If the pin is already at the active level now, it fires immediately.)
8. ISR: check `TAMP1F` → read TSTR/TSDR/TSSSR if TAMPTS → log → clear `TAMP1F` (and `TSF`) → clear `EXTI_PR` bit 21.
   - Level mode: while the lid stays open the event can re-trigger. Disable `TAMP1E` in the ISR and re-arm once PC13 reads normal again.

### F. Timestamp on PC13

1. RTC initialised.
2. Unlock WPR.
3. `TSE (bit 11) = 0`; clear `TSF`/`TSOVF` (do this **before** changing TSE/TSEDGE).
4. `TSEDGE (bit 3)`: 0 = rising, 1 = falling.
5. `TSIE (bit 15) = 1`, then `TSE = 1`.
6. Re-lock WPR.
7. EXTI line 21 (IMR + RTSR) and NVIC IRQ 2, as in E.
8. ISR: read **TSSSR → TSTR → TSDR**, year from `RTC_DR`, clear `TSF` (check `TSOVF`), clear `EXTI_PR` bit 21.

---

<a id="code"></a>
## 11. Code

### rtc.h

```c++
#ifndef FLASH_PROGRAMMER_RTC_H
#define FLASH_PROGRAMMER_RTC_H
#include <stdint.h>

#define bit(x)        (1UL << (x))          /* (x) in brackets! */

/* ---------- RCC ---------- */
#define RCC_APB1ENR_L (*(volatile uint32_t *)0x40023840UL)
#define RCC_BDCR_L    (*(volatile uint32_t *)0x40023870UL)
#define PWREN         bit(28)               /* RCC_APB1ENR */
#define LSEON         bit(0)                /* RCC_BDCR */
#define LSERDY        bit(1)
#define RTCSEL_MASK   (3UL << 8)
#define RTCSEL_LSE    (1UL << 8)            /* RTCSEL = 01 */
#define RTC_EN        bit(15)
#define BDRST         bit(16)

/* ---------- PWR ---------- */
typedef struct {
    volatile uint32_t CR;                   /* 0x00 */
    volatile uint32_t CSR;                  /* 0x04 */
} PWR_TypeDef_L;
#define PWR           ((PWR_TypeDef_L *) 0x40007000UL)
#define DBP           bit(8)                /* PWR_CR */

/* ---------- EXTI / NVIC (tamper & timestamp interrupt) ---------- */
#define EXTI_IMR_L    (*(volatile uint32_t *)0x40013C00UL)
#define EXTI_RTSR_L   (*(volatile uint32_t *)0x40013C08UL)
#define EXTI_PR_L     (*(volatile uint32_t *)0x40013C14UL)
#define NVIC_ISER0_L  (*(volatile uint32_t *)0xE000E100UL)
#define EXTI_RTC_TAMP_TS   bit(21)          /* EXTI line 21 */
#define IRQ_TAMP_STAMP     bit(2)           /* IRQ number 2 */

/* ---------- RTC_CR ---------- */
#define TSEDGE        bit(3)
#define FMT           bit(6)
#define TSE           bit(11)
#define TSIE          bit(15)
#define COSEL         bit(19)
#define OSEL_MASK     (3UL << 21)
#define COE           bit(23)

/* ---------- RTC_ISR ---------- */
#define INITS         bit(4)
#define RSF           bit(5)
#define INITF         bit(6)
#define INIT          bit(7)
#define TSF           bit(11)
#define TSOVF         bit(12)
#define TAMP1F        bit(13)
#define RECALPF       bit(16)

/* ---------- RTC_CALR ---------- */
#define CALP          bit(15)
#define CALM_MASK     0x1FFUL               /* 9 bits: 0..511 */

/* ---------- RTC_TAFCR ---------- */
#define TAMP1E        bit(0)
#define TAMP1TRG      bit(1)
#define TAMPIE        bit(2)
#define TAMPTS        bit(7)
#define TAMPFREQ_8HZ  (3UL << 8)            /* TAMPFREQ = 011 */
#define TAMPFLT_2     (1UL << 11)           /* TAMPFLT  = 01  */
#define TAMP_CFG_MASK 0xFFFFUL              /* bits 15:0 */

/* ---------- RTC register map ---------- */
typedef struct {
    volatile uint32_t TR;        /* 0x00 */
    volatile uint32_t DR;        /* 0x04 */
    volatile uint32_t CR;        /* 0x08 */
    volatile uint32_t ISR;       /* 0x0C */
    volatile uint32_t PRER;      /* 0x10 */
    volatile uint32_t WUTR;      /* 0x14 */
    volatile uint32_t CALIBR;    /* 0x18 */
    volatile uint32_t ALRMAR;    /* 0x1C */
    volatile uint32_t ALRMBR;    /* 0x20 */
    volatile uint32_t WPR;       /* 0x24 */
    volatile uint32_t SSR;       /* 0x28 */
    volatile uint32_t SHIFTR;    /* 0x2C */
    volatile uint32_t TSTR;      /* 0x30 */
    volatile uint32_t TSDR;      /* 0x34 */
    volatile uint32_t TSSSR;     /* 0x38 */
    volatile uint32_t CALR;      /* 0x3C */
    volatile uint32_t TAFCR;     /* 0x40 */
    volatile uint32_t ALRMASSR;  /* 0x44 */
    volatile uint32_t ALRMBSSR;  /* 0x48 */
             uint32_t RESERVED7; /* 0x4C */
    volatile uint32_t BKPR[20];  /* 0x50 .. 0x9C : backup registers */
} RTC_TypeDef;
#define RTC           ((RTC_TypeDef *) 0x40002800UL)

/* ---------- time types ---------- */
typedef struct {
    short YEAR;     /* 0-99 (20xx)            */
    short MONTH;    /* 1-12                   */
    short DAY;      /* 1-31                   */
    short WEEK;     /* 1 = Monday .. 7 = Sunday */
    short HOUR;     /* 0-23                   */
    short MINUTE;   /* 0-59                   */
    short SECOND;   /* 0-59                   */
} TIME_RAW_TypeDef;

typedef struct {
    uint32_t TR;
    uint32_t DR;
} TIME_FIN_TypeDef;

TIME_FIN_TypeDef time_convert(TIME_RAW_TypeDef in);
void             rtc_init(void);
TIME_RAW_TypeDef rtc_read(void);
void             rtc_wait_sync(void);
void             rtc_calib_out(int one_hz);
void             rtc_calib_out_off(void);
void             rtc_smooth_calib(int calp, uint32_t calm);
void             rtc_tamper_init(void);
void             rtc_timestamp_init(int falling_edge);

#endif /* FLASH_PROGRAMMER_RTC_H */
```

### rtc.c

```c++
#include "rtc.h"

static inline void rtc_unlock(void) { RTC->WPR = 0xCA; RTC->WPR = 0x53; }
static inline void rtc_lock(void)   { RTC->WPR = 0xFF; }

TIME_RAW_TypeDef present_time = {
    .YEAR = 26, .MONTH = 12, .DAY = 31, .WEEK = 4,   /* Thursday */
    .HOUR = 12, .MINUTE = 34, .SECOND = 4
};

/* ---------- BCD encode ---------- */
TIME_FIN_TypeDef time_convert(TIME_RAW_TypeDef in) {
    TIME_FIN_TypeDef r;
    r.TR = ((uint32_t)(in.HOUR   / 10) << 20) | ((uint32_t)(in.HOUR   % 10) << 16)
         | ((uint32_t)(in.MINUTE / 10) << 12) | ((uint32_t)(in.MINUTE % 10) <<  8)
         | ((uint32_t)(in.SECOND / 10) <<  4) | ((uint32_t)(in.SECOND % 10) <<  0);
    r.DR = ((uint32_t)(in.YEAR   / 10) << 20) | ((uint32_t)(in.YEAR   % 10) << 16)
         | ((uint32_t)(in.WEEK)        << 13)
         | ((uint32_t)(in.MONTH  / 10) << 12) | ((uint32_t)(in.MONTH  % 10) <<  8)
         | ((uint32_t)(in.DAY    / 10) <<  4) | ((uint32_t)(in.DAY    % 10) <<  0);
    return r;
}

/* ---------- Procedure A ---------- */
void rtc_init(void) {
    RCC_APB1ENR_L |= PWREN;                 /* 1. PWR clock      */
    (void)RCC_APB1ENR_L;
    PWR->CR |= DBP;                         /* 2. unlock backup  */
    (void)PWR->CR;                          /*    dummy read     */

    if ((RCC_BDCR_L & RTC_EN) && (RTC->ISR & INITS))
        return;                             /* 3. already running */

    if ((RCC_BDCR_L & RTCSEL_MASK) &&       /* 4. wrong source?  */
        (RCC_BDCR_L & RTCSEL_MASK) != RTCSEL_LSE) {
        RCC_BDCR_L |=  BDRST;
        RCC_BDCR_L &= ~BDRST;
    }

    RCC_BDCR_L |= LSEON;                    /* 5. LSE on         */
    while (!(RCC_BDCR_L & LSERDY)) {}
    RCC_BDCR_L = (RCC_BDCR_L & ~RTCSEL_MASK) | RTCSEL_LSE;   /* 6 */
    RCC_BDCR_L |= RTC_EN;                   /* 7. RTC clock      */

    rtc_unlock();                           /* 8                 */
    RTC->ISR |= INIT;                       /* 9. init mode      */
    while (!(RTC->ISR & INITF)) {}

    RTC->CR &= ~FMT;                        /* 11. 24 h          */
    TIME_FIN_TypeDef t = time_convert(present_time);
    RTC->TR = t.TR;                         /* 12                */
    RTC->DR = t.DR;

    RTC->ISR &= ~INIT;                      /* 13. run           */
    rtc_lock();                             /* 14                */
}

/* ---------- Procedure B ---------- */
void rtc_wait_sync(void) {                  /* after Stop/Standby */
    rtc_unlock();
    RTC->ISR = (uint32_t)~(RSF | INIT);               /* clear RSF only    */
    rtc_lock();
    while (!(RTC->ISR & RSF)) {}
}

TIME_RAW_TypeDef rtc_read(void) {
    TIME_RAW_TypeDef t;
    uint32_t tr = RTC->TR;                  /* TR first: locks DR */
    uint32_t dr = RTC->DR;

    t.HOUR   = (short)(((tr >> 20) & 0x3) * 10 + ((tr >> 16) & 0xF));
    t.MINUTE = (short)(((tr >> 12) & 0x7) * 10 + ((tr >>  8) & 0xF));
    t.SECOND = (short)(((tr >>  4) & 0x7) * 10 + ((tr >>  0) & 0xF));
    t.YEAR   = (short)(((dr >> 20) & 0xF) * 10 + ((dr >> 16) & 0xF));
    t.WEEK   = (short)((dr >> 13) & 0x7);
    t.MONTH  = (short)(((dr >> 12) & 0x1) * 10 + ((dr >>  8) & 0xF));
    t.DAY    = (short)(((dr >>  4) & 0x3) * 10 + ((dr >>  0) & 0xF));
    return t;
}

/* ---------- Procedure C ---------- */
void rtc_calib_out(int one_hz) {            /* 0 = 512 Hz, 1 = 1 Hz */
    rtc_unlock();
    RTC->CR &= ~OSEL_MASK;
    if (one_hz) RTC->CR |=  COSEL;
    else        RTC->CR &= ~COSEL;
    RTC->CR |= COE;
    rtc_lock();
}

void rtc_calib_out_off(void) {
    rtc_unlock();
    RTC->CR &= ~COE;
    rtc_lock();
}

/* ---------- Procedure D ---------- */
void rtc_smooth_calib(int calp, uint32_t calm) {
    rtc_unlock();
    while (RTC->ISR & RECALPF) {}
    RTC->CALR = (calp ? CALP : 0) | (calm & CALM_MASK);
    rtc_lock();
}

/* ---------- Procedure E ---------- */
void rtc_tamper_init(void) {
    RTC->TAFCR &= ~TAMP1E;                  /* off while configuring */
    RTC->TAFCR = (RTC->TAFCR & ~TAMP_CFG_MASK)
               | TAMPFLT_2                  /* level, 2 samples   */
               | TAMP1TRG                   /* high = tamper      */
               | TAMPFREQ_8HZ               /* sample 8 Hz        */
               | TAMPTS                     /* timestamp it       */
               | TAMPIE;                    /* interrupt          */
    RTC->ISR = (uint32_t)~(TAMP1F | TSF | INIT);      /* clear stale flags  */

    EXTI_IMR_L   |= EXTI_RTC_TAMP_TS;
    EXTI_RTSR_L  |= EXTI_RTC_TAMP_TS;
    NVIC_ISER0_L  = IRQ_TAMP_STAMP;

    RTC->TAFCR |= TAMP1E;                   /* armed              */
}

/* ---------- Procedure F ---------- */
void rtc_timestamp_init(int falling_edge) {
    rtc_unlock();
    RTC->CR &= ~TSE;
    RTC->ISR = (uint32_t)~(TSF | TSOVF | INIT);       /* clear BEFORE edge change */
    if (falling_edge) RTC->CR |=  TSEDGE;
    else              RTC->CR &= ~TSEDGE;
    RTC->CR |= TSIE | TSE;
    rtc_lock();

    EXTI_IMR_L   |= EXTI_RTC_TAMP_TS;
    EXTI_RTSR_L  |= EXTI_RTC_TAMP_TS;
    NVIC_ISER0_L  = IRQ_TAMP_STAMP;
}

/* ---------- shared ISR (name from the startup file) ---------- */
void TAMP_STAMP_IRQHandler(void) {
    uint32_t isr = RTC->ISR;

    if (isr & (TSF | TAMP1F)) {
        uint32_t ssr = RTC->TSSSR;          /* SSR -> TR -> DR    */
        uint32_t tr  = RTC->TSTR;
        uint32_t dr  = RTC->TSDR;
        uint32_t yr  = (RTC->DR >> 16) & 0xFF;   /* TSDR has no year */
        (void)ssr; (void)tr; (void)dr; (void)yr; /* -> log_event(...) */

        if (isr & TAMP1F)
            RTC->TAFCR &= ~TAMP1E;          /* stop re-triggering; re-arm later */
        /* if (isr & TSOVF) -> an event was missed */

        RTC->ISR = (uint32_t)~(TSF | TSOVF | TAMP1F | INIT);
    }
    EXTI_PR_L = EXTI_RTC_TAMP_TS;           /* write 1 to clear   */
}
```

**Usage**

```c
rtc_init();
rtc_calib_out(1);              /* LED on PC13 blinks at 1 Hz        */
rtc_smooth_calib(0, 279);      /* clock was fast by ~266 ppm        */
TIME_RAW_TypeDef now = rtc_read();
```

- Flags in RTC_ISR are **rc_w0** (write 0 to clear, writing 1 does nothing). `RTC->ISR = (uint32_t)~(FLAG | INIT)` clears only FLAG without a read-modify-write race. INIT is included so the write never sets INIT by accident.
- If anything includes ST's `stm32f4xx.h`, the names `PWR`, `RTC`, `RTC_TypeDef` **clash** → rename yours or use ST's.

---

<a id="c-notes"></a>
## 12. C language notes

### Mapping registers with a struct pointer

```c
#define PWR ((PWR_TypeDef_L *) 0x40007000UL)   /* cast address to POINTER-to-struct */
PWR->CR |= DBP;
```

- ❌ `((PWR_TypeDef_L) * 0x40007000)` — casts to a struct and multiplies; doesn't compile.
- Members are laid out **in declaration order**, first at offset 0. `uint32_t` needs 4-byte alignment → consecutive `uint32_t` have **no padding** → CR at 0x0, CSR at 0x4.
- **Gaps** in a register map → fill with a reserved member: words = (next offset − current offset) / 4.
- **Verify at compile time:**

```c
#include <stddef.h>
_Static_assert(offsetof(RTC_TypeDef, WPR)  == 0x24, "WPR offset");
_Static_assert(offsetof(RTC_TypeDef, BKPR) == 0x50, "BKP offset");
```

### Addresses are bytes

- ARM memory is **byte-addressable**: address +0x1 = **1 byte (8 bits)**.
- A 32-bit register occupies 4 addresses → registers are **0x4 apart**.
- **Little-endian:** lowest byte at lowest address.
- Pointer arithmetic: `uint32_t *p; p + 1` moves **4 bytes**.

### `volatile`

Tells the compiler "this can change, or be read, outside my code — do every access exactly as written". Without it, at `-O2`:

- Polling loops read once and spin forever (`while(!(RTC->ISR & INITF))`).
- Back-to-back writes get merged/deleted (pin pulse disappears).
- "Unused" reads get removed (flag never clears).

Also needed for variables shared between an ISR and `main()`. It does **not** make `x++` atomic.

Typical symptom: works at `-O0`, breaks at `-O2`.

### Division and digits

| Expression | Result | Note |
|---|---|---|
| `19 / 10` | 1 | integer division truncates **toward zero** |
| `-19 / 10` | −1 | (Python `//` gives −2) |
| `19 % 10` | 9 | remainder = units digit |
| `19.0 / 10` | 1.9 | float if either side is float |
| `19 // 10` | 19 | ⚠️ `//` is a **comment** in C! |

### Bit-field notation & masks

- `FIELD[high:low]` → width = **high − low + 1** (CALM[8:0] = 9 bits, OSEL[1:0] = 2 bits).
- Multi-bit field write = clear then set: `REG = (REG & ~MASK) | VALUE;` — plain `|=` can't clear bits.
- `#define bit(x) (1UL << (x))` — always bracket macro arguments.

---

<a id="troubleshooting"></a>
## 13. Troubleshooting checklist

**"I wrote an RTC register and nothing changed"** — check in this order:

1. ☐ `RCC_APB1ENR.PWREN` set?
2. ☐ `PWR_CR.DBP` set **before** touching RCC_BDCR / RTC?
3. ☐ WPR unlocked (`0xCA`, `0x53`) — and not re-locked by a stray write?
4. ☐ TR / DR / PRER: in **init mode** with INITF = 1?
5. ☐ RTCSEL already set to another source (write-once)? → BDRST.
6. ☐ Pointers `volatile`? Struct offsets correct (`_Static_assert`)?
7. ☐ Read back the register in the debugger after the write.

**Hangs at `while(!LSERDY)`** → DBP not set yet, or crystal not oscillating.
**Hangs at `while(!INITF)`** → RTC has no clock (LSE/RTCSEL/RTCEN) or WPR still locked.
**Time resets on every boot** → no "already running" check (INITS + RTCEN).
**Stale time after sleep** → clear RSF and wait (`rtc_wait_sync`).
**PC13 shows no clock** → `OSEL` ≠ 00 (alarm has priority), COE not set, or WPR locked.

---

<a id="bits"></a>
## 14. Register bit reference

| Register (address) | Bit(s) | Name | Meaning |
|---|---|---|---|
| RCC_APB1ENR (`0x40023840`) | 28 | PWREN | PWR clock |
| RCC_BDCR (`0x40023870`) | 0 / 1 | LSEON / LSERDY | LSE on / ready |
| | 9:8 | RTCSEL | 01 = LSE (write-once) |
| | 15 / 16 | RTCEN / BDRST | RTC clock / backup reset |
| PWR_CR (`0x40007000`) | 8 | DBP | Backup domain write enable |
| RTC_CR (`+0x08`) | 3 | TSEDGE | 0 rising / 1 falling |
| | 6 | FMT | 0 = 24 h |
| | 11 / 15 | TSE / TSIE | Timestamp enable / interrupt |
| | 19 | COSEL | 0 = 512 Hz / 1 = 1 Hz |
| | 22:21 | OSEL | 00 = alarm output off |
| | 23 | COE | Calibration output enable |
| RTC_ISR (`+0x0C`) | 4 | INITS | Calendar initialised (year ≠ 0) |
| | 5 | RSF | Shadows synchronised |
| | 6 / 7 | INITF / INIT | Init mode active / request |
| | 11 / 12 / 13 | TSF / TSOVF / TAMP1F | Timestamp / overflow / tamper flags |
| | 16 | RECALPF | Calibration write pending |
| RTC_PRER (`+0x10`) | 14:0 / 22:16 | PREDIV_S / PREDIV_A | Default 255 / 127 |
| RTC_WPR (`+0x24`) | 7:0 | KEY | `0xCA`, `0x53` unlock · other = lock |
| RTC_CALR (`+0x3C`) | 8:0 | CALM | Pulses removed / 32 s (0–511) |
| | 13 / 14 | CALW16 / CALW8 | 16 s / 8 s window |
| | 15 | CALP | +512 pulses |
| RTC_TAFCR (`+0x40`) | 0 / 1 / 2 | TAMP1E / TAMP1TRG / TAMPIE | Enable / trigger level-edge / interrupt |
| | 7 | TAMPTS | Timestamp on tamper |
| | 10:8 | TAMPFREQ | Sample rate (011 = 8 Hz) |
| | 12:11 | TAMPFLT | 00 edge · 01/10/11 = 2/4/8 samples |
| | 14:13 | TAMPPRCH | Precharge 1/2/4/8 cycles |
| | 15 | TAMPPUDIS | 1 = disable precharge pull-up |
| RTC_BKPxR (`+0x50…0x9C`) | — | BKP0R–BKP19R | 80 bytes, wiped by tamper |
| EXTI (`0x40013C00`) | 21 | line 21 | RTC tamper + timestamp |
| NVIC_ISER0 (`0xE000E100`) | 2 | TAMP_STAMP | IRQ 2 |
