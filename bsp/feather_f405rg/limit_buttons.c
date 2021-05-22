// limit_buttons.c
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

#include "stm32f4xx.h"
#include "stm32f4xx_simple_gpio.h"
#include "limit_buttons.h"

#define PORTS_ENABLE    (RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN)

#define BUTTON_20_PORT  GPIOC
#define BUTTON_30_PORT  GPIOC
#define BUTTON_40_PORT  GPIOC
#define BUTTON_50_PORT  GPIOB
#define BUTTON_60_PORT  GPIOB
#define BUTTON_70_PORT  GPIOC

#define BUTTON_20_PIN   PIN1
#define BUTTON_30_PIN   PIN2
#define BUTTON_40_PIN   PIN3
#define BUTTON_50_PIN   PIN9
#define BUTTON_60_PIN   PIN8
#define BUTTON_70_PIN   PIN6

void limit_buttons_init(void)
{
  RCC->AHB1ENR |= PORTS_ENABLE;
  (void)RCC->AHB1ENR;

  GPIO_input_pull_down(BUTTON_20_PORT, BUTTON_20_PIN);
  GPIO_input_pull_down(BUTTON_30_PORT, BUTTON_30_PIN);
  GPIO_input_pull_down(BUTTON_40_PORT, BUTTON_40_PIN);
  GPIO_input_pull_down(BUTTON_50_PORT, BUTTON_50_PIN);
  GPIO_input_pull_down(BUTTON_60_PORT, BUTTON_60_PIN);
  GPIO_input_pull_down(BUTTON_70_PORT, BUTTON_70_PIN);


  GPIO_input_pull_down(GPIOB, (PIN8 | PIN9));
  GPIO_input_pull_down(GPIOC, (PIN1 | PIN2 | PIN3 | PIN6));
}

unsigned int get_buttons(void)
{
  return (((BUTTON_20_PORT->IDR & BUTTON_20_PIN) ? BUTTON_20 : 0)
        | ((BUTTON_30_PORT->IDR & BUTTON_30_PIN) ? BUTTON_30 : 0)
        | ((BUTTON_40_PORT->IDR & BUTTON_40_PIN) ? BUTTON_40 : 0)
        | ((BUTTON_50_PORT->IDR & BUTTON_50_PIN) ? BUTTON_50 : 0)
        | ((BUTTON_60_PORT->IDR & BUTTON_60_PIN) ? BUTTON_60 : 0)
        | ((BUTTON_70_PORT->IDR & BUTTON_70_PIN) ? BUTTON_70 : 0));
}

unsigned int get_limit(void)
{
  static unsigned char limit = 70;

  if      (BUTTON_20_PORT->IDR & BUTTON_20_PIN){ limit = 20; }
  else if (BUTTON_30_PORT->IDR & BUTTON_30_PIN){ limit = 30; }
  else if (BUTTON_40_PORT->IDR & BUTTON_40_PIN){ limit = 40; }
  else if (BUTTON_50_PORT->IDR & BUTTON_50_PIN){ limit = 50; }
  else if (BUTTON_60_PORT->IDR & BUTTON_60_PIN){ limit = 60; }
  else if (BUTTON_70_PORT->IDR & BUTTON_70_PIN){ limit = 70; }
  else                                     { /* no change */ }

  return limit;
}
