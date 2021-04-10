// main.c
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/software/goodmicro

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

#include "lcd.h"
#include "lcd_text.h"
#include "hwrand.h"
#include "bitpool.h"

static void bitpool_free_test(void)
{
  unsigned int argument = (hwrand32() % 32);
  unsigned int initial = (hwrand32() & ~(1u << argument));
  unsigned int expected_final = (initial | (1u << argument));

  volatile unsigned int control = initial;

  bitpool_free(&control, argument);

  unsigned int actual_final = control;

  if (actual_final != expected_final)
  {
    lcd_printf("%08X,%d->%08X expected\n", initial, argument, expected_final);
    lcd_printf("%08X,%d->%08X actual\n"  , initial, argument,   actual_final);
    for(;;);
  }
}

int main (void)
{
  lcd_init();
  lcd_text_mask(0, 0, 40, 40);

  hwrand_init ();

  unsigned int i = 0;

  for (;; i++)
  {
    lcd_printf("%u bitpool_free correct\n", i);

    bitpool_free_test();
  }
}
