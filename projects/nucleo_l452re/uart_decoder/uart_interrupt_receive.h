// UART interrupt receiver
// Copyright Green Energy Options Ltd.

#ifndef UART_INTERRUPT_RECEIVE_H_INCLUDED
#define UART_INTERRUPT_RECEIVE_H_INCLUDED

#include "stm32l4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

void uart_rx_init(USART_TypeDef *uart);
void uart_rx_irq_handler(USART_TypeDef *uart, uint_fast8_t channel);

#ifdef __cplusplus
}
#endif

#endif // UART_INTERRUPT_RECEIVE_H_INCLUDED
