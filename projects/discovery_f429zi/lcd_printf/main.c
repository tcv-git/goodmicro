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

#include <stdarg.h>
#include <stdio.h>
#include "lcd.h"
#include "display_text.h"
#include "delay.h"

static void lcd_printf(const char *fmt, ...) __attribute__ ((format (__printf__, 1, 2)));

static void lcd_printf(const char *fmt, ...)
{
  char buffer[128];
  va_list ap;

  va_start(ap, fmt);
  int len = vsnprintf(buffer, sizeof buffer, fmt, ap);
  va_end(ap);

  if (len < 0)
  {
    len = 0;
  }

  if ((size_t)len >= sizeof buffer)
  {
    len = (sizeof buffer - 1);
  }

  if (len > 0)
  {
    text_write ((const unsigned char *)buffer, len);
  }
}

int main(void)
{
  lcd_init();
  text_mask(0, 0, 40, 40);

  unsigned int i;

  for (i = 0;; i++)
  {
    lcd_printf("%u\n", i);
    DELAY_MS(100);
  }
}
