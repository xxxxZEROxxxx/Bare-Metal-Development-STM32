#include <stdint.h>
typedef uint32_t u32;

extern u32 _estack;
extern u32 _sidata;
extern u32 _sdata;
extern u32 _edata;
extern u32 _sbss;
extern u32 _ebss;

int main(void);
void Reset_Handler(void);
void default_Handler(void);
void NMI_Handler(void)__attribute__((weak, alias("default_Handler")));
void HardFault_Handler(void)__attribute__((weak, alias("default_Handler")));
void SVC_Handler(void)__attribute__((weak, alias("default_Handler")));
void PendSV_Handler(void)__attribute__((weak, alias("default_Handler")));
void SysTick_Handler(void)__attribute__((weak, alias("default_Handler")));
void MemManage_Handler(void)__attribute__((weak, alias("default_Handler")));
void BusFault_Handler(void)__attribute__((weak, alias("default_Handler")));
void UsageFault_Handler(void)__attribute__((weak, alias("default_Handler")));
void DebugMon_Handler(void)__attribute__((weak, alias("default_Handler")));


const u32 vector_table[]__attribute__((section(".isr_vector"))) = {
    (u32)&_estack,
    (u32)&Reset_Handler,
    (u32)&NMI_Handler,
    (u32)&HardFault_Handler,
    (u32)&MemManage_Handler,
    (u32)&BusFault_Handler,
    (u32)&UsageFault_Handler,
    (u32)0x00,
    (u32)0x00,
    (u32)0x00,
    (u32)0x00,
    (u32)&SVC_Handler,
    (u32)&DebugMon_Handler,
    (u32)0x00,
    (u32)&PendSV_Handler,
    (u32)&SysTick_Handler
};


void default_Handler(void) {while(1){}}

void Reset_Handler(void){
    u32 len = ((u32)&_edata - (u32)&_sdata) / sizeof(u32);
    u32 * flash = (u32 *)&_sidata;
    u32 * ram = (u32 *)&_sdata;

    for(u32 i=0;i<len;i++) {
        *(ram++) = *(flash++);
    }

    u32 bss_size = ((u32)&_ebss - (u32)&_sbss) / sizeof(u32);
    u32 * bss_v = (u32 *)&_sbss;
    for (u32 i=0;i<bss_size;i++) {
        *(bss_v++) = 0;
    }

    main();
}
