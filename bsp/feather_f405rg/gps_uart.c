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
#include "delay.h"
#include "gps_uart.h"
#include "gps_protocol.h"

/*
PB10 AF7 USART3 TX  (GPS RX)
PB11 AF7 USART3 RX  (GPS TX)
*/

#define INITIAL_BAUD   9600
#define FINAL_BAUD   115200

#define BAUD_MESSAGE  "\r\n\r\n$PMTK251,115200*1F\r\n"
#define SETUP_MESSAGE  "\r\n$PMTK314,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n$PMTK220,100*2F\r\n"

static void send_message(const char *message, unsigned int length)
{
  for (unsigned int i = 0; i < length; i++)
  {
    while ((USART3->SR & USART_SR_TXE) != USART_SR_TXE);

    USART3->DR = message[i];
  }

  while ((USART3->SR & USART_SR_TC) != USART_SR_TC);
}

void gps_uart_init(void)
{
  RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  (void)RCC->AHB1ENR;

  GPIO_alternate_push_pull_slow(GPIOB, (PIN10 | PIN11), AF7);

  USART3->CR1 = 0;
  USART3->CR2 = 0;
  USART3->CR3 = 0;
  USART3->BRR = ((APB1_CLK + (INITIAL_BAUD / 2)) / INITIAL_BAUD);
  USART3->SR  = 0;
  USART3->CR1 = (USART_CR1_UE | USART_CR1_TE);

  send_message(BAUD_MESSAGE, (sizeof BAUD_MESSAGE) - 1);

  DELAY_MS(20);

  USART3->CR1 = 0;
  USART3->BRR = ((APB1_CLK + (FINAL_BAUD / 2)) / FINAL_BAUD);
  USART3->SR  = 0;
  USART3->CR1 = (USART_CR1_UE | USART_CR1_TE);

  send_message(SETUP_MESSAGE, (sizeof SETUP_MESSAGE) - 1);

  USART3->CR1 = 0;
  USART3->SR  = 0;
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
