@; vectors_stm32l442xx.s
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
.size    g_pfnVectors, 396
.align   9

g_pfnVectors:
.word _estack
.word Reset_Handler
.word NMI_Handler
.word HardFault_Handler
.word MemManage_Handler
.word BusFault_Handler
.word UsageFault_Handler
.word 0
.word 0
.word 0
.word 0
.word SVC_Handler
.word DebugMon_Handler
.word 0
.word PendSV_Handler
.word SysTick_Handler
.word WWDG_IRQHandler
.word PVD_PVM_IRQHandler
.word TAMP_STAMP_IRQHandler
.word RTC_WKUP_IRQHandler
.word FLASH_IRQHandler
.word RCC_IRQHandler
.word EXTI0_IRQHandler
.word EXTI1_IRQHandler
.word EXTI2_IRQHandler
.word EXTI3_IRQHandler
.word EXTI4_IRQHandler
.word DMA1_Channel1_IRQHandler
.word DMA1_Channel2_IRQHandler
.word DMA1_Channel3_IRQHandler
.word DMA1_Channel4_IRQHandler
.word DMA1_Channel5_IRQHandler
.word DMA1_Channel6_IRQHandler
.word DMA1_Channel7_IRQHandler
.word ADC1_IRQHandler
.word CAN1_TX_IRQHandler
.word CAN1_RX0_IRQHandler
.word CAN1_RX1_IRQHandler
.word CAN1_SCE_IRQHandler
.word EXTI9_5_IRQHandler
.word TIM1_BRK_TIM15_IRQHandler
.word TIM1_UP_TIM16_IRQHandler
.word TIM1_TRG_COM_IRQHandler
.word TIM1_CC_IRQHandler
.word TIM2_IRQHandler
.word 0
.word 0
.word I2C1_EV_IRQHandler
.word I2C1_ER_IRQHandler
.word 0
.word 0
.word SPI1_IRQHandler
.word 0
.word USART1_IRQHandler
.word USART2_IRQHandler
.word 0
.word EXTI15_10_IRQHandler
.word RTC_Alarm_IRQHandler
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word SPI3_IRQHandler
.word 0
.word 0
.word TIM6_DAC_IRQHandler
.word TIM7_IRQHandler
.word DMA2_Channel1_IRQHandler
.word DMA2_Channel2_IRQHandler
.word DMA2_Channel3_IRQHandler
.word DMA2_Channel4_IRQHandler
.word DMA2_Channel5_IRQHandler
.word 0
.word 0
.word 0
.word COMP_IRQHandler
.word LPTIM1_IRQHandler
.word LPTIM2_IRQHandler
.word USB_IRQHandler
.word DMA2_Channel6_IRQHandler
.word DMA2_Channel7_IRQHandler
.word LPUART1_IRQHandler
.word QUADSPI_IRQHandler
.word I2C3_EV_IRQHandler
.word I2C3_ER_IRQHandler
.word SAI1_IRQHandler
.word 0
.word SWPMI1_IRQHandler
.word TSC_IRQHandler
.word 0
.word AES_IRQHandler
.word RNG_IRQHandler
.word FPU_IRQHandler
.word CRS_IRQHandler

.weak Reset_Handler
.weak NMI_Handler
.weak HardFault_Handler
.weak MemManage_Handler
.weak BusFault_Handler
.weak UsageFault_Handler
.weak SVC_Handler
.weak DebugMon_Handler
.weak PendSV_Handler
.weak SysTick_Handler
.weak WWDG_IRQHandler
.weak PVD_PVM_IRQHandler
.weak TAMP_STAMP_IRQHandler
.weak RTC_WKUP_IRQHandler
.weak FLASH_IRQHandler
.weak RCC_IRQHandler
.weak EXTI0_IRQHandler
.weak EXTI1_IRQHandler
.weak EXTI2_IRQHandler
.weak EXTI3_IRQHandler
.weak EXTI4_IRQHandler
.weak DMA1_Channel1_IRQHandler
.weak DMA1_Channel2_IRQHandler
.weak DMA1_Channel3_IRQHandler
.weak DMA1_Channel4_IRQHandler
.weak DMA1_Channel5_IRQHandler
.weak DMA1_Channel6_IRQHandler
.weak DMA1_Channel7_IRQHandler
.weak ADC1_IRQHandler
.weak CAN1_TX_IRQHandler
.weak CAN1_RX0_IRQHandler
.weak CAN1_RX1_IRQHandler
.weak CAN1_SCE_IRQHandler
.weak EXTI9_5_IRQHandler
.weak TIM1_BRK_TIM15_IRQHandler
.weak TIM1_UP_TIM16_IRQHandler
.weak TIM1_TRG_COM_IRQHandler
.weak TIM1_CC_IRQHandler
.weak TIM2_IRQHandler
.weak I2C1_EV_IRQHandler
.weak I2C1_ER_IRQHandler
.weak SPI1_IRQHandler
.weak USART1_IRQHandler
.weak USART2_IRQHandler
.weak EXTI15_10_IRQHandler
.weak RTC_Alarm_IRQHandler
.weak SPI3_IRQHandler
.weak TIM6_DAC_IRQHandler
.weak TIM7_IRQHandler
.weak DMA2_Channel1_IRQHandler
.weak DMA2_Channel2_IRQHandler
.weak DMA2_Channel3_IRQHandler
.weak DMA2_Channel4_IRQHandler
.weak DMA2_Channel5_IRQHandler
.weak COMP_IRQHandler
.weak LPTIM1_IRQHandler
.weak LPTIM2_IRQHandler
.weak USB_IRQHandler
.weak DMA2_Channel6_IRQHandler
.weak DMA2_Channel7_IRQHandler
.weak LPUART1_IRQHandler
.weak QUADSPI_IRQHandler
.weak I2C3_EV_IRQHandler
.weak I2C3_ER_IRQHandler
.weak SAI1_IRQHandler
.weak SWPMI1_IRQHandler
.weak TSC_IRQHandler
.weak AES_IRQHandler
.weak RNG_IRQHandler
.weak FPU_IRQHandler
.weak CRS_IRQHandler

