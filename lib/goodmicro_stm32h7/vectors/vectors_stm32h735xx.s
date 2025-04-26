@; vectors_stm32h735xx.s
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
.size    g_pfnVectors, 716
.align   10

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
.word PVD_AVD_IRQHandler
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
.word FDCAN1_IT0_IRQHandler
.word FDCAN2_IT0_IRQHandler
.word FDCAN1_IT1_IRQHandler
.word FDCAN2_IT1_IRQHandler
.word EXTI9_5_IRQHandler
.word TIM1_BRK_IRQHandler
.word TIM1_UP_IRQHandler
.word TIM1_TRG_COM_IRQHandler
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
.word 0
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
.word ETH_IRQHandler
.word ETH_WKUP_IRQHandler
.word FDCAN_CAL_IRQHandler
.word 0
.word 0
.word 0
.word 0
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
.word DCMI_PSSI_IRQHandler
.word CRYP_IRQHandler
.word HASH_RNG_IRQHandler
.word FPU_IRQHandler
.word UART7_IRQHandler
.word UART8_IRQHandler
.word SPI4_IRQHandler
.word SPI5_IRQHandler
.word SPI6_IRQHandler
.word SAI1_IRQHandler
.word LTDC_IRQHandler
.word LTDC_ER_IRQHandler
.word DMA2D_IRQHandler
.word 0
.word OCTOSPI1_IRQHandler
.word LPTIM1_IRQHandler
.word CEC_IRQHandler
.word I2C4_EV_IRQHandler
.word I2C4_ER_IRQHandler
.word SPDIF_RX_IRQHandler
.word 0
.word 0
.word 0
.word 0
.word DMAMUX1_OVR_IRQHandler
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word DFSDM1_FLT0_IRQHandler
.word DFSDM1_FLT1_IRQHandler
.word DFSDM1_FLT2_IRQHandler
.word DFSDM1_FLT3_IRQHandler
.word 0
.word SWPMI1_IRQHandler
.word TIM15_IRQHandler
.word TIM16_IRQHandler
.word TIM17_IRQHandler
.word MDIOS_WKUP_IRQHandler
.word MDIOS_IRQHandler
.word 0
.word MDMA_IRQHandler
.word 0
.word SDMMC2_IRQHandler
.word HSEM1_IRQHandler
.word 0
.word ADC3_IRQHandler
.word DMAMUX2_OVR_IRQHandler
.word BDMA_Channel0_IRQHandler
.word BDMA_Channel1_IRQHandler
.word BDMA_Channel2_IRQHandler
.word BDMA_Channel3_IRQHandler
.word BDMA_Channel4_IRQHandler
.word BDMA_Channel5_IRQHandler
.word BDMA_Channel6_IRQHandler
.word BDMA_Channel7_IRQHandler
.word COMP1_IRQHandler
.word LPTIM2_IRQHandler
.word LPTIM3_IRQHandler
.word LPTIM4_IRQHandler
.word LPTIM5_IRQHandler
.word LPUART1_IRQHandler
.word 0
.word CRS_IRQHandler
.word ECC_IRQHandler
.word SAI4_IRQHandler
.word DTS_IRQHandler
.word 0
.word WAKEUP_PIN_IRQHandler
.word OCTOSPI2_IRQHandler
.word OTFDEC1_IRQHandler
.word OTFDEC2_IRQHandler
.word FMAC_IRQHandler
.word CORDIC_IRQHandler
.word UART9_IRQHandler
.word USART10_IRQHandler
.word I2C5_EV_IRQHandler
.word I2C5_ER_IRQHandler
.word FDCAN3_IT0_IRQHandler
.word FDCAN3_IT1_IRQHandler
.word TIM23_IRQHandler
.word TIM24_IRQHandler

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
.weak PVD_AVD_IRQHandler
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
.weak FDCAN1_IT0_IRQHandler
.weak FDCAN2_IT0_IRQHandler
.weak FDCAN1_IT1_IRQHandler
.weak FDCAN2_IT1_IRQHandler
.weak EXTI9_5_IRQHandler
.weak TIM1_BRK_IRQHandler
.weak TIM1_UP_IRQHandler
.weak TIM1_TRG_COM_IRQHandler
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
.weak ETH_IRQHandler
.weak ETH_WKUP_IRQHandler
.weak FDCAN_CAL_IRQHandler
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
.weak DCMI_PSSI_IRQHandler
.weak CRYP_IRQHandler
.weak HASH_RNG_IRQHandler
.weak FPU_IRQHandler
.weak UART7_IRQHandler
.weak UART8_IRQHandler
.weak SPI4_IRQHandler
.weak SPI5_IRQHandler
.weak SPI6_IRQHandler
.weak SAI1_IRQHandler
.weak LTDC_IRQHandler
.weak LTDC_ER_IRQHandler
.weak DMA2D_IRQHandler
.weak OCTOSPI1_IRQHandler
.weak LPTIM1_IRQHandler
.weak CEC_IRQHandler
.weak I2C4_EV_IRQHandler
.weak I2C4_ER_IRQHandler
.weak SPDIF_RX_IRQHandler
.weak DMAMUX1_OVR_IRQHandler
.weak DFSDM1_FLT0_IRQHandler
.weak DFSDM1_FLT1_IRQHandler
.weak DFSDM1_FLT2_IRQHandler
.weak DFSDM1_FLT3_IRQHandler
.weak SWPMI1_IRQHandler
.weak TIM15_IRQHandler
.weak TIM16_IRQHandler
.weak TIM17_IRQHandler
.weak MDIOS_WKUP_IRQHandler
.weak MDIOS_IRQHandler
.weak MDMA_IRQHandler
.weak SDMMC2_IRQHandler
.weak HSEM1_IRQHandler
.weak ADC3_IRQHandler
.weak DMAMUX2_OVR_IRQHandler
.weak BDMA_Channel0_IRQHandler
.weak BDMA_Channel1_IRQHandler
.weak BDMA_Channel2_IRQHandler
.weak BDMA_Channel3_IRQHandler
.weak BDMA_Channel4_IRQHandler
.weak BDMA_Channel5_IRQHandler
.weak BDMA_Channel6_IRQHandler
.weak BDMA_Channel7_IRQHandler
.weak COMP1_IRQHandler
.weak LPTIM2_IRQHandler
.weak LPTIM3_IRQHandler
.weak LPTIM4_IRQHandler
.weak LPTIM5_IRQHandler
.weak LPUART1_IRQHandler
.weak CRS_IRQHandler
.weak ECC_IRQHandler
.weak SAI4_IRQHandler
.weak DTS_IRQHandler
.weak WAKEUP_PIN_IRQHandler
.weak OCTOSPI2_IRQHandler
.weak OTFDEC1_IRQHandler
.weak OTFDEC2_IRQHandler
.weak FMAC_IRQHandler
.weak CORDIC_IRQHandler
.weak UART9_IRQHandler
.weak USART10_IRQHandler
.weak I2C5_EV_IRQHandler
.weak I2C5_ER_IRQHandler
.weak FDCAN3_IT0_IRQHandler
.weak FDCAN3_IT1_IRQHandler
.weak TIM23_IRQHandler
.weak TIM24_IRQHandler

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
.thumb_set PVD_AVD_IRQHandler, Default_Handler
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
.thumb_set FDCAN1_IT0_IRQHandler, Default_Handler
.thumb_set FDCAN2_IT0_IRQHandler, Default_Handler
.thumb_set FDCAN1_IT1_IRQHandler, Default_Handler
.thumb_set FDCAN2_IT1_IRQHandler, Default_Handler
.thumb_set EXTI9_5_IRQHandler, Default_Handler
.thumb_set TIM1_BRK_IRQHandler, Default_Handler
.thumb_set TIM1_UP_IRQHandler, Default_Handler
.thumb_set TIM1_TRG_COM_IRQHandler, Default_Handler
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
.thumb_set ETH_IRQHandler, Default_Handler
.thumb_set ETH_WKUP_IRQHandler, Default_Handler
.thumb_set FDCAN_CAL_IRQHandler, Default_Handler
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
.thumb_set DCMI_PSSI_IRQHandler, Default_Handler
.thumb_set CRYP_IRQHandler, Default_Handler
.thumb_set HASH_RNG_IRQHandler, Default_Handler
.thumb_set FPU_IRQHandler, Default_Handler
.thumb_set UART7_IRQHandler, Default_Handler
.thumb_set UART8_IRQHandler, Default_Handler
.thumb_set SPI4_IRQHandler, Default_Handler
.thumb_set SPI5_IRQHandler, Default_Handler
.thumb_set SPI6_IRQHandler, Default_Handler
.thumb_set SAI1_IRQHandler, Default_Handler
.thumb_set LTDC_IRQHandler, Default_Handler
.thumb_set LTDC_ER_IRQHandler, Default_Handler
.thumb_set DMA2D_IRQHandler, Default_Handler
.thumb_set OCTOSPI1_IRQHandler, Default_Handler
.thumb_set LPTIM1_IRQHandler, Default_Handler
.thumb_set CEC_IRQHandler, Default_Handler
.thumb_set I2C4_EV_IRQHandler, Default_Handler
.thumb_set I2C4_ER_IRQHandler, Default_Handler
.thumb_set SPDIF_RX_IRQHandler, Default_Handler
.thumb_set DMAMUX1_OVR_IRQHandler, Default_Handler
.thumb_set DFSDM1_FLT0_IRQHandler, Default_Handler
.thumb_set DFSDM1_FLT1_IRQHandler, Default_Handler
.thumb_set DFSDM1_FLT2_IRQHandler, Default_Handler
.thumb_set DFSDM1_FLT3_IRQHandler, Default_Handler
.thumb_set SWPMI1_IRQHandler, Default_Handler
.thumb_set TIM15_IRQHandler, Default_Handler
.thumb_set TIM16_IRQHandler, Default_Handler
.thumb_set TIM17_IRQHandler, Default_Handler
.thumb_set MDIOS_WKUP_IRQHandler, Default_Handler
.thumb_set MDIOS_IRQHandler, Default_Handler
.thumb_set MDMA_IRQHandler, Default_Handler
.thumb_set SDMMC2_IRQHandler, Default_Handler
.thumb_set HSEM1_IRQHandler, Default_Handler
.thumb_set ADC3_IRQHandler, Default_Handler
.thumb_set DMAMUX2_OVR_IRQHandler, Default_Handler
.thumb_set BDMA_Channel0_IRQHandler, Default_Handler
.thumb_set BDMA_Channel1_IRQHandler, Default_Handler
.thumb_set BDMA_Channel2_IRQHandler, Default_Handler
.thumb_set BDMA_Channel3_IRQHandler, Default_Handler
.thumb_set BDMA_Channel4_IRQHandler, Default_Handler
.thumb_set BDMA_Channel5_IRQHandler, Default_Handler
.thumb_set BDMA_Channel6_IRQHandler, Default_Handler
.thumb_set BDMA_Channel7_IRQHandler, Default_Handler
.thumb_set COMP1_IRQHandler, Default_Handler
.thumb_set LPTIM2_IRQHandler, Default_Handler
.thumb_set LPTIM3_IRQHandler, Default_Handler
.thumb_set LPTIM4_IRQHandler, Default_Handler
.thumb_set LPTIM5_IRQHandler, Default_Handler
.thumb_set LPUART1_IRQHandler, Default_Handler
.thumb_set CRS_IRQHandler, Default_Handler
.thumb_set ECC_IRQHandler, Default_Handler
.thumb_set SAI4_IRQHandler, Default_Handler
.thumb_set DTS_IRQHandler, Default_Handler
.thumb_set WAKEUP_PIN_IRQHandler, Default_Handler
.thumb_set OCTOSPI2_IRQHandler, Default_Handler
.thumb_set OTFDEC1_IRQHandler, Default_Handler
.thumb_set OTFDEC2_IRQHandler, Default_Handler
.thumb_set FMAC_IRQHandler, Default_Handler
.thumb_set CORDIC_IRQHandler, Default_Handler
.thumb_set UART9_IRQHandler, Default_Handler
.thumb_set USART10_IRQHandler, Default_Handler
.thumb_set I2C5_EV_IRQHandler, Default_Handler
.thumb_set I2C5_ER_IRQHandler, Default_Handler
.thumb_set FDCAN3_IT0_IRQHandler, Default_Handler
.thumb_set FDCAN3_IT1_IRQHandler, Default_Handler
.thumb_set TIM23_IRQHandler, Default_Handler
.thumb_set TIM24_IRQHandler, Default_Handler
