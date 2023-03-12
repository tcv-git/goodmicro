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

#include "stm32f0xx.h"
#include "stm32f0xx_simple_gpio.h"
#include "delay.h"

#define BLUE_ON    PIN8_HI
#define BLUE_OFF   PIN8_LO
#define GREEN_ON   PIN9_HI
#define GREEN_OFF  PIN9_LO

int main(void)
{
  RCC->AHBENR |= (RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN);
  (void)RCC->AHBENR;

  GPIO_output_push_pull_slow(GPIOC, (PIN8 | PIN9));
  GPIO_input(GPIOA, PIN0);

  for (;;)
  {
    GPIO_set_reset(GPIOC, (GREEN_ON | BLUE_OFF));
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
    GPIO_set_reset(GPIOC, (BLUE_ON | GREEN_OFF));
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
  }
}
