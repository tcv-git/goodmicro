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

#include "stm32h7xx.h"
#include "stm32h7xx_simple_gpio.h"

#define DMAMUX1_CxCR_DMAREQ_ID_USART1_TX  42
#define DMAMUX1_CxCR_DMAREQ_ID_USART3_TX  46

#ifndef ALT_DEBUG

#define DEBUG_TX_AHBxENR                  AHB4ENR
#define DEBUG_TX_AHBxENR_GPIOxEN          RCC_AHB4ENR_GPIODEN
#define DEBUG_TX_GPIOx                    GPIOD
#define DEBUG_TX_PINx                     PIN8
#define DEBUG_TX_AFx                      AF7

#define DEBUG_UART_APBx_ENR               APB1LENR
#define DEBUG_UART_APBx_ENR_UARTxEN       RCC_APB1LENR_USART3EN
#define DEBUG_UART_APBx_RSTR              APB1LRSTR
#define DEBUG_UART_APBx_RSTR_UARTxRST     RCC_APB1LRSTR_USART3RST
#define DEBUG_UARTx                       USART3

#define DEBUG_UART_IRQn                   USART3_IRQn
#define DEBUG_UART_IRQHandler             USART3_IRQHandler

#define DEBUG_UART_APBx_CLK               120000000u
#define DEBUG_BAUD                        115200u

#define DEBUG_DMA_AHBxENR                 AHB1ENR
#define DEBUG_DMA_AHBxENR_DMAxEN          RCC_AHB1ENR_DMA1EN
#define DEBUG_DMAx                        DMA1

#define DEBUG_TX_DMAMUXx_Channelx         DMAMUX1_Channel7
#define DEBUG_TX_DMAMUXx_CxCR_DMAREQ_ID   DMAMUX1_CxCR_DMAREQ_ID_USART3_TX

#define DEBUG_TX_DMA_xISR                 HISR
#define DEBUG_TX_DMA_xISR_TCIFx           DMA_HISR_TCIF7
#define DEBUG_TX_DMA_xISR_HTIFx           DMA_HISR_HTIF7
#define DEBUG_TX_DMA_xISR_TEIFx           DMA_HISR_TEIF7
#define DEBUG_TX_DMA_xISR_DMEIFx          DMA_HISR_DMEIF7
#define DEBUG_TX_DMA_xISR_FEIFx           DMA_HISR_FEIF7

#define DEBUG_TX_DMA_xIFCR                HIFCR
#define DEBUG_TX_DMA_xIFCR_CTCIFx         DMA_HIFCR_CTCIF7
#define DEBUG_TX_DMA_xIFCR_CHTIFx         DMA_HIFCR_CHTIF7
#define DEBUG_TX_DMA_xIFCR_CTEIFx         DMA_HIFCR_CTEIF7
#define DEBUG_TX_DMA_xIFCR_CDMEIFx        DMA_HIFCR_CDMEIF7
#define DEBUG_TX_DMA_xIFCR_CFEIFx         DMA_HIFCR_CFEIF7

#define DEBUG_TX_DMAx_Streamx             DMA1_Stream7
#define DEBUG_TX_DMAx_Streamx_IRQn        DMA1_Stream7_IRQn
#define DEBUG_TX_DMAx_Streamx_IRQHandler  DMA1_Stream7_IRQHandler

#else // ALT_DEBUG

#define DEBUG_TX_AHBxENR                AHB4ENR
#define DEBUG_TX_AHBxENR_GPIOxEN        RCC_AHB4ENR_GPIOBEN
#define DEBUG_TX_GPIOx                  GPIOB
#define DEBUG_TX_PINx                   PIN6
#define DEBUG_TX_AFx                    AF7

#define DEBUG_UART_APBx_ENR             APB2ENR
#define DEBUG_UART_APBx_ENR_UARTxEN     RCC_APB2ENR_USART1EN
#define DEBUG_UART_APBx_RSTR            APB2RSTR
#define DEBUG_UART_APBx_RSTR_UARTxRST   RCC_APB2RSTR_USART1RST
#define DEBUG_UARTx                     USART1

#define DEBUG_UART_APBx_CLK             120000000u
#define DEBUG_BAUD                      115200u

#endif // ALT_DEBUG
#endif // DEBUG_UART_H_INCLUDED
