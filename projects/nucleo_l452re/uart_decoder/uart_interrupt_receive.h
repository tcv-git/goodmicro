// Poll UART receiver
// Copyright Green Energy Options Ltd.

#ifndef UART_POLL_H_INCLUDED
#define UART_POLL_H_INCLUDED

#include "stm32l4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

enum uart_status
{
  NO_DATA       = -1,
  TIMEOUT       = -2,
  OVERRUN       = -3,
  NOISE_ERROR   = -4,
  FRAMING_ERROR = -5,
  PARITY_ERROR  = -6,
};

void uart_poll_init(USART_TypeDef *uart);

int uart_poll(USART_TypeDef *uart);

#ifdef __cplusplus
}
#endif

#endif // UART_POLL_H_INCLUDED
