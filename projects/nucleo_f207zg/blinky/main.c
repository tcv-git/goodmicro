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

#include "stm32f2xx_simple_gpio.h"
#include "delay.h"

int main(void)
{
  RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN);
  (void)RCC->AHB1ENR;

  GPIO_output_push_pull_slow(GPIOB, PIN7);
  GPIO_input(GPIOC, PIN13);

  for (;;)
  {
    GPIO_set_reset(GPIOB, PIN7_HI);
    DELAY_MS((GPIOC->IDR & PIN13) ? 400 : 150);
    GPIO_set_reset(GPIOB, PIN7_LO);
    DELAY_MS((GPIOC->IDR & PIN13) ? 400 : 150);
  }
}
