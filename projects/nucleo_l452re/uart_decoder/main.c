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
#include "stm32l4xx_simple_gpio.h"
#if 0
#include "delay.h"
#include "uart_dma_write.h"
#include "uart_poll.h"
#include "wb_printf.h"
#endif

int main(void)
{
#if 0
  uint8_t buffer[123];
#endif
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

#if 0
  uart_poll_init(USART1);
  uart_poll_init(USART3);
  uart_poll_init(UART4);

  uart_write_init();

  wb_init(buffer, sizeof buffer);
#endif

  for (;;)
  {
#if 0
    int b1 = uart_poll(USART1);  if (b1 != NO_DATA){ wb_printf("1: %i\n", b1); }
    int b3 = uart_poll(USART3);  if (b3 != NO_DATA){ wb_printf("3: %i\n", b3); }
    int b4 = uart_poll(UART4);   if (b4 != NO_DATA){ wb_printf("4: %i\n", b4); }
    wb_poll();
#endif
  }
}
