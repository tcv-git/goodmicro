// main.c
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/goodmicro/

/*
  I, Tom Vajzovic, am the author of this software and its documentation.
  I permanently abandon all intellectual property rights in them, including
  copyright, trademarks, design rights, database right, patents, and the right
  to be identified as the author.

  I am fairly certain that the software does what the documentation says it
  does, but I do not guarantee that it does, or that it does what you think it
  should.  I do not guarantee that it will not have undesirable side effects.

  You are free to use, modify and distribute this software as you please, but
  you do so at your own risk.  If you do not pass on this warning then you may
  be responsible for any problems encountered by those who obtain the software
  through you.
*/

#include "stm32l4xx.h"
#include "stm32l4xx_it.h"
#include "stm32l4xx_simple_gpio.h"
#include "uart_interrupt_receive.h"
#include "event_queue.h"
#include "write_buffer.h"
#include "uart_dma_write.h"
#include "terminal.h"
#include "crc.h"
#include "decoder.h"

#define COUNTOF(A) ((sizeof A)/sizeof(A[0]))

static uint16_t event_queue_buffer[1024];
static uint8_t  write_buffer[20 * 1024];
static uint8_t  decoder_buffers[3][20 * 1024];

struct decoder decoders[3];

static void uart_receivers_init(void);

int main(void)
{
  uart_write_init();
  write_buffer_init(write_buffer, sizeof write_buffer);

  uart_receivers_init();

  for (;;)
  {
    uint16_t event = event_queue_get();

    enum event_type type = event_get_type(event);
    uint_fast8_t channel = event_get_channel(event);
    uint8_t data = event_get_data(event);

    decoder_event(&decoders[channel], type, data);

    decoder_poll(&decoders[0]);
    decoder_poll(&decoders[1]);
    decoder_poll(&decoders[2]);

    write_buffer_poll();
  }
}

static void uart_receivers_init(void)
{
  crc_init();

  /*
  Pinout:
  PA2  AF7 USART2_TX
  PB7  AF7 USART1_RX
  PC11 AF7 USART3_RX
  PA1  AF8 UART4_RX
  PC13 Button B1 active low
  PA5  LED LD2 (green) active high
  */

  RCC->AHB2ENR   |=  RCC_AHB2ENR_GPIOAEN;
  RCC->AHB2ENR   |=  RCC_AHB2ENR_GPIOBEN;
  RCC->AHB2ENR   |=  RCC_AHB2ENR_GPIOCEN;
  RCC->APB2RSTR  |=  RCC_APB2RSTR_USART1RST;
  RCC->APB1RSTR1 |=  RCC_APB1RSTR1_USART3RST;
  RCC->APB1RSTR1 |=  RCC_APB1RSTR1_UART4RST;
  RCC->APB2ENR   |=  RCC_APB2ENR_USART1EN;
  RCC->APB1ENR1  |=  RCC_APB1ENR1_UART4EN;
  RCC->APB1ENR1  |=  RCC_APB1ENR1_USART3EN;
  RCC->APB2RSTR  &= ~RCC_APB2RSTR_USART1RST;
  RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_USART3RST;
  RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_UART4RST;

  GPIO_alternate_push_pull_slow(GPIOB, PIN7,  AF7);
  GPIO_alternate_push_pull_slow(GPIOC, PIN11, AF7);
  GPIO_alternate_push_pull_slow(GPIOA, PIN1,  AF8);

  decoder_init(&decoders[0], '<', (GREEN  | ON_BLACK), (BOLD | GREEN  | ON_BLACK), (RED | ON_WHITE), decoder_buffers[0], sizeof(decoder_buffers[0]));
  decoder_init(&decoders[1], '>', (BLUE   | ON_BLACK), (BOLD | BLUE   | ON_BLACK), (RED | ON_WHITE), decoder_buffers[1], sizeof(decoder_buffers[2]));
  decoder_init(&decoders[2], '^', (YELLOW | ON_BLACK), (BOLD | YELLOW | ON_BLACK), (RED | ON_WHITE), decoder_buffers[2], sizeof(decoder_buffers[3]));

  event_queue_init(event_queue_buffer, COUNTOF(event_queue_buffer));
  uart_rx_init(USART1);
  uart_rx_init(USART3);
  uart_rx_init(UART4);
  NVIC_EnableIRQ(USART1_IRQn);
  NVIC_EnableIRQ(USART3_IRQn);
  NVIC_EnableIRQ(UART4_IRQn);
}

void USART1_IRQHandler(void)
{
  uart_rx_irq_handler(USART1, 0);
}

void USART3_IRQHandler(void)
{
  uart_rx_irq_handler(USART3, 1);
}

void UART4_IRQHandler(void)
{
  uart_rx_irq_handler(UART4, 2);
}
