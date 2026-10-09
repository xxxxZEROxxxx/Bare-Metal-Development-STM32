# From HAL to Bare Metal and FreeRTOS: 60-Day Study Plan

**For Akary · 60 sessions × 4 hours = 240 hours · 5 sessions/week × 12 weeks**

Prepared 26 September 2026. Sessions are numbered study days, not consecutive calendar days. Take two days off each week; no required weekend homework.

## My assessment

Keep the goal and the main books, but change the plan. Your HAL experience makes it reasonable to move quickly through setup and basic peripherals. The missing depth is in how firmware starts, how hardware and software share data, how failures are diagnosed, and how timing is demonstrated. Those deserve more time than installing tools, copying examples, or polishing a portfolio.

The original is actually a 16-week schedule despite its 12-week title. At your pace that is about 320 hours, not 240. This replacement fits 60 sessions, covers the 18 technical chapters of Gbati's book, adds selected Cortex-M architecture readings, and gives FreeRTOS 18 sessions. It aims for independent, demonstrable competence—not a claim of mastery or production certification after three months.

## What I improved and corrected

| Original issue | Revision and reason |
|---|---|
| 12-week title but work scheduled through Week 16 | Exactly 12 weeks, 60 days, 240 hours; every day has a four-hour budget. |
| Several chapter numbers were shifted | Verified the Gbati chapter sequence against the publisher's contents and code repository; pinned the FreeRTOS book numbering below. [S1–S4] |
| RM0090 specified for the F411 | Use **RM0383** for STM32F411; other F4 parts require their own documentation. [S5] |
| Yiu M3/M4 book described as second edition | This plan uses the combined Cortex-M3/M4 **third edition**. Do not apply these chapter numbers to the earlier M3-only book. [S3] |
| Three weeks largely spent on setup/build basics | Reach a self-owned startup/build and architecture checkpoint by Day 10; use the saved time for faults, concurrency, integration and RTOS. |
| No HAL/CMSIS allowed | Write raw register definitions as an exercise, then use vendor CMSIS device headers and CMSIS-Core intrinsics. They do not prevent register-level driver development. No HAL or LL driver calls in the assessed implementation. [S7] |
| Debounce inside the ISR | ISR records/acknowledges an event; foreground code or a task handles debounce without waiting inside the interrupt. |
| Watchdog reset checked through IWDG_SR | Read reset-cause flags in RCC_CSR, including IWDGRSTF; IWDG_SR concerns register-update status. [S5] |
| DMA described as zero CPU load | Measure reduced CPU work, interrupt cost, buffer overruns and transfer timing. DMA still needs setup and completion handling. |
| Generic WHO_AM_I assumed for a BME280 | Use its actual chip-ID register: address 0xD0, expected BME280 ID 0x60. Temperature needs calibration/compensation, not just a raw register read. [S8] |
| DVFS and microamp measurements treated as simple | Make legal clock switching and Sleep the core exercise; study voltage scaling constraints. Only report current at the boundary and resolution you can actually measure. |
| Standby treated like ordinary execution resume | Separate Sleep, Stop and reset-like Standby wake; demonstrate their different state-retention behavior. [S5] |
| Move existing tick into a FreeRTOS tick hook | Give the port ownership of SysTick/PendSV/SVC; migrate application timing deliberately. Keep hardware timer triggering for precise ADC timing. [S6] |
| Binary semaphore used as a priority-inheritance fix | Teach event signaling separately from resource ownership; use a mutex for the priority-inheritance experiment. [S4] |
| One mocked test per driver / cppcheck implies MISRA compliance | Test behavior and failure paths; separate host tests from hardware evidence. Static analysis helps but does not establish MISRA compliance. [S11] |
| Linux/Yocto suggested for the F411 | Move conventional embedded Linux to a suitable application-processor board after this course. Keep networking, USB stacks and ML outside the 240-hour core. |

## Assumptions, hardware and scope

**Baseline:** NUCLEO-F411RE with STM32F411RET6. Confirm the exact board and revision on Day 1. If you own a different board, keep the learning sequence but replace the memory sizes, pin assignments, clock limits, DMA mappings, startup vectors and device documentation. Do not treat all STM32F4 devices as interchangeable.

Required for the full hardware track:

- Board, working data USB cable, breadboard, jumper wires, 10 kΩ potentiometer, an external LED and resistor.
- A documented **3.3 V-compatible BME280 breakout** with accessible I²C and SPI signals. Use the same sensor first over SPI, then I²C; no external flash purchase is necessary for the core course. Check module wiring and pull-ups before purchase/use. [S8]
- A logic analyzer capable of decoding the modest UART/SPI/I²C speeds used here, and a multimeter. An oscilloscope helps with analog noise and signal integrity but is not mandatory.
- For meaningful MCU-only low-power measurements: suitable current measurement equipment and a board-manual-guided measurement setup. A USB power meter only supports whole-board measurements at its actual resolution. [S9]

Software: an editor, one working GNU Arm toolchain, Make, GDB, OpenOCD or another supported ST-LINK debug server, Git, a serial terminal, host C compiler, Python, and Unity for host C tests. CubeIDE is optional as an initial known-good/debug reference. Use tools available on your OS; RealTerm and Windows-specific paths are not requirements. Avoid spending a day installing several equivalent toolchains.

**Learning boundary:** independently write the small peripheral drivers, startup, linker script and application. Reuse CMSIS headers, the official FreeRTOS port and a test framework. Read their relevant implementation. Reimplementing those entire projects would consume the course without improving the intended outcome.

**Hardware fallback:** if the sensor or analyzer is delayed, do host tests, SPI loopback and documented synthetic inputs within the assigned sessions. Mark those hardware checks **unverified**, not passed. A simulated reading is not sensor bring-up. Sleep is core; Stop/Standby are isolated experiments and do not have to be incorporated into the final high-rate data stream.

## Reading key and edition rules

The attachment contained your plan, but not the book TOC PDF it mentioned. The mappings below were checked against publicly available publisher/official contents. Page numbers are deliberately omitted because formats differ. Short topic labels below are reading locators, not verbatim chapter titles.

**B — Israel Gbati, _Bare-Metal Embedded C Programming_, 2024, ISBN 9781835460818.** Technical chapters 1–18; the publisher's online navigation may also count front/back matter. [S1, S2]

| B chapter | Topic locator | First main session(s) |
|---|---|---|
| 1 | Tools and documentation | 1 |
| 2 | Registers from addresses | 2–3 |
| 3 | Compilation and GNU tools | 4 |
| 4 | Linker and startup | 6–7 |
| 5 | Make | 5 |
| 6 | CMSIS | 8 |
| 7 | GPIO | 9 |
| 8 | SysTick | 11 |
| 9 | General timers | 12 |
| 10 | UART | 16–18 |
| 11 | ADC | 19–20 |
| 12 | SPI | 21–22 |
| 13 | I²C | 23–25 |
| 14 | EXTI | 13–14 |
| 15 | RTC | 31 |
| 16 | Independent watchdog | 32 |
| 17 | DMA | 26–30 |
| 18 | Power | 33–35 |

**Y — Joseph Yiu, _The Definitive Guide to ARM Cortex-M3 and Cortex-M4 Processors_, third edition, ISBN 9780124080829.** Selected readings only. Chapter locators used: 2 development; 4 architecture; 5 instructions; 6 memory; 7–8 exceptions; 9 power/SysTick; 10 OS support; 12 faults; 13 FPU; 14 debug; 17 GNU; 20 C/assembly. [S3]

**F — _Mastering the FreeRTOS Real Time Kernel_, official online book.** This plan uses the official repository's numbering in which Chapter 1 is the preface: 2 distribution, 3 allocation, 4 tasks, 5 queues, 6 software timers, 7 interrupts, 8 shared resources, 9 event groups, 10 notifications, 11 low power, 12 diagnostics, 13 troubleshooting. Older PDFs number topics differently. Match topics before starting; record the book revision and the stable kernel tag used. [S4]

**RM:** STM32F411 reference manual RM0383. **DS:** STM32F411 datasheet DS10314. **PM:** Cortex-M4 programming manual PM0214. **UM:** Nucleo board manual UM1724 and the matching board schematic. **ES:** device errata ES0287. Use the ST documentation landing page to obtain the current revisions. [S5]

