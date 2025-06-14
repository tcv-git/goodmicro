// rng.c
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

#include "stm32h7xx.h"
#include "peripheral_enable.h"
#include "rng.h"

void rng_init (void)
{
  peripheral_reset_enable(&RCC->AHB2RSTR, &RCC->AHB2ENR, RCC_AHB2ENR_RNGEN);

  RNG->CR = RNG_CR_CED;
  RNG->CR = (RNG_CR_CED | RNG_CR_RNGEN);
}

unsigned int rng_rand32 (void)
{
  while ((RNG->SR & (RNG_SR_SECS | RNG_SR_CECS | RNG_SR_DRDY)) != RNG_SR_DRDY);

  return RNG->DR;
}
