// main.c
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/software/goodmicro

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

uint64_t __attribute__((noinline)) call_udiv64(uint64_t dividend, uint32_t divisor);
uint64_t __attribute__((noinline)) call_udiv64_0(uint64_t dividend);
uint64_t __attribute__((noinline)) call_udiv64_1(uint64_t dividend);
uint64_t __attribute__((noinline)) call_udiv64_2(uint64_t dividend);
uint64_t __attribute__((noinline)) call_udiv64_999(uint64_t dividend);
uint64_t __attribute__((noinline)) call_udiv64_max_m2(uint64_t dividend);
uint64_t __attribute__((noinline)) call_udiv64_max_m1(uint64_t dividend);
uint64_t __attribute__((noinline)) call_udiv64_max(uint64_t dividend);

int main (void)
{
  debug_uart_init();

  hwrand_init ();

  unsigned int count = 0;

  for (;;)
  {
    unsigned long long dividend = ((((unsigned long long)hwrand32 ()) << 32) | hwrand32 ());
    unsigned int       divisor  = hwrand32 ();

    if (divisor)
    {
      unsigned long long int result = call_udiv64(dividend, divisor);

      unsigned long long int quotient = (dividend / divisor);  // this uses the compiler's own long division function

      if (result != quotient)
      {
        debug_printf("ERROR: (%llu / %u) = %llu, not %llu\n", dividend, divisor, quotient, result);
        for (;;);
      }

      count++;

      if ((count % 1000) == 0)
      {
        debug_printf("%u runs correct\n", count);
      }
    }
  }
}

uint64_t call_udiv64(uint64_t dividend, uint32_t divisor)
{
  return udiv64(dividend, divisor);
}

// these are not called but here so that the disassembly can be inspected
uint64_t call_udiv64_0      (uint64_t dividend){ return udiv64(dividend,   0); }
uint64_t call_udiv64_1      (uint64_t dividend){ return udiv64(dividend,   1); }
uint64_t call_udiv64_2      (uint64_t dividend){ return udiv64(dividend,   2); }
uint64_t call_udiv64_999    (uint64_t dividend){ return udiv64(dividend, 999); }
uint64_t call_udiv64_max_m2 (uint64_t dividend){ return udiv64(dividend, (UINT32_MAX - 2)); }
uint64_t call_udiv64_max_m1 (uint64_t dividend){ return udiv64(dividend, (UINT32_MAX - 1)); }
uint64_t call_udiv64_max    (uint64_t dividend){ return udiv64(dividend, UINT32_MAX); }