Every day lists a primary book reading. Manual sections are targeted register/reference lookups, not instructions to read hundreds of pages. On integration days, reread only the named topic needed to answer the design question. Total reading remains inside the 45-minute block; unfinished background reading is optional, not hidden overtime.

## How each four-hour session works

| Block | Minutes | Method |
|---|---:|---|
| Retrieve | 15 | Answer yesterday's key question from memory; predict today's hardware behavior. |
| Read | 45 | Read the assigned chapter portions; sketch the relevant state machine or register sequence. |
| Build | 120 | Implement the day's bounded lab. Start from your code; try before opening the book's solution. |
| Verify | 45 | Run the stated checks; capture evidence or debug the failed check. |
| Record | 15 | Commit meaningful work; record observation, cause, fix and remaining question in `docs/day-NN.md`. |
| **Total** | **240** | **4 hours** |

Breaks can be taken between blocks; 240 minutes refers to focused work. Each daily entry below fills these same blocks. “Build” means the two-hour lab, and “Pass” defines what to verify in the 45-minute block. A pass is not assumed just because the session ended.

**Intensity rule:** one clear new mechanism per day, then test it under failure. On weekly checkpoint days, spend the Build block repairing the weakest prerequisite before extending anything. If blocked for 30 minutes, record register values, expected sequence and the smallest reproducer; then consult the manual/errata or reference solution. Do not randomly change several settings at once.

**Recovery without adding days:** checkpoint sessions 10, 15, 20, 25, 30, 35, 40, 42, 50, 55 and 60 include consolidation. Drop optional embellishments first: pressure/humidity, extra sensor commands, Stop/Standby hardware extensions, rich CLI, DSP, dashboard and presentation polish. Preserve startup, interrupt safety, DMA ownership and RTOS API-priority correctness. If those remain unresolved at Day 60, report incomplete gates honestly; a calendar cannot guarantee mastery.

## Project used throughout: measured sensor hub

Build one system in two versions: a cooperative bare-metal application and a FreeRTOS application. Both use your own register-level drivers.

Proposed acceptance targets—not guaranteed device specifications:

- Timer-triggered ADC at **1,000 samples/s**, one channel, circular DMA into two 64-sample halves. Each completed half has a **64 ms reuse deadline**.
- BME280 temperature at **1 sample/s**, using documented compensation. Initial SPI lab; final application uses I²C. Pressure/humidity are optional.
- Binary UART telemetry at **115200 baud, 8N1**, with version, type, length, sequence, timestamp, payload and CRC-16. Write each field explicitly; do not transmit a compiler-dependent C struct image.
- With 128 payload bytes plus a proposed 20-byte overhead, one ADC frame is 148 bytes. At 15.625 frames/s this is about 2,313 bytes/s; 115200 8N1 gives a theoretical 11,520 bytes/s before margin and other traffic. Verify the actual format's budget before freezing it.
- Sequence numbers, DMA overrun counts, sensor errors, queue-full counts and reset cause are visible. A slow consumer follows a documented drop/recovery policy.
- A 30-minute supervised nominal run on Day 58 has zero unexplained resets, malformed frames or missing sequence numbers. Fault tests separately demonstrate bounded failure and recovery; do not demand zero drops during intentional overload.
- CPU work, interrupt latency, memory/stack use and timing are measured under a stated load. Observed maxima are evidence, not a formal worst-case execution-time proof.

Use monotonic timer time for intervals/deadlines and RTC time for calendar labels. A calendar adjustment must not break a timeout.

## Week 1 — Build confidence below HAL

### Day 01 — Establish the exact target and a debug baseline

- **Learn / retrieve:** Trace a HAL LED call conceptually through clock, pin and register layers. Identify what you already understand and what you cannot yet explain.
- **Read:** B1, tool and board portions; Y2, development flow. UM, board connections; DS, device identification and memory summary.
- **Build:** Confirm board/MCU/revision, tool versions and debug connection. Run a known-good LED project solely as a connection check. Create the repository, a board facts file and a separate register-level project with borrowed startup clearly labeled temporary.
- **Pass:** Halt at `main`, read a RAM variable, reset, reflash and reproduce. Record actual Flash/SRAM sizes and where the LED/button/debug UART connect. If setup consumes the lab, resolve it before peripherals.
- **Evidence / explain:** `docs/board.md`, baseline build instructions. Explain the difference between the MCU datasheet, reference manual, programming manual and board schematic.

### Day 02 — Derive GPIO from the documentation

- **Learn / retrieve:** Calculate an MMIO register address as peripheral base plus offset.
- **Read:** B2, register construction; RM, GPIO and RCC enable fields; DS, pin assignment.
- **Build:** Starting from an empty application file, define only the RCC/GPIO registers required for the LED. Enable the clock, set output mode and use BSRR for set/reset. Keep temporary startup from Day 1.
- **Pass:** Inspect addresses and register values in GDB, then make the LED change state. Disable the peripheral clock deliberately and explain the changed behavior. Avoid treating a busy-loop delay as a calibrated timebase.
- **Evidence / explain:** `labs/02_gpio_raw/`; write the clock-to-pin dependency sequence without looking at source.

### Day 03 — C semantics for hardware

- **Learn / retrieve:** Explain `volatile`, `const`, unsigned shifts, promotions, alignment and read-modify-write hazards.
- **Read:** B2, manipulation review; Y2, C types/peripheral access; Y6, alignment. RM, access semantics for today's registers.
- **Build:** Write unsigned mask/field helpers with range checks. Compare volatile/nonvolatile generated loads. Contrast BSRR writes with ODR read-modify-write. Add compile-time offset/size checks to your tiny register struct; avoid C bitfields for MMIO.
- **Pass:** Host-check boundary shift/mask cases; inspect optimized assembly. Explain why `volatile` is neither a mutex nor a general memory-order guarantee, and why W1C registers need special handling.
- **Evidence / explain:** `docs/c-hardware-rules.md` and a small reproducible assembly example.

### Day 04 — Own the compilation pipeline

- **Learn / retrieve:** Predict what exists after preprocessing, compilation, assembly and linking.
- **Read:** B3; Y17, command-line development portions.
- **Build:** Produce `.i`, `.s`, `.o`, `.elf`, `.bin` and `.hex` for the LED program. Use `objdump`, `readelf`, `nm` and `size`; identify a function, global, relocation and section. Keep target and host compilation separate.
- **Pass:** Trace one source function into the ELF. Explain why a raw binary loses ELF symbols and why an unresolved symbol is a link error. Save exact working compiler/CPU flags.
- **Evidence / explain:** `docs/build-pipeline.md`; an annotated, small disassembly excerpt.

### Day 05 — Reproducible Make build and first review

- **Learn / retrieve:** Reconstruct the Day 2 setup order from memory.
- **Read:** B5, dependencies and firmware Makefiles; B3 review of diagnostic tools.
- **Build:** Add Make targets for build, clean, flash, debug and size; header dependency generation; separate debug/release directories. Enable useful warnings such as `-Wall -Wextra -Wshadow`; investigate rather than silence warnings indiscriminately.
- **Pass:** A clean checkout builds and flashes using documented commands. Touching a header rebuilds affected files. Compare a debug and optimized LED build. No HAL/LL driver is linked into the register-level application.
- **Evidence / explain:** Working Makefile and weekly note: what generated code/startup you still depend on and will replace next week.

## Week 2 — Startup, architecture and dependable GPIO

### Day 06 — Linker script and the memory image

- **Learn / retrieve:** Predict the locations of code, constants, initialized globals, zeroed globals and stack.
- **Read:** B4, memory and linker portions; Y4, reset overview. RM/DS, actual memory map.
- **Build:** Write a minimal linker script with vector table, text/rodata, data, BSS and reserved stack. Distinguish load and execution addresses; retain the vector section with `KEEP`. Generate a map file.
- **Pass:** Locate one variable in each class and the initial stack address. Add linker assertions for overflow/alignment. Deliberately oversize a test allocation and see a useful link failure, then remove it.
- **Evidence / explain:** `linker/stm32f411.ld`; annotated memory map. Explain why `.data` occupies both Flash storage and RAM at runtime.

### Day 07 — From reset to main

