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
#include "stm32f4xx.h"
#include "stm32f4xx_simple_gpio.h"
#include "system_stm32f405-439.h"
#include "debug_printf.h"

#define GPIOx                   GPIOA
#define PINx                    PIN9
#define AFx                     AF7
#define AHBxENR                 AHB1ENR
#define RCC_AHBxENR_GPIOxEN     RCC_AHB1ENR_GPIOAEN

#define UARTx                   USART1
#define APBxENR                 APB2ENR
#define APBxRSTR                APB2RSTR
#define RCC_APBxENR_UARTxEN     RCC_APB2ENR_USART1EN
#define RCC_APBxRSTR_UARTxRST   RCC_APB2RSTR_USART1RST

#define APBx_CLK                APB2_CLK
#define DEBUG_BAUD              115200u


void debug_uart_init(void)
{
  RCC->APBxRSTR |=  RCC_APBxRSTR_UARTxRST;
  RCC->APBxENR  |=  RCC_APBxENR_UARTxEN;
  (void)RCC->APBxENR;
  RCC->APBxRSTR &= ~RCC_APBxRSTR_UARTxRST;
  (void)RCC->APBxRSTR;

  RCC->AHBxENR  |=  RCC_AHBxENR_GPIOxEN;
  (void)RCC->AHBxENR;

  GPIO_alternate_push_pull_slow(GPIOx, PINx, AFx);

  UARTx->CR1 = 0;
  UARTx->CR2 = 0;
  UARTx->CR3 = 0;
  UARTx->BRR = ((APBx_CLK + (DEBUG_BAUD / 2)) / DEBUG_BAUD);
  UARTx->CR1 = (USART_CR1_TE | USART_CR1_UE);
}

static void internal_putc(unsigned char c)
{
  if ((UARTx->CR1 & USART_CR1_UE) == USART_CR1_UE)
  {
    while ((UARTx->SR & USART_SR_TXE) != USART_SR_TXE);

    UARTx->DR = c;
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
