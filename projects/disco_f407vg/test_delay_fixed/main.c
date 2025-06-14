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

#include <stdint.h>
#include "debug_printf.h"
#include "rng.h"

//#define CLK  84000000uLL
//#define CLK 168000000uLL
//#define CLK 176947200uLL
#define CLK 180000000uLL

unsigned long long int delay_s (unsigned int);
unsigned long long int delay_ms(unsigned int);
unsigned long long int delay_us(unsigned int);
unsigned long long int delay_ns(unsigned int);

int main (void)
{
  debug_uart_init();

  rng_init ();

  unsigned int count = 0;

  for (;;)
  {
    unsigned int argument = rng_rand32 ();

    unsigned long long int cycles_s  = (((argument * CLK)            )             );
    unsigned long long int cycles_ms = (((argument * CLK) +       999) /       1000);
    unsigned long long int cycles_us = (((argument * CLK) +    999999) /    1000000);
    unsigned long long int cycles_ns = (((argument * CLK) + 999999999) / 1000000000);

    unsigned long long int result_s  = delay_s (argument);
    unsigned long long int result_ms = delay_ms(argument);
    unsigned long long int result_us = delay_us(argument);
    unsigned long long int result_ns = delay_ns(argument);

    if (result_s  != cycles_s ){ debug_printf("s  %u %llu %llu\n", argument, cycles_s , result_s ); }
    if (result_ms != cycles_ms){ debug_printf("ms %u %llu %llu\n", argument, cycles_ms, result_ms); }
    if (result_us != cycles_us){ debug_printf("us %u %llu %llu\n", argument, cycles_us, result_us); }
    if (result_ns != cycles_ns){ debug_printf("ns %u %llu %llu\n", argument, cycles_ns, result_ns); }

    count++;

    if ((count % 10000) == 0)
    {
      debug_printf("count %u\n", count);
    }
  }
}
