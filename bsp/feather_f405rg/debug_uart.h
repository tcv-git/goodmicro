// debug_uart.h
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/goodmicro/

/*
  I, Tom Vajzovic, am the author of this software and its documentation.
  I permanently abandon all copyright and other intellectual property rights
  in them.

  I am fairly certain that the software does what the documentation says it
  does, but I do not guarantee that it does, or that it does what you think it
  should.  I do not guarantee that it will not have undesirable side effects.

  If you use, modify or distribute this software then you do so at your own
  risk.  If you do not pass on this warning then you may be responsible for any
  problems encountered by those who obtain the software through you.
*/

#ifndef DEBUG_UART_H_INCLUDED
#define DEBUG_UART_H_INCLUDED

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_simple_gpio.h"
#include "system_stm32f405-439.h"

#define DEBUG_TX_AHBxENR                AHB1ENR
#define DEBUG_TX_AHBxENR_GPIOxEN        RCC_AHB1ENR_GPIOCEN
#define DEBUG_TX_GPIOx                  GPIOC
#define DEBUG_TX_PINx                   PIN10
#define DEBUG_TX_AFx                    AF8

#define DEBUG_UART_APBx_ENR             APB1ENR
#define DEBUG_UART_APBx_ENR_UARTxEN     RCC_APB1ENR_UART4EN
#define DEBUG_UART_APBx_RSTR            APB1RSTR
#define DEBUG_UART_APBx_RSTR_UARTxRST   RCC_APB1RSTR_UART4RST
#define DEBUG_UARTx                     UART4
#define DEBUG_UART_IRQn                 UART4_IRQn
#define DEBUG_UART_IRQHandler           UART4_IRQHandler

#define DEBUG_UART_APBx_CLK             APB1_CLK
#define DEBUG_BAUD                      525000u

#define DEBUG_DMA_AHBxENR                 AHB1ENR
#define DEBUG_DMA_AHBxENR_DMAxEN          RCC_AHB1ENR_DMA1EN
#define DEBUG_DMAx                        DMA1

#define DEBUG_TX_DMA_xISR                 HISR
#define DEBUG_TX_DMA_xIFCR                HIFCR

#define DEBUG_TX_DMA_xISR_TCIFx           DMA_HISR_TCIF4
#define DEBUG_TX_DMA_xISR_HTIFx           DMA_HISR_HTIF4
#define DEBUG_TX_DMA_xISR_TEIFx           DMA_HISR_TEIF4
#define DEBUG_TX_DMA_xISR_DMEIFx          DMA_HISR_DMEIF4
#define DEBUG_TX_DMA_xISR_FEIFx           DMA_HISR_FEIF4

#define DEBUG_TX_DMA_xIFCR_CTCIFx         DMA_HIFCR_CTCIF4
#define DEBUG_TX_DMA_xIFCR_CHTIFx         DMA_HIFCR_CHTIF4
#define DEBUG_TX_DMA_xIFCR_CTEIFx         DMA_HIFCR_CTEIF4
#define DEBUG_TX_DMA_xIFCR_CDMEIFx        DMA_HIFCR_CDMEIF4
#define DEBUG_TX_DMA_xIFCR_CFEIFx         DMA_HIFCR_CFEIF4

#define DEBUG_TX_DMAx_SxCR_CHSELx         DMA1_S4CR_CHSEL_UART4_TX
#define DEBUG_TX_DMAx_Streamx             DMA1_Stream4
#define DEBUG_TX_DMAx_Streamx_IRQn        DMA1_Stream4_IRQn
#define DEBUG_TX_DMAx_Streamx_IRQHandler  DMA1_Stream4_IRQHandler

#endif // DEBUG_UART_H_INCLUDED
