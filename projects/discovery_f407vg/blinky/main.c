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

#include "stm32f4xx_simple_gpio.h"
#include "delay.h"

#define GREEN_ON   PIN12_HI
#define GREEN_OFF  PIN12_LO
#define ORANGE_ON  PIN13_HI
#define ORANGE_OFF PIN13_LO
#define RED_ON     PIN14_HI
#define RED_OFF    PIN14_LO
#define BLUE_ON    PIN15_HI
#define BLUE_OFF   PIN15_LO


int main(void)
{
  RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIODEN);
  (void)RCC->AHB1ENR;

  GPIO_output_push_pull_slow(GPIOD, (PIN12 | PIN13 | PIN14 | PIN15));
  GPIO_input(GPIOA, PIN0);

  for (;;)
  {
    GPIO_set_reset(GPIOD, (GREEN_ON | RED_OFF));
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
    GPIO_set_reset(GPIOD, (BLUE_ON | ORANGE_OFF));
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
    GPIO_set_reset(GPIOD, (RED_ON | GREEN_OFF));
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
    GPIO_set_reset(GPIOD, (ORANGE_ON | BLUE_OFF));
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
  }
}
