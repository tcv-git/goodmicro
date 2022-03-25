@; vectors_stm32f732xx.s
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
.size    g_pfnVectors, 480
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
.word PVD_IRQHandler
.word TAMP_STAMP_IRQHandler
.word RTC_WKUP_IRQHandler
.word FLASH_IRQHandler
.word RCC_IRQHandler
.word EXTI0_IRQHandler
.word EXTI1_IRQHandler
.word EXTI2_IRQHandler
.word EXTI3_IRQHandler
.word EXTI4_IRQHandler
.word DMA1_Stream0_IRQHandler
.word DMA1_Stream1_IRQHandler
.word DMA1_Stream2_IRQHandler
.word DMA1_Stream3_IRQHandler
.word DMA1_Stream4_IRQHandler
.word DMA1_Stream5_IRQHandler
.word DMA1_Stream6_IRQHandler
.word ADC_IRQHandler
.word CAN1_TX_IRQHandler
.word CAN1_RX0_IRQHandler
.word CAN1_RX1_IRQHandler
.word CAN1_SCE_IRQHandler
.word EXTI9_5_IRQHandler
.word TIM1_BRK_TIM9_IRQHandler
.word TIM1_UP_TIM10_IRQHandler
.word TIM1_TRG_COM_TIM11_IRQHandler
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
.word OTG_FS_WKUP_IRQHandler
.word TIM8_BRK_TIM12_IRQHandler
.word TIM8_UP_TIM13_IRQHandler
.word TIM8_TRG_COM_TIM14_IRQHandler
.word TIM8_CC_IRQHandler
.word DMA1_Stream7_IRQHandler
.word FMC_IRQHandler
.word SDMMC1_IRQHandler
.word TIM5_IRQHandler
.word SPI3_IRQHandler
.word UART4_IRQHandler
.word UART5_IRQHandler
.word TIM6_DAC_IRQHandler
.word TIM7_IRQHandler
.word DMA2_Stream0_IRQHandler
.word DMA2_Stream1_IRQHandler
.word DMA2_Stream2_IRQHandler
.word DMA2_Stream3_IRQHandler
.word DMA2_Stream4_IRQHandler
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word OTG_FS_IRQHandler
.word DMA2_Stream5_IRQHandler
.word DMA2_Stream6_IRQHandler
.word DMA2_Stream7_IRQHandler
.word USART6_IRQHandler
.word I2C3_EV_IRQHandler
.word I2C3_ER_IRQHandler
.word OTG_HS_EP1_OUT_IRQHandler
.word OTG_HS_EP1_IN_IRQHandler
.word OTG_HS_WKUP_IRQHandler
.word OTG_HS_IRQHandler
.word 0
.word AES_IRQHandler
.word RNG_IRQHandler
.word FPU_IRQHandler
.word UART7_IRQHandler
.word UART8_IRQHandler
.word SPI4_IRQHandler
.word SPI5_IRQHandler
.word 0
.word SAI1_IRQHandler
.word 0
.word 0
.word 0
.word SAI2_IRQHandler
.word QUADSPI_IRQHandler
.word LPTIM1_IRQHandler
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word SDMMC2_IRQHandler

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
.weak PVD_IRQHandler
.weak TAMP_STAMP_IRQHandler
.weak RTC_WKUP_IRQHandler
.weak FLASH_IRQHandler
.weak RCC_IRQHandler
.weak EXTI0_IRQHandler
.weak EXTI1_IRQHandler
.weak EXTI2_IRQHandler
.weak EXTI3_IRQHandler
.weak EXTI4_IRQHandler
.weak DMA1_Stream0_IRQHandler
.weak DMA1_Stream1_IRQHandler
.weak DMA1_Stream2_IRQHandler
.weak DMA1_Stream3_IRQHandler
.weak DMA1_Stream4_IRQHandler
.weak DMA1_Stream5_IRQHandler
.weak DMA1_Stream6_IRQHandler
.weak ADC_IRQHandler
.weak CAN1_TX_IRQHandler
.weak CAN1_RX0_IRQHandler
.weak CAN1_RX1_IRQHandler
.weak CAN1_SCE_IRQHandler
.weak EXTI9_5_IRQHandler
.weak TIM1_BRK_TIM9_IRQHandler
.weak TIM1_UP_TIM10_IRQHandler
.weak TIM1_TRG_COM_TIM11_IRQHandler
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
.weak OTG_FS_WKUP_IRQHandler
.weak TIM8_BRK_TIM12_IRQHandler
.weak TIM8_UP_TIM13_IRQHandler
.weak TIM8_TRG_COM_TIM14_IRQHandler
.weak TIM8_CC_IRQHandler
.weak DMA1_Stream7_IRQHandler
.weak FMC_IRQHandler
.weak SDMMC1_IRQHandler
.weak TIM5_IRQHandler
.weak SPI3_IRQHandler
.weak UART4_IRQHandler
.weak UART5_IRQHandler
.weak TIM6_DAC_IRQHandler
.weak TIM7_IRQHandler
.weak DMA2_Stream0_IRQHandler
.weak DMA2_Stream1_IRQHandler
.weak DMA2_Stream2_IRQHandler
.weak DMA2_Stream3_IRQHandler
.weak DMA2_Stream4_IRQHandler
.weak OTG_FS_IRQHandler
.weak DMA2_Stream5_IRQHandler
.weak DMA2_Stream6_IRQHandler
.weak DMA2_Stream7_IRQHandler
.weak USART6_IRQHandler
.weak I2C3_EV_IRQHandler
.weak I2C3_ER_IRQHandler
.weak OTG_HS_EP1_OUT_IRQHandler
.weak OTG_HS_EP1_IN_IRQHandler
.weak OTG_HS_WKUP_IRQHandler
.weak OTG_HS_IRQHandler
.weak AES_IRQHandler
.weak RNG_IRQHandler
.weak FPU_IRQHandler
.weak UART7_IRQHandler
.weak UART8_IRQHandler
.weak SPI4_IRQHandler
.weak SPI5_IRQHandler
.weak SAI1_IRQHandler
.weak SAI2_IRQHandler
.weak QUADSPI_IRQHandler
.weak LPTIM1_IRQHandler
.weak SDMMC2_IRQHandler

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
.thumb_set PVD_IRQHandler, Default_Handler
.thumb_set TAMP_STAMP_IRQHandler, Default_Handler
.thumb_set RTC_WKUP_IRQHandler, Default_Handler
.thumb_set FLASH_IRQHandler, Default_Handler
.thumb_set RCC_IRQHandler, Default_Handler
.thumb_set EXTI0_IRQHandler, Default_Handler
.thumb_set EXTI1_IRQHandler, Default_Handler
.thumb_set EXTI2_IRQHandler, Default_Handler
.thumb_set EXTI3_IRQHandler, Default_Handler
.thumb_set EXTI4_IRQHandler, Default_Handler
.thumb_set DMA1_Stream0_IRQHandler, Default_Handler
.thumb_set DMA1_Stream1_IRQHandler, Default_Handler
.thumb_set DMA1_Stream2_IRQHandler, Default_Handler
.thumb_set DMA1_Stream3_IRQHandler, Default_Handler
.thumb_set DMA1_Stream4_IRQHandler, Default_Handler
.thumb_set DMA1_Stream5_IRQHandler, Default_Handler
.thumb_set DMA1_Stream6_IRQHandler, Default_Handler
.thumb_set ADC_IRQHandler, Default_Handler
.thumb_set CAN1_TX_IRQHandler, Default_Handler
.thumb_set CAN1_RX0_IRQHandler, Default_Handler
.thumb_set CAN1_RX1_IRQHandler, Default_Handler
.thumb_set CAN1_SCE_IRQHandler, Default_Handler
.thumb_set EXTI9_5_IRQHandler, Default_Handler
.thumb_set TIM1_BRK_TIM9_IRQHandler, Default_Handler
.thumb_set TIM1_UP_TIM10_IRQHandler, Default_Handler
.thumb_set TIM1_TRG_COM_TIM11_IRQHandler, Default_Handler
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
.thumb_set OTG_FS_WKUP_IRQHandler, Default_Handler
.thumb_set TIM8_BRK_TIM12_IRQHandler, Default_Handler
.thumb_set TIM8_UP_TIM13_IRQHandler, Default_Handler
.thumb_set TIM8_TRG_COM_TIM14_IRQHandler, Default_Handler
.thumb_set TIM8_CC_IRQHandler, Default_Handler
.thumb_set DMA1_Stream7_IRQHandler, Default_Handler
.thumb_set FMC_IRQHandler, Default_Handler
.thumb_set SDMMC1_IRQHandler, Default_Handler
.thumb_set TIM5_IRQHandler, Default_Handler
.thumb_set SPI3_IRQHandler, Default_Handler
.thumb_set UART4_IRQHandler, Default_Handler
.thumb_set UART5_IRQHandler, Default_Handler
.thumb_set TIM6_DAC_IRQHandler, Default_Handler
.thumb_set TIM7_IRQHandler, Default_Handler
.thumb_set DMA2_Stream0_IRQHandler, Default_Handler
.thumb_set DMA2_Stream1_IRQHandler, Default_Handler
.thumb_set DMA2_Stream2_IRQHandler, Default_Handler
.thumb_set DMA2_Stream3_IRQHandler, Default_Handler
.thumb_set DMA2_Stream4_IRQHandler, Default_Handler
.thumb_set OTG_FS_IRQHandler, Default_Handler
.thumb_set DMA2_Stream5_IRQHandler, Default_Handler
.thumb_set DMA2_Stream6_IRQHandler, Default_Handler
.thumb_set DMA2_Stream7_IRQHandler, Default_Handler
.thumb_set USART6_IRQHandler, Default_Handler
.thumb_set I2C3_EV_IRQHandler, Default_Handler
.thumb_set I2C3_ER_IRQHandler, Default_Handler
.thumb_set OTG_HS_EP1_OUT_IRQHandler, Default_Handler
.thumb_set OTG_HS_EP1_IN_IRQHandler, Default_Handler
.thumb_set OTG_HS_WKUP_IRQHandler, Default_Handler
.thumb_set OTG_HS_IRQHandler, Default_Handler
.thumb_set AES_IRQHandler, Default_Handler
.thumb_set RNG_IRQHandler, Default_Handler
.thumb_set FPU_IRQHandler, Default_Handler
.thumb_set UART7_IRQHandler, Default_Handler
.thumb_set UART8_IRQHandler, Default_Handler
.thumb_set SPI4_IRQHandler, Default_Handler
.thumb_set SPI5_IRQHandler, Default_Handler
.thumb_set SAI1_IRQHandler, Default_Handler
.thumb_set SAI2_IRQHandler, Default_Handler
.thumb_set QUADSPI_IRQHandler, Default_Handler
.thumb_set LPTIM1_IRQHandler, Default_Handler
.thumb_set SDMMC2_IRQHandler, Default_Handler
