// buttons_leds.c
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

#include <stdbool.h>
#include "stm32h7xx.h"
#include "stm32h7xx_simple_gpio.h"
#include "peripheral_enable.h"
#include "buttons_leds.h"

void buttons_init(void)
{
    peripheral_enable(&RCC->AHB4ENR, RCC_AHB4ENR_GPIOCEN);

    GPIO_input(GPIOC, PIN13);
}

bool button_pressed(void)
{
    return ((GPIOC->IDR & PIN13) != 0);
}

void leds_init(void)
{
    peripheral_enable(&RCC->AHB4ENR, (RCC_AHB4ENR_GPIOBEN | RCC_AHB4ENR_GPIOEEN));

    GPIO_output_push_pull_slow(GPIOB, (PIN0 | PIN14));
    GPIO_output_push_pull_slow(GPIOE, PIN1);
}

void led_red(bool on)
{
  GPIO_set_reset(GPIOB, (on ? PIN14_HI : PIN14_LO));
}

void led_amber(bool on)
{
  GPIO_set_reset(GPIOE, (on ? PIN1_HI : PIN1_LO));
}

void led_green(bool on)
{
  GPIO_set_reset(GPIOB, (on ? PIN0_HI : PIN0_LO));
}
