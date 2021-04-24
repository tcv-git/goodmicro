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

#include "debug_printf.h"
#include "gps_uart.h"
#include "gps_protocol.h"

int main(void)
{
  debug_uart_init();
  gps_uart_init();

  for (;;)
  {
    char * line = gps_uart_get_line();

    if (line)
    {
      debug_printf("%s\n", line);

      gps_uart_release_line();
    }
  }
}
