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

#include "stm32h7xx.h"
#include "stm32h7xx_simple_gpio.h"
#include "delay.h"

#define R 1
#define G 2
#define Y 4

static void leds(unsigned int in)
{
  uint32_t b = (((in & R) ? PIN14_HI : PIN14_LO) | ((in & G) ? PIN0_HI : PIN0_LO));
  uint32_t e =  ((in & Y) ? PIN1_HI : PIN1_LO);

  GPIO_set_reset(GPIOB, b);
  GPIO_set_reset(GPIOE, e);
}

int main(void)
{
  RCC->AHB4ENR |= (RCC_AHB4ENR_GPIOBEN | RCC_AHB4ENR_GPIOCEN | RCC_AHB4ENR_GPIOEEN);
  (void)RCC->AHB1ENR;

  GPIO_output_push_pull_slow(GPIOB, (PIN0 | PIN14));
  GPIO_output_push_pull_slow(GPIOE, PIN1);
  GPIO_input(GPIOC, PIN13);

  unsigned int i = 0;

  for (;;)
  {
    switch (i)
    {
      case 0: leds(0    ); DELAY_MS(150); break;
      case 1: leds(R    ); DELAY_MS(150); break;
      case 2: leds(R|Y  ); DELAY_MS( 50); break;
      case 3: leds(  Y  ); DELAY_MS(150); break;
      case 4: leds(  Y|G); DELAY_MS( 50); break;
      case 5: leds(    G); DELAY_MS(150); break;
    }

    i += ((GPIOC->IDR & PIN13) ? 7 : 5);
    i %= 6;
  }
}
