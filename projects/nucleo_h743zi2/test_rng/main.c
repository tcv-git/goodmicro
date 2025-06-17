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

  You may use, modify and distribute this software as you please, but you do
  so at your own risk.  If you do not pass on this warning then you may be
  responsible for any problems encountered by those who obtain the software
  through you.
*/

#include "stm32h7xx.h"
#include "stm32h7xx_simple_gpio.h"
#include "rng.h"
#include "debug_printf.h"
#include "delay.h"
#include "buttons_leds.h"

int main(void)
{
    buttons_init();
    leds_init();
    debug_uart_init();
    rng_init();

    for (;;)
    {
        unsigned int r = rng_rand32();

        debug_printf("%u\n", r);

        led_red   ((r >> 31) & 1);
        led_amber ((r >> 30) & 1);
        led_green ((r >> 29) & 1);

        DELAY_MS((r % (button_pressed() ? 201 : 951)) + 50);
    }
}
