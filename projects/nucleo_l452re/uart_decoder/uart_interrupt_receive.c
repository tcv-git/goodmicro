// UART interrupt receiver
// Copyright Green Energy Options Ltd.

#include "stm32l4xx.h"
#include "system_stm32l4xx.h"
#include "event_queue.h"
#include "uart_interrupt_receive.h"

#define UART_APBx_CLK   SystemCoreClock
#define BAUD_RATE       115200u


void uart_rx_init(USART_TypeDef *uart)
{
  uart->CR1 = USART_CR1_RXNEIE;
  uart->CR2 = 0;
  uart->CR3 = USART_CR3_EIE;
  uart->BRR = ((UART_APBx_CLK + (BAUD_RATE / 2)) / BAUD_RATE);
  uart->CR1 = (USART_CR1_RXNEIE | USART_CR1_UE | USART_CR1_RE);

  // FIXME enable receiver timeout
}

void uart_rx_irq_handler(USART_TypeDef *uart, uint_fast8_t channel)
{
  uint32_t isr = uart->ISR;

  if ((isr & USART_ISR_ORE) != 0)
  {
    (void)uart->RDR;
    uart->ICR = (USART_ICR_ORECF | USART_ICR_FECF | USART_ICR_NECF | USART_ICR_PECF | USART_ICR_RTOCF);
    event_queue_put(EVENT_HW_OVERRUN, channel, 0);
  }

  else if ((isr & USART_ISR_FE) != 0)
  {
    (void)uart->RDR;
    uart->ICR = (USART_ICR_FECF | USART_ICR_NECF | USART_ICR_PECF | USART_ICR_RTOCF);
    event_queue_put(EVENT_FRAMING_ERROR, channel, 0);
  }

  else if ((isr & USART_ISR_NE) != 0)
  {
    (void)uart->RDR;
    uart->ICR = (USART_ICR_NECF | USART_ICR_PECF | USART_ICR_RTOCF);
    event_queue_put(EVENT_NOISE_ERROR, channel, 0);
  }

  else if ((isr & USART_ISR_PE) != 0)
  {
    (void)uart->RDR;
    uart->ICR = (USART_ICR_PECF | USART_ICR_RTOCF);
    event_queue_put(EVENT_PARITY_ERROR, channel, 0);
  }

  else if ((isr & USART_ISR_RXNE) != 0)
  {
    uint8_t data = uart->RDR;
    uart->ICR = USART_ICR_RTOCF;
    event_queue_put(EVENT_DATA, channel, data);
  }

  else if ((isr & USART_ISR_RTOF) != 0)
  {
    uart->ICR = USART_ICR_RTOCF;
    event_queue_put(EVENT_HW_TIMEOUT, channel, 0);
  }

  else
  {
    // spurious interrupt (don't waste queue space with EVENT_NO_DATA)
  }
}
