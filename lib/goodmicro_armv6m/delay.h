// delay.h
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

#ifndef DELAY_H_INCLUDED
#define DELAY_H_INCLUDED

#ifndef SYSCLK
#error SYSCLK must be defined before including delay.h
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Delay in SYSCLK periods.
 *
 * Can be called from interrupt handlers, and can be interrupted without
 * increasing the requested delay as long as the interruption does not
 * last longer than SysTick->LOAD SYSCLK periods.
 */
void delay_sysclk (unsigned int count);

/* Use these macros when the parameter is a literal only, because there is
 * no instruction for long long division, it requires a library.
 *
 * The conversion from time units to counts will occur at compile time, and
 * the compiler will warn if overflow occurs (delay more than 0xFFFFFFFF
 * SYSCLK periods).
 */
#define DELAY_100_NS(t)     delay_sysclk((((unsigned long long)( t) * SYSCLK) + 9999999uLL) / 10000000uLL)
#define DELAY_US(us)        delay_sysclk((((unsigned long long)(us) * SYSCLK) +  999999uLL) /  1000000uLL)
#define DELAY_MS(ms)        delay_sysclk((((unsigned long long)(ms) * SYSCLK) +     999uLL) /     1000uLL)
#define DELAY_S(s)          delay_sysclk(  (unsigned long long)( s) * SYSCLK                             )

#ifdef __cplusplus
}
#endif

#endif /* DELAY_H_INCLUDED */