- **Learn / retrieve:** Describe the first two vector-table entries and why reset does not start directly at `main`.
- **Read:** B4, startup portions; Y4, reset; Y20, C/assembly interaction overview.
- **Build:** Write minimal startup with initial SP, Reset_Handler and correctly ordered core/device vectors. Copy `.data`, clear `.bss`, then call `main`; add safe default handlers. Use a small assembly entry or a carefully reviewed C startup; understand which runtime initialization your chosen build actually needs.
- **Pass:** Break before/after initialization and prove a nonzero global and a BSS variable are initialized correctly across reset. Read initial SP and reset vector from the linked image. Verify the Thumb entry and aligned stack.
- **Evidence / explain:** Self-owned startup and reset trace. The program now runs without borrowed startup code.

### Day 08 — CMSIS and enough assembly to debug

- **Learn / retrieve:** Explain the difference between a register declaration and a peripheral driver.
- **Read:** B6; Y5, basic load/store/branch instructions; Y20, calling conventions topic. CMSIS device-header guidance [S7].
- **Build:** Replace hand-maintained GPIO/RCC declarations with the correct device header. Step through a C function using R0–R3, LR, SP and return values. Compare generated MMIO instructions before and after using the header.
- **Pass:** LED behavior matches; you can identify a load, store, call, branch and stack operation. Explain caller/callee responsibilities and why manually recreating every device register is unnecessary.
- **Evidence / explain:** `docs/cmsis-boundary.md`; list exactly which vendor files are used and why.

### Day 09 — GPIO driver and pin ownership

- **Learn / retrieve:** Explain input/output/alternate/analog modes, pull resistors and push-pull versus open-drain.
- **Read:** B7; RM, GPIO fields; DS, alternate-function table; UM, shared board pins.
- **Build:** Create a small GPIO API and board pin table. Read a button, drive an external LED and preserve unrelated configuration fields. Assign planned UART, analog, timer and sensor pins; avoid conflicting with the on-board LED or debug interface.
- **Pass:** Verify button polarity and idle state; invalid pin/mode requests fail predictably. Inspect that configuring one pin does not change its neighbors.
- **Evidence / explain:** `drivers/gpio.*`, pin table and wiring photo. Explain why electrical drive capability cannot be inferred from a logic-high register value alone.

### Day 10 — Checkpoint: boot and build without a template

- **Learn / retrieve:** Draw reset → vector → runtime initialization → main → register write.
- **Read:** B3–B7 targeted review only; Y14, breakpoints/watchpoints introduction.
- **Build:** Use the two-hour block to rebuild a minimal LED/button application from your own startup/linker/driver pieces. Seed one bad pin mode and one bad build dependency, then diagnose them. Repair outstanding Week 1–2 failures.
- **Pass:** Clean command-line build, correct initialization, no HAL/LL dependency, working reset and watchpoint, and a register configuration you can explain without the book.
- **Evidence / explain:** Tag `foundation-v1` only if the gate passes; otherwise record the failed condition. A working LED alone does not pass this gate.

## Week 3 — Time, exceptions and fault diagnosis

### Day 11 — A real timebase and nonblocking deadlines

- **Learn / retrieve:** Explain why a CPU loop is not a stable clock.
- **Read:** B8; Y9, SysTick topic; RM, reset clock source.
- **Build:** Configure a millisecond tick from the known clock. Implement elapsed-time checks using unsigned wrap-safe subtraction within a documented interval bound. Schedule two LED patterns without blocking the foreground loop.
- **Pass:** Check timing against an external observation, then inject a counter near wraparound and prove deadlines still work. Bound your supported timeout range. Keep the ISR short.
- **Evidence / explain:** Timebase code and host boundary tests. Explain elapsed time versus wall-clock/calendar time.

### Day 12 — Clock tree, timer frequency and PWM

- **Learn / retrieve:** Calculate timer period from clock, prescaler and reload, including the `+1` terms.
- **Read:** B9; RM, clock tree/APB timer-clock rules and selected timer; DS, legal frequency limits.
- **Build:** Document core/AHB/APB/timer rates at your initial conservative configuration. Produce timer PWM and change duty through compare registers; inspect preload/update behavior. Reserve a timer suitable for the later ADC trigger.
- **Pass:** Measure two frequencies and three duty cycles on the analyzer. Explain any discrepancy, the effect of APB prescaling, and the distinction between PWM and sample scheduling.
- **Evidence / explain:** Clock table, calculation sheet and capture. Do not assume every bus runs at the core clock.

### Day 13 — EXTI and the interrupt path

- **Learn / retrieve:** Distinguish peripheral event, pending flag, NVIC enable and CPU exception entry.
- **Read:** B14; Y7, vectors/priorities; RM, SYSCFG and EXTI.
- **Build:** Route the button to EXTI, configure the edge and NVIC, clear pending state correctly, then enqueue/set an event for the foreground loop. Debounce with a time-based state machine outside the ISR.
- **Pass:** A deliberate sequence of button presses gives one accepted action each after debounce. Flood edges and show the foreground remains responsive. Demonstrate correct write-one-to-clear handling.
- **Evidence / explain:** ISR/foreground diagram and latency marker capture. Explain what goes wrong if an ISR waits for a lower-priority tick.

### Day 14 — Shared data, interrupt priority and latency

- **Learn / retrieve:** Explain why two operations on individually atomic words can still form a race.
- **Read:** Y6, exclusive access/barrier concepts; Y7–Y8, masking and exception entry; B14 review.
- **Build:** Create a controlled main/ISR shared-state race, then fix it with a short critical section that restores previous mask state. Use GPIO markers and optionally DWT cycles to measure handler work; distinguish handler duration from event-to-handler latency.
- **Pass:** Compare unprotected/protected runs and show the invariant holds under interrupt load. Document what your compiler/architecture guarantee and where a barrier or critical section is required. Never treat volatile alone as synchronization.
- **Evidence / explain:** Race reproducer, measured interrupt cost and a concurrency policy for future buffers.

### Day 15 — Fault handling and architecture checkpoint

- **Learn / retrieve:** Predict which evidence helps locate a faulting instruction.
- **Read:** Y12, fault registers and analysis; Y8, stacked exception context; PM, SCB fault fields.
- **Build:** Capture a minimal fault record in RAM and halt safely for GDB. Extract the appropriate stack frame using EXC_RETURN/MSP/PSP knowledge. Trigger a controlled undefined-instruction fault; avoid relying on undefined C behavior to generate it.
- **Pass:** Recover stacked PC/LR/xPSR and relevant fault flags; locate the instruction in disassembly. Repeat without `printf` inside the fault handler. Repair any timing/EXTI failures from Days 11–14.
- **Evidence / explain:** `docs/fault-case-01.md`. State that the initial decoder assumes a basic frame; account for extended FP frames before enabling FPU use in the RTOS build.

## Week 4 — UART, testable code and ADC

### Day 16 — Polling UART with bounded waits

- **Learn / retrieve:** Derive serial bit time and 8N1 byte time; distinguish peripheral clock from CPU clock.
- **Read:** B10, configuration/polling portions; RM, USART baud and status behavior; UM, virtual COM routing.
- **Build:** Implement transmit/receive with deadlines and explicit status codes. Add a small nonblocking command parser or foreground input state machine; keep commands limited to status and LED control.
- **Pass:** Decode a known byte pattern, verify baud error from your actual clock, and handle no-input timeout without freezing the system. Check standalone operation without a debugger or semihosting dependency.
- **Evidence / explain:** UART driver and capture. Explain TX-register-empty versus final transmission-complete.

### Day 17 — Interrupt-driven receive and a ring buffer

- **Learn / retrieve:** Define producer, consumer, full/empty state and buffer ownership.
- **Read:** B10 review; Y7, interrupt-control review; RM, USART receive/error clearing sequence.
- **Build:** Add RX interrupt capture into a single-producer/single-consumer ring and foreground parsing. Make overflow/drop behavior explicit. Use reviewed synchronization for shared indices; keep parsing and output out of the ISR.
- **Pass:** Exercise empty/full/wrap cases and bursts longer than the buffer. Report overrun/overflow counts. A malformed command must not stall reception.
- **Evidence / explain:** Ring tests and burst log. Explain the race implications of a shared count variable versus separate producer/consumer indices.

### Day 18 — Host tests that find real bugs

