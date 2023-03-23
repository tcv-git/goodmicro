// main.c
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
#include "measure_hse.h"
#include "debug_printf.h"

int main(void)
{
  debug_uart_init();

  debug_printf("hello\n");

  for (;;)
  {
    unsigned int i;

    for (i = 2; i < 32; i++)
    {
      RCC->CFGR = ((RCC->CFGR & ~RCC_CFGR_RTCPRE) | (RCC_CFGR_RTCPRE_0 * i));

      unsigned int hse = measure_hse();

      if (hse != 0)
      {
        debug_printf("%u, %u\n", i, hse);
      }
    }
  }
}
