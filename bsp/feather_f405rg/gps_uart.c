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

#include <stddef.h>
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_simple_gpio.h"
#include "system_stm32f405-439.h"
#include "delay.h"
#include "debug_printf.h"
#include "gps_uart.h"

/*
PB10 AF7 USART3 TX  (GPS RX)
PB11 AF7 USART3 RX  (GPS TX)
*/

#define INITIAL_BAUD    9600u
#define FINAL_BAUD    115200u

#define BAUD_MESSAGE   "\r\n\r\n$PMTK251,115200*1F\r\n"
#define SETUP_MESSAGE  "\r\n$PMTK314,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n$PMTK220,100*2F\r\n"

#define BUFFER_SIZE      256u
#define BUFFER_COUNT       8u

static          char         buffers[BUFFER_COUNT][BUFFER_SIZE];
static volatile uint32_t     buffer_control = 0;
static          unsigned int line_length    = 0;

static void gps_uart_rx(int c);

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

  send_message(BAUD_MESSAGE, ((sizeof BAUD_MESSAGE) - 1));

  DELAY_MS(20);

  USART3->CR1 = 0;
  USART3->BRR = ((APB1_CLK + (FINAL_BAUD / 2)) / FINAL_BAUD);
  USART3->SR  = 0;
  USART3->CR1 = (USART_CR1_UE | USART_CR1_TE);

  send_message(SETUP_MESSAGE, ((sizeof SETUP_MESSAGE) - 1));

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
      gps_uart_rx(-1);
      return;
    }

    else if ((sr & USART_SR_RXNE) == USART_SR_RXNE)
    {
      gps_uart_rx((unsigned char)USART3->DR);
    }

    else
    {
      return;
    }
  }
}

void gps_uart_rx(int c)
{
  if ((c == '\r') || (c == '\n') || (c == '\f') || (c == '\v') || (c == '\0'))
  {
    c = '\n';
  }
  else if (c == '\t')
  {
    c = ' ';
  }
  else if ((c < 0x20) || (c > 0x7E))
  {
    c = -1;
  }
  else
  {
    // printable
  }

  if (c < 0)
  {
    if (line_length > 0)
    {
      debug_printf("gps_uart discarding corrupted partial line");

      line_length = 0;
    }

    return;
  }

  if (line_length >= BUFFER_SIZE)
  {
    if (c == '\n')
    {
      debug_printf("gps_uart discarding too long line");

      line_length = 0;
    }

    return;
  }

  unsigned int filling_buffer = *(volatile uint16_t*)&buffer_control;

  if (c != '\n')
  {
    buffers[filling_buffer][line_length] = c;

    line_length++;

    return;
  }

  if (line_length == 0)
  {
    return;
  }

  buffers[filling_buffer][line_length] = '\0';

  unsigned int next_buffer = ((filling_buffer + 1) % BUFFER_COUNT);

  if (next_buffer != (buffer_control >> 16))
  {
    (*(volatile uint16_t*)&buffer_control) = next_buffer;
  }
  else
  {
    debug_printf("gps_uart discarding line because queue full");
  }

  line_length = 0;
}

char *gps_uart_get_line(void)
{
  uint32_t get_control = buffer_control;

  unsigned int filling_buffer = (get_control & 0xFFFF);

  unsigned int ready_buffer = (get_control >> 16);

  if (ready_buffer == filling_buffer)
  {
    return NULL;
  }
  else
  {
    return buffers[ready_buffer];
  }
}

void gps_uart_release_line(void)
{
  volatile uint16_t *controls = ((volatile uint16_t*)&buffer_control);

  controls[1] = ((controls[1] + 1) % BUFFER_COUNT);
}
