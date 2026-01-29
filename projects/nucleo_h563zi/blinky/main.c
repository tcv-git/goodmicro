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

#include "delay.h"
#include "buttons_leds.h"

int main(void)
{
  buttons_init();
  leds_init();

  unsigned int i = 0;

  for (;;)
  {
    switch (i)
    {
      case 0:  led_red(false);  led_amber(false);  led_green(false);  DELAY_MS(150);  break;
      case 1:  led_red(true);   led_amber(false);  led_green(false);  DELAY_MS(150);  break;
      case 2:  led_red(true);   led_amber(true);   led_green(false);  DELAY_MS( 50);  break;
      case 3:  led_red(false);  led_amber(true);   led_green(false);  DELAY_MS(150);  break;
      case 4:  led_red(false);  led_amber(true);   led_green(true);   DELAY_MS( 50);  break;
      case 5:  led_red(false);  led_amber(false);  led_green(true);   DELAY_MS(150);  break;
    }

    i += (button_pressed() ? 5 : 1);
    i %= 6;
  }
}
