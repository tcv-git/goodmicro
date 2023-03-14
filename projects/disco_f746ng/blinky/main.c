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

#include "stm32f7xx_simple_gpio.h"
#include "delay.h"

int main(void)
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
  (void)RCC->AHB1ENR;

  GPIO_output_push_pull_slow(GPIOI, PIN1);
  GPIO_input(GPIOI, PIN11);

  for (;;)
  {
    GPIO_set_reset(GPIOI, PIN1_HI);
    DELAY_MS((GPIOI->IDR & PIN11) ? 150 : 400);
    GPIO_set_reset(GPIOI, PIN1_LO);
    DELAY_MS((GPIOI->IDR & PIN11) ? 150 : 400);
  }
}
