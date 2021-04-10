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

static void bitpool_alloc_test(void)
{
  int          expected_result = (31 - (hwrand32() % 33));
  unsigned int expected_final;
  unsigned int initial;

  if (expected_result < 0)
  {
    initial        = 0;
    expected_final = 0;
  }
  if (expected_result == 0)
  {
    initial        = 1;
    expected_final = 0;
  }
  else
  {
    expected_final = (hwrand32() >> (32 - expected_result));

    initial = (expected_final | (1u << expected_result));
  }

  volatile unsigned int control = initial;

  int actual_result = bitpool_alloc(&control);

  unsigned int actual_final = control;

  if ((actual_result != expected_result)
    || (actual_final != expected_final))
  {
    lcd_printf("%08X->%08X,%d expected\n", initial, expected_final, expected_result);
    lcd_printf("%08X->%08X,%d actual\n"  , initial,   actual_final,   actual_result);
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
    lcd_printf("%u bitpool_alloc correct\n", i);

    bitpool_alloc_test();
  }
}
