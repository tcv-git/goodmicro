@; vectors_stm32g473xx.s
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
.size    g_pfnVectors, 472
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
.word RTC_TAMP_LSECSS_IRQHandler
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
.word ADC1_2_IRQHandler
.word USB_HP_IRQHandler
.word USB_LP_IRQHandler
.word FDCAN1_IT0_IRQHandler
.word FDCAN1_IT1_IRQHandler
.word EXTI9_5_IRQHandler
.word TIM1_BRK_TIM15_IRQHandler
.word TIM1_UP_TIM16_IRQHandler
.word TIM1_TRG_COM_TIM17_IRQHandler
.word TIM1_CC_IRQHandler
.word TIM2_IRQHandler
.word TIM3_IRQHandler
.word TIM4_IRQHandler
.word I2C1_EV_IRQHandler
.word I2C1_ER_IRQHandler
.word I2C2_EV_IRQHandler
.word I2C2_ER_IRQHandler
.word SPI1_IRQHandler
.word SPI2_IRQHandler
.word USART1_IRQHandler
.word USART2_IRQHandler
.word USART3_IRQHandler
.word EXTI15_10_IRQHandler
.word RTC_Alarm_IRQHandler
.word USBWakeUp_IRQHandler
.word TIM8_BRK_IRQHandler
.word TIM8_UP_IRQHandler
.word TIM8_TRG_COM_IRQHandler
.word TIM8_CC_IRQHandler
.word ADC3_IRQHandler
.word FMC_IRQHandler
.word LPTIM1_IRQHandler
.word TIM5_IRQHandler
.word SPI3_IRQHandler
.word UART4_IRQHandler
.word UART5_IRQHandler
.word TIM6_DAC_IRQHandler
.word TIM7_DAC_IRQHandler
.word DMA2_Channel1_IRQHandler
.word DMA2_Channel2_IRQHandler
.word DMA2_Channel3_IRQHandler
.word DMA2_Channel4_IRQHandler
.word DMA2_Channel5_IRQHandler
.word ADC4_IRQHandler
.word ADC5_IRQHandler
.word UCPD1_IRQHandler
.word COMP1_2_3_IRQHandler
.word COMP4_5_6_IRQHandler
.word COMP7_IRQHandler
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word CRS_IRQHandler
.word SAI1_IRQHandler
.word TIM20_BRK_IRQHandler
.word TIM20_UP_IRQHandler
.word TIM20_TRG_COM_IRQHandler
.word TIM20_CC_IRQHandler
.word FPU_IRQHandler
.word I2C4_EV_IRQHandler
.word I2C4_ER_IRQHandler
.word SPI4_IRQHandler
.word 0
.word FDCAN2_IT0_IRQHandler
.word FDCAN2_IT1_IRQHandler
.word FDCAN3_IT0_IRQHandler
.word FDCAN3_IT1_IRQHandler
.word RNG_IRQHandler
.word LPUART1_IRQHandler
.word I2C3_EV_IRQHandler
.word I2C3_ER_IRQHandler
.word DMAMUX_OVR_IRQHandler
.word QUADSPI_IRQHandler
.word DMA1_Channel8_IRQHandler
.word DMA2_Channel6_IRQHandler
.word DMA2_Channel7_IRQHandler
.word DMA2_Channel8_IRQHandler
.word CORDIC_IRQHandler
.word FMAC_IRQHandler

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
.weak RTC_TAMP_LSECSS_IRQHandler
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
.weak ADC1_2_IRQHandler
.weak USB_HP_IRQHandler
.weak USB_LP_IRQHandler
.weak FDCAN1_IT0_IRQHandler
.weak FDCAN1_IT1_IRQHandler
.weak EXTI9_5_IRQHandler
.weak TIM1_BRK_TIM15_IRQHandler
.weak TIM1_UP_TIM16_IRQHandler
.weak TIM1_TRG_COM_TIM17_IRQHandler
.weak TIM1_CC_IRQHandler
.weak TIM2_IRQHandler
.weak TIM3_IRQHandler
.weak TIM4_IRQHandler
.weak I2C1_EV_IRQHandler
.weak I2C1_ER_IRQHandler
.weak I2C2_EV_IRQHandler
.weak I2C2_ER_IRQHandler
.weak SPI1_IRQHandler
.weak SPI2_IRQHandler
.weak USART1_IRQHandler
.weak USART2_IRQHandler
.weak USART3_IRQHandler
.weak EXTI15_10_IRQHandler
.weak RTC_Alarm_IRQHandler
.weak USBWakeUp_IRQHandler
.weak TIM8_BRK_IRQHandler
.weak TIM8_UP_IRQHandler
.weak TIM8_TRG_COM_IRQHandler
.weak TIM8_CC_IRQHandler
.weak ADC3_IRQHandler
.weak FMC_IRQHandler
.weak LPTIM1_IRQHandler
.weak TIM5_IRQHandler
.weak SPI3_IRQHandler
.weak UART4_IRQHandler
.weak UART5_IRQHandler
.weak TIM6_DAC_IRQHandler
.weak TIM7_DAC_IRQHandler
.weak DMA2_Channel1_IRQHandler
.weak DMA2_Channel2_IRQHandler
.weak DMA2_Channel3_IRQHandler
.weak DMA2_Channel4_IRQHandler
.weak DMA2_Channel5_IRQHandler
.weak ADC4_IRQHandler
.weak ADC5_IRQHandler
.weak UCPD1_IRQHandler
.weak COMP1_2_3_IRQHandler
.weak COMP4_5_6_IRQHandler
.weak COMP7_IRQHandler
.weak CRS_IRQHandler
.weak SAI1_IRQHandler
.weak TIM20_BRK_IRQHandler
.weak TIM20_UP_IRQHandler
.weak TIM20_TRG_COM_IRQHandler
.weak TIM20_CC_IRQHandler
.weak FPU_IRQHandler
.weak I2C4_EV_IRQHandler
.weak I2C4_ER_IRQHandler
.weak SPI4_IRQHandler
.weak FDCAN2_IT0_IRQHandler
.weak FDCAN2_IT1_IRQHandler
.weak FDCAN3_IT0_IRQHandler
.weak FDCAN3_IT1_IRQHandler
.weak RNG_IRQHandler
.weak LPUART1_IRQHandler
.weak I2C3_EV_IRQHandler
.weak I2C3_ER_IRQHandler
.weak DMAMUX_OVR_IRQHandler
.weak QUADSPI_IRQHandler
.weak DMA1_Channel8_IRQHandler
.weak DMA2_Channel6_IRQHandler
.weak DMA2_Channel7_IRQHandler
.weak DMA2_Channel8_IRQHandler
.weak CORDIC_IRQHandler
.weak FMAC_IRQHandler

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
.thumb_set RTC_TAMP_LSECSS_IRQHandler, Default_Handler
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
.thumb_set ADC1_2_IRQHandler, Default_Handler
.thumb_set USB_HP_IRQHandler, Default_Handler
.thumb_set USB_LP_IRQHandler, Default_Handler
.thumb_set FDCAN1_IT0_IRQHandler, Default_Handler
.thumb_set FDCAN1_IT1_IRQHandler, Default_Handler
.thumb_set EXTI9_5_IRQHandler, Default_Handler
.thumb_set TIM1_BRK_TIM15_IRQHandler, Default_Handler
.thumb_set TIM1_UP_TIM16_IRQHandler, Default_Handler
.thumb_set TIM1_TRG_COM_TIM17_IRQHandler, Default_Handler
.thumb_set TIM1_CC_IRQHandler, Default_Handler
.thumb_set TIM2_IRQHandler, Default_Handler
.thumb_set TIM3_IRQHandler, Default_Handler
.thumb_set TIM4_IRQHandler, Default_Handler
.thumb_set I2C1_EV_IRQHandler, Default_Handler
.thumb_set I2C1_ER_IRQHandler, Default_Handler
.thumb_set I2C2_EV_IRQHandler, Default_Handler
.thumb_set I2C2_ER_IRQHandler, Default_Handler
.thumb_set SPI1_IRQHandler, Default_Handler
.thumb_set SPI2_IRQHandler, Default_Handler
.thumb_set USART1_IRQHandler, Default_Handler
.thumb_set USART2_IRQHandler, Default_Handler
.thumb_set USART3_IRQHandler, Default_Handler
.thumb_set EXTI15_10_IRQHandler, Default_Handler
.thumb_set RTC_Alarm_IRQHandler, Default_Handler
.thumb_set USBWakeUp_IRQHandler, Default_Handler
.thumb_set TIM8_BRK_IRQHandler, Default_Handler
.thumb_set TIM8_UP_IRQHandler, Default_Handler
.thumb_set TIM8_TRG_COM_IRQHandler, Default_Handler
.thumb_set TIM8_CC_IRQHandler, Default_Handler
.thumb_set ADC3_IRQHandler, Default_Handler
.thumb_set FMC_IRQHandler, Default_Handler
.thumb_set LPTIM1_IRQHandler, Default_Handler
.thumb_set TIM5_IRQHandler, Default_Handler
.thumb_set SPI3_IRQHandler, Default_Handler
.thumb_set UART4_IRQHandler, Default_Handler
.thumb_set UART5_IRQHandler, Default_Handler
.thumb_set TIM6_DAC_IRQHandler, Default_Handler
.thumb_set TIM7_DAC_IRQHandler, Default_Handler
.thumb_set DMA2_Channel1_IRQHandler, Default_Handler
.thumb_set DMA2_Channel2_IRQHandler, Default_Handler
.thumb_set DMA2_Channel3_IRQHandler, Default_Handler
.thumb_set DMA2_Channel4_IRQHandler, Default_Handler
.thumb_set DMA2_Channel5_IRQHandler, Default_Handler
.thumb_set ADC4_IRQHandler, Default_Handler
.thumb_set ADC5_IRQHandler, Default_Handler
.thumb_set UCPD1_IRQHandler, Default_Handler
.thumb_set COMP1_2_3_IRQHandler, Default_Handler
.thumb_set COMP4_5_6_IRQHandler, Default_Handler
.thumb_set COMP7_IRQHandler, Default_Handler
.thumb_set CRS_IRQHandler, Default_Handler
.thumb_set SAI1_IRQHandler, Default_Handler
.thumb_set TIM20_BRK_IRQHandler, Default_Handler
.thumb_set TIM20_UP_IRQHandler, Default_Handler
.thumb_set TIM20_TRG_COM_IRQHandler, Default_Handler
.thumb_set TIM20_CC_IRQHandler, Default_Handler
.thumb_set FPU_IRQHandler, Default_Handler
.thumb_set I2C4_EV_IRQHandler, Default_Handler
.thumb_set I2C4_ER_IRQHandler, Default_Handler
.thumb_set SPI4_IRQHandler, Default_Handler
.thumb_set FDCAN2_IT0_IRQHandler, Default_Handler
.thumb_set FDCAN2_IT1_IRQHandler, Default_Handler
.thumb_set FDCAN3_IT0_IRQHandler, Default_Handler
.thumb_set FDCAN3_IT1_IRQHandler, Default_Handler
.thumb_set RNG_IRQHandler, Default_Handler
.thumb_set LPUART1_IRQHandler, Default_Handler
.thumb_set I2C3_EV_IRQHandler, Default_Handler
.thumb_set I2C3_ER_IRQHandler, Default_Handler
.thumb_set DMAMUX_OVR_IRQHandler, Default_Handler
.thumb_set QUADSPI_IRQHandler, Default_Handler
.thumb_set DMA1_Channel8_IRQHandler, Default_Handler
.thumb_set DMA2_Channel6_IRQHandler, Default_Handler
.thumb_set DMA2_Channel7_IRQHandler, Default_Handler
.thumb_set DMA2_Channel8_IRQHandler, Default_Handler
.thumb_set CORDIC_IRQHandler, Default_Handler
.thumb_set FMAC_IRQHandler, Default_Handler
