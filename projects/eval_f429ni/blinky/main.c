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

#define GREEN_ON   PIN6_LO
#define GREEN_OFF  PIN6_HI
#define ORANGE_ON  PIN7_LO
#define ORANGE_OFF PIN7_HI
#define RED_ON     PIN10_LO
#define RED_OFF    PIN10_HI
#define BLUE_ON    PIN12_LO
#define BLUE_OFF   PIN12_HI

int main(void)
{
  RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOGEN);
  (void)RCC->AHB1ENR;

  GPIO_output_push_pull_slow(GPIOG, (PIN6 | PIN7 | PIN10 | PIN12));
  GPIO_input(GPIOA, PIN0);

  for (;;)
  {
    GPIO_set_reset(GPIOG, (GREEN_ON  | ORANGE_OFF | RED_OFF | BLUE_OFF));
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
    GPIO_set_reset(GPIOG, (GREEN_OFF | ORANGE_ON  | RED_OFF | BLUE_OFF));
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
    GPIO_set_reset(GPIOG, (GREEN_OFF | ORANGE_OFF | RED_ON  | BLUE_OFF));
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
    GPIO_set_reset(GPIOG, (GREEN_OFF | ORANGE_OFF | RED_OFF | BLUE_ON ));
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
    GPIO_set_reset(GPIOG, (GREEN_OFF | ORANGE_OFF | RED_OFF | BLUE_OFF));
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
    DELAY_MS((GPIOA->IDR & PIN0) ? 150 : 400);
  }
}
