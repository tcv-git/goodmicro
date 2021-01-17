// delay.h
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

#ifndef DELAY_H_INCLUDED
#define DELAY_H_INCLUDED

#if (defined(STM32F030x6) || defined(STM32F030x8) || defined(STM32F030xC) || defined(STM32F031x6) \
  || defined(STM32F038xx) || defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F051x8) \
  || defined(STM32F058xx) || defined(STM32F070x6) || defined(STM32F070xB) || defined(STM32F071xB) \
  || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F091xC) || defined(STM32F098xx))
#ifdef USE_CLOCK_CONFIG
#include "stm32f0xx_simple_clocks.h"
#endif
#endif

#if (defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) \
  || defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx))
#include "system_stm32f405-439.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Delay functions:

For a delay in seconds or milliseconds etc, C/C++ code should always use the
inline wrapper functions named in capitals.  If the argument is a compile time
constant and SYSTEM_CORE_CLOCK is defined then the conversion to clock cycles
will happen at compile time.  If it isn't then the conversion will happen at run
time, but the time taken to perform the conversion will happen after counting
has begun.

These functions never delay less than the requested period.  They typically
exceed it by 14-21 SYSTEM_CORE_CLOCK periods or ~100ns at 180MHz.

These functions are fully re-entrant: they can be called from interrupt handlers
or multi-threaded applications even if the interrupted code might itself be
using the same functions.

If a delay is interrupted by a context switch or hardware interrupt, then the
delay is accurately counted through the interruption, and will end at the same
time that it would have if there hadn't been an interruption (it will not "pick
up where it left off").  If an interrupted delay should have ended before the
interrupt returns or the task is rescheduled, then the delay function will
return immediately when the interruption ends.

A delay will be incorrectly increased if it is interrupted and not allowed to
run for longer than a whole period of the underlying clock.  Eg: using the
32-bit debug cycle counter and running at 180MHz this is ~23 seconds; using the
24-bit SysTick counter and running at 64MHz this is 262ms.

*/

void delay_s           (unsigned int);
void delay_ms          (unsigned int);
void delay_us          (unsigned int);
void delay_100_ns      (unsigned int);
void delay_sysclk_long (unsigned long long int);
void delay_sysclk      (unsigned int);

#if defined(__GNUC__) && defined(SYSTEM_CORE_CLOCK) && (SYSTEM_CORE_CLOCK != 0)

static inline void __attribute__((always_inline)) DELAY_S(unsigned int seconds)
{
  unsigned long long int product = ((unsigned long long int)seconds * SYSTEM_CORE_CLOCK);

  if (__builtin_constant_p(product))
  {
    if (product < (1uLL << 32))
    {
      delay_sysclk(product);
    }
    else
    {
      delay_sysclk_long(product);
    }
  }
  else
  {
    delay_s(seconds);
  }
}

static inline void __attribute__((always_inline)) DELAY_MS(unsigned int milliseconds)
{
  unsigned long long int product = (((unsigned long long int)milliseconds * SYSTEM_CORE_CLOCK) + 999);

  if (__builtin_constant_p(product))
  {
    if (product < (1000uLL << 32))
    {
      delay_sysclk(product / 1000);
    }
    else
    {
      delay_sysclk_long(product / 1000);
    }
  }
  else
  {
    delay_ms(milliseconds);
  }
}

static inline void __attribute__((always_inline)) DELAY_US(unsigned int microseconds)
{
  unsigned long long int product = (((unsigned long long int)microseconds * SYSTEM_CORE_CLOCK) + 999999);

  if (__builtin_constant_p(product))
  {
    if (product < (1000000uLL << 32))
    {
      delay_sysclk(product / 1000000);
    }
    else
    {
      delay_sysclk_long(product / 1000000);
    }
  }
  else
  {
    delay_us(microseconds);
  }
}

static inline void __attribute__((always_inline)) DELAY_100_NS(unsigned int t)
{
  unsigned long long int product = (((unsigned long long int)t * SYSTEM_CORE_CLOCK) + 9999999);

  if (__builtin_constant_p(product))
  {
    if (product < (10000000uLL << 32))
    {
      delay_sysclk(product / 10000000);
    }
    else
    {
      delay_sysclk_long(product / 10000000);
    }
  }
  else
  {
    delay_100_ns(t);
  }
}

#else // defined(__GNUC__) && defined(SYSTEM_CORE_CLOCK) && (SYSTEM_CORE_CLOCK != 0)

#ifndef SYSTEM_CORE_CLOCK
#warning SYSTEM_CORE_CLOCK is not defined, code size will be greater and short delays will be less accurate
// if system core clock changes at run-time or is not known at compile time then
// define SYSTEM_CORE_CLOCK to 0 to avoid this warning
#endif

#define DELAY_S       delay_s
#define DELAY_MS      delay_ms
#define DELAY_US      delay_us
#define DELAY_100_NS  delay_100_ns

#endif // defined(__GNUC__) && defined(SYSTEM_CORE_CLOCK) && (SYSTEM_CORE_CLOCK != 0)

#ifdef __cplusplus
}
#endif

#endif /* DELAY_H_INCLUDED */
