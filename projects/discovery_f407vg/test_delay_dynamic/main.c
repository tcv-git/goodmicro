// main.c
// PUBLIC DOMAIN
// http:///www.purposeful.co.uk/software/goodmicro

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
#include "system_stm32f4xx.h"
#include "debug_printf.h"
#include "hwrand.h"

unsigned long long int delay_s (unsigned int);
unsigned long long int delay_ms(unsigned int);
unsigned long long int delay_us(unsigned int);
unsigned long long int delay_ns(unsigned int);

int main (void)
{
  debug_uart_init();

  hwrand_init ();

  unsigned int count = 0;

  for (;;)
  {
    unsigned int core_clock = hwrand32();
    unsigned int argument = hwrand32();

    unsigned long long int cycles_s  = (((1uLL * argument * core_clock)            )             );
    unsigned long long int cycles_ms = (((1uLL * argument * core_clock) +       999) /       1000);
    unsigned long long int cycles_us = (((1uLL * argument * core_clock) +    999999) /    1000000);
    unsigned long long int cycles_ns = (((1uLL * argument * core_clock) + 999999999) / 1000000000);

    SystemCoreClock = core_clock;

    unsigned long long int result_s  = delay_s (argument);
    unsigned long long int result_ms = delay_ms(argument);
    unsigned long long int result_us = delay_us(argument);
    unsigned long long int result_ns = delay_ns(argument);

    if (result_s  != cycles_s ){ debug_printf("s  %u %u %llu %llu\n", core_clock, argument, cycles_s , result_s ); }
    if (result_ms != cycles_ms){ debug_printf("ms %u %u %llu %llu\n", core_clock, argument, cycles_ms, result_ms); }
    if (result_us != cycles_us){ debug_printf("us %u %u %llu %llu\n", core_clock, argument, cycles_us, result_us); }
    if (result_ns != cycles_ns){ debug_printf("ns %u %u %llu %llu\n", core_clock, argument, cycles_ns, result_ns); }

    count++;

    if ((count % 10000) == 0)
    {
      debug_printf("count %u\n", count);
    }
  }
}
