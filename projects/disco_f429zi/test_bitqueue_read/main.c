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

#include <string.h>
#include "debug_printf.h"
#include "rng.h"
#include "bitqueue.h"

static void bitqueue_read_check(unsigned int initial, int expected_result, unsigned int expected_final)
{
  volatile unsigned int control = initial;

  int actual_result = bitqueue_read(&control);

  unsigned int actual_final = control;

  if ((actual_result == expected_result)
    && (actual_final == expected_final))
  {
    debug_printf("%08X->%08X,%d correct\n", initial, expected_final, expected_result);
  }
  else
  {
    debug_printf("%08X->%08X,%d expected\n", initial, expected_final, expected_result);
    debug_printf("%08X->%08X,%d actual\n"  , initial,   actual_final,   actual_result);
    for(;;);
  }
}

static void bitqueue_read_test(void)
{
  unsigned int initial_queue = 0;
  int          expected_result;
  unsigned int expected_final;

  unsigned char messages[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

  unsigned int message;

  unsigned int position;

  for (position = 0; position < 8; position++)
  {
    int message_index = ((rng_rand32() % (20 - position)) - 4);

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

  if (position == 0)
  {
    initial_queue   = 0x00010000u;
    expected_result = -1;
    expected_final  = 0x00010000u;
  }
  else
  {
    expected_result = (initial_queue & 0xF);

    if (position == 1)
    {
      expected_final  = 0x00010000u;
    }
    else
    {
      expected_final  = 0;
    }

    for (; position < 8; position++)
    {
      initial_queue |= (message << (position * 4));
    }

    if (expected_final == 0)
    {
      expected_final = ((initial_queue >> 4) | (initial_queue & 0xF0000000u));
    }
  }

  bitqueue_read_check(initial_queue, expected_result, expected_final);
}



int main (void)
{
  debug_uart_init();

  bitqueue_read_check(0x00010000u, -1, 0x00010000u);
  bitqueue_read_check(0x00000000u,  0, 0x00010000u);
  bitqueue_read_check(0x11111111u,  1, 0x00010000u);
  bitqueue_read_check(0x22222222u,  2, 0x00010000u);
  bitqueue_read_check(0x33333333u,  3, 0x00010000u);
  bitqueue_read_check(0x44444444u,  4, 0x00010000u);
  bitqueue_read_check(0x55555555u,  5, 0x00010000u);
  bitqueue_read_check(0x66666666u,  6, 0x00010000u);
  bitqueue_read_check(0x77777777u,  7, 0x00010000u);
  bitqueue_read_check(0x88888888u,  8, 0x00010000u);
  bitqueue_read_check(0x99999999u,  9, 0x00010000u);
  bitqueue_read_check(0xAAAAAAAAu, 10, 0x00010000u);
  bitqueue_read_check(0xBBBBBBBBu, 11, 0x00010000u);
  bitqueue_read_check(0xCCCCCCCCu, 12, 0x00010000u);
  bitqueue_read_check(0xDDDDDDDDu, 13, 0x00010000u);
  bitqueue_read_check(0xEEEEEEEEu, 14, 0x00010000u);
  bitqueue_read_check(0xFFFFFFFFu, 15, 0x00010000u);

  rng_init ();

  unsigned int i = 0;

  for (;; i++)
  {
    bitqueue_read_test();
  }
}