- **Learn / retrieve:** Explain what a host test can and cannot establish about MMIO.
- **Read:** B10, driver structure review; Unity guide [S10]; B5, host-test target review.
- **Build:** Separate ring, parser, timeout arithmetic and baud calculations from hardware access. Add `make test` using Unity; use simple fakes first, CMock only if it reduces effort. Define a narrow register-access seam where useful.
- **Pass:** Include normal, boundary and failure cases; deliberately introduce an off-by-one error and see a test fail. Use host sanitizers if supported. Record that fake registers cannot prove bus timing or hardware side effects.
- **Evidence / explain:** At least eight focused behavioral tests across these modules, with meaningful failure messages—not a quota of one superficial test per driver.

### Day 19 — ADC measurement fundamentals

- **Learn / retrieve:** Predict counts for ground, midscale and a safe near-full-scale voltage.
- **Read:** B11, ADC setup and conversion; RM/DS, analog input limits, sample time and ADC clock.
- **Build:** Wire the potentiometer within the board's analog voltage limits. Configure analog mode, sample time and one conversion; print raw counts and a documented voltage estimate using measured/reference supply assumptions.
- **Pass:** Measure three input levels with the multimeter and compare readings. Log an error range and noise distribution. Explain quantization, reference error, source impedance and settling without claiming lab-grade calibration.
- **Evidence / explain:** ADC table and driver; a timeout path that exits if conversion never completes.

### Day 20 — Peripheral integration checkpoint

- **Learn / retrieve:** Explain why serial logging can distort the thing being measured.
- **Read:** B9–B11, only trigger/timing/error topics needed today; Y14, observation methods review.
- **Build:** Run LED scheduling, button events, UART input and modest-rate ADC acquisition cooperatively. Add a first telemetry record with sequence and monotonic time. Repair the weakest driver/test before adding features.
- **Pass:** Ten-minute run with responsive commands and bounded waits. Inject UART bursts while sampling; quantify observed missed deadlines instead of hiding them. Log CPU-side limitations that DMA should later address.
- **Evidence / explain:** `peripherals-v1` checkpoint and measured baseline. Identify the single next bottleneck from evidence.

## Week 5 — External buses and a real sensor

### Day 21 — SPI from waveforms to transactions

- **Learn / retrieve:** Sketch clock polarity/phase, chip-select lifetime and full-duplex transfer.
- **Read:** B12, SPI fundamentals/configuration; RM, SPI flags; BME280 datasheet, SPI interface [S8].
- **Build:** Configure a conservative SPI clock on nonconflicting pins. First use a MOSI-to-MISO loopback if available, then write a bounded byte/buffer transaction API with software chip select. Ensure receive data is drained even for transmit-oriented operations.
- **Pass:** Decode known patterns and explain each edge. Verify timeout cleanup and chip-select deassertion after errors. Do not interpret loopback success as proof that a sensor command is correct.
- **Evidence / explain:** SPI capture and transaction contract, including who owns the bus until completion.

### Day 22 — Bring up the sensor over SPI

- **Learn / retrieve:** Separate transport success from device identification and measurement validity.
- **Read:** B12, device transaction portions; BME280 datasheet, SPI register access, reset, status and identification.
- **Build:** Verify breakout mode straps and power; read the chip ID, reset the sensor and poll its documented initialization status with a timeout. Add register read/write helpers and a raw-data dump. Do not yet implement all environmental outputs.
- **Pass:** Repeat identity reads across power cycles; disconnect the sensor and return an error instead of valid-looking data. Explain dummy transmit bytes, read-command encoding and chip-select framing.
- **Evidence / explain:** `drivers/bme280_transport.*`, identity transcript and annotated analyzer trace.

### Day 23 — I²C electrical behavior and register reads

- **Learn / retrieve:** Explain open-drain signaling, pull-ups, ACK/NACK, seven-bit addressing and repeated START.
- **Read:** B13, bus fundamentals/master transactions; RM, I²C transmit/receive sequences; ES, relevant limitations; sensor datasheet, I²C interface.
- **Build:** Rewire the same sensor for I²C using its documented mode selection. Begin at 100 kHz with verified pull-ups. Implement a bounded register-address write followed by a repeated-START read. Follow the F411-specific receive sequence; do not copy a different STM32 I²C peripheral generation.
- **Pass:** Read the same identity as Day 22; decode address, direction, ACK and final NACK/STOP. Test one-byte reception explicitly. A missing device produces a bounded error.
- **Evidence / explain:** Pin/pull-up table and I²C capture; explain seven-bit address versus the transmitted address byte.

### Day 24 — I²C multi-byte transfers and error recovery

- **Learn / retrieve:** Predict the cleanup required after NACK, timeout and stuck-bus conditions.
- **Read:** B13, receive/write portions; RM/ES, one-byte, two-byte and longer receive sequences plus error flags.
- **Build:** Extend the read API to 1, 2 and multiple bytes; inspect the sensor calibration block. Implement bounded cleanup, retry limits and a single-master recovery policy. Document when recovery clocks/STOP are appropriate and when a held line cannot be recovered by software.
- **Pass:** Test each receive length and a wrong address. Simulate timeout at the access seam; if hardware permits, demonstrate a safe bus-fault test. Recovery must not loop forever or silently return stale data as fresh.
- **Evidence / explain:** Failure matrix with maximum wait budgets and a distinction between transport error and sensor-invalid state.

### Day 25 — Compensated temperature and bus checkpoint

- **Learn / retrieve:** Explain why raw sensor codes are not physical units.
- **Read:** B13 review; BME280 datasheet, calibration coefficients, forced measurement and temperature compensation. Use the manufacturer's reference implementation as a cross-check [S8].
- **Build:** Read calibration once, initiate a measurement, wait without blocking unrelated foreground work and calculate temperature. Validate arithmetic against a known input/reference calculation; add a sensor state machine and status flags. Pressure/humidity are optional.
- **Pass:** Temperature responds plausibly to a gentle environmental change; compare with another thermometer while acknowledging uncertainty. Pass host compensation tests and disconnect/reconnect behavior. Repair SPI/I²C essentials before extra outputs.
- **Evidence / explain:** One sensor API with separated transport and conversion logic; bus checklist and test vectors with their provenance.

## Week 6 — DMA, sample timing and buffer ownership

### Day 26 — Understand a DMA transfer before using a peripheral

- **Learn / retrieve:** Identify source/destination, widths, counts, increments and ownership.
- **Read:** B17, DMA fundamentals/memory transfers; RM, DMA controller and applicable memory-to-memory capability.
- **Build:** Implement one small memory-to-memory test on a supported stream/controller. Derive rather than guess the stream configuration. Add completion/error reporting and a bounded disable/reconfigure sequence.
- **Pass:** Compare destination against source, check guard values around both buffers and test several aligned lengths. Inspect count and flags. Record unsupported requests as errors rather than programming arbitrary addresses.
- **Evidence / explain:** DMA checklist: request mapping, direction, widths, addresses, count, flags, interrupt and lifetime.

### Day 27 — Timer-triggered ADC plus circular DMA

- **Learn / retrieve:** Explain why acquisition timing should not depend on the foreground loop's speed.
- **Read:** B17, ADC/DMA portions; B9/B11, timer-trigger and conversion review; RM, ADC trigger selection and DMA request table.
- **Build:** Configure the proposed 1 ksample/s acquisition into a 128-sample circular buffer. Select a documented timer trigger and compatible stream/channel. Handle half/full completion minimally; retain the precise timer even when an RTOS is added later.
- **Pass:** Count blocks over a known interval, verify half ordering and inspect changing analog data. Check trigger rate independently where possible and document conversion-time margin.
- **Evidence / explain:** ADC/DMA configuration table and capture. Explain why a task delay is not equivalent to hardware triggering.

### Day 28 — Race-free DMA consumption

- **Learn / retrieve:** Calculate the time until DMA overwrites a completed half.
- **Read:** B17 review; Y6, memory-order concepts; RM, circular transfer/interrupt semantics.
- **Build:** Define who owns each DMA half. Copy completed data promptly into a bounded software block pool, or use a proven ownership scheme with an explicit deadline. Publish completed blocks only after their contents are ready. Add sequence and overrun counters.
- **Pass:** Artificially delay the consumer past the 64 ms half-buffer deadline. Detect invalid/overwritten data rather than quietly transmitting it. Explain why queuing only a pointer does not extend the buffer's lifetime.
- **Evidence / explain:** Ownership diagram, processing-time measurement and deliberate-overrun test.

