// debug_printf.h
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

#include <stdarg.h>
#include <stdio.h>
#include "debug_uart.h"
#include "debug_printf.h"

void debug_uart_init(void)
{
  RCC->DEBUG_UART_APBx_RSTR |=  DEBUG_UART_APBx_RSTR_UARTxRST;
  RCC->DEBUG_UART_APBx_ENR  |=  DEBUG_UART_APBx_ENR_UARTxEN;
  (void)RCC->DEBUG_UART_APBx_ENR;
  RCC->DEBUG_UART_APBx_RSTR &= ~DEBUG_UART_APBx_RSTR_UARTxRST;
  (void)RCC->DEBUG_UART_APBx_RSTR;

  RCC->DEBUG_TX_AHBxENR  |=  DEBUG_TX_AHBxENR_GPIOxEN;
  (void)RCC->DEBUG_TX_AHBxENR;

  GPIO_alternate_push_pull_slow(DEBUG_TX_GPIOx, DEBUG_TX_PINx, DEBUG_TX_AFx);

  DEBUG_UARTx->CR1 = 0;
  DEBUG_UARTx->CR2 = 0;
  DEBUG_UARTx->CR3 = 0;
  DEBUG_UARTx->BRR = ((DEBUG_UART_APBx_CLK + (DEBUG_BAUD / 2)) / DEBUG_BAUD);
  DEBUG_UARTx->CR1 = (USART_CR1_TE | USART_CR1_UE);
}

static void internal_putc(unsigned char c)
{
  if ((DEBUG_UARTx->CR1 & USART_CR1_UE) == USART_CR1_UE)
  {
    while ((DEBUG_UARTx->SR & USART_SR_TXE) != USART_SR_TXE);

    DEBUG_UARTx->DR = c;
  }
}

void debug_putc(unsigned char c)
{
  static unsigned char cr_already = 0;

  if ((c == '\n') && !cr_already)
  {
    internal_putc('\r');
  }

  internal_putc(c);

  cr_already = (c == '\r');
}

void debug_printf(const char *fmt, ...)
{
  char buffer[128];
  va_list ap;

  va_start(ap, fmt);
  int len = vsnprintf(buffer, sizeof buffer, fmt, ap);
  va_end(ap);

  if (len < 0)
  {
    len = 0;
  }

  if ((size_t)len >= sizeof buffer)
  {
    len = (sizeof buffer - 1);
  }

  int i;

  for (i = 0; i < len; i++)
  {
    debug_putc(buffer[i]);
  }
}
