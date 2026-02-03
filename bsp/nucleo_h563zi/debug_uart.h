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

#include "stm32h5xx.h"
#include "stm32h5xx_it.h"
#include "stm32h5xx_simple_gpio.h"

#define DEBUG_TX_AHBxENR                    AHB2ENR
#define DEBUG_TX_AHBxENR_GPIOxEN            RCC_AHB2ENR_GPIODEN
#define DEBUG_TX_GPIOx                      GPIOD
#define DEBUG_TX_PINx                       PIN8
#define DEBUG_TX_AFx                        AF7

#define DEBUG_RX_AHBxENR                    AHB2ENR
#define DEBUG_RX_AHBxENR_GPIOxEN            RCC_AHB2ENR_GPIODEN
#define DEBUG_RX_GPIOx                      GPIOD
#define DEBUG_RX_PINx                       PIN9
#define DEBUG_RX_AFx                        AF7

#define DEBUG_UART_APBx_ENR                 APB1LENR
#define DEBUG_UART_APBx_ENR_UARTxEN         RCC_APB1LENR_USART3EN
#define DEBUG_UART_APBx_RSTR                APB1LRSTR
#define DEBUG_UART_APBx_RSTR_UARTxRST       RCC_APB1LRSTR_USART3RST
#define DEBUG_UARTx                         USART3

#define DEBUG_UART_IRQn                     USART3_IRQn
#define DEBUG_UART_IRQHandler               USART3_IRQHandler

#define DEBUG_UART_APBx_CLK                 250000000u
#define DEBUG_BAUD                          115200u

#define DEBUG_DMA_AHBxENR                   AHB1ENR
#define DEBUG_DMA_AHBxENR_DMAxEN            RCC_AHB1ENR_GPDMA1EN
#define DEBUG_DMAx                          GPDMA1

#define DEBUG_TX_DMAx_Channelx              GPDMA1_Channel1
#define DEBUG_TX_DMAx_Channelx_IRQn         GPDMA1_Channel1_IRQn
#define DEBUG_TX_DMAx_Channelx_IRQHandler   GPDMA1_Channel1_IRQHandler
#define DEBUG_TX_DMAx_Channelx_CCR_REQSEL   26

#define DEBUG_RX_DMAx_Channelx              GPDMA1_Channel0
#define DEBUG_RX_DMAx_Channelx_IRQn         GPDMA1_Channel0_IRQn
#define DEBUG_RX_DMAx_Channelx_IRQHandler   GPDMA1_Channel0_IRQHandler
#define DEBUG_RX_DMAx_Channelx_CCR_REQSEL   25

#endif // DEBUG_UART_H_INCLUDED
