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

#include <string.h>
#include "debug_printf.h"
#include "hwrand.h"
#include "bitqueue.h"

static void bitqueue_write_test(void)
{
  unsigned int initial_queue = 0;
  int          expected_result;
  unsigned int expected_final;

  unsigned char messages[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

  unsigned int message;
  unsigned int position;

  for (position = 0; position < 8; position++)
  {
    int message_index = ((hwrand32() % (20 - position)) - 4);

    if (message_index < 0)
    {
      break;
    }
    else
    {
      message = messages[message_index];

      memmove(&messages[message_index], &messages[message_index + 1], (16 - (message_index + position)));

      initial_queue |= (message << (position * 4));
    }
  }

  int argument_message_index = (hwrand32() % (16 - position));

  unsigned int argument_message = messages[argument_message_index];

  if (position == 8)
  {
    expected_result = -1;
    expected_final = initial_queue;
  }
  else
  {
    unsigned int initial_position = position;

    expected_final = initial_queue;
    expected_result = 0;

    if (initial_position == 0)
    {
      initial_queue = 0x00010000u;
    }
    else
    {
      for (position = initial_position; position < 8; position++)
      {
        initial_queue |= (message << (position * 4));
      }
    }

    for (position = initial_position; position < 8; position++)
    {
      expected_final |= (argument_message << (position * 4));
    }
  }

  volatile unsigned int control = initial_queue;

  int actual_result = bitqueue_write(&control, argument_message);

  unsigned int actual_final = control;

  if ((actual_result == expected_result)
    && (actual_final == expected_final))
  {
    debug_printf("%08X,%d->%08X,%d correct\n", initial_queue, argument_message, expected_final, expected_result);
  }
  else
  {
    debug_printf("%08X,%d->%08X,%d expected\n", initial_queue, argument_message, expected_final, expected_result);
    debug_printf("%08X,%d->%08X,%d actual\n"  , initial_queue, argument_message,   actual_final,   actual_result);
    for(;;);
  }
}

int main (void)
{
  debug_uart_init();

  hwrand_init ();

  unsigned int i = 0;

  for (;; i++)
  {
    bitqueue_write_test();
  }
}