### Day 29 — UART transmit DMA and packet lifetime

- **Learn / retrieve:** Explain when a DMA source buffer may be reused and when the wire is actually idle.
- **Read:** B17, UART DMA; B10, USART completion review; RM, USART DMA request behavior.
- **Build:** Add nonblocking UART-TX DMA using a dedicated packet buffer or fixed pool. Distinguish DMA completion from final USART transmission completion. Reject or queue a new request while busy; define reset/timeout cleanup.
- **Pass:** Send a recognizable byte pattern and decode it exactly. Try back-to-back requests and a deliberately premature caller-buffer modification in an isolated test, then show how the API prevents corruption.
- **Evidence / explain:** TX ownership contract and completion timeline; CPU-cost comparison with polling for the same payload.

### Day 30 — Streaming checkpoint under load

- **Learn / retrieve:** Derive sustainable data rate, UART occupancy and the buffer budget.
- **Read:** B9–B11/B17 targeted review; Y14, measurement review.
- **Build:** Connect timer → ADC → DMA → block processing → UART DMA. Add a minimal host capture/decoder with timestamps and sequence checks. Keep format simple until Week 8. Repair concurrency errors before raising rates.
- **Pass:** Ten-minute nominal stream with correct counts and no unexplained corruption. Force a slow consumer and verify the documented drop/overrun policy. Measure CPU work with stated instrumentation overhead; do not claim zero CPU use.
- **Evidence / explain:** `streaming-v1` checkpoint, bandwidth calculation, max observed processing time and error-counter report.

## Week 7 — Recovery, calendar time and power

### Day 31 — RTC and the backup domain

- **Learn / retrieve:** Contrast persistent calendar state with the millisecond uptime counter.
- **Read:** B15; RM, RTC/backup-domain sequencing and clock sources; UM, oscillator population for your board revision.
- **Build:** Select a verified available RTC clock source, initialize calendar time once using a backup marker and read a coherent date/time snapshot. Create one alarm/wakeup experiment. If using the internal low-speed oscillator, document its accuracy limitations.
- **Pass:** Verify seconds/date transition logic and software-reset persistence under the actual power arrangement. Never claim battery-backed retention unless backup power is really provided. Show that a time adjustment leaves monotonic deadlines unaffected.
- **Evidence / explain:** RTC initialization policy, clock-source record and timestamped UART log.

### Day 32 — Watchdog as a health decision

- **Learn / retrieve:** Explain why feeding from an unconditional timer ISR can conceal a dead application.
- **Read:** B16; RM, IWDG timing and RCC reset flags.
- **Build:** Enable a conservatively timed watchdog and capture reset cause early in boot, before clearing flags. Refresh only when required foreground activities have made progress. Add deliberate sensor/processing stalls; distinguish recoverable sensor errors from loss of system progress.
- **Pass:** A deliberate deadlock/stall resets the board; healthy operation does not. Report the cause after reboot. Account for low-speed clock tolerance and the debugger's watchdog-freeze configuration.
- **Evidence / explain:** Reset log and health policy. Explain why a returning error is different from a hung driver.

### Day 33 — Sleep and legal clock reconfiguration

- **Learn / retrieve:** Explain why changing the system clock also affects timeouts and peripheral divisors.
- **Read:** B18, Sleep/power concepts; Y9, wait instructions; RM/DS, RCC, Flash latency and voltage-scale constraints.
- **Build:** Add an idle policy with WFI after pending work is checked safely. Compare active spinning with Sleep. If prerequisite timing is solid, switch between two documented legal clock configurations using the required sequencing, then recompute timing-dependent values. Dynamic voltage scaling is a reading exercise, not a required implementation.
- **Pass:** Events are not stranded by a check-then-sleep race; UART and timing still work after wake. For a clock-change experiment, verify actual rates and readiness flags; preserve a known-good recovery build.
- **Evidence / explain:** Idle policy and clock transition checklist. Do not change frequency while a live transfer depends on the old clock.

### Day 34 — Stop and Standby as separate experiments

- **Learn / retrieve:** Predict what survives in RAM, clocks and backup state for each mode.
- **Read:** B18; Y9 review; RM, wake-source and state-retention tables.
- **Build:** In a separate lab image, enter Stop with a verified wake source, then restore required clocks/peripherals. Inspect Standby entry/wake as a reset-like path using a supported source and backup marker. Keep debugger reconnect/reflash instructions ready; if hardware is unsuitable, complete an annotated code walkthrough instead.
- **Pass:** Demonstrate or explicitly mark unverified the resume/reset distinction. Report wake cause and identify retained/lost state. Do not combine deep sleep with continuous high-rate acquisition today.
- **Evidence / explain:** Mode/state matrix and one wake trace; state exactly which modes were tested on hardware.

### Day 35 — Power and robustness checkpoint

- **Learn / retrieve:** Identify the measurement boundary: whole USB board, target supply, or MCU alone.
- **Read:** B18 review; UM, current-measurement arrangement; DS, current specifications and test conditions.
- **Build:** Compare active and Sleep using the available instrument; add Stop/Standby only if the setup supports them. Record supply voltage, debug attachment, LEDs, external sensor state, meter range and sampling limitations. Repair watchdog/wake issues in the remaining lab time.
- **Pass:** Repeated readings are internally consistent. Report low readings below resolution as such—not fabricated µA figures. Explain why a board measurement need not equal the datasheet's MCU figure.
- **Evidence / explain:** `docs/power.md` with actual values or explicit unmeasured entries, plus a recovery checklist. Energy per measurement is optional if current/time data are adequate.

## Week 8 — Turn the drivers into a defensible application

### Day 36 — Freeze the capstone's contracts

- **Learn / retrieve:** Explain the distinction between a deadline, a throughput requirement and a functional requirement.
- **Read:** B10/B17, buffering and transfer review; Y6, ownership/order review.
- **Build:** Write one-page requirements for the sensor hub using the proposed rates above. Specify data/block ownership, buffer capacities, timeouts, priorities of foreground work and fault behavior. Define compact driver APIs returning status and separating start/poll/completion where needed.
- **Pass:** Every requirement has a test method. The stream fits the calculated transport budget with margin. Draw module dependencies and identify which layer may call each other layer.
- **Evidence / explain:** `docs/requirements.md`, architecture sketch and acceptance checklist. Reject extra features that lack a clear place in the budget.

### Day 37 — Cooperative scheduler and sensor state machine

- **Learn / retrieve:** Explain why a superloop can be responsive only when each unit of work is bounded.
- **Read:** B8/B13, timing/sensor transaction review; B16, health review.
- **Build:** Integrate periodic sensor acquisition, DMA block processing, UART commands and health monitoring in a cooperative event loop. Keep sensor waits as state transitions. Separate monotonic scheduling from RTC presentation.
- **Pass:** Commands remain responsive while the sensor is missing or busy. Timestamp work duration and identify the longest foreground step. Sensor failure must not stop ADC streaming without an explicitly documented reason.
- **Evidence / explain:** Application state diagram, scheduling table and missing-sensor log.

### Day 38 — A protocol that survives corrupted input

- **Learn / retrieve:** Explain framing, endianness, sequence tracking and resynchronization.
- **Read:** B10, serial-transfer review; B17, transfer-buffer review. Reread your Day 36 protocol requirements.
- **Build:** Freeze a small binary format and an explicit CRC-16 variant with all parameters documented. Write encode/decode functions plus a host decoder. Bound length before accessing payload, reject bad CRC and recover framing after junk bytes.
- **Pass:** Feed truncated, corrupted, oversized and concatenated frames to host tests. Verify a documented CRC test vector, round trips, byte order and sequence-wrap handling. Hardware payload matches the decoded values.
- **Evidence / explain:** `docs/protocol.md`, test vectors and host capture utility. Do not serialize padding or native pointers.

### Day 39 — Integration failures and automated checks

