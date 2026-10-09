ENTRY(Reset_Handler)

MEMORY
{
    RAM(rwx) : ORIGIN = 0x20000000, LENGTH = 64K
    FLASH(rx) : ORIGIN = 0X08000000, LENGTH = 256K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);
_max_heap_size = 0x200;
_max_stack_size = 0x400;

SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector)) /* Startup code */
        . = ALIGN(4);
    } >FLASH

    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.rodata)
        *(.heap)
        *(.stack)
        . = ALIGN(4);
        _etext = .;
    } >FLASH

    _sidata = LOADADDR(.data);

    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        . = ALIGN(4);
        _edata = .;
    } >RAM AT> FLASH

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        . = ALIGN(4);
        _ebss = .;
    } >RAM


}
