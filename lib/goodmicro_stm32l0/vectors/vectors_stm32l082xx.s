@; vectors_stm32l082xx.s
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
.size    g_pfnVectors, 192
.align   8

g_pfnVectors:
.word _estack
.word Reset_Handler
.word NMI_Handler
.word HardFault_Handler
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word SVC_Handler
.word 0
.word 0
.word PendSV_Handler
.word SysTick_Handler
.word WWDG_IRQHandler
.word PVD_IRQHandler
.word RTC_IRQHandler
.word FLASH_IRQHandler
.word RCC_CRS_IRQHandler
.word EXTI0_1_IRQHandler
.word EXTI2_3_IRQHandler
.word EXTI4_15_IRQHandler
.word TSC_IRQHandler
.word DMA1_Channel1_IRQHandler
.word DMA1_Channel2_3_IRQHandler
.word DMA1_Channel4_5_6_7_IRQHandler
.word ADC1_COMP_IRQHandler
.word LPTIM1_IRQHandler
.word USART4_5_IRQHandler
.word TIM2_IRQHandler
.word TIM3_IRQHandler
.word TIM6_DAC_IRQHandler
.word TIM7_IRQHandler
.word 0
.word TIM21_IRQHandler
.word I2C3_IRQHandler
.word TIM22_IRQHandler
.word I2C1_IRQHandler
.word I2C2_IRQHandler
.word SPI1_IRQHandler
.word SPI2_IRQHandler
.word USART1_IRQHandler
.word USART2_IRQHandler
.word AES_RNG_LPUART1_IRQHandler
.word 0
.word USB_IRQHandler

.weak Reset_Handler
.weak NMI_Handler
.weak HardFault_Handler
.weak SVC_Handler
.weak PendSV_Handler
.weak SysTick_Handler
.weak WWDG_IRQHandler
.weak PVD_IRQHandler
.weak RTC_IRQHandler
.weak FLASH_IRQHandler
.weak RCC_CRS_IRQHandler
.weak EXTI0_1_IRQHandler
.weak EXTI2_3_IRQHandler
.weak EXTI4_15_IRQHandler
.weak TSC_IRQHandler
.weak DMA1_Channel1_IRQHandler
.weak DMA1_Channel2_3_IRQHandler
.weak DMA1_Channel4_5_6_7_IRQHandler
.weak ADC1_COMP_IRQHandler
.weak LPTIM1_IRQHandler
.weak USART4_5_IRQHandler
.weak TIM2_IRQHandler
.weak TIM3_IRQHandler
.weak TIM6_DAC_IRQHandler
.weak TIM7_IRQHandler
.weak TIM21_IRQHandler
.weak I2C3_IRQHandler
.weak TIM22_IRQHandler
.weak I2C1_IRQHandler
.weak I2C2_IRQHandler
.weak SPI1_IRQHandler
.weak SPI2_IRQHandler
.weak USART1_IRQHandler
.weak USART2_IRQHandler
.weak AES_RNG_LPUART1_IRQHandler
.weak USB_IRQHandler

.thumb_set Reset_Handler, Default_Handler
.thumb_set NMI_Handler, Default_Handler
.thumb_set HardFault_Handler, Default_Handler
.thumb_set SVC_Handler, Default_Handler
.thumb_set PendSV_Handler, Default_Handler
.thumb_set SysTick_Handler, Default_Handler
.thumb_set WWDG_IRQHandler, Default_Handler
.thumb_set PVD_IRQHandler, Default_Handler
.thumb_set RTC_IRQHandler, Default_Handler
.thumb_set FLASH_IRQHandler, Default_Handler
.thumb_set RCC_CRS_IRQHandler, Default_Handler
.thumb_set EXTI0_1_IRQHandler, Default_Handler
.thumb_set EXTI2_3_IRQHandler, Default_Handler
.thumb_set EXTI4_15_IRQHandler, Default_Handler
.thumb_set TSC_IRQHandler, Default_Handler
.thumb_set DMA1_Channel1_IRQHandler, Default_Handler
.thumb_set DMA1_Channel2_3_IRQHandler, Default_Handler
.thumb_set DMA1_Channel4_5_6_7_IRQHandler, Default_Handler
.thumb_set ADC1_COMP_IRQHandler, Default_Handler
.thumb_set LPTIM1_IRQHandler, Default_Handler
.thumb_set USART4_5_IRQHandler, Default_Handler
.thumb_set TIM2_IRQHandler, Default_Handler
.thumb_set TIM3_IRQHandler, Default_Handler
.thumb_set TIM6_DAC_IRQHandler, Default_Handler
.thumb_set TIM7_IRQHandler, Default_Handler
.thumb_set TIM21_IRQHandler, Default_Handler
.thumb_set I2C3_IRQHandler, Default_Handler
.thumb_set TIM22_IRQHandler, Default_Handler
.thumb_set I2C1_IRQHandler, Default_Handler
.thumb_set I2C2_IRQHandler, Default_Handler
.thumb_set SPI1_IRQHandler, Default_Handler
.thumb_set SPI2_IRQHandler, Default_Handler
.thumb_set USART1_IRQHandler, Default_Handler
.thumb_set USART2_IRQHandler, Default_Handler
.thumb_set AES_RNG_LPUART1_IRQHandler, Default_Handler
.thumb_set USB_IRQHandler, Default_Handler
