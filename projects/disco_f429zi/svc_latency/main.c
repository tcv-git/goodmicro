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

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_simple_gpio.h"
#include "peripheral_enable.h"

#define GREEN_ON   PIN13_HI
#define GREEN_OFF  PIN13_LO
#define RED_ON     PIN14_HI
#define RED_OFF    PIN14_LO

int main(void)
{
    peripheral_enable(&RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);
    GPIO_output_push_pull_slow(GPIOG, (PIN13 | PIN14));

    for (;;)
    {
        GPIO_set_reset(GPIOG, GREEN_ON);
        __asm volatile("svc 0");
    }
}

void SVC_Handler(void)
{
    GPIO_set_reset(GPIOG, GREEN_OFF);
}
