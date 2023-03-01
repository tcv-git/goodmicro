// Poll UART receiver
// Copyright Green Energy Options Ltd.

#include "stm32l0xx.h"
#include "uart_poll.h"

#define UART_APBx_CLK   SYSTEM_CORE_CLOCK
#define BAUD_RATE       115200u


void uart_poll_init(USART_TypeDef *uart)
{
  uart->CR1 = 0;
  uart->CR2 = 0;
  uart->CR3 = 0;
  uart->BRR = ((UART_APBx_CLK + (BAUD_RATE / 2)) / BAUD_RATE);
  uart->CR1 = (USART_CR1_UE | USART_CR1_RE);
}

int uart_poll(USART_TypeDef *uart)
{
  uint32_t isr = uart->ISR;

  if ((isr & USART_ISR_ORE) != 0)
  {
    (void)uart->RDR;
    uart->ICR = (USART_ICR_ORECF | USART_ICR_FECF | USART_ICR_NECF | USART_ICR_PECF | USART_ICR_RTOCF);
    return OVERRUN;
  }

  else if ((isr & USART_ISR_FE) != 0)
  {
    (void)uart->RDR;
    uart->ICR = (USART_ICR_FECF | USART_ICR_NECF | USART_ICR_PECF | USART_ICR_RTOCF);
    return FRAMING_ERROR;
  }

  else if ((isr & USART_ISR_NE) != 0)
  {
    (void)uart->RDR;
    uart->ICR = (USART_ICR_NECF | USART_ICR_PECF | USART_ICR_RTOCF);
    return NOISE_ERROR;
  }

  else if ((isr & USART_ISR_PE) != 0)
  {
    (void)uart->RDR;
    uart->ICR = (USART_ICR_PECF | USART_ICR_RTOCF);
    return PARITY_ERROR;
  }

  else if ((isr & USART_ISR_RXNE) != 0)
  {
    uint8_t data = uart->RDR;
    uart->ICR = USART_ICR_RTOCF;
    return data;
  }

  else if ((isr & USART_ISR_RTOF) != 0)
  {
    // don't clear flag, keep returning this value until data arrives
    return TIMEOUT;
  }

  else
  {
    return NO_DATA;
  }
}
