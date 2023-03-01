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

#include "delay.h"
#include "uart_dma_write.h"
#include "wb_printf.h"

#define N 1
#define M 10

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

  uart_write_init();

  wb_init(buffer, sizeof buffer);

  unsigned int i;

  for (i = 0;; i++)
  {
    if ((i % N) == 0)
    {
      wb_printf("%u\n", i);
    }

    if ((i % M) == 0)
    {
      wb_poll();
    }

    DELAY_MS(10);
  }
}
