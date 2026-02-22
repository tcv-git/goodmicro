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

#include <stddef.h>
#include "lcd.h"
#include "lcd_text.h"
#include "delay.h"
#include "atomic_test_and_set.h"
#include "struct_queue.h"

struct queued_int
{
    struct queued_int *next;
    int                i;
};

int main(void)
{
  lcd_init();
  lcd_text_mask(0, 0, 40, 40);

  lcd_printf("hello\n");

  struct queued_item * volatile head = NULL;

  struct queued_int a, b, c, d, e;

  a.i = 111;  queue_write(&head, (struct queued_item*)&a);
  b.i = 222;  queue_write(&head, (struct queued_item*)&b);
  c.i = 333;  queue_write(&head, (struct queued_item*)&c);

  struct queued_int *x;

  x = (struct queued_int*)queue_read(&head); if (x){ lcd_printf("%i\n", x->i); }else{ lcd_printf("null\n"); }
  x = (struct queued_int*)queue_read(&head); if (x){ lcd_printf("%i\n", x->i); }else{ lcd_printf("null\n"); }
  x = (struct queued_int*)queue_read(&head); if (x){ lcd_printf("%i\n", x->i); }else{ lcd_printf("null\n"); }
  x = (struct queued_int*)queue_read(&head); if (x){ lcd_printf("%i\n", x->i); }else{ lcd_printf("null\n"); }

  d.i = 444;  queue_write(&head, (struct queued_item*)&d);
  a.i = 555;  queue_write(&head, (struct queued_item*)&a);
  e.i = 667;  queue_write(&head, (struct queued_item*)&e);

  x = (struct queued_int*)queue_read(&head); if (x){ lcd_printf("%i\n", x->i); }else{ lcd_printf("null\n"); }
  x = (struct queued_int*)queue_read(&head); if (x){ lcd_printf("%i\n", x->i); }else{ lcd_printf("null\n"); }

  b.i = 777;  queue_write(&head, (struct queued_item*)&b);
  c.i = 888;  queue_write(&head, (struct queued_item*)&c);

  x = (struct queued_int*)queue_read(&head); if (x){ lcd_printf("%i\n", x->i); }else{ lcd_printf("null\n"); }
  x = (struct queued_int*)queue_read(&head); if (x){ lcd_printf("%i\n", x->i); }else{ lcd_printf("null\n"); }
  x = (struct queued_int*)queue_read(&head); if (x){ lcd_printf("%i\n", x->i); }else{ lcd_printf("null\n"); }
  x = (struct queued_int*)queue_read(&head); if (x){ lcd_printf("%i\n", x->i); }else{ lcd_printf("null\n"); }
  x = (struct queued_int*)queue_read(&head); if (x){ lcd_printf("%i\n", x->i); }else{ lcd_printf("null\n"); }
  x = (struct queued_int*)queue_read(&head); if (x){ lcd_printf("%i\n", x->i); }else{ lcd_printf("null\n"); }
  x = (struct queued_int*)queue_read(&head); if (x){ lcd_printf("%i\n", x->i); }else{ lcd_printf("null\n"); }
  x = (struct queued_int*)queue_read(&head); if (x){ lcd_printf("%i\n", x->i); }else{ lcd_printf("null\n"); }

  for (;;);
}
