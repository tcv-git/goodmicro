@; vectors_stm32h523xx.s
@; automaically generated interrupt vector

.syntax  unified

.section .text.Default_Handler, "ax", %progbits
.global  Default_Handler
.type    Default_Handler, %function
.align   2
.thumb_func

Default_Handler:
b .

.size Default_Handler, . - Default_Handler


.section .isr_vector, "a", %progbits
.global  g_pfnVectors
.type    g_pfnVectors, %object
.size    g_pfnVectors, 596
.align   10

g_pfnVectors:
.word _estack
.word Reset_Handler
.word NMI_Handler
.word HardFault_Handler
.word MemManage_Handler
.word BusFault_Handler
.word UsageFault_Handler
.word SecureFault_Handler
.word 0
.word 0
.word 0
.word SVC_Handler
.word DebugMon_Handler
.word 0
.word PendSV_Handler
.word SysTick_Handler
.word WWDG_IRQHandler
.word PVD_AVD_IRQHandler
.word RTC_IRQHandler
.word RTC_S_IRQHandler
.word TAMP_IRQHandler
.word RAMCFG_IRQHandler
.word FLASH_IRQHandler
.word FLASH_S_IRQHandler
.word GTZC_IRQHandler
.word RCC_IRQHandler
.word RCC_S_IRQHandler
.word EXTI0_IRQHandler
.word EXTI1_IRQHandler
.word EXTI2_IRQHandler
.word EXTI3_IRQHandler
.word EXTI4_IRQHandler
.word EXTI5_IRQHandler
.word EXTI6_IRQHandler
.word EXTI7_IRQHandler
.word EXTI8_IRQHandler
.word EXTI9_IRQHandler
.word EXTI10_IRQHandler
.word EXTI11_IRQHandler
.word EXTI12_IRQHandler
.word EXTI13_IRQHandler
.word EXTI14_IRQHandler
.word EXTI15_IRQHandler
.word GPDMA1_Channel0_IRQHandler
.word GPDMA1_Channel1_IRQHandler
.word GPDMA1_Channel2_IRQHandler
.word GPDMA1_Channel3_IRQHandler
.word GPDMA1_Channel4_IRQHandler
.word GPDMA1_Channel5_IRQHandler
.word GPDMA1_Channel6_IRQHandler
.word GPDMA1_Channel7_IRQHandler
.word IWDG_IRQHandler
.word 0
.word ADC1_IRQHandler
.word DAC1_IRQHandler
.word FDCAN1_IT0_IRQHandler
.word FDCAN1_IT1_IRQHandler
.word TIM1_BRK_IRQHandler
.word TIM1_UP_IRQHandler
.word TIM1_TRG_COM_IRQHandler
.word TIM1_CC_IRQHandler
.word TIM2_IRQHandler
.word TIM3_IRQHandler
.word TIM4_IRQHandler
.word TIM5_IRQHandler
.word TIM6_IRQHandler
.word TIM7_IRQHandler
.word I2C1_EV_IRQHandler
.word I2C1_ER_IRQHandler
.word I2C2_EV_IRQHandler
.word I2C2_ER_IRQHandler
.word SPI1_IRQHandler
.word SPI2_IRQHandler
.word SPI3_IRQHandler
.word USART1_IRQHandler
.word USART2_IRQHandler
.word USART3_IRQHandler
.word UART4_IRQHandler
.word UART5_IRQHandler
.word LPUART1_IRQHandler
.word LPTIM1_IRQHandler
.word TIM8_BRK_IRQHandler
.word TIM8_UP_IRQHandler
.word TIM8_TRG_COM_IRQHandler
.word TIM8_CC_IRQHandler
.word ADC2_IRQHandler
.word LPTIM2_IRQHandler
.word TIM15_IRQHandler
.word 0
.word 0
.word USB_DRD_FS_IRQHandler
.word CRS_IRQHandler
.word UCPD1_IRQHandler
.word FMC_IRQHandler
.word OCTOSPI1_IRQHandler
.word SDMMC1_IRQHandler
.word I2C3_EV_IRQHandler
.word I2C3_ER_IRQHandler
.word SPI4_IRQHandler
.word 0
.word 0
.word USART6_IRQHandler
.word 0
.word 0
.word 0
.word 0
.word GPDMA2_Channel0_IRQHandler
.word GPDMA2_Channel1_IRQHandler
.word GPDMA2_Channel2_IRQHandler
.word GPDMA2_Channel3_IRQHandler
.word GPDMA2_Channel4_IRQHandler
.word GPDMA2_Channel5_IRQHandler
.word GPDMA2_Channel6_IRQHandler
.word GPDMA2_Channel7_IRQHandler
.word 0
.word 0
.word 0
.word 0
.word 0
.word FPU_IRQHandler
.word ICACHE_IRQHandler
.word DCACHE1_IRQHandler
.word 0
.word 0
.word DCMI_PSSI_IRQHandler
.word FDCAN2_IT0_IRQHandler
.word FDCAN2_IT1_IRQHandler
.word 0
.word 0
.word DTS_IRQHandler
.word RNG_IRQHandler
.word 0
.word 0
.word HASH_IRQHandler
.word 0
.word CEC_IRQHandler
.word TIM12_IRQHandler
.word 0
.word 0
.word I3C1_EV_IRQHandler
.word I3C1_ER_IRQHandler
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word I3C2_EV_IRQHandler
.word I3C2_ER_IRQHandler