- **Learn / retrieve:** Choose evidence that distinguishes a transport problem from sensor failure or scheduling overload.
- **Read:** Y12, diagnosis review; B13/B16/B17, relevant cleanup paths; Cppcheck documentation [S11].
- **Build:** Add a single local verification command for host tests and both firmware build modes; CI is optional if quickly available. Exercise unplugged sensor, corrupt command, queue/buffer saturation and stalled processing. Run configured static analysis; classify warnings and fix significant ones.
- **Pass:** Each injected failure produces the specified status/counter/recovery. Build and tests fail on a known planted defect, then pass after repair. Review error paths for unbounded waits and buffer reuse.
- **Evidence / explain:** Fault matrix and analysis report. Call this a documented coding policy, not certified MISRA compliance.

### Day 40 — Bare-metal release candidate

- **Learn / retrieve:** Trace one ADC sample through every buffer and execution context.
- **Read:** B1–B18 selective review of unresolved topics only; Y14, debug observation review.
- **Build:** Repair the weakest acceptance test. Consolidate pinout, clocks, build/flash steps, memory map, protocol, measurement method and known limitations. Run a 20-minute nominal test within the verification block.
- **Pass:** Fresh build and power-on run; functional sensor/ADC/telemetry/health paths; visible counters; host tests passing; no unexplained corruption or reset during the test. Mark any missing hardware evidence explicitly.
- **Evidence / explain:** Tag `v1.0-bare-metal-rc` only with a corresponding test report. A short demo is optional; correctness evidence comes first.

## Week 9 — Prove the foundation, then start FreeRTOS

### Day 41 — Timing and memory before introducing an RTOS

- **Learn / retrieve:** Explain why an RTOS cannot repair an over-budget hardware/data path by itself.
- **Read:** Y14, debug/trace topics; B17, processing/transfer review; Y6, memory-map review.
- **Build:** Profile the bare-metal hub under nominal load and UART command bursts. Record Flash/static RAM, maximum observed processing/ISR times and latency. Estimate stack needs using compiler stack-use output plus runtime evidence; note recursion and library-call limitations.
- **Pass:** Block handling remains inside its reuse deadline with stated observed margin. Identify how debug logging changes measurements. List every shared object and execution context touching it.
- **Evidence / explain:** `docs/baseline-metrics.md`; a concrete reason for each planned task boundary, rather than one task per peripheral by habit.

### Day 42 — Bare-metal competence gate and recovery session

- **Learn / retrieve:** Explain startup, one interrupt, one bus transaction and one DMA lifetime without opening example code.
- **Read:** B4/B14/B17 and Y12, targeted weak-topic review only.
- **Build:** Re-create one small peripheral initialization from the manual, diagnose one seeded fault and repair the weakest capstone prerequisite. Use a fresh build directory to confirm reproducibility. Freeze the bare-metal baseline.
- **Pass:** All critical gates: own startup/linker; bounded driver waits; correct interrupt acknowledgment; no known buffer race; host tests; on-board nominal stream; fault record; watchdog recovery. Unavailable optional measurements may be explicitly unverified, but critical failures remain failures.
- **Evidence / explain:** Tag `v1.0-bare-metal` with the pass/fail report. If a critical gate fails, keep Days 43–49 as isolated RTOS labs and use Days 50/55 repair time before migrating the hub; do not combine two unstable systems.

### Day 43 — The smallest correct FreeRTOS build

- **Learn / retrieve:** Explain what services the kernel adds and which hardware drivers remain yours.
- **Read:** F1–F2, overview/build topics; F4, task entry/creation; official Cortex-M guidance and port source [S6].
- **Build:** Branch from the known-good foundation. Pin a stable kernel release, add only required kernel sources and the official GCC Cortex-M4F port, and select a consistent FPU/ABI configuration across objects/libraries. Start two simple tasks with conservative stacks. Enable `configASSERT`; wire port exception handlers exactly once.
- **Pass:** Scheduler starts and both tasks run. Inspect SysTick, PendSV and SVC vector ownership. Remove the old application SysTick handler; do not run the old scheduler from a tick hook.
- **Evidence / explain:** `docs/rtos-config.md`, exact kernel tag/compiler flags and a two-task build. Explain when the FPU is enabled and why mismatched object ABIs are a build problem.

### Day 44 — Task states, priorities and periodic release

- **Learn / retrieve:** Draw Ready, Running, Blocked and Suspended with real transitions.
- **Read:** F4, priorities, blocking, tick time and periodic delay-until topics.
- **Build:** Compare relative delay with the periodic delay-until API provided by your pinned kernel. Make a high-priority task busy-loop in an isolated experiment, observe starvation, then make it block correctly. Keep ADC timing on its hardware trigger.
- **Pass:** Measure wake intervals and scheduling jitter under light load. Explain task priority ordering versus Cortex-M interrupt priority ordering. Demonstrate that a blocked task does not consume a full CPU timeslice waiting.
- **Evidence / explain:** State-transition and scheduling traces; selected tick rate and its resolution/overhead tradeoff.

### Day 45 — Allocation, stack budgets and early diagnostics

- **Learn / retrieve:** Distinguish task stack, kernel object storage, application pools and C library heap.
- **Read:** F3, static allocation and heap_4 comparison; F12–F13, assertions/hooks/stack diagnostics.
- **Build:** Move the simple tasks and core objects to static allocation where practical. Supply the required idle/timer task memory callbacks for the pinned configuration. Add stack monitoring and allocation checks; keep allocation at startup rather than continually creating/deleting objects.
- **Pass:** Verify configured stack units against `StackType_t` and convert reported high-water marks to bytes correctly. A deliberately failed object creation in a lab is caught. Explain that high-water marks show observed use, not a mathematical worst-case guarantee.
- **Evidence / explain:** Memory budget, checkable assertions and stack-sizing rationale. Preserve fault decoding assumptions established on Day 15.

## Week 10 — Communication and synchronization that remain correct

### Day 46 — Queues and ownership across task boundaries

- **Learn / retrieve:** Explain when queue copying is useful and why a queued pointer can outlive its storage.
- **Read:** F5, queue creation, blocking, copying and pointer-transfer topics.
- **Build:** Create a producer and telemetry consumer using small copied messages. Define finite send timeouts and a full-queue policy. For ADC blocks, plan a fixed pool with explicit acquire/publish/release ownership; do not queue stack-local addresses.
- **Pass:** Test empty/full queues and a slow consumer; check sequence and drop counters. Demonstrate buffer lifetime with a controlled bad example, then remove it from the production path.
- **Evidence / explain:** Queue/pool sizing table and ownership transitions; explain what happens when the producer permanently outruns the consumer.

### Day 47 — ISR-to-task handoff and interrupt-priority rules

- **Learn / retrieve:** Explain which interrupt priorities may call kernel APIs and why raw NVIC priority fields differ from unshifted library values.
- **Read:** F7 and F10, ISR APIs/notifications; official Cortex-M FreeRTOS guidance [S6].
- **Build:** Wake a processing task from DMA completion using an appropriate `...FromISR` notification and conditional yield. Explicitly configure every kernel-calling IRQ at a permitted priority. Use the implemented priority-bit count, correct grouping and reviewed threshold values; leave no such IRQ at its default highest urgency.
- **Pass:** `configASSERT` remains enabled, priority settings are independently reviewed, and DMA-to-task latency is measured. Show that coalesced notification bits are not a substitute for counting/owning multiple completed buffers.
- **Evidence / explain:** IRQ priority/API table, handoff trace and a documented distinction between event counts and data storage.

### Day 48 — Mutexes, priority inversion and resource owners

- **Learn / retrieve:** Choose between a mutex, binary semaphore, counting semaphore, queue and notification for five example needs.
- **Read:** F8, mutexes, inversion, inheritance and deadlock [S12].
- **Build:** In a small separate test, make low/medium/high-priority tasks reproduce inversion around a shared resource, then repeat using a mutex. For the hub, prefer one UART-owning task; if sharing another resource, document lock order and hold time.
- **Pass:** Capture scheduling evidence before/after inheritance. Explain why inheritance is not a cure for deadlock or unbounded blocking, and why a mutex is not an ISR signaling primitive.
- **Evidence / explain:** Demonstration trace and per-resource ownership policy. Keep the educational inversion test separate from release behavior.

### Day 49 — Software timers, event groups and application timing

