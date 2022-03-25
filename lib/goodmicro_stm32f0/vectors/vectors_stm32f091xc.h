// vectors_stm32f091xc.h
// automaically generated interrupt vector header

#ifndef VECTORS_STM32F091XC_H_INCLUDED
#define VECTORS_STM32F091XC_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void WWDG_IRQHandler(void);
void PVD_VDDIO2_IRQHandler(void);
void RTC_IRQHandler(void);
void FLASH_IRQHandler(void);
void RCC_CRS_IRQHandler(void);
void EXTI0_1_IRQHandler(void);
void EXTI2_3_IRQHandler(void);
void EXTI4_15_IRQHandler(void);
void TSC_IRQHandler(void);
void DMA1_Ch1_IRQHandler(void);
void DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler(void);
void DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler(void);
void ADC1_COMP_IRQHandler(void);
void TIM1_BRK_UP_TRG_COM_IRQHandler(void);
void TIM1_CC_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM6_DAC_IRQHandler(void);
void TIM7_IRQHandler(void);
void TIM14_IRQHandler(void);
void TIM15_IRQHandler(void);
void TIM16_IRQHandler(void);
void TIM17_IRQHandler(void);
void I2C1_IRQHandler(void);
void I2C2_IRQHandler(void);
void SPI1_IRQHandler(void);
void SPI2_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_8_IRQHandler(void);
void CEC_CAN_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif // VECTORS_STM32F091XC_H_INCLUDED
