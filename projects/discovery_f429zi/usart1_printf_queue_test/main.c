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

#include "delay.h"
#include "usart1_printf_queue.h"
#include "lcd.h"
#include "lcd_text.h"

int main(void)
{
  usart1_printf_init(115200);

  lcd_init();
  lcd_text_mask(0, 0, 40, 40);

  unsigned int i = 0;

  for (;; i++)
  {
    lcd_printf    ("%u\n", i);
    usart1_printf ("%u\n", i);

    DELAY_MS (100);
  }
}
