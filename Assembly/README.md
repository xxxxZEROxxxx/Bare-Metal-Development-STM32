# ARM Assembly Notes for STM32 Bare Metal

This project uses the GNU Arm Embedded toolchain, usually called
`arm-none-eabi-gcc`. That means the assembly files should use **GNU assembler
syntax**, also called **GAS syntax**.

ARM assembly examples in books often use ARMASM or Keil syntax. The CPU
instructions are mostly the same, but the assembler directives are different.
Directives are commands for the assembler itself, such as "put this data here",
"export this label", or "align the next value".

## Structure

An assembly file usually contains:

1. **Labels**: names for addresses.
2. **Instructions**: operations executed by the CPU.
3. **Directives**: instructions for the assembler, not for the CPU.
4. **Data**: literal bytes, words, strings, or constants.

Basic GNU assembly shape:

```asm
label:
    instruction operand1, operand2    /* comment */
```

Example:

```asm
Reset_Handler:
    ldr r0, =0x20000000
    movs r1, #0
    str r1, [r0]
```

Meaning:

- `Reset_Handler:` is a label. Its the pointer point to the start of the instruction set which is `ldr r0, =0x20000000`.
- `ldr`, `movs`, and `str` are CPU instructions.
- `r0` and `r1` are CPU registers.
- `#0` means the immediate value `0`.
- `[r0]` means the memory located at the address stored inside `r0`.

## File Extension

Common assembly file extensions:

| Extension | Meaning |
| --- | --- |
| `.s` | Assembly source. Usually passed directly to the assembler. |
| `.S` | Assembly source preprocessed by the C preprocessor first. Useful if you want `#define`, `#include`, or conditional compilation. |

For simple assembly notes, `.s` is enough. For startup files that use C-style
macros, `.S` is often more convenient.

## Comments

GNU assembler accepts these comment styles on ARM:

```asm
// C++ style comment
/* C style block comment */
```

Many ARMASM examples use `;` for comments. Do not copy that style blindly into
GNU assembly.

## Common GNU Directives

Directives start with a dot:

```asm
.section  .text
.global   Reset_Handler
.word     0x12345678
```

These are not CPU instructions. They tell the assembler how to arrange the
program.

