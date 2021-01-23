/* hwrand.c PUBLIC DOMAIN 2019 t.cortexm@purposeful.co.uk */

/* http:///www.purposeful.co.uk/software/cortexm */

/*
  I, Tom Vajzovic, am the author of this software and its documentation.
  I permanently abandon all intellectual property rights in them, including
  copyright, trademarks, design rights, database right, patents, and the right
  to be identified as the author.

  I am fairly certain that the software does what the documentation says it
  does, but I do not guarantee that it does, or that it does what you think it
  should.  I do not guarantee that it will not have undesirable side effects.

  You are free to use, modify and distribute this software as you please, but
  you do so at your own risk.  If you do not pass on this warning then you may
  be responsible for any problems encountered by those who obtain the software
  through you.
*/

#include "stm32f4xx.h"
#include "hwrand.h"

void hwrand_init (void)
{
  RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;
  __DSB();
  RNG->CR = RNG_CR_RNGEN;
}

unsigned int hwrand32 (void)
{
  while ((RNG->SR & RNG_SR_DRDY) != RNG_SR_DRDY);

  return RNG->DR;
}