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

#include "stm32f2xx.h"
#include "stm32f2xx_it.h"
#include "stm32f2xx_simple_gpio.h"


#define DEBUG_TX_AHBxENR                AHB1ENR
#define DEBUG_TX_AHBxENR_GPIOxEN        RCC_AHB1ENR_GPIODEN
#define DEBUG_TX_GPIOx                  GPIOD
#define DEBUG_TX_PINx                   PIN8
#define DEBUG_TX_AFx                    AF7

#define DEBUG_UART_APBx_ENR             APB1ENR
#define DEBUG_UART_APBx_ENR_UARTxEN     RCC_APB1ENR_USART3EN
#define DEBUG_UART_APBx_RSTR            APB1RSTR
#define DEBUG_UART_APBx_RSTR_UARTxRST   RCC_APB1RSTR_USART3RST
#define DEBUG_UARTx                     USART3
#define DEBUG_UART_IRQn                 USART3_IRQn
#define DEBUG_UART_IRQHandler           USART3_IRQHandler

#define DEBUG_UART_APBx_CLK             30000000u
#define DEBUG_BAUD                      115200u

#endif // DEBUG_UART_H_INCLUDED
