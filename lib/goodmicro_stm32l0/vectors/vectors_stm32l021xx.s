@; vectors_stm32l021xx.s
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
.word RCC_IRQHandler
.word EXTI0_1_IRQHandler
.word EXTI2_3_IRQHandler
.word EXTI4_15_IRQHandler
.word 0
.word DMA1_Channel1_IRQHandler
.word DMA1_Channel2_3_IRQHandler
.word DMA1_Channel4_5_IRQHandler
.word ADC1_COMP_IRQHandler
.word LPTIM1_IRQHandler
.word 0
.word TIM2_IRQHandler
.word 0
.word 0
.word 0
.word 0
.word TIM21_IRQHandler
.word 0
.word 0
.word I2C1_IRQHandler
.word 0
.word SPI1_IRQHandler
.word 0
.word 0
.word USART2_IRQHandler
.word AES_LPUART1_IRQHandler
.word 0
.word 0

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
.weak RCC_IRQHandler
.weak EXTI0_1_IRQHandler
.weak EXTI2_3_IRQHandler
.weak EXTI4_15_IRQHandler
.weak DMA1_Channel1_IRQHandler
.weak DMA1_Channel2_3_IRQHandler
.weak DMA1_Channel4_5_IRQHandler
.weak ADC1_COMP_IRQHandler
.weak LPTIM1_IRQHandler
.weak TIM2_IRQHandler
.weak TIM21_IRQHandler
.weak I2C1_IRQHandler
.weak SPI1_IRQHandler
.weak USART2_IRQHandler
.weak AES_LPUART1_IRQHandler

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
.thumb_set RCC_IRQHandler, Default_Handler
.thumb_set EXTI0_1_IRQHandler, Default_Handler
.thumb_set EXTI2_3_IRQHandler, Default_Handler
.thumb_set EXTI4_15_IRQHandler, Default_Handler
.thumb_set DMA1_Channel1_IRQHandler, Default_Handler
.thumb_set DMA1_Channel2_3_IRQHandler, Default_Handler
.thumb_set DMA1_Channel4_5_IRQHandler, Default_Handler
.thumb_set ADC1_COMP_IRQHandler, Default_Handler
.thumb_set LPTIM1_IRQHandler, Default_Handler
.thumb_set TIM2_IRQHandler, Default_Handler
.thumb_set TIM21_IRQHandler, Default_Handler
.thumb_set I2C1_IRQHandler, Default_Handler
.thumb_set SPI1_IRQHandler, Default_Handler
.thumb_set USART2_IRQHandler, Default_Handler
.thumb_set AES_LPUART1_IRQHandler, Default_Handler
