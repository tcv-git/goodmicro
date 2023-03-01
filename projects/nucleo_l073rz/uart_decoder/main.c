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

#include "stm32l0xx.h"
#include "stm32l0xx_simple_gpio.h"
#include "delay.h"
#include "uart_dma_write.h"
#include "uart_poll.h"
#include "wb_printf.h"

int main(void)
{
  uint8_t buffer[123];
  /*
  Pinout:
  PA2  AF4 USART2_TX
  PB7  AF0 USART1_RX
  PA1  AF6 USART4_RX
  PD2  AF6 USART5_RX
  PC13 Button B1 active low
  PA5  LED LD2 (green) active high
  */

  RCC->IOPENR   |=  RCC_IOPENR_IOPAEN;
  RCC->IOPENR   |=  RCC_IOPENR_IOPBEN;
  RCC->IOPENR   |=  RCC_IOPENR_IOPDEN;
  RCC->APB2RSTR |=  RCC_APB2RSTR_USART1RST;
  RCC->APB1RSTR |=  RCC_APB1RSTR_USART4RST;
  RCC->APB1RSTR |=  RCC_APB1RSTR_USART5RST;
  RCC->APB2ENR  |=  RCC_APB2ENR_USART1EN;
  RCC->APB1ENR  |=  RCC_APB1ENR_USART4EN;
  RCC->APB1ENR  |=  RCC_APB1ENR_USART5EN;
  RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;
  RCC->APB1RSTR &= ~RCC_APB1RSTR_USART4RST;
  RCC->APB1RSTR &= ~RCC_APB1RSTR_USART5RST;

  GPIO_alternate_push_pull_slow(GPIOB, PIN7, AF0);
  GPIO_alternate_push_pull_slow(GPIOA, PIN1, AF6);
  GPIO_alternate_push_pull_slow(GPIOD, PIN2, AF6);

  uart_poll_init(USART1);
  uart_poll_init(USART4);
  uart_poll_init(USART5);

  uart_write_init();

  wb_init(buffer, sizeof buffer);

  for (;;)
  {
    int b1 = uart_poll(USART1);  if (b1 != NO_DATA){ wb_printf("1: %i\n", b1); }
    int b4 = uart_poll(USART4);  if (b4 != NO_DATA){ wb_printf("4: %i\n", b4); }
    int b5 = uart_poll(USART5);  if (b5 != NO_DATA){ wb_printf("5: %i\n", b5); }
    wb_poll();
  }
}