- **Learn / retrieve:** Explain the execution context of a software timer callback.
- **Read:** F6, timer service/commands; F9, event bits and synchronization.
- **Build:** Add a software-timer heartbeat and a short callback that signals work. Build one event-group experiment for initialization/readiness flags. Use queues or notifications for recurring data/events where flags would lose information.
- **Pass:** Timer callbacks do not block or perform slow sensor transactions. Verify behavior when two readiness bits arrive in either order. Distinguish a software timer from the hardware timer that clocks the ADC.
- **Evidence / explain:** A primitive-selection note; remove demonstration-only synchronization objects if the capstone does not need them.

### Day 50 — RTOS migration checkpoint

- **Learn / retrieve:** Trace DMA completion through task wake, packet construction and UART completion.
- **Read:** F4/F5/F7/F10, only application-relevant review; B17, DMA ownership review.
- **Build:** Migrate the stable hub into a small task set: acquisition/processing, slow sensor, telemetry/commands and health as justified by your measurements. Reuse drivers behind RTOS adapters; keep hardware timing intact. If the Day 42 gate failed, first repair that failure and integrate only the validated subset.
- **Pass:** A ten-minute nominal stream matches the bare-metal protocol/rates. Missing sensor and slow telemetry paths stay bounded. No ISR/task double ownership of buffers or UART.
- **Evidence / explain:** Task table with trigger, priority, stack, owned resources and blocking points. Tag an integration checkpoint only for the tested scope.

## Week 11 — Understand and stress the kernel integration

### Day 51 — Read the context-switch mechanism

- **Learn / retrieve:** Explain PSP versus MSP, automatic exception stacking and software-saved registers.
- **Read:** Y10, SVC/PendSV/context switching; F2, port separation; selected official port routines [S6].
- **Build:** Follow first-task startup, PendSV and tick handling in the pinned port. Annotate a small source/disassembly path; inspect task stack pointers and saved context in GDB. Do not replace the working kernel port with a homemade scheduler.
- **Pass:** Explain where execution resumes after a switch and how an interrupt can unblock a task without running its entire body inside the ISR. Identify critical-section masking and context-save responsibilities.
- **Evidence / explain:** One-page context-switch walkthrough with the exact port revision and your debugger observations.

### Day 52 — Scheduling budget, backpressure and overload

- **Learn / retrieve:** Identify deadline, release rate, compute time and blocking time for each task.
- **Read:** F4/F5, scheduling and blocking review; F8, resource waiting; F12, runtime statistics.
- **Build:** Measure task execution and response under nominal load, UART command bursts and delayed telemetry. Size queues/pools from arrival and service behavior; add explicit overload counters and policy. Avoid calling a utilization sum a schedulability proof.
- **Pass:** Normal operation meets observed deadlines with documented margin. Intentional overload produces controlled drops/recovery rather than corruption, deadlock or uncontrolled heap growth. List load cases not tested.
- **Evidence / explain:** Timing/queue budget with observed maximum, target and margin. State the limits of your measurement method.

### Day 53 — Stack, FPU and library reentrancy

- **Learn / retrieve:** Explain why enabling floating-point work can change task/exception stack requirements.
- **Read:** Y13, FPU/context topics; F13, stacks/printf issues; F4, reentrancy topic.
- **Build:** Audit all task stacks and shared library calls under peak tested load. Prefer one logging owner and bounded formatting. If floating point is used, verify consistent ABI and extended-frame fault handling; otherwise keep compensation fixed-point and document the avoided cost. Exercise overflow detection in an isolated test build, not the release image.
- **Pass:** Stack margins are measured with diagnostic settings recorded; canaries/hooks or assertions catch the test fault. Explain that stack overflow detection may be late and cannot guarantee corruption prevention.
- **Evidence / explain:** Final memory/stack table and one controlled failure report; no unreviewed `printf` calls from ISRs.

### Day 54 — RTOS-aware idle and watchdog supervision

- **Learn / retrieve:** Explain why task health must reflect progress rather than merely a running timer.
- **Read:** F11, tickless/idle concepts; B16/B18, health/power review.
- **Build:** Centralize watchdog refresh after required task heartbeats advance within deadlines. Use the port's supported idle/tickless path in a separate low-activity profile if integration is ready; do not add an ad hoc deep-sleep call that loses kernel time. Suspend high-rate acquisition explicitly for the low-power experiment.
- **Pass:** A deliberately stalled required task causes recovery; a healthy blocked task does not cause false resets. Compare periodic timing before/after idle. Explain why continuous ADC/DMA activity limits available sleep depth.
- **Evidence / explain:** Health windows and tested idle configuration. A reasoned decision to retain ordinary idle is acceptable if deeper sleep is not verified.

### Day 55 — RTOS release-candidate gate

- **Learn / retrieve:** Choose the correct synchronization primitive and timeout for each capstone interaction.
- **Read:** F7/F8/F12/F13, targeted review of audit findings.
- **Build:** Audit IRQ priorities, handler ownership, task/ISR API use, queue bounds, lock order, stack margins and object creation. Repair the weakest integration issue. Build both bare-metal and RTOS images from a clean directory.
- **Pass:** Nominal acquisition and telemetry plus sensor-failure, overload and watchdog cases behave as specified. Critical assertions are enabled for diagnostic testing; every unresolved critical issue blocks a final release claim.
- **Evidence / explain:** `v2.0-freertos-rc` report comparing current results against Day 41, including overhead and benefits rather than assuming RTOS is faster.

## Week 12 — Independent problem solving and final evidence

### Day 56 — Implement a controlled change independently

- **Learn / retrieve:** Predict every dependency affected by changing a timing requirement.
- **Read:** B9/B11/B17, trigger and buffering topics; F4/F5, timing/capacity review.
- **Build:** Without copying a chapter solution, add selectable ADC rates of 500 and 1,000 samples/s, or an equivalently bounded timer/PWM change if acquisition is incomplete. Stop/reconfigure/restart at a safe boundary and recompute processing/transport budgets. Preserve the required final baseline.
- **Pass:** Both configurations behave as predicted; no stale block is mislabeled after switching. Invalid settings are rejected. Explain how the change would affect DMA deadlines and RTOS scheduling.
- **Evidence / explain:** Small reviewed diff, revised calculation and measurement. This is an independence test, not permission to expand the feature set.

### Day 57 — Hardware-in-the-loop regression

- **Learn / retrieve:** Explain why a host test suite cannot establish that the correct pin or DMA stream was selected.
- **Read:** F12/F13, diagnostics/troubleshooting review; B10/B17, transfer review.
- **Build:** Extend the host utility to run a repeatable serial regression: request status, decode frames, check sequences/CRC/rates and save a report. Add manual checkpoints for cold boot, button event, sensor disconnect and watchdog reset. Run debug and optimized builds.
- **Pass:** A planted protocol defect is detected. The actual firmware works after cold boot with the debugger detached. Results identify firmware revision, configuration, board and host command used.
- **Evidence / explain:** `tools/hil_check.py` or equivalent, concise manual checklist and reproducible report format.

### Day 58 — Supervised soak and fault campaign

- **Learn / retrieve:** Distinguish a nominal soak from intentional overload and recovery testing.
- **Read:** F13, failure diagnosis; B16/B17, reset/buffer review.
- **Build:** In the two-hour lab, run at least 30 minutes nominally, then perform separate bounded fault cases: missing sensor, malformed command, delayed consumer and stalled required task. Save raw reports; rerun a case after a fix only when the change warrants it.
- **Pass:** Nominal run: no unexplained reset, missing sequence or corrupted frame. Fault runs: predicted counters/status/recovery with no silent corruption. If a test fails, preserve the log and use the verification block to narrow the cause.
- **Evidence / explain:** Results table with duration, revision, conditions, expected/observed outcome and unresolved issue. Do not relabel a failed soak as passed because a later short run worked.

### Day 59 — Reproducibility and a technical handoff

- **Learn / retrieve:** Explain what another engineer would need to reproduce your results without asking you questions.
- **Read:** B3–B5, build/startup review; F2, pinned integration/configuration review.
- **Build:** Finalize README, pinout/wiring diagram, memory/clock/task tables, protocol, measurements, test commands and limitations. Check dependency licenses and pin versions. Record a short demo only after build/test instructions work. A clear wiring diagram is sufficient; a fabricated PCB or polished slide deck is not required.
- **Pass:** Follow your own instructions from a fresh directory, build both versions and run the regression. A reader can tell measured facts from estimates, and hardware-tested features from simulations.
- **Evidence / explain:** Complete repository handoff and release notes with the meaningful technical tradeoffs.

