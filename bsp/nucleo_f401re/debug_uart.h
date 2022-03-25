// debug_uart.h
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/goodmicro/

/*
  I, Tom Vajzovic, am the author of this software and its documentation.
  I permanently abandon all intellectual property rights in them, including
  copyright, trademarks, design rights, database right, patents, and the right
  to be identified as the author.

  I am fairly certain that the software does what the documentation says it
  does, but I do not guarantee that it does, or that it does what you think it
  should.  I do not guarantee that it will not have undesirable side effects.

  You are free to use, modify and distribute this software as you please, but
  you do so at your own risk.  If you do not pass on this warning then you may
  be responsible for any problems encountered by those who obtain the software
  through you.
*/

#ifndef DEBUG_UART_H_INCLUDED
#define DEBUG_UART_H_INCLUDED

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_simple_gpio.h"

#define DEBUG_TX_AHBxENR                AHB1ENR
#define DEBUG_TX_AHBxENR_GPIOxEN        RCC_AHB1ENR_GPIOAEN
#define DEBUG_TX_GPIOx                  GPIOA
#define DEBUG_TX_PINx                   PIN2
#define DEBUG_TX_AFx                    AF7

#define DEBUG_UART_APBx_ENR             APB1ENR
#define DEBUG_UART_APBx_ENR_UARTxEN     RCC_APB1ENR_USART2EN
#define DEBUG_UART_APBx_RSTR            APB1RSTR
#define DEBUG_UART_APBx_RSTR_UARTxRST   RCC_APB1RSTR_USART2RST
#define DEBUG_UARTx                     USART2
#define DEBUG_UART_IRQn                 USART2_IRQn
#define DEBUG_UART_IRQHandler           USART2_IRQHandler

#define DEBUG_UART_APBx_CLK             21000000u
#define DEBUG_BAUD                        115200u

#endif // DEBUG_UART_H_INCLUDED