| Directive | Meaning                                                          |
| --- |------------------------------------------------------------------|
| `.section name` | Put the following code or data into a named section.             |
| `.global name` | Make a label visible to the linker.                              |
| `.type name, %function` | Mark a label as a function symbol.                               |
| `.equ NAME, value` | Define a constant.                                               |
| `.align n` | Align the next item. See the [alignment](#Alignment) note below. |
| `.byte value` | Insert 1 byte.                                                   |
| `.hword value` / `.2byte value` | Insert 2 bytes.                                                  |
| `.word value` / `.4byte value` | Insert 4 bytes.                                                  |
| `.quad value` | Insert 8 bytes.                                                  |
| `.ascii "text"` | Insert text without a null terminator.                           |
| `.asciz "text"` | Insert text with a null terminator.                              |

## Labels

A label is a name for an address:

```asm
MY_NUMBER:
    .word 0x12345678

Reset_Handler:
    bl main
```

`MY_NUMBER` is the address where the word `0x12345678` is stored.
`Reset_Handler` is the address of the first instruction in that handler.

Important: a label is an address, not automatically the value stored at that
address.

## Constants with `.equ`

In ARMASM or Keil syntax, constants are often written with `EQU`:

```asm
NVIC_IRQ_SETEN  EQU 0xE000E100
NVIC_IRQ0_ENABLE EQU 0x1
```

In GNU assembly, use `.equ`:

```asm
.equ NVIC_IRQ_SETEN,  0xE000E100
.equ NVIC_IRQ0_ENABLE, 0x1
```

Then you can use those names in instructions:

```asm
    ldr  r0, =NVIC_IRQ_SETEN
    movs r1, #NVIC_IRQ0_ENABLE
    str  r1, [r0]
```

Step by step:

1. `ldr r0, =NVIC_IRQ_SETEN`
   loads the address value `0xE000E100` into `r0`.
2. `movs r1, #NVIC_IRQ0_ENABLE`
   loads the immediate value `1` into `r1`.
3. `str r1, [r0]`
   stores `1` into memory address `0xE000E100`.

This is how register programming works on Cortex-M: hardware registers are
controlled by normal memory reads and writes.

## `#value` vs `[register]`

This is one of the most important ideas.

| Syntax | Meaning | Example |
| --- | --- | --- |
| `#5` | The literal number 5. | `movs r0, #5` puts `5` in `r0`. |
| `r0` | The value currently inside register `r0`. | `mov r1, r0` copies `r0` into `r1`. |
| `[r0]` | Memory at the address stored in `r0`. | `ldr r1, [r0]` reads memory pointed to by `r0`. |
| `=symbol` | GNU `ldr` pseudo-instruction syntax for loading a constant or address. | `ldr r0, =GPIOA_BASE` loads the value/address into `r0`. |

Example:

```asm
.equ GPIOA_ODR, 0x40020014

    ldr r0, =GPIOA_ODR   /* r0 = 0x40020014 */
    ldr r1, [r0]         /* r1 = memory value at 0x40020014 */
    orr r1, r1, #(1 << 5)
    str r1, [r0]         /* write updated value back */
```

Think of it like C:

```c
uint32_t *r0 = (uint32_t *)0x40020014;
uint32_t r1 = *r0;
r1 = r1 | (1 << 5);
*r0 = r1;
```

## `ldr r0, =something` Is a Pseudo-Instruction

This form:

```asm
ldr r0, =0xE000E100
```

does not always become one real `ldr` instruction. It is a GNU assembler
shortcut.

The assembler chooses a valid way to load the value. It may:

- replace it with a simple immediate instruction, if possible;
- place the value in a nearby literal pool and load it using a PC-relative load.

For learning, read `ldr r0, =X` as:

> Put the value/address `X` into `r0`.

## Alignment

CPUs are usually happiest when 32-bit words are stored at addresses divisible by
4. This is called **word alignment**.

Use alignment before inserting word-sized data:

```asm
    .align 2
MY_NUMBER:
    .word 0x12345678
```

Important GNU assembler detail for ARM:

- `.align 2` means align to `2^2` bytes, which is 4 bytes.
- `.align 4` means align to `2^4` bytes, which is 16 bytes.

Some books say `.align 4` when they mean "align to 4 bytes". That is often
ARMASM syntax, not GNU syntax. In GNU ARM assembly, use `.align 2` for a normal
4-byte word boundary.

You can also use `.balign 4`, which directly means "align to 4 bytes":

```asm
    .balign 4
MY_NUMBER:
    .word 0x12345678
```

For clarity, `.balign 4` is often easier to read.

## Data in Assembly

Example:

```asm
    ldr r3, =MY_NUMBER
    ldr r4, [r3]          /* r4 = 0x12345678 */

    ldr r0, =HELLO_TEXT   /* r0 = address of string */
    bl  PrintText

    .balign 4
MY_NUMBER:
    .word 0x12345678

HELLO_TEXT:
    .asciz "Hello\n"
```

Key point:

- `ldr r3, =MY_NUMBER` loads the address of `MY_NUMBER`.
- `ldr r4, [r3]` loads the value stored at that address.

That is the same idea as:

```c
uint32_t *r3 = &MY_NUMBER;
uint32_t r4 = *r3;
```

## ARMASM vs GNU Data Directives

| Data type | ARMASM / Keil | GNU assembler | Example in GNU syntax |
| --- | --- | --- | --- |
| Byte, 8-bit | `DCB` | `.byte` | `.byte 0x12` |
| Half-word, 16-bit | `DCW` | `.hword` or `.2byte` | `.hword 0x1234` |
| Word, 32-bit | `DCD` | `.word` or `.4byte` | `.word 0x12345678` |
| Double-word, 64-bit | `DCQ` | `.quad` or `.8byte` | `.quad 0x12345678FF0055AA` |
| Single-precision float | `DCFS` | `.float` | `.float 1.0e3` |
| Double-precision float | `DCFD` | `.double` | `.double 3.14159` |
| String without null terminator | `DCB` | `.ascii` | `.ascii "Hello\n"` |
| String with null terminator | `DCB ..., 0` | `.asciz` | `.asciz "Hello\n"` |
| Raw instruction/data half-word | `DCI` | `.hword` | `.hword 0xBE00` |

`0xBE00` is the machine-code encoding for `BKPT #0` on Thumb. Normally you
should write the instruction itself:

```asm
    bkpt #0
```

Use raw instruction words only when you deliberately need exact machine bytes.

## Minimal GNU Assembly Function

This is the kind of style that fits this project:

```asm
.syntax unified
.cpu cortex-m4
.thumb

.section .text
.global add_one
.type add_one, %function

add_one:
    adds r0, r0, #1
    bx lr
```

Called from C:

```c
extern int add_one(int value);

int x = add_one(41); /* x becomes 42 */
```

Calling convention basics:

- Function argument 1 is passed in `r0`.
- Return value is placed in `r0`.
- `lr` contains the return address.
- `bx lr` returns to the caller.

## Mental Model

When reading assembly, ask these questions in order:

1. Is this line a label, an instruction, or a directive?
2. If it is an instruction, which registers does it read?
3. Which register or memory address does it write?
4. Does `#` mean an immediate number?
5. Does `[rX]` mean memory access through a pointer?
6. Does `=symbol` mean the assembler is helping load an address or constant?

Once those are clear, assembly becomes much less mysterious: it is mostly moving
numbers between registers and memory.
