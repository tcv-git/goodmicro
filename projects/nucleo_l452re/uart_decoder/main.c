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

#define COUNTOF(A) ((sizeof A)/sizeof(A[0]))

static uint16_t event_queue_buffer[1024];
static uint8_t  write_buffer[20 * 1024];

int main(void)
{
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

  event_queue_init(event_queue_buffer, COUNTOF(event_queue_buffer));
  uart_rx_init(USART1);
  uart_rx_init(USART3);
  uart_rx_init(UART4);
  NVIC_EnableIRQ(USART1_IRQn);
  NVIC_EnableIRQ(USART3_IRQn);
  NVIC_EnableIRQ(UART4_IRQn);

  uart_write_init();
  write_buffer_init(write_buffer, sizeof write_buffer);

  for (;;)
  {
    uint16_t event = event_queue_get();

    enum event_type type = event_get_type(event);
    uint_fast8_t channel = event_get_channel(event);
    uint8_t data = event_get_data(event);

    switch (type)
    {
      case EVENT_HW_TIMEOUT:
        write_buffer_printf("hw timeout on %u\r\n", (unsigned int)channel);
        break;

      case EVENT_DATA:
        if ((data >= 0x20) && (data <= 0x7E))
        {
          write_buffer_printf("data '%c' on %u\r\n", (int)data, (unsigned int)channel);
        }
        else
        {
          write_buffer_printf("data 0x%02X on %u\r\n", (unsigned int)data, (unsigned int)channel);
        }
        break;

      case EVENT_MUX_OVERRUN:
        write_buffer_printf("event queue overrun\r\n");
        break;

      case EVENT_HW_OVERRUN:
        write_buffer_printf("hw overrun on %u\r\n", (unsigned int)channel);
        break;

      case EVENT_NOISE_ERROR:
        write_buffer_printf("noise error on %u\r\n", (unsigned int)channel);
        break;

      case EVENT_FRAMING_ERROR:
        write_buffer_printf("framing error on %u\r\n", (unsigned int)channel);
        break;

      case EVENT_PARITY_ERROR:
        write_buffer_printf("parity error on %u\r\n", (unsigned int)channel);
        break;

      default: // must be EVENT_NO_DATA
        break;
    }

    write_buffer_poll();
  }
}


void USART1_IRQHandler(void)
{
  uart_rx_irq_handler(USART1, 1);
}

void USART3_IRQHandler(void)
{
  uart_rx_irq_handler(USART3, 2);
}

void UART4_IRQHandler(void)
{
  uart_rx_irq_handler(UART4, 3);
}
