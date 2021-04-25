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

#define DEBUG_TX_AHBxENR                AHB1ENR
#define DEBUG_TX_AHBxENR_GPIOxEN        RCC_AHB1ENR_GPIOCEN
#define DEBUG_TX_GPIOx                  GPIOC
#define DEBUG_TX_PINx                   PIN6
#define DEBUG_TX_AFx                    AF8

#define DEBUG_UART_APBx_ENR             APB2ENR
#define DEBUG_UART_APBx_ENR_UARTxEN     RCC_APB2ENR_USART6EN
#define DEBUG_UART_APBx_RSTR            APB2RSTR
#define DEBUG_UART_APBx_RSTR_UARTxRST   RCC_APB2RSTR_USART6RST
#define DEBUG_UARTx                     USART6
#define DEBUG_UART_APBx_CLK             APB2_CLK

#define DEBUG_BAUD                      115200u

#define DEBUG_DMAx_STREAMx_CHSELx       DMA2_S7CR_CHSEL_USART6_TX
#define DEBUG_DMAx_STREAMx              DMA2_Stream7
#define DEBUG_DMAx_STREAMx_IRQn         DMA2_Stream7_IRQn
#define DEBUG_DMAx_Streamx_IRQHandler   DMA2_Stream7_IRQHandler

#endif // DEBUG_UART_H_INCLUDED