.thumb_set Reset_Handler, Default_Handler
.thumb_set NMI_Handler, Default_Handler
.thumb_set HardFault_Handler, Default_Handler
.thumb_set MemManage_Handler, Default_Handler
.thumb_set BusFault_Handler, Default_Handler
.thumb_set UsageFault_Handler, Default_Handler
.thumb_set SVC_Handler, Default_Handler
.thumb_set DebugMon_Handler, Default_Handler
.thumb_set PendSV_Handler, Default_Handler
.thumb_set SysTick_Handler, Default_Handler
.thumb_set WWDG_IRQHandler, Default_Handler
.thumb_set PVD_PVM_IRQHandler, Default_Handler
.thumb_set TAMP_STAMP_IRQHandler, Default_Handler
.thumb_set RTC_WKUP_IRQHandler, Default_Handler
.thumb_set FLASH_IRQHandler, Default_Handler
.thumb_set RCC_IRQHandler, Default_Handler
.thumb_set EXTI0_IRQHandler, Default_Handler
.thumb_set EXTI1_IRQHandler, Default_Handler
.thumb_set EXTI2_IRQHandler, Default_Handler
.thumb_set EXTI3_IRQHandler, Default_Handler
.thumb_set EXTI4_IRQHandler, Default_Handler
.thumb_set DMA1_Channel1_IRQHandler, Default_Handler
.thumb_set DMA1_Channel2_IRQHandler, Default_Handler
.thumb_set DMA1_Channel3_IRQHandler, Default_Handler
.thumb_set DMA1_Channel4_IRQHandler, Default_Handler
.thumb_set DMA1_Channel5_IRQHandler, Default_Handler
.thumb_set DMA1_Channel6_IRQHandler, Default_Handler
.thumb_set DMA1_Channel7_IRQHandler, Default_Handler
.thumb_set ADC1_IRQHandler, Default_Handler
.thumb_set CAN1_TX_IRQHandler, Default_Handler
.thumb_set CAN1_RX0_IRQHandler, Default_Handler
.thumb_set CAN1_RX1_IRQHandler, Default_Handler
.thumb_set CAN1_SCE_IRQHandler, Default_Handler
.thumb_set EXTI9_5_IRQHandler, Default_Handler
.thumb_set TIM1_BRK_TIM15_IRQHandler, Default_Handler
.thumb_set TIM1_UP_TIM16_IRQHandler, Default_Handler
.thumb_set TIM1_TRG_COM_IRQHandler, Default_Handler
.thumb_set TIM1_CC_IRQHandler, Default_Handler
.thumb_set TIM2_IRQHandler, Default_Handler
.thumb_set I2C1_EV_IRQHandler, Default_Handler
.thumb_set I2C1_ER_IRQHandler, Default_Handler
.thumb_set SPI1_IRQHandler, Default_Handler
.thumb_set USART1_IRQHandler, Default_Handler
.thumb_set USART2_IRQHandler, Default_Handler
.thumb_set EXTI15_10_IRQHandler, Default_Handler
.thumb_set RTC_Alarm_IRQHandler, Default_Handler
.thumb_set SPI3_IRQHandler, Default_Handler
.thumb_set TIM6_DAC_IRQHandler, Default_Handler
.thumb_set TIM7_IRQHandler, Default_Handler
.thumb_set DMA2_Channel1_IRQHandler, Default_Handler
.thumb_set DMA2_Channel2_IRQHandler, Default_Handler
.thumb_set DMA2_Channel3_IRQHandler, Default_Handler
.thumb_set DMA2_Channel4_IRQHandler, Default_Handler
.thumb_set DMA2_Channel5_IRQHandler, Default_Handler
.thumb_set COMP_IRQHandler, Default_Handler
.thumb_set LPTIM1_IRQHandler, Default_Handler
.thumb_set LPTIM2_IRQHandler, Default_Handler
.thumb_set USB_IRQHandler, Default_Handler
.thumb_set DMA2_Channel6_IRQHandler, Default_Handler
.thumb_set DMA2_Channel7_IRQHandler, Default_Handler
.thumb_set LPUART1_IRQHandler, Default_Handler
.thumb_set QUADSPI_IRQHandler, Default_Handler
.thumb_set I2C3_EV_IRQHandler, Default_Handler
.thumb_set I2C3_ER_IRQHandler, Default_Handler
.thumb_set SAI1_IRQHandler, Default_Handler
.thumb_set SWPMI1_IRQHandler, Default_Handler
.thumb_set TSC_IRQHandler, Default_Handler
.thumb_set AES_IRQHandler, Default_Handler
.thumb_set RNG_IRQHandler, Default_Handler
.thumb_set FPU_IRQHandler, Default_Handler
.thumb_set CRS_IRQHandler, Default_Handler