### Day 60 — Final practical review and release decision

- **Learn / retrieve:** Give a closed-notes explanation of reset, MMIO, interrupts, a bus transaction, DMA ownership and an RTOS context switch. Then use manuals normally for the practical task.
- **Read:** B/Y/F targeted review of only the weakest remaining concept; no new chapter obligation.
- **Build:** Spend the two-hour lab diagnosing two bounded seeded defects selected from wrong clock divisor, unacknowledged interrupt, early DMA-buffer reuse or invalid task/ISR interaction. Use the rest to fix a remaining release blocker; no new features.
- **Pass:** Clean build, host tests and hardware regression pass; Day 58 evidence is valid for the final changes. Explain one design decision you would make differently. If a material fix invalidates soak evidence, mark that gate pending rather than quietly assuming it still passes.
- **Evidence / explain:** Tag `v2.0-freertos` only if the gates pass. Otherwise tag a clearly labeled learning checkpoint with a short blocker list. Record the next focused learning goal and the evidence that justifies it.

## Milestones and completion rules

| End of day | Required capability | Evidence |
|---|---|---|
| 10 | Build and boot your own minimal firmware | Startup/linker, map, reset observation, GPIO explanation |
| 15 | Diagnose exceptions and reason about ISR concurrency | Fault record, latency evidence, race experiment |
| 25 | Use serial/analog peripherals and a real sensor | Analyzer traces, host tests, error paths, compensated reading |
| 30 | Stream timer-controlled data safely | DMA ownership, rate/bandwidth budget, overload test |
| 35 | Explain recovery and power behavior | Watchdog cause, mode matrix, honest measurement boundary |
| 42 | Freeze a dependable bare-metal baseline | Clean build and explicit competence-gate report |
| 50 | Integrate tasks without breaking drivers | Queue/notification/priority evidence and nominal stream |
| 55 | Defend RTOS timing and memory choices | Stack/IRQ/ownership audit and fault results |
| 60 | Independently diagnose and hand over the system | Reproducible release, measurements and known limitations |

For each gate, record **Pass**, **Fail** or **Unverified**, with a link to evidence. A peripheral that “worked once” is not the same as a driver with a defined contract and tested failure behavior.

## Suggested repository contents

| Path | Purpose |
|---|---|
| `README.md` | Exact target, prerequisites, build/flash/debug/test commands, quick demonstration |
| `startup/`, `linker/`, `board/` | Boot, memory layout and board-specific choices |
| `drivers/` | Small register-level drivers and their contracts |
| `app_baremetal/`, `app_freertos/` | Two applications sharing validated core modules |
| `protocol/` | Explicit serialization, CRC and host-testable parsing |
| `tests/` | Boundary, error, state-transition and ownership tests |
| `tools/` | Host capture/decoder/regression scripts |
| `docs/` | Daily journal, pinout, clocks, timing, memory, power, faults and test reports |
| `third_party/` or pinned dependency manifest | CMSIS, FreeRTOS, Unity and license/version records |

Commit when a meaningful unit of work or documented finding is ready. Git history should show thought and progress; an arbitrary commit quota is not a quality metric. Keep generated binaries and large captures out of routine source history unless deliberately archived with a release.

## Personal daily note template

```markdown
# Day NN — Topic
Date:
Focused time: /240 minutes
Reading completed (book, chapter/topic):
Prediction before coding:
What I changed:
Pass checks and evidence:
Failure observed / root cause / fix:
Can I explain this without the source open?
One question to retrieve next session:
Gate status: Pass / Fail / Unverified
Commit:
```

## What is deliberately outside the 60 sessions

Do not add a full USB CDC stack, TCP/IP, custom bootloader/OTA, production security design, PCB fabrication, TinyML or a Linux BSP during these sessions. Each is worthwhile but would displace the foundations you specifically want to strengthen. MPU protection, advanced DSP and deeper formal scheduling analysis are later topics, not implied competencies of this plan.

After Day 60, choose **one** next track based on demonstrated gaps or your intended work:

- **Firmware depth:** robust bootloader/update design, Flash persistence with power-failure handling, MPU and production diagnostics.
- **DSP:** sampling/aliasing, fixed-point arithmetic, FIR/FFT and CMSIS-DSP using captured ADC data.
- **Embedded Linux:** a Linux-capable board, cross-compilation, device tree and drivers; then Buildroot/Yocto. Use a suitable application-processor platform rather than expecting the F411 Nucleo to run a conventional Yocto Linux system.

These are future directions, not extra sessions hidden after Day 60.

## Source notes and links

The schedule, exercises, time budgets and project targets are original recommendations for your stated experience and available time. Sources below establish book mappings, hardware references and the technical distinctions used in the corrections. Public contents were checked; I did not inspect your personal copies of the full books. Save the versions you actually use on Day 1/Day 43.

- **S1 — Gbati publisher contents:** [Packt book listing](https://www.packtpub.com/en-nz/product/bare-metal-embedded-c-programming-9781835460818). Used to correct early chapter mappings and distinguish technical chapters from site navigation entries.
- **S2 — Official companion code and errata:** [PacktPublishing/Bare-Metal-Embedded-C-Programming](https://github.com/PacktPublishing/Bare-Metal-Embedded-C-Programming). Read its errata before reproducing an example; adapt to your actual board.
- **S3 — Yiu edition and chapter/section contents:** [Elsevier, third edition](https://shop.elsevier.com/books/the-definitive-guide-to-arm-cortex-m3-and-cortex-m4-processors/yiu/978-0-12-408082-9).
- **S4 — FreeRTOS reading map:** [Official kernel-book contents](https://github.com/FreeRTOS/FreeRTOS-Kernel-Book/blob/main/toc.md). This numbering differs from some older PDF editions; the online repository may evolve.
- **S5 — STM32F411 official documents:** [ST documentation hub](https://www.st.com/en/microcontrollers-microprocessors/stm32f411/documentation.html); [RM0383](https://www.st.com/resource/en/reference_manual/dm00119316.pdf). Obtain DS10314, PM0214 and ES0287 through the same hub. Use the exact device/revision information when applying limits or errata.
- **S6 — FreeRTOS Cortex-M rules and implementation:** [Official Cortex-M guidance](https://freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/ARM-Cortex/RTOS-Cortex-M3-M4); [GCC ARM_CM4F port](https://github.com/FreeRTOS/FreeRTOS-Kernel/blob/main/portable/GCC/ARM_CM4F/port.c). For actual work, inspect the port in your pinned release rather than silently tracking `main`.
- **S7 — CMSIS-Core device access:** [Arm device-header documentation](https://arm-software.github.io/CMSIS_6/main/Core/device_h_pg.html); [using CMSIS-Core](https://arm-software.github.io/CMSIS_6/v6.0.0/Core/using_pg.html). Use mutually compatible Core/device-header versions.
- **S8 — Sensor behavior and reference arithmetic:** [Bosch BME280 datasheet](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bme280-ds002.pdf); [Bosch reference driver](https://github.com/boschsensortec/BME280_SensorAPI). Check the breakout vendor's schematic in addition to the sensor datasheet.
- **S9 — Board connections and measurement setup:** [ST UM1724](https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf). Match the board revision; do not assume oscillator population, solder bridges or power routing from another Nucleo.
- **S10 — Host C testing:** [Unity getting-started guide](https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityGettingStartedGuide.md).
- **S11 — Static analysis configuration:** [Cppcheck manual](https://cppcheck.sourceforge.io/manual.pdf). Configure the actual target/build; distinguish general analysis, specific rule-checking support and a complete compliance process.
- **S12 — Resource ownership and inversion:** [Official FreeRTOS book, Chapter 8](https://github.com/FreeRTOS/FreeRTOS-Kernel-Book/blob/main/ch08.md).

**Success criterion:** By the end, you can derive a peripheral setup from documentation, explain the code's execution and ownership, measure its behavior, diagnose a deliberate failure, and justify how the RTOS version preserves those guarantees. That is a much stronger result than simply completing every example.
