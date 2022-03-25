// vectors_stm32l063xx.h
// automaically generated interrupt vector header

#ifndef VECTORS_STM32L063XX_H_INCLUDED
#define VECTORS_STM32L063XX_H_INCLUDED

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
void PVD_IRQHandler(void);
void RTC_IRQHandler(void);
void FLASH_IRQHandler(void);
void RCC_CRS_IRQHandler(void);
void EXTI0_1_IRQHandler(void);
void EXTI2_3_IRQHandler(void);
void EXTI4_15_IRQHandler(void);
void TSC_IRQHandler(void);
void DMA1_Channel1_IRQHandler(void);
void DMA1_Channel2_3_IRQHandler(void);
void DMA1_Channel4_5_6_7_IRQHandler(void);
void ADC1_COMP_IRQHandler(void);
void LPTIM1_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM6_DAC_IRQHandler(void);
void TIM21_IRQHandler(void);
void TIM22_IRQHandler(void);
void I2C1_IRQHandler(void);
void I2C2_IRQHandler(void);
void SPI1_IRQHandler(void);
void SPI2_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void AES_RNG_LPUART1_IRQHandler(void);
void LCD_IRQHandler(void);
void USB_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif // VECTORS_STM32L063XX_H_INCLUDED
