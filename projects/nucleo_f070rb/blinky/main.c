// main.c
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/goodmicro/

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

#include "stm32f0xx.h"
#include "stm32f0xx_simple_gpio.h"
#include "delay.h"

int main(void)
{
  RCC->AHBENR |= (RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN);
  (void)RCC->AHBENR;

  GPIO_output_push_pull_slow(GPIOA, PIN5);
  GPIO_input(GPIOC, PIN13);

  for (;;)
  {
    GPIO_set_reset(GPIOA, PIN5_HI);
    DELAY_MS((GPIOC->IDR & PIN13) ? 400 : 150);
    GPIO_set_reset(GPIOA, PIN5_LO);
    DELAY_MS((GPIOC->IDR & PIN13) ? 400 : 150);
  }
}
