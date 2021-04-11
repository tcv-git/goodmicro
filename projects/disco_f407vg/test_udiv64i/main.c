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

#include "debug_printf.h"
#include "hwrand.h"
#include "udiv64.h"

unsigned long long int test_udiv64i(unsigned long long int, unsigned int, unsigned int, unsigned int *);

int main (void)
{
  debug_uart_init();

  hwrand_init ();

  unsigned int count      = 0;
  unsigned int sum_cycles = 0;

  for (;;)
  {
    unsigned long long dividend = ((((unsigned long long)hwrand32 ()) << 32) | hwrand32 ());
    unsigned int       divisor  = hwrand32 ();

    if (divisor)
    {
      unsigned int reciprocal = ((divisor > 1) ? ((1uLL << 32) / divisor) : 0xFFFFFFFFu);
      unsigned int cycles;
      unsigned long long int result = test_udiv64i(dividend, divisor, reciprocal, &cycles);

      unsigned long long int quotient = (dividend / divisor);  // this uses the compiler's own long division function

      if (result != quotient)
      {
        debug_printf("ERROR: (%llu / %u) = %llu, not %llu\n", dividend, divisor, quotient, result);
        for (;;);
      }

      count      += 1;
      sum_cycles += cycles;

      if (count == 10000)
      {
        debug_printf("%u runs correct, average cycles %6u.%03u\n", count, (sum_cycles / count), (((sum_cycles % count) * 1000) / count));
        count      = 0;
        sum_cycles = 0;
      }
    }
  }
}
