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

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#define WEAK_DEFAULT_HANDLER(name) void name(void)__attribute__((weak,alias("Default_Handler")))

WEAK_DEFAULT_HANDLER(WWDG_IRQHandler);
WEAK_DEFAULT_HANDLER(PVD_IRQHandler);
WEAK_DEFAULT_HANDLER(TAMP_STAMP_IRQHandler);
WEAK_DEFAULT_HANDLER(RTC_WKUP_IRQHandler);
WEAK_DEFAULT_HANDLER(FLASH_IRQHandler);
WEAK_DEFAULT_HANDLER(RCC_IRQHandler);
WEAK_DEFAULT_HANDLER(EXTI0_IRQHandler);
WEAK_DEFAULT_HANDLER(EXTI1_IRQHandler);
WEAK_DEFAULT_HANDLER(EXTI2_IRQHandler);
WEAK_DEFAULT_HANDLER(EXTI3_IRQHandler);
WEAK_DEFAULT_HANDLER(EXTI4_IRQHandler);
WEAK_DEFAULT_HANDLER(DMA1_Stream0_IRQHandler);
WEAK_DEFAULT_HANDLER(DMA1_Stream1_IRQHandler);
WEAK_DEFAULT_HANDLER(DMA1_Stream2_IRQHandler);
WEAK_DEFAULT_HANDLER(DMA1_Stream3_IRQHandler);
WEAK_DEFAULT_HANDLER(DMA1_Stream4_IRQHandler);
WEAK_DEFAULT_HANDLER(DMA1_Stream5_IRQHandler);
WEAK_DEFAULT_HANDLER(DMA1_Stream6_IRQHandler);
WEAK_DEFAULT_HANDLER(ADC_IRQHandler);
WEAK_DEFAULT_HANDLER(EXTI9_5_IRQHandler);
WEAK_DEFAULT_HANDLER(TIM1_BRK_TIM9_IRQHandler);
WEAK_DEFAULT_HANDLER(TIM1_UP_TIM10_IRQHandler);
WEAK_DEFAULT_HANDLER(TIM1_TRG_COM_TIM11_IRQHandler);
WEAK_DEFAULT_HANDLER(TIM1_CC_IRQHandler);
WEAK_DEFAULT_HANDLER(TIM2_IRQHandler);
WEAK_DEFAULT_HANDLER(TIM3_IRQHandler);
WEAK_DEFAULT_HANDLER(TIM4_IRQHandler);
WEAK_DEFAULT_HANDLER(I2C1_EV_IRQHandler);
WEAK_DEFAULT_HANDLER(I2C1_ER_IRQHandler);
WEAK_DEFAULT_HANDLER(I2C2_EV_IRQHandler);
WEAK_DEFAULT_HANDLER(I2C2_ER_IRQHandler);
WEAK_DEFAULT_HANDLER(SPI1_IRQHandler);
WEAK_DEFAULT_HANDLER(SPI2_IRQHandler);
WEAK_DEFAULT_HANDLER(USART1_IRQHandler);
WEAK_DEFAULT_HANDLER(USART2_IRQHandler);
WEAK_DEFAULT_HANDLER(EXTI15_10_IRQHandler);
WEAK_DEFAULT_HANDLER(RTC_Alarm_IRQHandler);
WEAK_DEFAULT_HANDLER(OTG_FS_WKUP_IRQHandler);
WEAK_DEFAULT_HANDLER(DMA1_Stream7_IRQHandler);
WEAK_DEFAULT_HANDLER(SDIO_IRQHandler);
WEAK_DEFAULT_HANDLER(TIM5_IRQHandler);
WEAK_DEFAULT_HANDLER(SPI3_IRQHandler);
WEAK_DEFAULT_HANDLER(DMA2_Stream0_IRQHandler);
WEAK_DEFAULT_HANDLER(DMA2_Stream1_IRQHandler);
WEAK_DEFAULT_HANDLER(DMA2_Stream2_IRQHandler);
WEAK_DEFAULT_HANDLER(DMA2_Stream3_IRQHandler);
WEAK_DEFAULT_HANDLER(DMA2_Stream4_IRQHandler);
WEAK_DEFAULT_HANDLER(OTG_FS_IRQHandler);
WEAK_DEFAULT_HANDLER(DMA2_Stream5_IRQHandler);
WEAK_DEFAULT_HANDLER(DMA2_Stream6_IRQHandler);
WEAK_DEFAULT_HANDLER(DMA2_Stream7_IRQHandler);
WEAK_DEFAULT_HANDLER(USART6_IRQHandler);
WEAK_DEFAULT_HANDLER(I2C3_EV_IRQHandler);
WEAK_DEFAULT_HANDLER(I2C3_ER_IRQHandler);
WEAK_DEFAULT_HANDLER(FPU_IRQHandler);
WEAK_DEFAULT_HANDLER(SPI4_IRQHandler);


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
    (u32)&SysTick_Handler,

    /* External interrupts */
    (u32)&WWDG_IRQHandler,
    (u32)&PVD_IRQHandler,
    (u32)&TAMP_STAMP_IRQHandler,
    (u32)&RTC_WKUP_IRQHandler,
    (u32)&FLASH_IRQHandler,
    (u32)&RCC_IRQHandler,
    (u32)&EXTI0_IRQHandler,
    (u32)&EXTI1_IRQHandler,
    (u32)&EXTI2_IRQHandler,
    (u32)&EXTI3_IRQHandler,
    (u32)&EXTI4_IRQHandler,
    (u32)&DMA1_Stream0_IRQHandler,
    (u32)&DMA1_Stream1_IRQHandler,
    (u32)&DMA1_Stream2_IRQHandler,
    (u32)&DMA1_Stream3_IRQHandler,
    (u32)&DMA1_Stream4_IRQHandler,
    (u32)&DMA1_Stream5_IRQHandler,
    (u32)&DMA1_Stream6_IRQHandler,
    (u32)&ADC_IRQHandler,
    0,
    0,
    0,
    0,
    (u32)&EXTI9_5_IRQHandler,
    (u32)&TIM1_BRK_TIM9_IRQHandler,
    (u32)&TIM1_UP_TIM10_IRQHandler,
    (u32)&TIM1_TRG_COM_TIM11_IRQHandler,
    (u32)&TIM1_CC_IRQHandler,
    (u32)&TIM2_IRQHandler,
    (u32)&TIM3_IRQHandler,
    (u32)&TIM4_IRQHandler,
    (u32)&I2C1_EV_IRQHandler,
    (u32)&I2C1_ER_IRQHandler,
    (u32)&I2C2_EV_IRQHandler,
    (u32)&I2C2_ER_IRQHandler,
    (u32)&SPI1_IRQHandler,
    (u32)&SPI2_IRQHandler,
    (u32)&USART1_IRQHandler,
    (u32)&USART2_IRQHandler,
    0,
    (u32)&EXTI15_10_IRQHandler,
    (u32)&RTC_Alarm_IRQHandler,
    (u32)&OTG_FS_WKUP_IRQHandler,
    0,
    0,
    0,
    0,
    (u32)&DMA1_Stream7_IRQHandler,
    0,
    (u32)&SDIO_IRQHandler,
    (u32)&TIM5_IRQHandler,
    (u32)&SPI3_IRQHandler,
    0,
    0,
    0,
    0,
    (u32)&DMA2_Stream0_IRQHandler,
    (u32)&DMA2_Stream1_IRQHandler,
    (u32)&DMA2_Stream2_IRQHandler,
    (u32)&DMA2_Stream3_IRQHandler,
    (u32)&DMA2_Stream4_IRQHandler,
    0,
    0,
    0,
    0,
    0,
    0,
    (u32)&OTG_FS_IRQHandler,
    (u32)&DMA2_Stream5_IRQHandler,
    (u32)&DMA2_Stream6_IRQHandler,
    (u32)&DMA2_Stream7_IRQHandler,
    (u32)&USART6_IRQHandler,
    (u32)&I2C3_EV_IRQHandler,
    (u32)&I2C3_ER_IRQHandler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    (u32)&FPU_IRQHandler,
    0,
    0,
    (u32)&SPI4_IRQHandler
};

void NMI_Handler(void) { while(1); }
void HardFault_Handler(void) { while(1); }
void MemManage_Handler(void) { while(1); }
void BusFault_Handler(void) { while(1); }
void UsageFault_Handler(void) { while(1); }
void SVC_Handler(void) { while(1); }
void DebugMon_Handler(void) { while(1); }
void PendSV_Handler(void) { while(1); }
void SysTick_Handler(void) { while(1); }

void Default_Handler(void) { while(1); }

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


