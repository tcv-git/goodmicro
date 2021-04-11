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
#include "debug_printf.h"
#include "lcd.h"
#include "lcd_text.h"
#include "printf_queue.h"


static void uart_puts(const char *str)
{
  while (*str)
  {
    debug_putc(*str++);
  }
}

static int get_and_print(void)
{
  char *str = printf_queue_get();

  if (str)
  {
    uart_puts(str);
    printf_queue_free(str);
  }

  return !!str;
}

static void get_and_print_all(void)
{
  while (get_and_print());
}

static void get_and_print_n(unsigned int n)
{
  unsigned int i;

  for (i = 0; i < n; i++)
  {
    get_and_print();
  }
}

void test_printf(const char *format, ...) __attribute__((format(printf,1,2)));
void test_printf(const char *format, ...)
{
  va_list args;

  va_start(args, format);
  printf_queue_put(format, args);
  va_end(args);
}

int main (void)
{
  debug_uart_init();

  lcd_init();
  lcd_text_mask(0, 0, 40, 40);

  unsigned int i = 0;

  for (;; i++)
  {
    lcd_printf  ("%u\n", i);
    test_printf ("%u\n", i);

    DELAY_MS (250);

    if ((i % 20) == 0)
    {
      get_and_print_n(3);
    }

    if (i > 200)
    {
      get_and_print_all();
    }
  }
}
