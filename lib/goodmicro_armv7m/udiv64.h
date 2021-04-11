// udiv64.h
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

/*
  udiv64 performs unsigned integer division of a 64-bit value by a 32-bit one;
  the result is rounded towards zero.

  This function is much smaller and simpler than the general purpose division
  routines provided the compiler's runtime library.  It is also faster in many
  cases.

  If the divisor is a compile-time constant less than (1 << 16) then udiv64
  takes on average about 40 processor cycles.

  If the divisor is a compile-time constant less than (1 << 24) then udiv64
  takes on average about 50 processor cycles.

  If the divisor is a compile-time constant using all 32 bits then udiv64 takes
  on average about 140 processor cycles.

  If the divisor is not a compile-time constant then it takes about 10 cycles
  longer than the above times.

  If the divisor is zero then the behaviour is undefined.  In reality this means
  it will either loop around forever without returning, return an incorrect
  value, or execute a hardware instruction to divide by zero (which causes an
  exception if it is enabled).

  This code does not require to be linked with the runtime library's divide-by-
  zero handling code.  This avoids significantly increasing program size to deal
  with a situation that should never occur in a well-written program.
*/

#ifndef UDIV64_H_INCLUDED
#define UDIV64_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// assembly function should not be called directly
uint64_t __attribute__((const)) udiv64i(uint64_t, uint32_t, uint32_t);

// returns (dividend / divisor) rounding down
// gets exponentially slower as divisor approaches UINT32_MAX
static inline __attribute__((const,always_inline)) uint64_t udiv64(uint64_t dividend, uint32_t divisor)
{
  uint64_t quotient = (dividend / divisor);

  if (__builtin_constant_p(quotient))
  {
    return quotient;
  }
  else
  {
    uint64_t reciprocal = ((1uLL << 32) / divisor);

    if (__builtin_constant_p(reciprocal) && (reciprocal <= UINT32_MAX))
    {
      return udiv64i(dividend, divisor, reciprocal);
    }
    else
    {
      return udiv64i(dividend, divisor, (UINT32_MAX / divisor));
    }
  }
}

#ifdef __cplusplus
}
#endif

#endif /* UDIV64_H_INCLUDED */