.weak Reset_Handler
.weak NMI_Handler
.weak HardFault_Handler
.weak MemManage_Handler
.weak BusFault_Handler
.weak UsageFault_Handler
.weak SecureFault_Handler
.weak SVC_Handler
.weak DebugMon_Handler
.weak PendSV_Handler
.weak SysTick_Handler
.weak WWDG_IRQHandler
.weak PVD_AVD_IRQHandler
.weak RTC_IRQHandler
.weak RTC_S_IRQHandler
.weak TAMP_IRQHandler
.weak RAMCFG_IRQHandler
.weak FLASH_IRQHandler
.weak FLASH_S_IRQHandler
.weak GTZC_IRQHandler
.weak RCC_IRQHandler
.weak RCC_S_IRQHandler
.weak EXTI0_IRQHandler
.weak EXTI1_IRQHandler
.weak EXTI2_IRQHandler
.weak EXTI3_IRQHandler
.weak EXTI4_IRQHandler
.weak EXTI5_IRQHandler
.weak EXTI6_IRQHandler
.weak EXTI7_IRQHandler
.weak EXTI8_IRQHandler
.weak EXTI9_IRQHandler
.weak EXTI10_IRQHandler
.weak EXTI11_IRQHandler
.weak EXTI12_IRQHandler
.weak EXTI13_IRQHandler
.weak EXTI14_IRQHandler
.weak EXTI15_IRQHandler
.weak GPDMA1_Channel0_IRQHandler
.weak GPDMA1_Channel1_IRQHandler
.weak GPDMA1_Channel2_IRQHandler
.weak GPDMA1_Channel3_IRQHandler
.weak GPDMA1_Channel4_IRQHandler
.weak GPDMA1_Channel5_IRQHandler
.weak GPDMA1_Channel6_IRQHandler
.weak GPDMA1_Channel7_IRQHandler
.weak IWDG_IRQHandler
.weak ADC1_IRQHandler
.weak DAC1_IRQHandler
.weak FDCAN1_IT0_IRQHandler
.weak FDCAN1_IT1_IRQHandler
.weak TIM1_BRK_IRQHandler
.weak TIM1_UP_IRQHandler
.weak TIM1_TRG_COM_IRQHandler
.weak TIM1_CC_IRQHandler
.weak TIM2_IRQHandler
.weak TIM3_IRQHandler
.weak TIM4_IRQHandler
.weak TIM5_IRQHandler
.weak TIM6_IRQHandler
.weak TIM7_IRQHandler
.weak I2C1_EV_IRQHandler
.weak I2C1_ER_IRQHandler
.weak I2C2_EV_IRQHandler
.weak I2C2_ER_IRQHandler
.weak SPI1_IRQHandler
.weak SPI2_IRQHandler
.weak SPI3_IRQHandler
.weak USART1_IRQHandler
.weak USART2_IRQHandler
.weak USART3_IRQHandler
.weak UART4_IRQHandler
.weak UART5_IRQHandler
.weak LPUART1_IRQHandler
.weak LPTIM1_IRQHandler
.weak TIM8_BRK_IRQHandler
.weak TIM8_UP_IRQHandler
.weak TIM8_TRG_COM_IRQHandler
.weak TIM8_CC_IRQHandler
.weak ADC2_IRQHandler
.weak LPTIM2_IRQHandler
.weak TIM15_IRQHandler
.weak USB_DRD_FS_IRQHandler
.weak CRS_IRQHandler
.weak UCPD1_IRQHandler
.weak FMC_IRQHandler
.weak OCTOSPI1_IRQHandler
.weak SDMMC1_IRQHandler
.weak I2C3_EV_IRQHandler
.weak I2C3_ER_IRQHandler
.weak SPI4_IRQHandler
.weak USART6_IRQHandler
.weak GPDMA2_Channel0_IRQHandler
.weak GPDMA2_Channel1_IRQHandler
.weak GPDMA2_Channel2_IRQHandler
.weak GPDMA2_Channel3_IRQHandler
.weak GPDMA2_Channel4_IRQHandler
.weak GPDMA2_Channel5_IRQHandler
.weak GPDMA2_Channel6_IRQHandler
.weak GPDMA2_Channel7_IRQHandler
.weak FPU_IRQHandler
.weak ICACHE_IRQHandler
.weak DCACHE1_IRQHandler
.weak DCMI_PSSI_IRQHandler
.weak FDCAN2_IT0_IRQHandler
.weak FDCAN2_IT1_IRQHandler
.weak DTS_IRQHandler
.weak RNG_IRQHandler
.weak HASH_IRQHandler
.weak CEC_IRQHandler
.weak TIM12_IRQHandler
.weak I3C1_EV_IRQHandler
.weak I3C1_ER_IRQHandler
.weak I3C2_EV_IRQHandler
.weak I3C2_ER_IRQHandler

