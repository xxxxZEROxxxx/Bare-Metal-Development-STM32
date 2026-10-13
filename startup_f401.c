#include <stdint.h>
typedef uint32_t u32;

extern u32 _estack; //addr of end of stack
extern u32 _etext;  //end of text in flash
extern u32 _fsdata; //start of data in flash
extern u32 _sdata;  //start of data in ram
extern u32 _edata;  //end of data in ram
extern u32 _sbss;   //start of bss in ram
extern u32 _ebss;   //end of bss in ram

int main(void);

void Default_Handler(void);

void Reset_Handler(void);

void NMI_Handler(void)__attribute__((weak,alias("Default_Handler")));

void HardFault_Handler(void)__attribute__((weak,alias("Default_Handler")));

void MemManage_Handler(void)__attribute__((weak,alias("Default_Handler")));

void BusFault_Handler(void)__attribute__((weak,alias("Default_Handler")));

void UsageFault_Handler(void)__attribute__((weak,alias("Default_Handler")));

void SVC_Handler(void)__attribute__((weak,alias("Default_Handler")));

void DebugMon_Handler(void)__attribute__((weak,alias("Default_Handler")));

void PendSV_Handler(void)__attribute__((weak,alias("Default_Handler")));

void SysTick_Handler(void)__attribute__((weak,alias("Default_Handler")));


const u32 vct[]__attribute__((section(".vector"))) = {
    (u32)&_estack,
    (u32)&Reset_Handler,
    (u32)&NMI_Handler,
    (u32)&HardFault_Handler,
    (u32)&MemManage_Handler,
    (u32)&BusFault_Handler,
    (u32)&UsageFault_Handler,
    0,
    0,
    0,
    0,
    (u32)&SVC_Handler,
    (u32)&DebugMon_Handler,
    0,
    (u32)&PendSV_Handler,
    (u32)&SysTick_Handler
};

void Default_Handler(void){while (1){}};

void Reset_Handler(void) {
    u32 * fsdata = &_fsdata; //start of data in flash
    u32 * rsdata = &_sdata;  //start of data in ram
    while (rsdata < &_edata ) {
        *(rsdata++) = *(fsdata++);
    }

    u32 * ram_bss_start = &_sbss;
    u32 * ram_bss_end = &_ebss;

    while ((int)ram_bss_start < (int)ram_bss_end ) {
        *(ram_bss_start++) = 0x00;
    }

    main();
}



