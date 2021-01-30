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
#include "stm32f4xx.h"
#include "system_stm32f405-439.h"
#include "delay.h"

void __attribute__((noinline)) call_DELAY_S_1(void);
void __attribute__((noinline)) call_DELAY_MS_1(void);
void __attribute__((noinline)) call_DELAY_US_1(void);
void __attribute__((noinline)) call_DELAY_NS_1(void);
void __attribute__((noinline)) call_DELAY_S_131(void);
void __attribute__((noinline)) call_DELAY_MS_131(void);
void __attribute__((noinline)) call_DELAY_US_131(void);
void __attribute__((noinline)) call_DELAY_NS_131(void);
void __attribute__((noinline)) call_DELAY_S_1000000(void);
void __attribute__((noinline)) call_DELAY_MS_1000000(void);
void __attribute__((noinline)) call_DELAY_US_1000000(void);
void __attribute__((noinline)) call_DELAY_NS_1000000(void);

int main (void)
{
  return 0;
}

void call_DELAY_S_1(void)
{
  DELAY_S(1);
}

void call_DELAY_MS_1(void)
{
  DELAY_MS(1);
}

void call_DELAY_US_1(void)
{
  DELAY_US(1);
}

void call_DELAY_NS_1(void)
{
  DELAY_NS(1);
}

void call_DELAY_S_131(void)
{
  DELAY_S(131);
}

void call_DELAY_MS_131(void)
{
  DELAY_MS(131);
}

void call_DELAY_US_131(void)
{
  DELAY_US(131);
}

void call_DELAY_NS_131(void)
{
  DELAY_NS(131);
}

void call_DELAY_S_1000000(void)
{
  DELAY_S(1000000);
}

void call_DELAY_MS_1000000(void)
{
  DELAY_MS(1000000);
}

void call_DELAY_US_1000000(void)
{
  DELAY_US(1000000);
}

void call_DELAY_NS_1000000(void)
{
  DELAY_NS(1000000);
}
