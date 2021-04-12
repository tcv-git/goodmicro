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

#include "i2c_master.h"
#include "alnum.h"
#include "delay.h"

int main(void)
{
  i2cm_init();

  alnum_init();

  for (;;)
  {
    alnum_green(0);

    DELAY_MS(300);

    for (unsigned int i = 1; i <= 9; i++)
    {
      alnum_green(i);

      DELAY_MS(150);
    }

    for (unsigned int i = 10; i <= 30; i++)
    {
      alnum_green(i);

      DELAY_MS(50);
    }

    for (unsigned int i = 30; i <= 99; i++)
    {
      alnum_red(i);

      DELAY_MS(50);
    }

    for (unsigned int i = 20; i <= 70; i += 10)
    {
      alnum_lim(i);

      DELAY_MS(500);
    }
  }
}