.thumb_set Reset_Handler, Default_Handler
.thumb_set NMI_Handler, Default_Handler
.thumb_set HardFault_Handler, Default_Handler
.thumb_set MemManage_Handler, Default_Handler
.thumb_set BusFault_Handler, Default_Handler
.thumb_set UsageFault_Handler, Default_Handler
.thumb_set SecureFault_Handler, Default_Handler
.thumb_set SVC_Handler, Default_Handler
.thumb_set DebugMon_Handler, Default_Handler
.thumb_set PendSV_Handler, Default_Handler
.thumb_set SysTick_Handler, Default_Handler
.thumb_set WWDG_IRQHandler, Default_Handler
.thumb_set PVD_AVD_IRQHandler, Default_Handler
.thumb_set RTC_IRQHandler, Default_Handler
.thumb_set RTC_S_IRQHandler, Default_Handler
.thumb_set TAMP_IRQHandler, Default_Handler
.thumb_set RAMCFG_IRQHandler, Default_Handler
.thumb_set FLASH_IRQHandler, Default_Handler
.thumb_set FLASH_S_IRQHandler, Default_Handler
.thumb_set GTZC_IRQHandler, Default_Handler
.thumb_set RCC_IRQHandler, Default_Handler
.thumb_set RCC_S_IRQHandler, Default_Handler
.thumb_set EXTI0_IRQHandler, Default_Handler
.thumb_set EXTI1_IRQHandler, Default_Handler
.thumb_set EXTI2_IRQHandler, Default_Handler
.thumb_set EXTI3_IRQHandler, Default_Handler
.thumb_set EXTI4_IRQHandler, Default_Handler
.thumb_set EXTI5_IRQHandler, Default_Handler
.thumb_set EXTI6_IRQHandler, Default_Handler
.thumb_set EXTI7_IRQHandler, Default_Handler
.thumb_set EXTI8_IRQHandler, Default_Handler
.thumb_set EXTI9_IRQHandler, Default_Handler
.thumb_set EXTI10_IRQHandler, Default_Handler
.thumb_set EXTI11_IRQHandler, Default_Handler
.thumb_set EXTI12_IRQHandler, Default_Handler
.thumb_set EXTI13_IRQHandler, Default_Handler
.thumb_set EXTI14_IRQHandler, Default_Handler
.thumb_set EXTI15_IRQHandler, Default_Handler
.thumb_set GPDMA1_Channel0_IRQHandler, Default_Handler
.thumb_set GPDMA1_Channel1_IRQHandler, Default_Handler
.thumb_set GPDMA1_Channel2_IRQHandler, Default_Handler
.thumb_set GPDMA1_Channel3_IRQHandler, Default_Handler
.thumb_set GPDMA1_Channel4_IRQHandler, Default_Handler
.thumb_set GPDMA1_Channel5_IRQHandler, Default_Handler
.thumb_set GPDMA1_Channel6_IRQHandler, Default_Handler
.thumb_set GPDMA1_Channel7_IRQHandler, Default_Handler
.thumb_set IWDG_IRQHandler, Default_Handler
.thumb_set ADC1_IRQHandler, Default_Handler
.thumb_set DAC1_IRQHandler, Default_Handler
.thumb_set FDCAN1_IT0_IRQHandler, Default_Handler
.thumb_set FDCAN1_IT1_IRQHandler, Default_Handler
.thumb_set TIM1_BRK_IRQHandler, Default_Handler
.thumb_set TIM1_UP_IRQHandler, Default_Handler
.thumb_set TIM1_TRG_COM_IRQHandler, Default_Handler
.thumb_set TIM1_CC_IRQHandler, Default_Handler
.thumb_set TIM2_IRQHandler, Default_Handler
.thumb_set TIM3_IRQHandler, Default_Handler
.thumb_set TIM4_IRQHandler, Default_Handler
.thumb_set TIM5_IRQHandler, Default_Handler
.thumb_set TIM6_IRQHandler, Default_Handler
.thumb_set TIM7_IRQHandler, Default_Handler
.thumb_set I2C1_EV_IRQHandler, Default_Handler
.thumb_set I2C1_ER_IRQHandler, Default_Handler
.thumb_set I2C2_EV_IRQHandler, Default_Handler
.thumb_set I2C2_ER_IRQHandler, Default_Handler
.thumb_set SPI1_IRQHandler, Default_Handler
.thumb_set SPI2_IRQHandler, Default_Handler
.thumb_set SPI3_IRQHandler, Default_Handler
.thumb_set USART1_IRQHandler, Default_Handler
.thumb_set USART2_IRQHandler, Default_Handler
.thumb_set USART3_IRQHandler, Default_Handler
.thumb_set UART4_IRQHandler, Default_Handler
.thumb_set UART5_IRQHandler, Default_Handler
.thumb_set LPUART1_IRQHandler, Default_Handler
.thumb_set LPTIM1_IRQHandler, Default_Handler
.thumb_set TIM8_BRK_IRQHandler, Default_Handler
.thumb_set TIM8_UP_IRQHandler, Default_Handler
.thumb_set TIM8_TRG_COM_IRQHandler, Default_Handler
.thumb_set TIM8_CC_IRQHandler, Default_Handler
.thumb_set ADC2_IRQHandler, Default_Handler
.thumb_set LPTIM2_IRQHandler, Default_Handler
.thumb_set TIM15_IRQHandler, Default_Handler
.thumb_set USB_DRD_FS_IRQHandler, Default_Handler
.thumb_set CRS_IRQHandler, Default_Handler
.thumb_set UCPD1_IRQHandler, Default_Handler
.thumb_set FMC_IRQHandler, Default_Handler
.thumb_set OCTOSPI1_IRQHandler, Default_Handler
.thumb_set SDMMC1_IRQHandler, Default_Handler
.thumb_set I2C3_EV_IRQHandler, Default_Handler
.thumb_set I2C3_ER_IRQHandler, Default_Handler
.thumb_set SPI4_IRQHandler, Default_Handler
.thumb_set USART6_IRQHandler, Default_Handler
.thumb_set GPDMA2_Channel0_IRQHandler, Default_Handler
.thumb_set GPDMA2_Channel1_IRQHandler, Default_Handler
.thumb_set GPDMA2_Channel2_IRQHandler, Default_Handler
.thumb_set GPDMA2_Channel3_IRQHandler, Default_Handler
.thumb_set GPDMA2_Channel4_IRQHandler, Default_Handler
.thumb_set GPDMA2_Channel5_IRQHandler, Default_Handler
.thumb_set GPDMA2_Channel6_IRQHandler, Default_Handler
.thumb_set GPDMA2_Channel7_IRQHandler, Default_Handler
.thumb_set FPU_IRQHandler, Default_Handler
.thumb_set ICACHE_IRQHandler, Default_Handler
.thumb_set DCACHE1_IRQHandler, Default_Handler
.thumb_set DCMI_PSSI_IRQHandler, Default_Handler
.thumb_set FDCAN2_IT0_IRQHandler, Default_Handler
.thumb_set FDCAN2_IT1_IRQHandler, Default_Handler
.thumb_set DTS_IRQHandler, Default_Handler
.thumb_set RNG_IRQHandler, Default_Handler
.thumb_set HASH_IRQHandler, Default_Handler
.thumb_set CEC_IRQHandler, Default_Handler
.thumb_set TIM12_IRQHandler, Default_Handler
.thumb_set I3C1_EV_IRQHandler, Default_Handler
.thumb_set I3C1_ER_IRQHandler, Default_Handler
.thumb_set I3C2_EV_IRQHandler, Default_Handler
.thumb_set I3C2_ER_IRQHandler, Default_Handler
