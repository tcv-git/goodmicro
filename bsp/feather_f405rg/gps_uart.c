// gps_uart.c
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

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_simple_gpio.h"
#include "system_stm32f405-439.h"
#include "gps_uart.h"
#include "gps_protocol.h"

/*
PB10 AF7 USART3 TX  (GPS RX)
PB11 AF7 USART3 RX  (GPS TX)
*/

#define BAUD  9600


void gps_uart_init(void)
{
  RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  (void)RCC->AHB1ENR;

  GPIO_alternate_push_pull_slow(GPIOB, PIN11, AF7);

  USART3->CR1 = 0;
  USART3->CR2 = 0;
  USART3->CR3 = 0;
  USART3->BRR = ((APB1_CLK + (BAUD / 2)) / BAUD);
  USART3->CR1 = (USART_CR1_UE | USART_CR1_RE | USART_CR1_RXNEIE);

  NVIC_EnableIRQ(USART3_IRQn);
}

void USART3_IRQHandler(void)
{
  for (;;)
  {
    uint32_t sr = USART3->SR;

    if ((sr & (USART_SR_ORE | USART_SR_NE | USART_SR_FE | USART_SR_PE)) != 0)
    {
      (void)USART3->DR;
      (void)USART3->DR;
      gps_protocol_flush();
      return;
    }

    else if ((sr & USART_SR_RXNE) == USART_SR_RXNE)
    {
      gps_protocol_rx(USART3->DR);
    }

    else
    {
      return;
    }
  }
}
