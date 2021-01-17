// udiv64.h
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

#ifndef UDIV64_H_INCLUDED
#define UDIV64_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* assembly function should not be called directly */
uint64_t __attribute__((const)) udiv64i (uint64_t, uint32_t, uint32_t);

/* returns (dividend/divisor) rounding down */
/* gets exponentially slower as divisor approaches (1<<32) */
static inline __attribute__((const,always_inline)) uint64_t udiv64 (uint64_t dividend, uint32_t divisor)
{
  uint64_t quotient = (dividend / divisor);

  if (__builtin_constant_p (quotient))
  {
    return quotient;
  }
  else if (__builtin_constant_p (divisor))
  {
    return udiv64i (dividend, divisor, ((1uLL << 32) / divisor));
  }
  else
  {
    return udiv64i (dividend, divisor, (0xFFFFFFFFu / divisor));
  }
}

#ifdef __cplusplus
}
#endif

#endif /* UDIV64_H_INCLUDED */
